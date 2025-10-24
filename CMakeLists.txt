cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_FILES 
    main.c # main C file
    src/messages.c
    src/options_args.c
    src/use_clipboard.c 
    src/use_file.c
    src/quickexec.c
    
)


add_executable(hyprprev ${SOURCE_FILES})

target_include_directories(hyprprev PUBLIC include)