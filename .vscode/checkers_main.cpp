#include <iostream>
#include <iomanip>
using namespace std;

<<<<<<< HEAD
class Cell{
private:
int x , y;
bool isEmpty = true;
=======
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
            cout << "|" << setw(2) << x + 1 << endl;
            cout << "+---+---+---+---+---+---+---+---+" << endl;
        }
    } 
    void printBoard(){
>>>>>>> parent of 2a9021f (Last Board)

// ****** cell class ******
public:
    Cell(int = 0 , int = 0);
    void setState(bool b){
    isEmpty = b;
}
};

Cell::Cell(int ix , int iy){
    x = ix;
    y = iy;
}
// ****** cell class ******



// ******functions******
void printTable();

// ******functions******

int main(){
    


cout<<"test"<<endl;
 return 0;
}

void printTable(Cell cell[]){
    cout<<"  +---+---+---+---+---+---+---+---+\n";
    for(int i = 0 ; i<4 ; i++){
        
    }
    cout<<"    a   b   c   d   e   f   g   h\n";

}