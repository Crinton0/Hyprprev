#include <unistd.h>

#include <string.h>

#include "messages.h"
#include "options_args.h"
#include "use_file.h"
#include "use_clipboard.h"


#include <stdio.h>


void documentation_option();

int process_opt_args(int argc, char** argv){

    if(argc == 1){
        write_help_message();
        write_no_args_message();
        return 0;
    }

    int option;
    char* input_argument;

    

    while((option = getopt(argc, argv, ":hct:")) != -1)
    {

        

        switch(option)
        {
            case 'h':
                write_help_message();
                return 0;
            case 't':
                write(STDOUT_FILENO, "Time", strlen("Time"));
                return 0;
            case '?':
                invalid_args_message();
                return 0;
            case ':':
                write(STDOUT_FILENO, "args", strlen("args"));
                return 0;
        }
        
    }

        
    input_argument = argv[optind];
    file_handler(input_argument);


    return 0;
}