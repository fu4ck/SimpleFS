//
// Created by xudong on 2021/8/28.
//

# include <sys/socket.h>
# include <sys/un.h>

int tcpsocket(void) {
    return socket(AF_INET,SOCK_STREAM,0);
}


int matocsserv_init(void) {
    lsock = tcpsocket();
    if (lsock<0) {
        return -1;
    }

    return 0;
}


int matoclserv_init(void){
    return 0;
}


int metadata_init(void){
    return 0;
}



