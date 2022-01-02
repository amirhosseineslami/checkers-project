#include <iostream>
#include <iomanip>
using namespace std;

class checkerboard{
    public:
    void initBoard(){//this is a function for initializing the board
        for(int x = 1 ; x <= 8 ; x++){
            for(int y = 1; y <= 8; y++){
                if((y % 2) == 0){
                    board[x][y] = 'O';
                }
                else{
                    board[x][y] = '*';
                }
            }
        }
    } 
    void printBoard(){

    }
    private:
    char board[8][8];
};
int main(){
    checkerboard board;
        board.initBoard(); 
        board.printBoard(); 
}