#include <iostream>
#include <csignal>
#include <termios.h>

bool run_program, refresh_cursor;
static struct termios default_attributes;
static unsigned int tui_total_height;
static int cursor_col, cursor_row, cursor_row_pre;
char game_board[3][3]; // Por enunciado: matriz de punteros a char(?)

void tui_set_input_mode (void) {
    struct termios tattr;

    if (!isatty(STDIN_FILENO)) {
        std::cerr <<  "Not a terminal" << std::endl;
        exit (EXIT_FAILURE);
    }

    tcgetattr(STDIN_FILENO, &default_attributes);
    // std::cout << "\033[?25l"; // hide cursor

    /* Set the terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void tui_reset_input_mode (void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &default_attributes);
    // std::cout << "\033[?25h"; // show cursor
}

void game_sig_handler(int signo) {
    signal(signo, SIG_IGN);
    if ((signo == SIGINT) || (signo == SIGQUIT)) {
        run_program = false;
        exit(0);
    }
}

void game_clear_board(void) {
    std::cout << "\033[" << (cursor_row_pre*2)+1 << "F\033[0K";
    cursor_row_pre = cursor_row;
}

void game_print_board(void) {
    std::cout << "┌───┬───┬───┐\n│ "
              << game_board[0][0] << " │ "
              << game_board[0][1] << " │ " 
              << game_board[0][2] << " │\n";

    std::cout << "├───┼───┼───┤\n│ "
              << game_board[1][0] << " │ "
              << game_board[1][1] << " │ " 
              << game_board[1][2] << " │\n";

    std::cout << "├───┼───┼───┤\n│ "
              << game_board[2][0] << " │ "
              << game_board[2][1] << " │ " 
              << game_board[2][2] << " │\n"
              << "└───┴───┴───┘\n";
    // std::cout << "┌───┬───┬───┐\n"
    //           << "│ · │ · │ · │\n"
    //           << "├───┼───┼───┤\n"
    //           << "│ · │ · │ · │\n"
    //           << "├───┼───┼───┤\n"
    //           << "│ · │ · │ · │\n"
    //           << "└───┴───┴───┘\n";
}

void game_board_set_cursor(void) {
    if(cursor_row)
        std::cout << "\033[" << cursor_row*2 << "B";

    std::cout << "\033[0G\033[" << (cursor_col*4)+2 << "C";
}

void game_move_cursor_right(void) {
    cursor_col = (cursor_col == 2) ? 0 : cursor_col + 1;
}

void game_move_cursor_left(void) {
    cursor_col = (cursor_col > 0) ? cursor_col-1 : 2;
}

void game_move_cursor_up(void) {
    cursor_row_pre = cursor_row;
    cursor_row = (cursor_row > 0) ? cursor_row-1 : 2;
}
 
void game_move_cursor_down(void) {
    cursor_row_pre = cursor_row;
    cursor_row = ((cursor_row + 1) > 2) ? 0 : cursor_row+1;
}

void game_set_cross_at_cursor_pos(void) {
    game_board[cursor_row][cursor_col] = 'X';
}

void game_redraw_board(void) {
    game_clear_board();
    game_print_board();
    std::cout << "\033[" << tui_total_height-1 << "A";
    game_board_set_cursor();
}

void game_tui_cleanup() {
    tui_reset_input_mode();
    game_clear_board();
}

void game_tui_setup() {
    tui_set_input_mode();
    signal(SIGINT,  game_sig_handler);
    signal(SIGQUIT, game_sig_handler);
    signal(SIGTSTP, SIG_IGN);
    atexit(game_tui_cleanup);
    std::cout << "\033[4 q"; // Blinking block cursor
}

void game_initialize_board() {
    for(size_t i = 0; i < 3; ++i) {
        for(size_t j = 0; j < 3; ++j) {
            game_board[i][j] = ' ';
        }
    }
}


void game_key_handler(void) {
    char cmd;

    std::cin.get(cmd);
    switch(cmd) {
    case 'w':
    case 'k':
    case 's':
    case 'j':
        break;
    case  10: // Enter
    case ' ':
        game_set_cross_at_cursor_pos();
        break;
    case 'l':
    case 'f':
        break;
    case 'q':
        run_program = false;
        break;
    case 27: { // Escape codes (i.e. arrow keys)
        std::cin.get(cmd); // skip '['
        std::cin.get(cmd);
        switch (cmd) {
        case 'A': // up
            game_move_cursor_up();
            break;
        case 'B': // down
            game_move_cursor_down();
            break;
        case 'C': // right
            game_move_cursor_right();
            break;
        case 'D': // left
            game_move_cursor_left();
            break;
        }
        break;
        }
    }
}

int main (void) {
    run_program = true;
    refresh_cursor = false;
    tui_total_height = 7;
    cursor_row = cursor_row_pre = cursor_col = 0;

    game_tui_setup();

    game_initialize_board();
    game_print_board();
    std::cout << "\033[" << tui_total_height-1 << "A";
    std::cout << "\033[" << ((cursor_col*4)+2) << "C";

    while(run_program) {
        game_key_handler();
        game_redraw_board();
    }

    return 0;
}
