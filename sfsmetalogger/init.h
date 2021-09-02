//
// Created by xudong on 2021/8/28.
//

#include "metalogger.h"

typedef int (*runfn)(void);

struct {
    runfn fn;
    char *name;
} RunTab[] = {
        //TODO
        {metalogger_init, "metalogger init function"},
};