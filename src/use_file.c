#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <time.h>

#include "quickexec.h"


typedef struct {
    int is_active;
    
    char* old_config_path;
} hyprpaper_info;

char* get_extension(char* last_dot_pointer){
    char* result = malloc(5);
    result[0] = '.';


    strcat(result, last_dot_pointer + 1);
    

    return result;

}

int check_valid_extension(char* file_path){
    int is_valid = 0;
    char* extension_list[] = {".png", ".jpg", ".jpeg", ".jxl", ".webp"};

    char* last_dot_pointer = strrchr(file_path, '.');

    if(*last_dot_pointer == NULL)
        return is_valid;

    char* extension = get_extension(last_dot_pointer);

    for(int i = 0; i < 5; i++){
        if(strcmp(extension, extension_list[i]) == 0)
            is_valid = 1;
    }

    free(extension);
    return is_valid;

}


int create_preview_config(char* file_path, int file_length, char* new_config_path, int ipc_true)
{
    int config_fd = open(new_config_path, O_WRONLY | O_CREAT, 0644);
    
    char* ipc_line = "ipc = false\n\n\n";
    if(ipc_true == 1){
        ipc_line = "ipc = true\n\n\n";
    }

    ssize_t preload_line_size = 12 + file_length;
    char* preload_line = malloc(preload_line_size);


    snprintf(preload_line, preload_line_size , "preload = %s\n\n", file_path);

    ssize_t wallpaper_line_length = 21 + file_length; 
    // will need to add accountint for diff monitor sizes
    char* wallpaper_line = malloc(21+file_length);

    snprintf(wallpaper_line, wallpaper_line_length, "wallpaper = %s,%s\n\n", "eDP-1", file_path);

    


    write(config_fd, ipc_line, strlen(ipc_line));
    write(config_fd, preload_line, strlen(preload_line));
    write(config_fd, wallpaper_line, strlen(wallpaper_line));

    free(preload_line);
    free(wallpaper_line);
    close(config_fd);


    return 0;
}

int run_hyprpaper(char* config_path, int duration_s, int is_quiet)
{
    char cmd_buf[256] = {0};
    snprintf(cmd_buf, sizeof(cmd_buf), "hyprpaper -c %s", config_path);

    system("pkill hyprpaper");



    
    quickexec(cmd_buf);
    pid_t pid = fork();
    if (pid == 0) {
        int devnull = open("/dev/null", O_WRONLY);
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);
        execlp("hyprpaper", "hyprpaper", "-c", config_path, (char *)NULL);
        _exit(1);
    } else if (pid > 0 && duration_s == -1){
        // placeholder
    }

    char start_notif_cmd[256] = {0};
    snprintf(start_notif_cmd, sizeof(start_notif_cmd), "notify-send \"Hyprprev running!\" \"Hyprprev launched for %d seconds\"", duration_s);


    system(start_notif_cmd);

    sleep(duration_s);

    char* exit_notif_cmd = "notify-send \"Hyprprev over!\" \"Preview has been successfully terminated.\"\n";
    system(exit_notif_cmd);
    system("pkill hyprpaper");

    return 0;
}


int file_handler(char* file_path){
    char* no_file_exists = "File Error: No such file exists.\n";
    char* incorrect_file_extension = "File Error: Incorrect Extension (Allowed Extensions are: .png .jpg .jpeg .jxl .webp).\n";
    
    char* default_config_path = "/tmp/Hyprpreview_temp_config.conf";

    int file_fd = open(file_path, O_RDONLY);

    if(file_fd == -1){
        write(STDOUT_FILENO, no_file_exists, strlen(no_file_exists));
        return -1;
    }
    if(check_valid_extension(file_path) != 1){
        write(STDOUT_FILENO, incorrect_file_extension, strlen(incorrect_file_extension));
        return -1;
    }


    create_preview_config(file_path, strlen(file_path), default_config_path, 1);
    run_hyprpaper(default_config_path, 5, 1);
    
    return 0;

    
}




