#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <poll.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT "5555"
#define HOST "127.0.0.1"
#define MAX_SIZE 64
int height = 1;

void *service_incoming_messages(void* var) {
    struct pollfd* pfds = (struct pollfd*) var;
    size_t buffer_size = MAX_SIZE;
    char* buffer = malloc(buffer_size);
    int incoming_calls;
    int bytes_received;

    for(;;) {
        incoming_calls = poll(pfds,1,250);
        if(incoming_calls> 0) {
            bytes_received = recv(pfds[0].fd,buffer,buffer_size,0);
            if(bytes_received > 0) {
                mvprintw(height,0,"%s ",buffer);
                ++height;
                move(height,0);
                refresh();
                //read messeges
            }
            else {
                mvprintw(height-1,0,"Server is down!");
                endwin();
                exit(1);
            }
        }

    }
}

int get_string_length(char* name) {
    int counter = 0 ;
    for(int i =0 ; name[i] != '\n' && name[i] != '\0'; ++i) {
        ++counter;
    }
    return counter;
}

char* concat_string(char* username, char* message, int username_size, int message_size) {
    char* result = malloc(sizeof(char)*(username_size+message_size+1));
    strcpy(result,username);
    strcat(result,": ");
    strcat(result,message);
    strcat(result, "\0");
    return result;
}


int main(int argc, char* argv[]) {
    int sock_fd;
    struct addrinfo hints, *serverinfo;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("127.0.0.1", PORT, &hints, &serverinfo);

    sock_fd = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    connect(sock_fd, serverinfo->ai_addr, serverinfo->ai_addrlen);
    
    struct pollfd pfds[1];
    pfds[0].fd = sock_fd;
    pfds[0].events = POLLIN;

    //getting username
    size_t username_size = MAX_SIZE;
    char* username = malloc(username_size);
    printf("Enter username: ");
    getline(&username,&username_size,stdin);
    int username_length = get_string_length(username);
    username[strcspn(username, "\n")] = 0;


    size_t size = MAX_SIZE;
    char* line = malloc(size);
    //int message_length = ; 
    int msg[MAX_SIZE];
    int index = 0;
    int tmp = 0;

    pthread_t thread_id ;
    pthread_create(&thread_id,NULL,service_incoming_messages,&pfds);

    initscr();
    refresh();
    for(;;) {
        tmp = getchar();
        
        //send message if user pressed ENTER
        if(tmp == 13){ 
            char* result = concat_string(username, line, username_length,index);
            send(sock_fd,result,size,0);
            mvprintw(height,0,"%s", result);
            refresh();
            for(int i = 0 ; i < index; ++i) {
                line[i] = '\0'; 
            }
            index = -1;
            ++height;
            move(height,0);
            refresh();
        }
        //else just handle typing
        else {
            //if user typed BACKSPACE
            if(tmp == 127 || tmp == 8) {
                msg[index-1] = 0;
                index = index -2;
                for(int i = 0 ; i <= index; ++i) {
                    line[i] = msg[i]; 
                }
                line[index+1] = '\0';
                clrtoeol();
            }
        //copying from integer array to char array
            else {
                msg[index] = tmp;
                for(int i = 0 ; i <= index; ++i) {
                    line[i] = msg[i]; 
                }
            }
        }
        mvprintw(height,0,"%s",line);
        refresh();
        ++index;
    }
    endwin();
    pthread_join(thread_id,NULL);
    return 0;
}