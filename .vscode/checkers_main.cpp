#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <vector>
// white : $ black : #
using namespace std;
const int boardSize = 8;
class Bead {
    public:
    int x , y ;
    bool isKing = false;
    Bead(int , int , bool);

};
// based on details of every cells of board
Bead::Bead(int inputx , int inputy , bool inputIsKing){
    x = inputx;
    y = inputy;
    isKing = inputIsKing;
}
int getExistBeadIndex(vector<Bead> beads , int x , int y);
void printBoard(vector<Bead> whiteBeads , vector<Bead> blackBeads);

int main(){
    vector<Bead> whiteBeads , blackBeads;
    Bead b(1 , 2 , true);
    Bead b2(3 , 2 , false);
    whiteBeads.push_back(b);
    blackBeads.push_back(b2);
    printBoard(whiteBeads , blackBeads);
}

void printBoard(vector<Bead> whiteBeads , vector<Bead> blackBeads){
    // based for saving the index of the bead that is in that special cell
    int existWhiteIndex , existBlackIndex;
    cout << "    a   b   c   d   e   f   g   h" << endl;
    for(int j = 1 ; j<=boardSize ; j++){
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout<<j<<" |";
        for(int i = 1 ; i<=boardSize ; i++){
            existWhiteIndex = getExistBeadIndex(whiteBeads , i , j);
            if(existWhiteIndex<0)existBlackIndex = getExistBeadIndex(blackBeads , i , j);
            else existBlackIndex = -1;
            // *if there is any white bead in this cell of the board*
            if(existWhiteIndex >= 0){
                // this isn't a king bead
                if(!whiteBeads.at(existWhiteIndex).isKing){
                    cout<<" $ ";
                }
                // this is a king bead
                else{
                    cout<<" $*";
                }
            }
            // *if there is any black bead in this cell of the board*
            else if(existBlackIndex>=0){
                // this isn't a king bead
                if(!blackBeads.at(existBlackIndex).isKing){
                    cout<<" # ";
                }
                // this is a king bead
                else{
                    cout<<" #*";
                }
            }
            // *if there isn't any bead in this cell of the board
            else{
                cout<<"   ";
            }
            cout<<"|";
            }
            cout<<endl;
        }
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
int getExistBeadIndex(vector<Bead> beads , int x , int y){
    int result = -1;
    for(int i = 0 ; i<beads.size() ; i++){
        if((beads.at(i).x == x)&&(beads.at(i).y == y)){
            result = i;
            break;
        }
    }
    //if(result>=0)cout<<"a Bead found at "<<result<<endl;
    return result;
}