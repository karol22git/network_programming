#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>

#include <arpa/inet.h>

#define PORT "5555"


int main(int argc, char* argv[]) {
    int sockfd;
    char buf[100];
    struct addrinfo hints, *serverinfo;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("127.0.0.1", PORT, &hints, &serverinfo);

    sockfd = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);

    connect(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen);

    struct pollfd pfds[1];

    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    int num_events;
    int n;
    size_t message_size = 32;
    char* message = malloc(message_size);
    printf("Enter a message: ");
    getline(&message,&message_size,stdin);
    for(int i  = 0 ; i < 10 ; ++i) {
    printf("Enter a message: ");
    getline(&message,&message_size,stdin);
    send(sockfd,message,message_size,0);
    }
    
    close(sockfd);
    return 0;
}