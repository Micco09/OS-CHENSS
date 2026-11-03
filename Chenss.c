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

#define WHITE 1
#define BLACK 0
int turn = WHITE; /*1 if turn belongs to white, 0 if black*/

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

int input (const char *prompt){
    int r;
    int c;
    printf("%s", prompt);
    if (scanf("%d %c", &r, &c) !=2 ) return -1;
    r-=8;
    c-=1;
    if (r < 0 || r > 7 || c < 0 || c > 7) return -1;
    return r*8+c;
}

void take()
{
    /*call roll(), check who has the higher roll before determining an outcome*/
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

    displayboard();

    /*code when moving a piece*/

    /*code when taking a piece*/

    /*code when rolling*/

    return 0;
}