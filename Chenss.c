#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*focus muna sa base mechanics kang chess bago iimplement ang whole rng thing*/

#define Pawn_W 'P'
#define Pawn_B 'p'
#define Rook_W 'R'
#define Rook_B 'r'
#define Knight_W 'N'
#define Knight_B 'n'
#define Bishop_W 'B'
#define Bishop_B 'b'
#define Queen_W 'Q'
#define Queen_B 'q'
#define King_W 'K'
#define King_B 'k'
#define Empty ' '   

static char board[8][8] = {
    {Rook_B, Knight_B, Bishop_B, Queen_B, King_B, Bishop_B, Knight_B, Rook_B},
    {Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W},
    {Rook_W, Knight_W, Bishop_W, Queen_W, King_W, Bishop_W, Knight_W,Rook_W}
};

void displayboard(){
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void move_white(int row, char col)
{
    int n;
    // moves pieces for white
    /*check whether black king is under attack*/
    /*call check() if under attack*/
    if (n = 0 /*check if move is valid*/)
    {
        /*continue*/
    }
    else
    {
        /*deny the move and make the player input another move*/
        /*probably call the function again??*/
    }
}

void move_black(int row, char col)
{
    int n;
    // moves pieces for black
    /*check whether white king is under attack*/
    /*call check() if under attack*/
    if (n = 0 /*check if move is valid*/)
    {
        /*continue;*/
    }
    else
    {
        /*deny the move and make the player input another move*/
        /*probably call the function again??*/
    }
}

void turn()
{
    /*turn counter*/
}

void roll()
{
    // dice roll when trying to take a piece
}

void take()
{
    /*call roll(), check who has the higher roll before determining an outcome*/
}

void roll_outcome()
{
    /*booleans for loss, draw, sacrifice?? then call sa take()*/
}

void check()
{
    /*give checked player their turn to move if they have a valid move*/
    /*call checkmate()*/
}

void checkmate()
{
    /*checks whether the player who's checked had any available moves*/
    /*if they dont, ends the game and with the current player getting the win*/
}

int main(void)
{
    /*dae pa ako sigurado sa part na ni, nag fofocus muna ako sa mga function*/
    int row;
    char col;

    disp_chess_board();

    /*code when moving a piece*/
    if (row == 0 /*bool*/)
    {
        move_white(row, col);
    }
    else
    {
        move_black(row, col);
    }

    /*code when taking a piece*/
    /*code when rolling*/

    return 0;
}