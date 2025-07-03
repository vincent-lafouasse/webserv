#pragma once

#include <sys/socket.h>
#include <unistd.h>

class Socket {
public:
    Socket(int domain, int type, int protocol) {
        this->fd = socket(domain, type, protocol);
        // throw on 0 ?
    }

    ~Socket() {
        close(this->fd);
    }

private:
    int fd;
};
