#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>

#define myclear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int size = 5;
int index = 0;
int height = 1;
size_t s = 32;
int msg[32];
char* line;
void *print_ten_messeges(void* var) {
    char** msg = (char**)var;
    sleep(5);

    for(int i = 0 ; i < size ; ++i) {
        mvprintw(height-1,0,"%s ",msg[i]);
        refresh();
        ++height;
        mvprintw(height,0,"%s",line);
        refresh();
        sleep(1);
        
    }
}

void* scan_messeges(void* var) {
   // int msg[32];
    for(;;) {
    //mvprintw(0,0,"%s \n", line);
    //printf("hello \n");
    msg[index] = getch();
    if(msg[index] == '\n') {
        //break;
        for(int i = 0 ; i <= index; ++i) {
        line[i] = '\0'; 
    }
        index = 0;
        ++height;
    }
    for(int i = 0 ; i <= index; ++i) {
        line[i] = msg[i]; 
    }
    if(index!=0) {
        mvprintw(height,0,"%s",line);
        refresh();
    }
    ++index;
    // end curses:
    }

}

int main(int argc, char* argv[]) {
    char* message[] = {"siema","co tam", "elo","pozdrawiam","zaraz zaraz zaraz zaraz"};

int k;
    char* line2 = "hello";
    //size_t s = 32;
    line = malloc(s);
    // init curses:
    initscr();
    //int msg[32];
   // int index = 0;
   int c;
    for(;;) {
        c = getchar();
        mvprintw(height+1,0,"%d ",c); 
         refresh();
    }

    // in curses, you have to use curses functions for all terminal I/O
   // mvprintw(height-1,0, "%s \n",line2);
    ++height;
   // pthread_t thread_id ;
   // pthread_create(&thread_id,NULL,print_ten_messeges,&message);
    //pthread_t thread_id_two ;
   // pthread_create(&thread_id_two,NULL,scan_messeges,NULL);
   /* for(;;) {
    //mvprintw(0,0,"%s \n", line);
    //printf("hello \n");
    msg[index] = getch();
    if(msg[index] == '\n') {
        //break;
        for(int i = 0 ; i <= index; ++i) {
        line[i] = '\0'; 
    }
        index = 0;
        ++height;
    }
    for(int i = 0 ; i <= index; ++i) {
        line[i] = msg[i]; 
    }
    mvprintw(height,0,"%s",line);
    ++index;
    // end curses:
    }*/
    //printf("You entered %c\n", k);}
    endwin();
    //printf("I read: ");
   // for(int i = 0 ; i < index ; ++i) {
    //    printf("%c", msg[i]);
    //}
    //printf("\n");
   //pthread_join(thread_id,NULL);
   //pthread_join(thread_id_two,NULL);
    return 0;
}