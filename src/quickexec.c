#include "quickexec.h"
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
int quickexec(const char* command)
{

    char** cmd_vector_buf = malloc(10* sizeof(char*)); // length = strlen(command), amount = strlen(command/2);
    *cmd_vector_buf = "test\0";
    printf("Hi!\n");
    printf("================= cmd vector size: %d\n", sizeof(*cmd_vector_buf));
    printf("================ cmd vector contents: %p\n", cmd_vector_buf); // first char pointer (pointer to a string)
    printf("================ *cmd vector pointer contents: %p\n", *cmd_vector_buf); // pointer to the first char of the string
    printf("================ *cmd vector string contents: %s\n", *cmd_vector_buf); // the full string itself
    printf("================ **cmd vector char contents: %c\n", **cmd_vector_buf); // the first char of the string
    printf("Hi!\n");
    fflush(stdin);
    free(cmd_vector_buf);
    write(STDOUT_FILENO, command, strlen(command));

    pid_t pid = fork();
        if (pid == 0) {
            //execvp("hyprpaper",["hyprpaper", "-c", config_path, (char *)NULL]);
            _exit(1);
        } else if (pid > 0){
            // placeholder
        }
}

