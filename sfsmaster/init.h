//
// Created by xudong on 2021/8/28.
//

typedef int (*runfn)(void);

struct {
    runfn fn;
    char *name;
} RunTab[] = {
        //TODO
        {matochunkserver_init, "communication with chunkserver"},
};
