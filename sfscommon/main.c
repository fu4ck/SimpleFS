//
// Created by xudong on 2021/8/28.
//


#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <init.h>


int initialize(void) {
    uint32_t i;
    int ok;
    ok = 1;
    for (i=0 ; (long int)(RunTab[i].fn)!=0 && ok ; i++) {
        if (RunTab[i].fn()<0) {
            ok=0;
        }
    }
    return ok;
}


// TODO
void mainloop() {
    LOOP_VARS;
    uint64_t prevtime = 0;
    uint64_t useclast;
    struct timeval tv;
    // poll thread
    pollentry *pollit;
    struct pollfd pdesc[MFSMAXFILES];
    uint32_t ndesc;
    int i;
    int t,r;

    t = 0;
    r = 0;
    while (t!=3) {
        ndesc=1;
        pdesc[0].fd = signalpipe[0];
        pdesc[0].events = POLLIN;
        pdesc[0].revents = 0;
        for (pollit = pollhead ; pollit != NULL ; pollit = pollit->next) {
            LOOP_START;
            pollit->desc(pdesc,&ndesc);
            LOOP_END(pollit->dname);
        }
        i = poll(pdesc,ndesc,10);
        gettimeofday(&tv,NULL);

        if (i<0) {
            if (!ERRNO_ERROR) {
                syslog(LOG_WARNING,"poll returned EAGAIN");
                portable_usleep(10000);
                continue;
            }
            if (errno!=EINTR) {
                syslog(LOG_WARNING,"poll error: %s", strerr(errno));
                break;
            }
        } else {
            if ((pdesc[0].revents)&POLLIN) {
                uint8_t sigid;
                if (read(signalpipe[0],&sigid,1)==1) {
                    if (sigid=='\001' && t==0) {
                        syslog(LOG_NOTICE,"terminate signal received");
                        t = 1;
                    } else if (sigid=='\002') {
                        syslog(LOG_NOTICE,"reloading config files");
                        r = 1;
                    } else if (sigid=='\003') {
                        syslog(LOG_NOTICE,"child finished");
                        r = 2;
                    } else if (sigid=='\004') {
                        syslog(LOG_NOTICE,"log extra info");
                        r = 3;
                    } else if (sigid=='\005') {
                        syslog(LOG_NOTICE,"unexpected alarm/prof signal received - ignoring");
                    } else if (sigid=='\006') {
                        syslog(LOG_NOTICE,"internal terminate request");
                        t = 1;
                    }
                }
            }

            // poll thread loop
            for (pollit = pollhead ; pollit != NULL ; pollit = pollit->next) {
                LOOP_START;
                pollit->serve(pdesc);
                LOOP_END(pollit->sname);
            }
        }

    }
}


int main(int argc,char **argv) {

    int rundaemon;

    // cfg read
    cfgfile = strdup("/etc/sfs/sfs.cfg");
    if ((fd = open(cfgfile,O_RDONLY))<0 && errno==ENOENT) {
        ocfgfile=strdup("/etc/sfs/sfs.cfg");
        if ((fd = open(ocfgfile,O_RDONLY))>=0) {
            free(cfgfile);
            cfgfile = ocfgfile;
            movewarning = 1;
        } else {
            free(ocfgfile);
        }
    }
    if (fd>=0) {
        close(fd);
    }
    //TODO parse args


    //init server
    rundaemon = 1;

    if(initialize()) {
        if (rundaemon) {
           //     close_msg_channel();
        }
        mainloop();
    }

    syslog(LOG_NOTICE,"exititng ...");
}

