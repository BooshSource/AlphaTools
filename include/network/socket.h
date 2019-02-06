#pragma once

#include <sys/socket.h>
#ifdef __CYGWIN__
#include <cygwin/in.h>
#endif
#include <arpa/inet.h>
#include <string>
#include <stdexcept>
#include "types.h"

namespace network {

class socket_error : public std::runtime_error {
public:
    explicit socket_error(const std::string &msg);
};

class bind_error : public socket_error {
public:
    explicit bind_error(int errnum, const std::string &msg);
};

struct SockOpt {
    
    std::string name;
    int sock_name;
    socklen_t length;
    
    SockOpt(const std::string &name, int sock_name, socklen_t length) {
        this->name = name;
        this->sock_name = sock_name;
        this->length = length;
    }
    
    static const SockOpt DEBUG, BROADCAST, REUSEADDR, KEEPALIVE, LINGER, OOBINLINE, SNDBUF, RCVBUF, DONTROUTE,
    RCVLOWAT, RCVTIMEO, SNDLOWAT, SNDTIMEO;
};

struct IPAddr {

    std::string text;
    in_addr addr;
    
    explicit IPAddr(const std::string &text) : addr() {
        this->text = text;
        // TODO: implement this here, as it will be more portable then
        inet_pton(AF_INET, text.c_str(), &addr);
    }

};

/**
 * A low level socket. In most cases, shouldn't use this
 */
class Socket {
    
    explicit Socket(int sockfd, ushort domain = AF_INET, uint type = SOCK_STREAM);
    
    ushort domain;
    int sockfd;
    uint type;
    
    sockaddr *addr;

public:
    
    explicit Socket(ushort domain = AF_INET, uint type = SOCK_STREAM);
    
    void setopt(SockOpt option, const void *val);
    void* getopt(SockOpt option, void *val);
    
    void bind(ushort port);
    
    void connect(const std::string &ip, ushort port);
    void connect(IPAddr ip, ushort port);
    
    void listen(uint backlog);
    Socket accept();
    const char* recv(uint size = 1);
    void send(const char *bytes, uint length);
    
    void close();
    void shutdown(int how);
    
};

}
