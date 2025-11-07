#include <unistd.h>
#include <string.h>
#include "messages.h"


void write_help_message()
{
    char* help_message = "Welcome to Hyprpaper Preview Utility!\n\nUsage: hyprprev [args] \"path/to/image\"\n\nArguments:\n-h      | Show this message\n-t      | Specify a duration\n-q      | Quiet mode (no output or notification)\n";
    write(STDOUT_FILENO, help_message, strlen(help_message));
}

void write_no_args_message()
{
    char* no_args_message = "\nNo arguments provided. Use -h to show the help message. Quitting...\n";
    write(STDOUT_FILENO, no_args_message, strlen(no_args_message));
}

void invalid_args_message()
{
    char* invalid_args_message = "Arguments provided are invalid. Quitting...\n";
    write(STDOUT_FILENO, invalid_args_message, strlen(invalid_args_message));
}

void required_args()
{
    char* required_message = "This option requires an argument! Check the help page using -h.";

}


