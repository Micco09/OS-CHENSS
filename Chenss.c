#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
int turn = WHITE;

int roll_d20(void)
{
    int range = RAND_MAX - (RAND_MAX % 20);
    int roll;
    do
    {
        roll = rand();
    } while (roll >= range);
    return roll % 20 + 1;
}

void init_board(void)
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

const char *piece_char(int piece, int pieceColor)
{
    switch (piece)
    {
    case Pawn:
        return pieceColor == WHITE ? "P" : "p";
    case Rook:
        return pieceColor == WHITE ? "R" : "r";
    case Knight:
        return pieceColor == WHITE ? "N" : "n";
    case Bishop:
        return pieceColor == WHITE ? "B" : "b";
    case Queen:
        return pieceColor == WHITE ? "Q" : "q";
    case King:
        return pieceColor == WHITE ? "K" : "k";
    default:
        return "-";
    }
}

void displayboard(void)
{
    printf("\n  a b c d e f g h\n");
    for (int r = 0; r < 8; r++)
    {
        printf("%d ", 8 - r);
        for (int c = 0; c < 8; c++)
        {
            printf("%c ", board[r][c] ? piece_char(board[r][c], color[r][c])[0] : '_');
        }
        printf("%d\n", 8 - r);
    }
    printf("  a b c d e f g h\n\n");
}

int input(const char *prompt)
{
    char square[16];
    printf("%s", prompt);
    if (scanf("%15s", square) != 1)
        return -1;

    if (strcmp(square, "quit") == 0 || strcmp(square, "q") == 0)
        return -2;

    if (strlen(square) != 2)
        return -1;

    char file = (char)tolower((unsigned char)square[0]);
    char rank = square[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
        return -1;

    int row = 8 - (rank - '0');
    int col = file - 'a';
    return row * 8 + col;
}

int is_clear_straight_path(int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow != toRow && fromCol != toCol)
        return 0;

    int stepRow = (toRow == fromRow) ? 0 : (toRow > fromRow ? 1 : -1);
    int stepCol = (toCol == fromCol) ? 0 : (toCol > fromCol ? 1 : -1);

    int r = fromRow + stepRow;
    int c = fromCol + stepCol;
    while (r != toRow || c != toCol)
    {
        if (board[r][c] != Empty)
            return 0;
        r += stepRow;
        c += stepCol;
    }
    return 1;
}

int is_clear_diagonal_path(int fromRow, int fromCol, int toRow, int toCol)
{
    if (abs(toRow - fromRow) != abs(toCol - fromCol))
        return 0;

    int stepRow = (toRow > fromRow) ? 1 : -1;
    int stepCol = (toCol > fromCol) ? 1 : -1;

    int r = fromRow + stepRow;
    int c = fromCol + stepCol;
    while (r != toRow || c != toCol)
    {
        if (board[r][c] != Empty)
            return 0;
        r += stepRow;
        c += stepCol;
    }
    return 1;
}

int is_legal_piece_move(int piece, int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow == toRow && fromCol == toCol)
        return 0;

    int dRow = toRow - fromRow;
    int dCol = toCol - fromCol;
    int absRow = abs(dRow);
    int absCol = abs(dCol);
    int pieceColor = color[fromRow][fromCol];

    switch (piece)
    {
    case Pawn:
    {
        int forward = (pieceColor == WHITE) ? -1 : 1;
        int startRow = (pieceColor == WHITE) ? 6 : 1;

        /* 1 square straight push */
        if (dCol == 0 && dRow == forward)
        {
            return (board[toRow][toCol] == Empty);
        }
        /* 2 squares initial push */
        if (dCol == 0 && dRow == 2 * forward && fromRow == startRow)
        {
            return (board[fromRow + forward][fromCol] == Empty &&
                    board[toRow][toCol] == Empty);
        }
        /* Diagonal capture */
        if (absCol == 1 && dRow == forward)
        {
            return (board[toRow][toCol] != Empty && color[toRow][toCol] != pieceColor);
        }
        return 0;
    }
    case Rook:
    {
        if (fromRow != toRow && fromCol != toCol)
            return 0;
        return is_clear_straight_path(fromRow, fromCol, toRow, toCol);
    }
    case Bishop:
    {
        if (absRow != absCol)
            return 0;
        return is_clear_diagonal_path(fromRow, fromCol, toRow, toCol);
    }
    case Knight:
    {
        return ((absRow == 1 && absCol == 2) || (absRow == 2 && absCol == 1));
    }
    case Queen:
    {
        if (fromRow == toRow || fromCol == toCol)
            return is_clear_straight_path(fromRow, fromCol, toRow, toCol);
        if (absRow == absCol)
            return is_clear_diagonal_path(fromRow, fromCol, toRow, toCol);
        return 0;
    }
    case King:
    {
        /* 1 square in any direction */
        if (absRow <= 1 && absCol <= 1)
            return 1;

        /* Castling (king moves 2 squares horizontally on back rank) */
        if (dRow == 0 && absCol == 2)
        {
            int homeRow = (pieceColor == WHITE) ? 7 : 0;
            if (fromRow != homeRow || fromCol != 4)
                return 0;

            /* Kingside */
            if (toCol == 6)
            {
                if (board[homeRow][7] == Rook && color[homeRow][7] == pieceColor &&
                    board[homeRow][5] == Empty && board[homeRow][6] == Empty)
                    return 1;
            }
            /* Queenside */
            else if (toCol == 2)
            {
                if (board[homeRow][0] == Rook && color[homeRow][0] == pieceColor &&
                    board[homeRow][1] == Empty && board[homeRow][2] == Empty && board[homeRow][3] == Empty)
                    return 1;
            }
        }
        return 0;
    }
    default:
        return 0;
    }
}

