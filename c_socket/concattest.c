#include<string.h>
#include<stdio.h>
#include <stdlib.h>
char* concat_string(char* username, char* message, int username_size, int message_size) {
    char* result = malloc(sizeof(char)*(username_size+message_size+1));
    strcpy(result,username);
    strcat(result,": ");
    strcat(result,message);
    strcat(result, "\0");
    return result;
}

int get_string_length(char* name) {
    int counter = 0 ;
    for(int i =0 ; name[i] != '\n' && name[i] != '\0'; ++i) {
        ++counter;
    }
    return counter;
}

int main(int argc, char* argv[]) {
    char* message = "siema to ja karol";
    char* username = "karol";
    char* result = concat_string(username, message,5, 17);
    printf("%s ",result);
    printf("%d ", get_string_length((result)));


    return 0;
}
