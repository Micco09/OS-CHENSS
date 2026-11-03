#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*focus muna sa base mechanics kang chess bago iimplement ang whole rng thing*/
void disp_chess_board()
{
    static char board[8][8];
    static const char Pawn_W = 'P';
    static const char Pawn_B = 'p';
    static const char Rook_W = 'R';
    static const char Rook_B = 'r';
    static const char Knight_W = 'N';
    static const char Knight_B = 'n';
    static const char Bishop_W = 'B';
    static const char Bishop_B = 'b';
    static const char Queen_W = 'Q';
    static const char Queen_B = 'q';
    static const char King_W = 'K';
    static const char King_B = 'k';
    static const char Empty = ' ';
    static const char Border = '|';
    static const char Line = '-';
    static const char Space = ' ';
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