#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h"

int main(void)
{
    char play_again = 'y';
    int draws = 0;
    int players_num = 0;
    int board_size = 0;

    printf("Enter the number of players (from 2 to 26): ");
    scanf("%d", &players_num);
    while (players_num < MIN_PLAYERS || players_num > MAX_PlAYERS) {
        printf("Sorry, the game only allows 2 to 26 players. Try again: ");
        scanf("%d", &players_num);
    }

    printf("Enter the size of the game board (Recommended size should be greater than the number of players): ");
    scanf("%d", &board_size);
    while (board_size < players_num) {
        printf("Too small. Try again: ");
        scanf("%d", &board_size);
    }

    int wins[board_size];   // Keep track of players' wins in an array

    // Initialize each player's win to 0
    for (int i = 0; i < players_num; i++) {
        wins[i] = 0;
    }

    while (play_again == 'y') {
        Game *game = init_game(players_num, board_size);
        int row, col;
        char winner = ' ';
        int move_count = 0;

        printf("Welcome to Tic Tac Toe\n");
        printf("Enter your move as row and column numbers (0, 1, 2\n\n");

        while (winner == ' ' && move_count < board_size * board_size) {
            display_board(game, board_size);

            for (int i = 0; i < players_num; i++) {
                if (game->current_player == game->players[i]) {
                    printf("Player %c, enter your move (row and column): ", game->players[i]);
                }

                // Get user input fo rorw and column
                scanf("%d %d", &row, &col);

                if (!make_move(game, row, col, players_num, board_size)) {
                    printf("Invalid move! Try again.\n");
                    i--;
                    continue;
                }
            }

            // Check for a winner after the move
            winner = check_winner(game, board_size);

            // If there's a winner, break the loop
            if(winner != ' ') {
                for (int i = 0; i < players_num; i++) {
                    if (winner == game->players[i]) {
                        printf("Player %c wins!\n", game->players[i]);
                        wins[i]++;
                    }
                }
            } else {
                printf("It's a draw!");
                draws++;
            }

            move_count++;
        }

        display_board(game, board_size);

        for (int i = 0; i < players_num; i++) {
            printf("Player %c Wins: %d\n", game->players[i], wins[i]);
            printf("Player %c Moves: %d\n", game->players[i], game->player_moves[i]);
        }

        free_game(game);

        // Ask the user if they want to play again
        printf("\ndo you want to play again? (y/n): ");
        scanf(" %c", &play_again);
    }

    printf("Thanks for playing!\n");
    return 0;

}
