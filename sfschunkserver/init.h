//
// Created by xudong on 2021/8/28.
//
#include "chunkserver.h"

typedef int (*runfn) (void);

struct {
    runfn fn;
    char *name;
} RunTab[] = {
        //TODO
        {chunkserver_init, "chunkserver init"},
};
