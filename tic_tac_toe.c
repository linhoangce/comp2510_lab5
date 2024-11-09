// Created by linho on 2024-10-13.
//

#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h"

Game* init_game(int players_num, int board_size) {

    Game *game = (Game*)malloc(sizeof(Game));

    // Assign the name for the players from A-Z and initialize their move to 0
    for (int i = 0; i < board_size; i++) {
        game->players[i] = 'A' + i;
        game->player_moves[i] = 0;
    }

    // Initialize the board with no player
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            game->board[i][j] = ' ';
        }
    }

    game->current_player = 'A';

    return game;
}

void display_board(const Game *game, int board_size) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            printf(" %c ", game->board[i][j]);

            if (j < board_size - 1) printf("|");
        }
        printf("\n");

        // Dynamically print the border based on the board size
        for (int i = 0; i < board_size - 1; i++) {
            printf("---");
            if (i < board_size - 2) {
                printf("|");
            }
        }
        printf("\n");
    }
}

int make_move(Game *game, int row, int col, int player_num, int board_size) {
    if (row < 0 || row >= board_size || col < 0 || col >= board_size || game->board[row][col] != ' ') {
        return 0;
    }

    game->board[row][col] = game->current_player;   // Save the player, e.g 'A'

    // Update move counts for current player
    for (int i = 0; i < player_num; i++) {
        if (game->current_player == game->players[i]) {
            game->player_moves[i]++;
        }
    }

    // Rotate the turn to the next player in the list
    for (int i = 0; i < player_num; i++) {
        if (game->current_player == game->players[i]) {
            game->current_player = game->players[(i + 1) % player_num]; // Ensures that the rotation wraps around when the last player has had their turn
            break;
        }
    }

    return 1;
}


char check_winner(const Game *game, int board_size) {
    // Checking rows
    for (int i = 0; i < board_size; i++) {
        int same = 1;

        for (int j = 0; j < board_size; j++) {
            if (game->board[i][j] != game->board[i][0] || game->board[i][0] == ' ') {
                same = 0;
                break;
            }
        }

        if (same == 1) {
            return game->board[i][0];
        }
    }

    // checking columns
    for (int i = 0; i < board_size; i++) {
        int same = 1;
        for (int j = 0; j < board_size; j++) {
            if (game->board[j][i] != game->board[0][i] || game->board[0][i] == ' ') {
                same = 0;
                break;
            }
        }

        if (same == 1) {
            return game->board[0][i];
        }
    }

    // Check diagonal
    int same_diag1 = 1;
    int same_diag2 = 1;

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (game->board[i][i] != game->board[0][0] || game->board[0][0] == ' ') {
                same_diag1 = 0;
            }
            if (game->board[i][board_size - i - 1] != game->board[0][board_size - 1] || game->board[0][board_size - 1] == ' ') {
                same_diag2 = 0;
            }
        }
    }

        if (same_diag1) return game->board[0][0];
        if (same_diag2) return game->board[0][board_size - 1];

        return ' ';  // No winner yet
}

void free_game(Game *game) {
    free(game);
}

