#include "quickexec.h"
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
int quickexec(const char* command)
{

    char** cmd_vector_buf = malloc(10* sizeof(char*)); // length = strlen(command), amount = strlen(command/2);
    for(int i = 0; i < 10; i++){
        cmd_vector_buf[i] = malloc(256* sizeof(char));
        strcpy(cmd_vector_buf[i], "Test??? Idk");
    }
    
    printf("================= cmd vector size: %d\n", sizeof(*cmd_vector_buf));
    printf("================ cmd vector contents: %p\n", cmd_vector_buf); // first char pointer (pointer to a string)
    printf("================ *cmd vector pointer contents: %p\n", *cmd_vector_buf); // pointer to the first char of the string
    printf("================ *cmd vector string contents: %s\n", *cmd_vector_buf); // the full string itself
    printf("================ **cmd vector char contents: %c\n", **cmd_vector_buf); // the first char of the string

    
    printf("\nCommand: %s\n\n", command);

    char word_buf[256] = "";
    int i = 0;
    int arg_count = 0;
    for(i = 0; i < strlen(command)+1; i++){
        if(command[i] != ' ' && command[i] != '\0'){
            strncat(word_buf, command + i, 1);
            printf("Saving character: %c\n", *(command+i));
        } else if (command[i] == ' ' || command[i] == '\0') {

            printf("Space Detected. Saving word to the vector.\n");
            //word_buf[strlen(word_buf)] = '\0';
            //printf("initialized word_buf[i] as a null terminator \\0\n");
            printf("Current word_buf: %s. Length is: %d\n", word_buf, strlen(word_buf));
            printf("Current cmd_vector_buf[%d]: %s\n", arg_count, cmd_vector_buf[arg_count]);
            strncpy(cmd_vector_buf[arg_count], word_buf, strlen(word_buf));
            printf("Copied word_buf to the cmd_vector_buf[%d].\n", arg_count);
            cmd_vector_buf[arg_count][strlen(word_buf)] = '\0';
            printf("Initialized cmd_vector_buf[%d][%d] as a null terminator\n", arg_count, strlen(word_buf));
            word_buf[0] = '\0';
            printf("Reset word_buf as a \0");
            arg_count++;
        }
    }
    //word_buf[i+1] = "\n";
    printf("\nWord buffer: %s\n", word_buf);

    for(int i = 0; i < 10; i++){
        printf("Word %d: %s\n", i, cmd_vector_buf[i]);
        free(cmd_vector_buf[i]);
    }
    free(cmd_vector_buf);

    /*pid_t pid = fork();
        if (pid == 0) {
            //execvp("hyprpaper",["hyprpaper", "-c", config_path, (char *)NULL]);
            _exit(1);
        } else if (pid > 0){
            // placeholder
        }*/
}

