/*
 * @Author       : xianduana
 * @Date         : 2024-02
 */
#ifndef EPOLLER_H
#define EPOLLER_H

#include <sys/epoll.h> //epoll_ctl()
#include <fcntl.h>  // fcntl()
#include <unistd.h> // close()
#include <assert.h> // close()
#include <vector>
#include <errno.h>

class Epoller {
public:
    explicit Epoller(int maxEvent = 1024);

    ~Epoller();

    //使用epoll_ctl取添加add，修改mod，删除del
    bool AddFd(int fd, uint32_t events);

    bool ModFd(int fd, uint32_t events);

    bool DelFd(int fd);

    int Wait(int timeoutMs = -1);

    int GetEventFd(size_t i) const;

    uint32_t GetEvents(size_t i) const;
        
private:
    int epollFd_;//epoll_create()创建一个epoll对象，返回值为epollFd_

    std::vector<struct epoll_event> events_;//检测到的事件集合 
};

#endif //EPOLLER_H