#include <iostream>
#include <iomanip>
using namespace std;

class Cell{
private:
int x , y;
bool isEmpty = true;

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