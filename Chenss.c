#include<stdio.h>
#include<stdlib.h>
#include<bool.h>
#include<string.h>
#include<ctype.h>

/*focus muna sa base mechanics kang chess bago iimplement ang whole rng thing*/
void disp_chess_board(){
    //displays board
}

void move_white(int row, char col){
    //moves pieces for white
    /*check whether black king is under attack*/
    /*call check() if under attack*/   
    if(/*check if move is valid*/){
            continue;
        }else{
            /*deny the move and make the player input another move*/
            /*probably call the function again??*/
    }
}

void move_black(int row, char col){
    //moves pieces for black
    /*check whether white king is under attack*/
    /*call check() if under attack*/   
    if(/*check if move is valid*/){
            continue;
        }else{
            /*deny the move and make the player input another move*/
            /*probably call the function again??*/
    }
}

void turn(){
    /*turn counter*/
}

void roll(){
    //dice roll when trying to take a piece
}


void take(){
    /*call roll(), check who has the higher roll before determining an outcome*/
}

void roll_outcome(){
    /*booleans for loss, draw, sacrifice?? then call sa take()*/
}

void check(){
    /*give checked player their turn to move if they have a valid move*/
    /*call checkmate()*/
}

void checkmate(){
    /*checks whether the player who's checked had any available moves*/
    /*if they dont, ends the game and with the current player getting the win*/
}



main(){
    /*dae pa ako sigurado sa part na ni, nag fofocus muna ako sa mga function*/
    int row;
    char col;

    disp_chess_board();

    /*code when moving a piece*/
    if(/*bool*/){
        move_white(row, col);
    }else{
        move_black(row,col);
    }

    /*code when taking a piece*/
    /*code when rolling*/

}
return 0;