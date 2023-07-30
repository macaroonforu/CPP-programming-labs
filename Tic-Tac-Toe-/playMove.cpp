//
//  playMove.cpp
//  TicTacToe
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    //Algorithm: 
    //if(game_state.get_turn()){ //This block will execute when it is X's turn 

        //STEP 1: Find out if they made a valid choice of board coordinates 
        int currentValue = game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()); 

        //STEP 2: Either place a value or don't depending on what get_GameBoard returns 
        //game_state.get_GameBoard will return empty (0) for an invalid choice of coordinates, so....

        if(currentValue==1||currentValue==-1){ 
            game_state.set_moveValid(false); 
            game_state.set_gameOver(false); 
            game_state.set_winCode(0); 
        }
        //remember that main filters for valid board coordinates, so only need to check if box is currently occupied
        //Our else block represents the case that get_GameBoard returned zero, in which case we proced to placing the proper mark 
        else{
            game_state.set_moveValid(true); 
            int MarkToBePlaced = game_state.get_turn()? 1:-1; 
            game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), MarkToBePlaced);
            game_state.set_winCode(0); 
        }
        //I set it to zero now as a default, but if the move made a win, wincode will be updated in the code below. 
        //NOW, WE BEGIN EXECUTING OUR CODE FOR WINCHEKING

        int box1= game_state.get_gameBoard(0,0); 
        int box2= game_state.get_gameBoard(0,1); 
        int box3= game_state.get_gameBoard(0,2); 
        int box4= game_state.get_gameBoard(1,0); 
        int box5= game_state.get_gameBoard(1,1); 
        int box6= game_state.get_gameBoard(1,2); 
        int box7= game_state.get_gameBoard(2,0); 
        int box8= game_state.get_gameBoard(2,1); 
        int box9= game_state.get_gameBoard(2,2); 

        if(box3==box5 &&box5==box7 && box5!=0){
            game_state.set_winCode(8); 
        }
        else if(box1==box5 && box5==box9 && box5!=0){
            game_state.set_winCode(7); 
        }
        else if(box3==box6 && box6==box9 && box6!=0){
            game_state.set_winCode(6); 
        }
        else if(box2==box5 && box5==box8 &&box5!=0){
            game_state.set_winCode(5);
        }
        else if(box1==box4 && box4==box7 &&box4!=0){
            game_state.set_winCode(4); 
        }
        else if(box7==box8 && box8==box9 &&box8!=0){
            game_state.set_winCode(3); 
        }
        else if(box4==box5 &&box5==box6 && box5!=0){
            game_state.set_winCode(2); 
        }
        else if(box1==box2 && box2==box3 && (box2!=0)){
            game_state.set_winCode(1); 
        }
        
        
        int count=0; 

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if (game_state.get_gameBoard(i,j)==Empty){
                     count+= 1; 
                }
            }
        }

        if (game_state.get_winCode() > 0 || count==0){
            game_state.set_gameOver(true); 
        }

        if(game_state.get_moveValid()==true){
            game_state.set_turn(!(game_state.get_turn()));
        }     
}


    