int find_king(int kingColor, int *kRow, int *kCol)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] == King && color[r][c] == kingColor)
            {
                *kRow = r;
                *kCol = c;
                return 1;
            }
        }
    }
    return 0;
}

int is_in_check(int kingColor)
{
    int kRow = -1;
    int kCol = -1;
    if (!find_king(kingColor, &kRow, &kCol))
        return 0;

    int enemyColor = (kingColor == WHITE) ? BLACK : WHITE;
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] != Empty && color[r][c] == enemyColor)
            {
                if (is_legal_piece_move(board[r][c], r, c, kRow, kCol))
                    return 1;
            }
        }
    }
    return 0;
}

int has_legal_moves(int playerColor)
{
    for (int fr = 0; fr < 8; fr++)
    {
        for (int fc = 0; fc < 8; fc++)
        {
            if (board[fr][fc] != Empty && color[fr][fc] == playerColor)
            {
                int p = board[fr][fc];
                for (int tr = 0; tr < 8; tr++)
                {
                    for (int tc = 0; tc < 8; tc++)
                    {
                        if (fr == tr && fc == tc)
                            continue;
                        if (board[tr][tc] != Empty && color[tr][tc] == playerColor)
                            continue;
                        if (!is_legal_piece_move(p, fr, fc, tr, tc))
                            continue;

                        /* Simulate move to check if it leaves own king in check */
                        int savedPiece = board[tr][tc];
                        int savedColor = color[tr][tc];

                        board[tr][tc] = p;
                        color[tr][tc] = playerColor;
                        board[fr][fc] = Empty;

                        int inCheck = is_in_check(playerColor);

                        /* Revert move */
                        board[fr][fc] = p;
                        color[fr][fc] = playerColor;
                        board[tr][tc] = savedPiece;
                        color[tr][tc] = savedColor;

                        if (!inCheck)
                            return 1; /* Found at least one legal move */
                    }
                }
            }
        }
    }
    return 0;
}

