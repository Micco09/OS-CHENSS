#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*focus muna sa base mechanics kang chess bago iimplement ang whole rng thing*/

// #define Pawn_W 'P'
// #define Pawn_B 'p'
// #define Rook_W 'R'
// #define Rook_B 'r'
// #define Knight_W 'N'
// #define Knight_B 'n'
// #define Bishop_W 'B'
// #define Bishop_B 'b'
// #define Queen_W 'Q'
// #define Queen_B 'q'
// #define King_W 'K'
// #define King_B 'k'
// #define Empty ' '

#define Pawn 1
#define Rook 2
#define Bishop 3
#define Knight 4
#define Queen 5
#define King 6
#define Empty 0

int board[8][8];
int color[8][8];

#define WHITE 1
#define BLACK 0
int turn = WHITE; /*1 if turn belongs to white, 0 if black*/

void init_board()
{
    memset(board, 0, sizeof(board));
    memset(color, 0, sizeof(color));

    int backrank[8] = {Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook};

    for (int i = 0; i < 8; i++)
    {
        board[0][i] = backrank[i];
        color[0][i] = BLACK;
        board[1][i] = Pawn;
        color[1][i] = BLACK;

        board[6][i] = Pawn;
        color[6][i] = WHITE;
        board[7][i] = backrank[i];
        color[7][i] = WHITE;
    }
}

const char *piece_char(int piece, int color)
{
    switch (piece)
    {
    case Pawn:
        return color == WHITE ? "P" : "p";
    case Rook:
        return color == WHITE ? "R" : "r";
    case Knight:
        return color == WHITE ? "N" : "n";
    case Bishop:
        return color == WHITE ? "B" : "b";
    case Queen:
        return color == WHITE ? "Q" : "q";
    case King:
        return color == WHITE ? "K" : "k";
    default:
        return "-";
    }
}

void displayboard()
{
    printf("  a b c d e f g h\n");
    for (int r = 0; r < 8; r++)
    {
        printf("%d ", 8 - r);
        for (int c = 0; c < 8; c++)
        {
            printf("%c ", board[r][c] ? piece_char(board[r][c], color[r][c])[0] : '_');
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n\n");
}

// static char board[8][8] = {
//     {Rook_B, Knight_B, Bishop_B, Queen_B, King_B, Bishop_B, Knight_B, Rook_B},
//     {Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B, Pawn_B},
//     {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
//     {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
//     {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
//     {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
//     {Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W, Pawn_W},
//     {Rook_W, Knight_W, Bishop_W, Queen_W, King_W, Bishop_W, Knight_W,Rook_W}
// };

int input(const char *prompt)
{
    char square[4];
    printf("%s", prompt);
    if (scanf("%3s", square) != 1 || strlen(square) != 2)
        return -1;

    char file = (char)tolower((unsigned char)square[0]);
    char rank = square[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
        return -1;

    int row = 8 - (rank - '0');
    int col = file - 'a';
    return row * 8 + col;
}

int is_legal_piece_move(int piece, int fromRow, int fromCol, int toRow, int toCol)
{
    (void)fromRow;
    (void)fromCol;
    (void)toRow;
    (void)toCol;

    switch (piece)
    {
    case Pawn:
        /* Add pawn movement and capture rules here. */
        return 0;
    case Rook:
        /* Add rook movement rules here. */
        return 0;
    case Bishop:
        /* Add bishop movement rules here. */
        return 0;
    case Knight:
        /* Add knight movement rules here. */
        return 0;
    case Queen:
        /* Add queen movement rules here. */
        return 0;
    case King:
        /* Add king movement rules here. */
        return 0;
    default:
        return 0;
    }
}

int move(void)
{
    int from = input("Move from (e.g. e2): ");
    if (from < 0)
    {
        printf("Invalid starting square.\n");
        return 0;
    }

    int to = input("Move to (e.g. e4): ");
    if (to < 0)
    {
        printf("Invalid destination square.\n");
        return 0;
    }

    int fromRow = from / 8;
    int fromCol = from % 8;
    int toRow = to / 8;
    int toCol = to % 8;
    int piece = board[fromRow][fromCol];
    int movingColor = color[fromRow][fromCol];

    if (piece == Empty)
    {
        printf("There is no piece on that starting square.\n");
        return 0;
    }
    if (movingColor != turn)
    {
        printf("That piece does not belong to the current player.\n");
        return 0;
    }
    if (color[toRow][toCol] == movingColor && board[toRow][toCol] != Empty)
    {
        printf("The destination contains one of your pieces.\n");
        return 0;
    }
    if (!is_legal_piece_move(piece, fromRow, fromCol, toRow, toCol))
    {
        printf("That move is not legal yet. Add the piece movement rules first.\n");
        return 0;
    }

    board[toRow][toCol] = piece;
    color[toRow][toCol] = movingColor;
    board[fromRow][fromCol] = Empty;
    color[fromRow][fromCol] = BLACK;
    turn = movingColor == WHITE ? BLACK : WHITE;
    return 1;
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
    init_board();
    displayboard();

    if (move())
        displayboard();

    /*code when taking a piece*/

    /*code when rolling*/

    return 0;
}