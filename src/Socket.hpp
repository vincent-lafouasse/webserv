#pragma once

#include <sys/socket.h>
#include <unistd.h>

class Socket {
public:
    Socket() {
        /*
     *  domain (of communication)
     *      address format (eg IP version) and range (local vs internet)
     *
     *      PF_LOCAL, local ie host internal
     *      PF_INET, IPv4
     *      PF_INET6, IPv6
     *
     *  type (of socket)
     *      SOCK_STREAM,  bidirectional, connection-oriented
     *      SOCK_DGRAM,   connectionless
     *
     *  the rest of this will assume domain is IPv4
     *  ie that its address format is u32 address + u16 port
     *  and its address struct is `sockaddr_in`
    */
        const int connectionDomain = PF_INET;
        const int socketType = SOCK_STREAM;
        const int protocol = 0; // always 0 as per TLPI 56.2

        this->fd = socket(connectionDomain, socketType, protocol);
        // throw on 0 ?
    }

    ~Socket() {
        close(this->fd);
    }

private:
    int fd;
};
