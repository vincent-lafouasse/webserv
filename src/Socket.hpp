#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>

class SocketCreationException : public std::runtime_error {
   public:
    SocketCreationException(int domain, int type, int protocol, int errno_)
        : std::runtime_error(
              SocketCreationException::format(domain, type, protocol, errno_)) {
    }

   private:
    static std::string format(int domain, int type, int protocol, int errno_) {
        std::stringstream ss;

        ss << '\n';
        ss << "# Failed to open socket with:\n";
        ss << "Connection domain:\n---- " << domain << '\n';
        ss << "Socket Type:\n---- " << type << '\n';
        ss << "Protocol:\n---- " << protocol << '\n';
        ss << "Errno:\n---- " << errno_ << '\n';

        return ss.str();
    }
};

class Socket {
   public:
    // creates a passive socket, ie a server
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
        const int protocol = 0;  // always 0 as per TLPI 56.2

        this->fd = socket(connectionDomain, socketType, protocol);
        if (this->fd == -1) {
            const int errno_ = errno;
            throw SocketCreationException(connectionDomain, socketType,
                                          protocol, errno_);
        }

        // contains IP address as a u32
        in_addr internetAddress = {
            /* .s_addr = */ INADDR_ANY,  // bind to all interfaces
            // alternatively, `inet_addr("127.0.0.1")` or something
            // inet_addr is fallible
        };

        const int port = 8080;
        sockaddr_in socketAddress = {};
        socketAddress.sin_family = connectionDomain;
        socketAddress.sin_port = htons(port);
        socketAddress.sin_addr = internetAddress;
        const socklen_t addressLen = sizeof(socketAddress);

        if (bind(this->fd, reinterpret_cast<sockaddr*>(&socketAddress),
                 addressLen) < 0) {
            std::perror("bind error");
            throw std::runtime_error("bind error");
        }

        const int backlog = 5;  // number of pending connections before the
                                // server starts refusing
        // pending connection ==
        // client calls `connect` before the server calls `accept`

        // marks the socket as a passive socket, ie a server
        if (listen(this->fd, backlog) < 0) {
            std::perror("listen error");
            throw std::runtime_error("listen error");
        }
    }

    // main usage ?
    std::string getline();

    ssize_t read(void* buffer, std::size_t n) {
        return ::read(this->fd, buffer, n);
    }

    ssize_t write(void* buffer, std::size_t n) {
        return ::write(this->fd, buffer, n);
    }

    ssize_t send(void* buffer, std::size_t n, int flags) {
        return ::send(this->fd, buffer, n, flags);
    }

    ssize_t recv(void* buffer, std::size_t n, int flags) {
        return ::recv(this->fd, buffer, n, flags);
    }

    ~Socket() { close(this->fd); }

   private:
    int fd;
};
