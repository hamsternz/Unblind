#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>

#include "unblind.h"

int main(int argc, char *argv[]) {
    print_to_log("Program start");

    FILE *f;
    char *file_name;
    WINDOW *win = (WINDOW *) malloc(sizeof(WINDOW *));

    unblind_info_t *info = (unblind_info_t *) malloc(INFO_SIZE);
    setup_unblind_info(info);

    print_to_log("info created");

    WINDOW *main_win = initscr();
    win = newwin(MAX_LINES, MAX_CHARS_PER_LINE, 0, 0);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, FALSE);
    scrollok(win, FALSE);
    raw();

    if(argc == 2) {
        file_name = argv[1];
        f = fopen(file_name, "a+"); // opens for reading and appending
        if(f == NULL) {
            fprintf(stderr, "Error: File not found!");
            endwin();
            exit(1);
        }
    } else {
        endwin();
        fprintf(stderr, "Error: ./unblind <file name>\n");
        exit(1);
    }

    read_contents_from_file(f, win, info);
    print_to_log("right before draw\n");
    draw(win, info);
    print_to_log("Starting main loop\n");
    for(;;) {
        print_to_log("Main loop start\n");
        manage_input(file_name, win, info);
    }
    fclose(f);
    endwin();
    return 0;
}
