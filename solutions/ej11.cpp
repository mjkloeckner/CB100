/* Termios solo funciona en sistemas basados en UNIX */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <termios.h>

using namespace std;

const unsigned int menu_items = 4;
static struct termios default_attributes;

char cursor[menu_items] = {0};
unsigned int cursor_pos;
bool run_program;

string menu[menu_items] = {
	"Español",
	"English",
	"Deutsch",
	"Português" 
};

void sig_handler(int signo) {
    signal(signo, SIG_IGN);
    if ((signo == SIGINT) || (signo == SIGQUIT)) {
        run_program = false;
        exit(0);
    }
}

void set_input_mode (void) {
    struct termios tattr;

    if (!isatty(STDIN_FILENO)) {
        cerr <<  "Not a terminal" << endl;
        exit (EXIT_FAILURE);
    }

    tcgetattr(STDIN_FILENO, &default_attributes);

    /* hide cursor */
    printf("\033[?25l");

    /* Set the terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void reset_input_mode (void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &default_attributes);

    /* show cursor */
    printf("\033[?25h");
}

void print_menu(void) {
    for(size_t i = 0; i < menu_items; ++i) {
        cursor[cursor_pos] = ((i == cursor_pos) ? '>' : ' ');
        cout << cursor[cursor_pos] << menu[i] << (i == menu_items ? "" : "\n")
            << flush;
    }
}

void clear_menu(void) {
    cout << "\033[" << menu_items << "A";
}

void refresh_menu(void) {
    clear_menu();
    print_menu();
}

void move_cursor_up() {
    if(cursor_pos >= 1)
        cursor_pos--;
    else cursor_pos = (menu_items - 1);
}

void move_cursor_down() {
    if(cursor_pos < (menu_items - 1))
        cursor_pos++;
    else cursor_pos = 0;
}

int main (void) {
    const clock_t start = clock();
    char cmd;
    unsigned int selected_item;
    run_program = true;
    cursor_pos = 0;
    selected_item = menu_items;

    set_input_mode();
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGTSTP, SIG_IGN);
    atexit(reset_input_mode);

    print_menu();
    while(run_program) {
        clock_t now = clock();
        clock_t delta = (now - start);
        cin.get(cmd);
        switch(cmd) {
            case 'w':
            case 'k':
                move_cursor_up();
                refresh_menu();
                break;
            case 's':
            case 'j':
                move_cursor_down();
                refresh_menu();
                break;
            case 'q':
                run_program = false;
                break;
            case 10: // Enter
            case ' ':
                selected_item = cursor_pos;
                run_program = false;
                break;
            case 27: { // Escape codes i.e. arrow keys
                cin.get(cmd); // skip '['
                cin.get(cmd);
                switch (cmd) {
                    case 'A':
                        move_cursor_up();
                        refresh_menu();
                        break;
                    case 'B':
                        move_cursor_down();
                        refresh_menu();
                        break;
                    case 'c':
                        run_program = false;
                        break;
                    default:
                        break;
                }
            }
            default:
                continue;
        }
    }

    clear_menu();
    if(selected_item != menu_items)
        cout << "You selected: `" << menu[selected_item] << "`" << endl;

    exit(EXIT_SUCCESS);
}
