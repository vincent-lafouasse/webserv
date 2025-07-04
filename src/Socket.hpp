#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
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

        in_addr internetAddress = {
            .s_addr = INADDR_ANY,
        };

        const int port = 8080;
        sockaddr_in socketAddress = {
            .sin_family = connectionDomain,
            .sin_port = htons(port),
            .sin_addr = internetAddress,
            .sin_zero = {0},
        };
        socklen_t addressLen = sizeof(socketAddress);

        if (bind(this->fd, reinterpret_cast<sockaddr*>(&socketAddress), addressLen) < 0) {
            // bind error
        }
    }

    // main usage ?
    std::string getline();

    ~Socket() { close(this->fd); }

   private:
    int fd;
};
