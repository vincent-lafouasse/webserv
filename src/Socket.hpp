#pragma once

#include <sys/socket.h>
#include <unistd.h>

class Socket {
public:
    /*
     * domain (of communication)
     *      address format (eg IP version) and range (local vs internet)
     *
     *      PF_LOCAL, local ie host internal
     *      PF_INET, IPv4
     *      PF_INET6, IPv6
    */
    Socket(int domain, int type, int protocol) {
        this->fd = socket(domain, type, protocol);
        // throw on 0 ?
    }

    ~Socket() {
        close(this->fd);
    }

private:
    int fd;

    static const int defaultDomain = PF_INET;
};
