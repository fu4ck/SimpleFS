//
// Created by xudong on 2021/9/2.
//
#include "chunk.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct chunk {
    char *filename;
    uint64_t chunkid;
    uint64_t blocks;
    int fd;
    uint8_t* block;
    uint16_t blockno;
    struct chunk* testnext, **testprev;
    struct chunk* next;
} chunk;

