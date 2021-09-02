//
// Created by xudong on 2021/8/28.
//
#include "matochunkserver.h"


typedef int (*runfn)(void);

struct {
    runfn fn;
    char *name;
} RunTab[] = {
        //TODO
        {metadata_init, "metadata init thread"},
        {matocsserv_init, "communication with chunkserver"},
        {matoclserv_init, "communication with client fuse"}
};
