#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <netdb.h>

#define PORT "8080"
#define BUFFER 4096

void *get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char const *argv[])
{
    int rv;
    int optval = 1;
    socklen_t addr_size;
    char s[INET6_ADDRSTRLEN];
    int sockfd, client_sockfd;
    struct sockaddr_storage client_addr;
    struct addrinfo hints{}, *servinfo, *p;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    rv = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if(rv == -1)
    {
        std::cerr << "getaadrinfo error: " << gai_strerror(rv) << std::endl;
        return -1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            std::cerr << "Error: Socket Creation Failed " << std::endl;
            continue;
        }

        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        {
            std::cerr << "Error: Set Socket Option" << std::endl;
            exit(1);
        }

        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            std::cerr << "Error: Failed to Bind" << std::endl;
            continue;
        }
        
        break;
    }

    freeaddrinfo(servinfo);

    if(p == NULL)
    {
        std::cerr << "Error: Server failed to bind" << std::endl;
        exit(1);
    }

    if(listen(sockfd, 20) == -1)
    {
        std::cerr << "Error: Listen" << std::endl;
        exit(1);
    }       

    std::cout << "Wating for connection...." << std::endl;
    
    while(1)
    {
        addr_size = sizeof client_addr;
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);

        if(client_sockfd == -1)
        {
            std::cerr << "Error: Accept" << std::endl;
            continue;
        }

        inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), s, sizeof s);

        std::cout << "Got connection from " << s << std::endl; 

        
    }

    return 0;
}