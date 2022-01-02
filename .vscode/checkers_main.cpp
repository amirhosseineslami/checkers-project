#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
using namespace std;

class checkerboard{
    public:
    void initBoard(){//this is a function for initializing the board
        cout << "  a   b   c   d   e   f   g   h" << endl;
        cout << "+---+---+---+---+---+---+---+---+" << endl;
        for(int x = 0 ; x < 8 ; x++){
            for(int y = 0; y < 8; y++){
                if (x <= 2 && (x + y) % 2 == 0 ){
                    Oplayer[x][y] = ' ';
                cout << '|' << setw(2) << Oplayer[x][y] <<  " ";    
                }
                else if(x <= 2 && (x + y) % 2 != 0){ 
                    Oplayer[x][y] = 'O';
                    cout << '|' << setw(2) << Oplayer[x][y] << " "; 

                }
                if(x > 2 && x < 5 ){
                    cout << '|' << setw(4);
                }
                if(((x + y) % 2 != 0) && x >= 5){
                    starplayer[x][y] = '*';
                    cout << '|' << setw(2) << starplayer[x][y] <<  " "; 
                }
                else if(x >= 5 && (x + y) % 2 == 0){ 
                    Oplayer[x][y] = ' ';
                    cout << '|' << setw(2) << Oplayer[x][y] << " "; 

                }
            }
            cout << "|" ;
            cout << setw(2) << x + 1 << endl;
            cout << "+---+---+---+---+---+---+---+---+" << endl;
        }
    } 
    void printBoard(){

    }
    private:
    char board[8][8];
    char Oplayer[8][8];
    char starplayer[8][8];
};
int main(){
    checkerboard board;
        board.initBoard(); 
}