int move(void)
{
    int from = input("Move from (e.g. e2, or 'q' to forfeit): ");
    if (from == -2)
        return -2;
    if (from < 0)
    {
        printf("Invalid starting square.\n");
        return 0;
    }

    int to = input("Move to (e.g. e4): ");
    if (to == -2)
        return -2;
    if (to < 0)
    {
        printf("Invalid destination square.\n");
        return 0;
    }

    if (from == to)
    {
        printf("Starting square and destination cannot be the same.\n");
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
        printf("The destination contains one of your own pieces.\n");
        return 0;
    }
    if (!is_legal_piece_move(piece, fromRow, fromCol, toRow, toCol))
    {
        printf("That is not a legal move for that piece.\n");
        return 0;
    }

    /* Verify move does not leave own king in check */
    int savedDestPiece = board[toRow][toCol];
    int savedDestColor = color[toRow][toCol];

    board[toRow][toCol] = piece;
    color[toRow][toCol] = movingColor;
    board[fromRow][fromCol] = Empty;

    if (is_in_check(movingColor))
    {
        board[fromRow][fromCol] = piece;
        color[fromRow][fromCol] = movingColor;
        board[toRow][toCol] = savedDestPiece;
        color[toRow][toCol] = savedDestColor;
        printf("Illegal move: this move puts or leaves your King in check!\n");
        return 0;
    }

    /* Restore the board after validating the move before resolving any capture. */
    board[fromRow][fromCol] = piece;
    color[fromRow][fromCol] = movingColor;
    board[toRow][toCol] = savedDestPiece;
    color[toRow][toCol] = savedDestColor;

    if (savedDestPiece != Empty)
    {
        int attackerRoll = roll_d20();
        int defenderRoll = roll_d20();
        printf("Capture roll: %s rolls %d; %s rolls %d.\n",
               movingColor == WHITE ? "WHITE" : "BLACK", attackerRoll,
               movingColor == WHITE ? "BLACK" : "WHITE", defenderRoll);

        if (attackerRoll > defenderRoll)
        {
            printf("%s wins the capture roll and takes the piece.\n",
                   movingColor == WHITE ? "WHITE" : "BLACK");
            board[toRow][toCol] = piece;
            color[toRow][toCol] = movingColor;
            board[fromRow][fromCol] = Empty;
            color[fromRow][fromCol] = Empty;
        }
        else if (attackerRoll < defenderRoll)
        {
            printf("%s wins the capture roll. The attacking piece is lost; "
                   "the target stays in place.\n",
                   movingColor == WHITE ? "BLACK" : "WHITE");
            board[fromRow][fromCol] = Empty;
            color[fromRow][fromCol] = Empty;
        }
        else
        {
            printf("The rolls are tied. Both pieces are lost.\n");
            board[fromRow][fromCol] = Empty;
            color[fromRow][fromCol] = Empty;
            board[toRow][toCol] = Empty;
            color[toRow][toCol] = Empty;
        }
    }
    else
    {
        board[toRow][toCol] = piece;
        color[toRow][toCol] = movingColor;
        board[fromRow][fromCol] = Empty;
        color[fromRow][fromCol] = Empty;
    }

    /* Castling: move the rook alongside king */
    if (piece == King && abs(toCol - fromCol) == 2)
    {
        if (toCol == 6)
        {
            board[fromRow][5] = Rook;
            color[fromRow][5] = movingColor;
            board[fromRow][7] = Empty;
        }
        else if (toCol == 2)
        {
            board[fromRow][3] = Rook;
            color[fromRow][3] = movingColor;
            board[fromRow][0] = Empty;
        }
    }

    /* Standard pawn promotion: default promotes to Queen */
    if (board[toRow][toCol] == Pawn && color[toRow][toCol] == movingColor &&
        ((movingColor == WHITE && toRow == 0) || (movingColor == BLACK && toRow == 7)))
    {
        printf("Pawn reached the opposite back rank! Promoted to Queen.\n");
        board[toRow][toCol] = Queen;
    }

    turn = (movingColor == WHITE) ? BLACK : WHITE;
    return 1;
}

void check(void)
{
    if (is_in_check(turn))
    {
        printf("--> CHECK! %s King is under attack!\n", turn == WHITE ? "WHITE" : "BLACK");
    }
}

int checkmate(void)
{
    if (is_in_check(turn) && !has_legal_moves(turn))
    {
        printf("CHECKMATE! %s wins the match!\n", turn == WHITE ? "BLACK" : "WHITE");
        return 1;
    }
    else if (!is_in_check(turn) && !has_legal_moves(turn))
    {
        printf("\n-------------------------------------\n");
        printf("STALEMATE! The match ended in a draw.\n");
        printf("==========================================\n");
        return 1;
    }
    return 0;
}

int main(void)
{
    srand((unsigned int)time(NULL));
    init_board();
    printf("-------------------------------------\n");
    printf("               CHENSS                \n");
    printf("    Standard Chess Mechanics Mode    \n");
    printf("-------------------------------------\n");
    printf("Enter moves like 'e2' then 'e4'.\n");
    printf("Type 'q' or 'quit' to forfeit.\n\n");

    displayboard();

    while (1)
    {
        printf("[%s's Turn]\n", turn == WHITE ? "WHITE (Uppercase)" : "BLACK (Lowercase)");
        int res = move();
        if (res == -2)
        {
            printf("\n%s forfeited the game. %s wins!\n",
                   turn == WHITE ? "WHITE" : "BLACK",
                   turn == WHITE ? "BLACK" : "WHITE");
            break;
        }
        if (res == 1)
        {
            displayboard();

            int whiteKingRow = -1;
            int whiteKingCol = -1;
            int blackKingRow = -1;
            int blackKingCol = -1;
            int whiteKingAlive = find_king(WHITE, &whiteKingRow, &whiteKingCol);
            int blackKingAlive = find_king(BLACK, &blackKingRow, &blackKingCol);
            if (!whiteKingAlive || !blackKingAlive)
            {
                if (!whiteKingAlive && !blackKingAlive)
                    printf("Both Kings were lost. The game is a draw.\n");
                else
                    printf("%s King was lost. %s wins!\n",
                           whiteKingAlive ? "BLACK" : "WHITE",
                           whiteKingAlive ? "WHITE" : "BLACK");
                break;
            }

            if (checkmate())
                break;
            check();
        }
    }

    return 0;
}
