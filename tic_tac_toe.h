#ifndef TIC_TAC_TOE_H
#define MAX_PlAYERS 26
#define MIN_PLAYERS 2

typedef struct {
    char board[MAX_PlAYERS][MAX_PlAYERS];
    char current_player;
    char players[MAX_PlAYERS];
    int player_moves[MAX_PlAYERS];
} Game;

// Function prototypes
Game* init_game(int players_num, int board_size);

void display_board(const Game *game, int board_size);
int make_move(Game *game, int row, int col, int player_num, int board_size);
char check_winner(const Game *game, int board_size);
void free_game(Game *game);

#endif