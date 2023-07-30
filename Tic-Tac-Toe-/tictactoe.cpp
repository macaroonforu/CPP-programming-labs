//
//  main.cpp
//  TicTacTo


#include <iostream>
#include <string>
using namespace std;

#include "globals.h"
#include "GameState.h"

// Function prototype for playMove
void playMove(GameState&);
void printGameState(GameState&); 
void printBoard(GameState&); 

// The main function
int main() {

    /**********************************************************************************/
    /* Create an initialized game state object                                        */
    /**********************************************************************************/
    GameState game_state;

    //printBoard(game_state); 
    //printGameState(game_state); 

    // Read two integers from the user that represent the row and column
    // the player would like to place an X or an O in
    // You can assume there will be no formatting errors in the input

    int row;
    int col;
    while (!game_state.get_gameOver()) {
        cout << "Enter row and column of a grid cell: ";
        cin >> row >> col;
        
        // Check that the read row and column values are valid grid coordinates
        if ( (row < 0) || (row > 2) || (col < 0) || (col > 2) ) {
            cout << "Invalid board coordinates " << row << " " << col << endl << endl;
           continue;
        }
        // The coordinates are valid; set the selectedRow and selectedColumn
        // members of the game state to the read values
        // Again, the corresponding mutators of GameState must be first
        // implemented before this works

        // ECE244 Student: add your code here
          game_state.set_selectedRow(row); 
          game_state.set_selectedColumn(col); 
            
        // Call playMove
        // ECE244 Student: add your code here
         playMove(game_state); 
            
        // Print the GameState object, as prescribed in the handout
        // ECE244 Student: add your code here

        cout << "Selected row " << game_state.get_selectedRow() << " and column " << game_state.get_selectedColumn() << endl; 
        cout << "Game state after playMove:" << endl; 
        cout << "Board:" << endl; 

        printBoard(game_state);

        //printGameState(game_state); 

        string moveValid = game_state.get_moveValid()? "true": "false"; 
        string gameOver = game_state.get_gameOver()? "true": "false"; 

        cout << "moveValid: " << moveValid << endl; 
        cout << "gameOver: " << gameOver << endl; 
        cout << "winCode: " << game_state.get_winCode() << endl;        
    }
    return 0;
}


void printGameState(GameState& game_state){
    for (int i=0; i<3; i++){  //i refers to the rows 
        for(int j=0; j<3; j++){ //j refers to the colums 
           cout<<(game_state.get_gameBoard(i,j))<< "   "; 
        }
    }
}

void printBoard(GameState& game_state){
    for (int i=0; i<3; i++){  //i refers to the rows 
        cout << "   "; //start each row with 3 spaces 
        for(int j=0; j<3; j++){ //j refers to the colums 
            if(game_state.get_gameBoard(i,j)==1){
            cout << "X "; 
            }
            if(game_state.get_gameBoard(i,j)==-1){
                cout << "O "; 
            }   
            if(game_state.get_gameBoard(i,j)==0){
                cout << "B "; 
            }
        } //After one run of the inner loop has executed, we have printed a row, going column by column so we have to indent now 
    cout <<endl;
    }  
}
