#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define PORT "5555"
#define MAX_QUE 15
#define MAX_SIZE 64

int main(int argc, char* argv[]) {
    int sockfd, new_fd, listener;
    int fd_count, fd_size;
    struct addrinfo hints, *serverinfo;
    socklen_t addrlen;
    struct sockaddr_storage remoteaddr;

    struct sockaddr_storage their_addr;
    socklen_t sin_size = sizeof their_addr;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL,PORT,&hints,&serverinfo);
    listener = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    bind(listener, serverinfo->ai_addr, serverinfo->ai_addrlen);
    listen(listener,MAX_QUE);


    fd_count = 0 ;
    fd_size = 2 ;
    struct pollfd *pfds= malloc(sizeof(*pfds)*fd_size);
    size_t bufsize = MAX_SIZE;
    char* buf  = malloc(bufsize);


    pfds[0].fd = listener;
    pfds[0].events = POLLIN;
    ++fd_count;
    while(1) {
        int poll_count = poll(pfds,fd_count,500);
        if(poll_count == - 1) {
            exit(1);
        }
        for(int i = 0 ; i < fd_count ; ++i) {
            if(pfds[i].revents == POLLIN) {
                if(pfds[i].fd == listener) {
                    addrlen = sizeof(remoteaddr);
                    new_fd = accept(listener, (struct sockaddr*)&remoteaddr, &addrlen);
                    if(new_fd == -1) {
                        perror("error");
                    }
                    else {
                        if(fd_count == fd_size) {
                            fd_size = 2*fd_size;
                            pfds = realloc(pfds,sizeof(pfds)*fd_size);
                        }
                        pfds[fd_count].fd = new_fd;
                        pfds[fd_count].events = POLLIN;
                        ++fd_count;
                        printf("LOG: adding descriptor %d to list. \n",new_fd);
                    }
                }
                else {
                    int bytes = recv(pfds[i].fd,buf,bufsize,0);
                    printf("LOG: i received message from %d \n",pfds[i].fd);
                    if(bytes <= 0) {
                        printf("LOG: connection on socked %d closed. \n",pfds[i].fd);
                        close(pfds[i].fd);
                        pfds[i]  = pfds[fd_count - 1];
                        fd_count = fd_count - 1;
                    }
                    else {
                        for(int j = 0 ; j < fd_count ; ++j) {
                            if(j != i && pfds[j].fd != listener) {
                                send(pfds[j].fd, buf, bufsize,0);
                            }
                        }
                    }
                
                }
            }
        }
        fflush(stdout);
    }
    return 0;
}