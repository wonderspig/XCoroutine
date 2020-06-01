/*
 * Copyright (c) 2020, xie wenwu <870585356@qq.com>
 * 
 * All rights reserved.
 */

#include "syscall.h"
#include "scheduler.h"

typedef ssize_t (*SysRead)(int fd, void *buf, size_t count);
typedef ssize_t (*SysWrite)(int fd, const void *buf, size_t count);
typedef int (*SysAccept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

SysRead sysRead	= (SysRead)dlsym(RTLD_NEXT, "read");
SysWrite sysWrite = (SysWrite)dlsym(RTLD_NEXT, "write");
SysAccept sysAccept= (SysAccept)dlsym(RTLD_NEXT, "accept");

ssize_t read(int fd, void *buf, size_t count){
    int ret = sysRead(fd, buf, count);
    if(ret < 0){
        if(errno == EAGAIN){
            waitOnRead(fd);
        }
    }
    return ret;
}

ssize_t write(int fd, const void *buf, size_t count){
    int ret = sysWrite(fd, buf, count);
    if(ret < 0){
        if(errno == EAGAIN){
            waitOnWrite(fd);
        }
    }
    return ret;
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int ret = sysAccept(sockfd, addr, addrlen);
    if(ret < 0){
        if(errno == EAGAIN){
            waitOnRead(sockfd);
        }
    }
    return ret;
}
