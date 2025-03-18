/*
 * Copyright (c) 2025 AmirHossein Eslami
 * This project is licensed under the MIT License.
 * See the LICENSE file for details.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <vector>
#include <stdio.h>

// white : $ black : #
using namespace std;
// size of the board
const int boardSize = 8;
// if it become true the game will be finished
bool exitState = false;
const int arSize = 50;
char englishWords[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

class Bead
{
public:
    int x, y;
    bool isKing = false;
    Bead(int, int, bool);
};
// based on details of every cells of board
Bead::Bead(int inputx, int inputy, bool inputIsKing)
{
    x = inputx;
    y = inputy;
    isKing = inputIsKing;
}
// (other functions)
int getExistBeadIndex(vector<Bead>, int, int);
void printBoard(vector<Bead>, vector<Bead>);
void addAllBeads(vector<Bead> *, vector<Bead> *);
int getWordNumber(char *);
int getWordNumber(char);
void getInputPositionFromUser(int *, int *, int);
void checkPositionAbleToMoveWhite(vector<Bead> *);
int checkRightSideOfWhite(vector<Bead>, vector<Bead>, Bead);
int checkLeftSideOfWhite(vector<Bead>, vector<Bead>, Bead);
int checkLeftSideOfBlack(vector<Bead>, vector<Bead>, Bead);
int checkRightSideOfBlack(vector<Bead>, vector<Bead>, Bead);
int checkUpRightSideOfWhiteKing(vector<Bead>, vector<Bead>, Bead);
int checkUpLeftSideOfWhiteKing(vector<Bead>, vector<Bead>, Bead);
int checkDownRightSideOfBlackKing(vector<Bead>, vector<Bead>, Bead);
int checkDownLeftSideOfBlackKing(vector<Bead>, vector<Bead>, Bead);
void moveAndRemoveBeadsWhite(vector<Bead> *, vector<Bead> *, int, int, int);
void moveAndRemoveBeadsBlack(vector<Bead> *, vector<Bead> *, int, int, int);
void getBeadsMustMove(vector<Bead>, vector<Bead>, vector<Bead> *, int);
void printMustMoveBead(vector<Bead>);
bool isBeadInTheList(Bead, vector<Bead>);

int main()
{
    cout<<" ***********************************"<<endl<<" ********* Checkers game ***********"<<endl<<" ***********************************"<<endl;
cout<<"White: $ "<<endl<<"Black: #"<<endl;
bool isTheGameStarted = false;
string gamestartString;
cout<<"Insert (y) to Start The Game."<<endl;
while (!isTheGameStarted)
{
    cin>>gamestartString;
    if(gamestartString == "y")isTheGameStarted = true;
}

    bool playExit = false;
    while(!playExit){
    // make the basic form of the game board with its beads
    vector<Bead> whiteBeads, blackBeads;
    addAllBeads(&whiteBeads, &blackBeads);
    // test
    /*
        Bead test(5, 4, true);
        blackBeads.push_back(test);
        int testIndex1 = getExistBeadIndex(whiteBeads, 3, 2);
        whiteBeads.at(testIndex1).x = 1;
        whiteBeads.at(testIndex1).y = 3;
        int testIndex2 = getExistBeadIndex(whiteBeads, 4, 3);
        whiteBeads.at(testIndex2).x = 1;
        whiteBeads.at(testIndex2).y = 1;
        int testIndex = getExistBeadIndex(blackBeads, 6, 7);
        blackBeads.at(testIndex).x = 3;
        blackBeads.at(testIndex).y = 2;
        int testIndex3 = getExistBeadIndex(blackBeads, 8, 7);
        blackBeads.at(testIndex3).x = 1;
        blackBeads.at(testIndex3).y = 7;
        int testIndex4 = getExistBeadIndex(whiteBeads, 2, 3);
        whiteBeads.at(testIndex4).x = 2;
        whiteBeads.at(testIndex4).y = 5;
        whiteBeads.at(11).isKing = true;
        */

    string turn = "white";
    // start of the game
    while (!exitState)
    {
        // white's turn
        if (turn == "white")
        {

            printBoard(whiteBeads, blackBeads);
            // based on give us the beads that must move
            vector<Bead> mustMoveBeadWhite;
            cout << "(White's turn!)" << endl;

            // get the position of the bead that wanted to move from user
            int beadPositionX, beadPositionY, toMoveBeadIndex;
            bool beadExist = false;
            while (!beadExist)
            {
                getBeadsMustMove(whiteBeads, blackBeads, &mustMoveBeadWhite, 1);
                printMustMoveBead(mustMoveBeadWhite);

                getInputPositionFromUser(&beadPositionX, &beadPositionY, 1);
                // cout << "the position has been gotten (" << beadPositionX << " " << beadPositionY << endl;
                toMoveBeadIndex = getExistBeadIndex(whiteBeads, beadPositionX, beadPositionY);
                // check if there is any white bead in that position
                if (toMoveBeadIndex < 0)
                {
                    // there isn't any bead
                    cout << "There isn't any white bead in that position!" << endl;
                }
                else
                    // a bead is found
                    if (mustMoveBeadWhite.size() > 0)
                    {
                        // player has choice to to jump
                        if (!isBeadInTheList(whiteBeads.at(toMoveBeadIndex), mustMoveBeadWhite))
                            cout << "You must take a jump if it exists!" << endl;
                        else
                            beadExist = true;
                    }
                    else
                    {
                        // player doesn't have any choice to jump
                        Bead gottenBead = whiteBeads.at(toMoveBeadIndex);

                        if (!gottenBead.isKing && ((checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead) > 0) || checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead) > 0))
                            beadExist = true;
                        else if (gottenBead.isKing && ((checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead) > 0) || (checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead) > 0) || (checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead) > 0) || (checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead) > 0)))
                            beadExist = true;
                        else
                            cout << "This bead doesn't have any way to move!" << endl;
                    }
            }
            // we have gotten a bead from the user to move
            Bead gottenBead = whiteBeads.at(toMoveBeadIndex);
            /*
            int rightDownWhite = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead);
            cout << "Right side: " << checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead) << endl;
            cout << "Left side: " << checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead) << endl;
            int leftDownWhite = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead);
            cout << "up right side : " << checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead) << endl;
            cout << "up left side : " << checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead) << endl;
            */
            int rightSideJumpLengthWhite = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead);
            int leftSideJumpLengthWhite = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead);
            int upRightSideJumpLengthWhite = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
            int upLeftSideJumpLengthWhite = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);

            // getting position to move the bead
            int positionToMoveX, positionToMoveY;
            if (mustMoveBeadWhite.size() < 1)
            {
                // there is no bead that must jump
                bool positionExist = false;
                while (!positionExist)
                {
                    getInputPositionFromUser(&positionToMoveX, &positionToMoveY, 2);
                    if (getExistBeadIndex(whiteBeads, positionToMoveX, positionToMoveY) < 0 && getExistBeadIndex(blackBeads, positionToMoveX, positionToMoveY) < 0)
                    {

                        if (!gottenBead.isKing)
                        {
                            // Gotten bead isn't a king so it just can move front
                            if (((gottenBead.x + 1 == positionToMoveX) || (gottenBead.x - 1 == positionToMoveX)) && (gottenBead.y + 1 == positionToMoveY))
                            {
                                // the destination is in front of the bead on right or left
                                if ((gottenBead.x + 1 == positionToMoveX))
                                {
                                    // move to right
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 4);
                                    positionExist = true;
                                }
                                else
                                {
                                    // move to left
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 3);
                                    positionExist = true;
                                }
                            }
                            else
                            {
                                cout << "Your destination position is incorrect!" << endl;
                            }
                        }
                        else
                        {
                            //** Gotten bead is a king so it can move in 4 ways
                            if (((gottenBead.x + 1 == positionToMoveX) || (gottenBead.x - 1 == positionToMoveX)) && ((gottenBead.y + 1 == positionToMoveY) || (gottenBead.y - 1 == positionToMoveY)))
                            {
                                // the destination is in front of the bead on right or left
                                if ((gottenBead.x + 1 == positionToMoveX) && (gottenBead.y + 1 == positionToMoveY))
                                {
                                    // move to down right
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 4);
                                    positionExist = true;
                                }
                                else if ((gottenBead.x - 1 == positionToMoveX) && (gottenBead.y + 1 == positionToMoveY))
                                {
                                    // move to down left
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 3);
                                    positionExist = true;
                                }
                                else if ((gottenBead.x + 1 == positionToMoveX) && (gottenBead.y - 1 == positionToMoveY))
                                {
                                    // move to up right
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 1);
                                    positionExist = true;
                                }
                                else
                                {
                                    // move to up left
                                    moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 2);
                                    positionExist = true;
                                }
                            }
                            else
                            {
                                cout << "Your destination position is incorrect!" << endl;
                            }
                        }
                    }
                    else
                    {
                        // there is a bead in that position!
                        cout << "There is a bead in that position! You shoud choose an empty cell to move." << endl;
                    }
                }
                // The position is gotten from the user succesfully.
            }
            else
            {
                //******************************** must jump **********************************
                bool positionExist = false;
                while (!positionExist)
                {
                    getInputPositionFromUser(&positionToMoveX, &positionToMoveY, 2);

                    int differenceX, differenceY;
                    if ((gottenBead.x - positionToMoveX) > 0)
                        differenceX = (gottenBead.x - positionToMoveX);
                    else
                        differenceX = (positionToMoveX - gottenBead.x);
                    if ((gottenBead.y - positionToMoveY) > 0)
                        differenceY = (gottenBead.y - positionToMoveY);
                    else
                        differenceY = (positionToMoveY - gottenBead.y);

                    if ((differenceX % 2 == 0) && (differenceY % 2 == 0) && (differenceY == differenceX))
                    {
                        rightSideJumpLengthWhite = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead);
                        leftSideJumpLengthWhite = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead);
                        upRightSideJumpLengthWhite = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
                        upLeftSideJumpLengthWhite = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);

                        /*
                        cout << "right: " << rightSideJumpLengthWhite << endl;
                        cout << "left: " << leftSideJumpLengthWhite << endl;
                        cout << "upRight : " << upRightSideJumpLengthWhite << endl;
                        cout << "up left : " << upLeftSideJumpLengthWhite << endl;
                        */

                        // x & y difference is 2X

                        if (rightSideJumpLengthWhite > 1 && (gottenBead.x < positionToMoveX) && (gottenBead.y < positionToMoveY))
                        {
                            // move to down right
                            int moveLength = (positionToMoveY - gottenBead.y);
                            moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 4);
                            gottenBead = whiteBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead), upRight = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead), upLeft = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {// This isn't a king bead
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {// This is a king bead
                                if ((left < 2) && (right < 2) && (upLeft < 2) && (upRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (leftSideJumpLengthWhite > 1 && (gottenBead.x > positionToMoveX) && (gottenBead.y < positionToMoveY))
                        {
                            // move to down left
                            int moveLength = (positionToMoveY - gottenBead.y);
                            moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 3);
                            gottenBead = whiteBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead), upRight = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead), upLeft = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                if ((left < 2) && (right < 2) && (upLeft < 2) && (upRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (upRightSideJumpLengthWhite > 1 && (gottenBead.x < positionToMoveX) && (gottenBead.y > positionToMoveY))
                        {
                            // move to up right
                            int moveLength = (gottenBead.y - positionToMoveY);
                            moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 1);
                            gottenBead = whiteBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead), upRight = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead), upLeft = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                            // This isn't a king bead
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                // This is a king bead
                                if ((left < 2) && (right < 2) && (upLeft < 2) && (upRight < 2))
                                    positionExist = true;
                                else
                                    {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (upLeftSideJumpLengthWhite > 1 && (gottenBead.x > positionToMoveX) && (gottenBead.y > positionToMoveY))
                        {
                            // move to up left
                            int moveLength = (gottenBead.y - positionToMoveY);
                            moveAndRemoveBeadsWhite(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 2);
                            gottenBead = whiteBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfWhite(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfWhite(whiteBeads, blackBeads, gottenBead), upRight = checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, gottenBead), upLeft = checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                if ((left < 2) && (right < 2) && (upLeft < 2) && (upRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else
                        {
                            cout << "The position that you have chosen isn't correct! choose a position for jumping." << endl;
                        }
                    }
                    else
                    {
                        cout << "The position that you have chosen isn't correct! choose a position for jumping." << endl;
                    }
                }
            }
            // destination position is gotten
            if (blackBeads.size() == 0)
            {
                cout << "White player win the game!" << endl;
                exitState = true;
            }
            else if (whiteBeads.size() == 0)
            {
                cout << "Black player win the game!" << endl;
                exitState = true;
            }
            else
                turn = "black";
        }

        // black's turn
        else if (turn == "black")
        {
            printBoard(whiteBeads, blackBeads);
            vector<Bead> mustMoveBeadBlack;
            cout << "(Black's turn!)" << endl;
            int beadPositionX, beadPositionY, toMoveBeadIndex;
            bool beadExist = false;
            while (!beadExist)
            {
                getBeadsMustMove(whiteBeads, blackBeads, &mustMoveBeadBlack, 2);
                printMustMoveBead(mustMoveBeadBlack);
                getInputPositionFromUser(&beadPositionX, &beadPositionY, 1);
                // cout << "the position has been gotten (" << beadPositionX << " " << beadPositionY << endl;
                toMoveBeadIndex = getExistBeadIndex(blackBeads, beadPositionX, beadPositionY);
                // check if there is any black bead in that position
                if (toMoveBeadIndex < 0)
                {
                    cout << "There isn't any black bead in that position!" << endl;
                }
                else
                    // a bead is found
                    if (mustMoveBeadBlack.size() > 0)
                    {
                        // player has choice to to jump
                        if (!isBeadInTheList(blackBeads.at(toMoveBeadIndex), mustMoveBeadBlack))
                            cout << "You must take a jump if it exists!" << endl;
                        else
                            beadExist = true;
                    }
                    else
                    {
                        // player doesn't have any choice to jump
                        Bead gottenBead = blackBeads.at(toMoveBeadIndex);

                        if (!gottenBead.isKing && ((checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead) > 0) || checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead) > 0))
                            beadExist = true;
                        else if (gottenBead.isKing && ((checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead) > 0) || (checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead) > 0) || (checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead) > 0) || (checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead) > 0)))
                            beadExist = true;
                        else
                            cout << "This bead doesn't have any way to move!" << endl;
                    }
            }
            Bead gottenBead = blackBeads.at(toMoveBeadIndex);
            /*
            cout << "left side :" << checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead) << endl;
            cout << "Right side :" << checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead) << endl;
            cout << "down right side : " << checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead) << endl;
            cout << "down left side : " << checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead) << endl;
            */
            int rightSideJumpLengthBlack = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead);
            int leftSideJumpLengthBlack = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead);
            int downRightSideJumpLengthBlack = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
            int downLeftSideJumpLengthBlack = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
            // getting position to move the bead
            int positionToMoveX, positionToMoveY;
            if (mustMoveBeadBlack.size() < 1)
            {
                // there is no bead that must jump
                bool positionExist = false;
                while (!positionExist)
                {
                    getInputPositionFromUser(&positionToMoveX, &positionToMoveY, 2);
                    if (getExistBeadIndex(whiteBeads, positionToMoveX, positionToMoveY) < 0 && getExistBeadIndex(blackBeads, positionToMoveX, positionToMoveY) < 0)
                    {

                        if (!gottenBead.isKing)
                        {
                            // Gotten bead isn't a king so it just can move front
                            if (((gottenBead.x + 1 == positionToMoveX) || (gottenBead.x - 1 == positionToMoveX)) && (gottenBead.y - 1 == positionToMoveY))
                            {
                                // the destination is in front of the bead on right or left
                                if ((gottenBead.x + 1 == positionToMoveX))
                                {
                                    // move to right
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 1);
                                    positionExist = true;
                                }
                                else
                                {
                                    // move to left
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 2);
                                    positionExist = true;
                                }
                            }
                            else
                            {
                                cout << "Your destination position is incorrect!" << endl;
                            }
                        }
                        else
                        {
                            //** Gotten bead is a king so it can move in 4 ways
                            if (((gottenBead.x + 1 == positionToMoveX) || (gottenBead.x - 1 == positionToMoveX)) && ((gottenBead.y + 1 == positionToMoveY) || (gottenBead.y - 1 == positionToMoveY)))
                            {
                                // the destination is in front of the bead on right or left
                                if ((gottenBead.x + 1 == positionToMoveX) && (gottenBead.y + 1 == positionToMoveY))
                                {
                                    // move to down right
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 4);
                                    positionExist = true;
                                }
                                else if ((gottenBead.x - 1 == positionToMoveX) && (gottenBead.y + 1 == positionToMoveY))
                                {
                                    // move to down left
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 3);
                                    positionExist = true;
                                }
                                else if ((gottenBead.x + 1 == positionToMoveX) && (gottenBead.y - 1 == positionToMoveY))
                                {
                                    // move to up right
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 1);
                                    positionExist = true;
                                }
                                else
                                {
                                    // move to up left
                                    moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, 1, 2);
                                    positionExist = true;
                                }
                            }
                            else
                            {
                                cout << "Your destination position is incorrect!" << endl;
                            }
                        }
                    }
                    else
                    {
                        // there is a bead in that position!
                        cout << "There is a bead in that position! You shoud choose an empty cell to move." << endl;
                    }
                }
                // The position is gotten from the user succesfully.
            }
            else
            {
                //******************************** must jump **********************************
                bool positionExist = false;
                while (!positionExist)
                {
                    getInputPositionFromUser(&positionToMoveX, &positionToMoveY, 2);

                    int differenceX, differenceY;
                    if ((gottenBead.x - positionToMoveX) > 0)
                        differenceX = (gottenBead.x - positionToMoveX);
                    else
                        differenceX = (positionToMoveX - gottenBead.x);
                    if ((gottenBead.y - positionToMoveY) > 0)
                        differenceY = (gottenBead.y - positionToMoveY);
                    else
                        differenceY = (positionToMoveY - gottenBead.y);

                    if ((differenceX % 2 == 0) && (differenceY % 2 == 0) && (differenceY == differenceX))
                    {
                        rightSideJumpLengthBlack = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead);
                        leftSideJumpLengthBlack = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead);
                        downRightSideJumpLengthBlack = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
                        downLeftSideJumpLengthBlack = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);

                        /*
                        cout << "right: " << rightSideJumpLengthWhite << endl;
                        cout << "left: " << leftSideJumpLengthWhite << endl;
                        cout << "upRight : " << upRightSideJumpLengthWhite << endl;
                        cout << "up left : " << upLeftSideJumpLengthWhite << endl;
                        */

                        // x & y difference is 2X

                        if (rightSideJumpLengthBlack > 1 && (gottenBead.x < positionToMoveX) && (gottenBead.y > positionToMoveY))
                        {
                            // move to right
                            int moveLength = (gottenBead.y - positionToMoveY);
                            moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 1);
                            gottenBead = blackBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead), downRight = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead), downLeft = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {// This isn't a king
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {// This is a king bead
                                if ((left < 2) && (right < 2) && (downLeft < 2) && (downRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (leftSideJumpLengthBlack > 1 && (gottenBead.x > positionToMoveX) && (gottenBead.y > positionToMoveY))
                        {
                            // move to up left
                            int moveLength = (gottenBead.y - positionToMoveY);
                            moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 2);
                            gottenBead = blackBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead), downRight = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead), downLeft = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                if ((left < 2) && (right < 2) && (downLeft < 2) && (downRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (downRightSideJumpLengthBlack > 1 && (gottenBead.x < positionToMoveX) && (gottenBead.y < positionToMoveY))
                        {
                            // move to down right
                            int moveLength = (positionToMoveY - gottenBead.y);
                            moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 4);
                            gottenBead = blackBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead), downRight = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead), downLeft = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                if ((left < 2) && (right < 2) && (downLeft < 2) && (downRight < 2))
                                    positionExist = true;
                                    else {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else if (downLeftSideJumpLengthBlack > 1 && (gottenBead.x > positionToMoveX) && (gottenBead.y < positionToMoveY))
                        {
                            // move to down left
                            int moveLength = (positionToMoveY - gottenBead.y);
                            moveAndRemoveBeadsBlack(&whiteBeads, &blackBeads, toMoveBeadIndex, moveLength, 3);
                            //************************************************
                            gottenBead = blackBeads.at(toMoveBeadIndex);
                            int left = checkLeftSideOfBlack(whiteBeads, blackBeads, gottenBead), right = checkRightSideOfBlack(whiteBeads, blackBeads, gottenBead), downRight = checkDownRightSideOfBlackKing(whiteBeads, blackBeads, gottenBead), downLeft = checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, gottenBead);
                            if (!gottenBead.isKing)
                            {
                                // check does it have any other jump or no ?
                                if ((left < 2) && (right < 2))
                                    positionExist = true;
                                else
                                {
                                    printBoard(whiteBeads, blackBeads);
                                }
                            }
                            else
                            {
                                if ((left < 2) && (right < 2) && (downLeft < 2) && (downRight < 2))
                                    positionExist = true;
                                    {printBoard(whiteBeads , blackBeads);
                                    cout<<"Your selected bead have some other jump choices!"<<endl;}
                            }
                        }
                        else
                        {
                            cout << "The position that you have chosen isn't correct! choose a position for jumping." << endl;
                        }
                    }
                    else
                    {
                        cout << "The position that you have chosen isn't correct! choose a position for jumping." << endl;
                    }
                }
            }
            if (blackBeads.size() == 0)
            {
                cout << "White player win the game!" << endl;
                exitState = true;
            }
            else if (whiteBeads.size() == 0)
            {
                cout << "Black player win the game!" << endl;
                exitState = true;
            }
            else{
                turn = "white";
            }
        }
    }
    string playingState;
    cout<<"Do you want play again? (y/n)"<<endl;
    bool finishingTheGameStateMenu = false;
    while(!finishingTheGameStateMenu){
        cin>>playingState;
        if(playingState == "y"){
            finishingTheGameStateMenu = true;
            exitState = false;
            break;
            }
        else if (playingState == "n"){
            playExit = true;
            finishingTheGameStateMenu = true;
            break;
        }
    }
    }
}

void printBoard(vector<Bead> whiteBeads, vector<Bead> blackBeads)
{
    // based for saving the index of the bead that is in that special cell
    int existWhiteIndex, existBlackIndex;
    cout << endl << "     a   b   c   d   e   f   g   h" << endl;
    for (int j = 1; j <= boardSize; j++)
    {
        cout << "   +---+---+---+---+---+---+---+---+" << endl;
        cout <<" "<< j << " |";
        for (int i = 1; i <= boardSize; i++)
        {
            existWhiteIndex = getExistBeadIndex(whiteBeads, i, j);
            if (existWhiteIndex < 0)
                existBlackIndex = getExistBeadIndex(blackBeads, i, j);
            else
                existBlackIndex = -1;
            // *if there is any white bead in this cell of the board*
            if (existWhiteIndex >= 0)
            {
                // this isn't a king bead
                if (!whiteBeads.at(existWhiteIndex).isKing)
                {
                    cout << " $ ";
                }
                // this is a king bead
                else
                {
                    cout << " $*";
                }
            }
            // *if there is any black bead in this cell of the board*
            else if (existBlackIndex >= 0)
            {
                // this isn't a king bead
                if (!blackBeads.at(existBlackIndex).isKing)
                {
                    cout << " # ";
                }
                // this is a king bead
                else
                {
                    cout << " #*";
                }
            }
            // *if there isn't any bead in this cell of the board
            else
            {
                cout << "   ";
            }
            cout << "|";
        }
        cout << endl;
    }
    cout << "   +---+---+---+---+---+---+---+---+" << endl;
    cout << "     a   b   c   d   e   f   g   h" << endl<<endl;
}
int getExistBeadIndex(vector<Bead> beads, int x, int y)
{
    int result = -1;
    for (int i = 0; i < beads.size(); i++)
    {
        if ((beads.at(i).x == x) && (beads.at(i).y == y))
        {
            result = i;
            break;
        }
    }
    // if(result>=0)cout<<"a Bead found at "<<result<<endl;
    return result;
}
void addAllBeads(vector<Bead> *whiteBeads, vector<Bead> *blackBeads)
{
    int y = 1;
    for (int x = 2; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*whiteBeads).push_back(bead);
    }
    y = 2;
    for (int x = 1; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*whiteBeads).push_back(bead);
    }
    y = 3;
    for (int x = 2; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*whiteBeads).push_back(bead);
    }
    y = 6;
    for (int x = 1; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*blackBeads).push_back(bead);
    }
    y = 7;
    for (int x = 2; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*blackBeads).push_back(bead);
    }
    y = 8;
    for (int x = 1; x <= boardSize; x += 2)
    {
        Bead bead(x, y, false);
        (*blackBeads).push_back(bead);
    }
}
int getWordNumber(char word)
{
    int number;
    word = tolower(word);
    switch (word)
    {
    case 'a':
        number = 1;
        break;
    case 'b':
        number = 2;
        break;
    case 'c':
        number = 3;
        break;
    case 'd':
        number = 4;
        break;
    case 'e':
        number = 5;
        break;
    case 'f':
        number = 6;
        break;
    case 'g':
        number = 7;
        break;
    case 'h':
        number = 8;
        break;

    default:
        number = -1;
        break;
    }
    return number;
}
void getInputPositionFromUser(int *x, int *y, int status)
{
    // status 1: for choosing the bead
    // status 2: for get position to move
    char inputPlace;
    bool correctInputX = false;
    while (!correctInputX)
    {
        if (status == 1)
            cout << "Define the position of bead which you want to move." << endl
                 << "Insert a word from a to h: ";
        else
            cout << "Define the position to move the bead." << endl
                 << "Insert a word from a to h: ";
        cin >> inputPlace;
        *x = getWordNumber(inputPlace);
        // if the y input is correct it will get x input
        if (*x > 0)
        {
            bool correctInputY = false;
            while (!correctInputY)
            {
                cout << "Insert a number from 1 to 8: ";
                char tempInput;
                cin >> tempInput;
                if (tempInput == '1')
                    *y = 1;
                else if (tempInput == '2')
                    *y = 2;
                else if (tempInput == '3')
                    *y = 3;
                else if (tempInput == '4')
                    *y = 4;
                else if (tempInput == '5')
                    *y = 5;
                else if (tempInput == '6')
                    *y = 6;
                else if (tempInput == '7')
                    *y = 7;
                else if (tempInput == '8')
                    *y = 8;
                else
                    continue;

                if (*y < 1 || *y > 8)
                {
                    cout << "Your input isn't correct!" << endl;
                    continue;
                }
                else
                {
                    correctInputY = true;
                    correctInputX = true;
                }
            }
        }
        else
        {
            cout << "Your input isn't correct!" << endl;
            continue;
        }
    }
}
/*
void checkPositionAbleToMoveWhite(vector<Bead> whiteBeads , vector<Bead> blackBeads , vector<Bead> *positions , Bead bead ){
    int x = bead.x , y = bead.y;
    // if it isn't a king
    if(!bead.isKing){
    // check this position (x-1 & y+1) is in the board
    if(isInTheBoard(x-1 , y+1)){
        // check if there isn't any

    }


    }



    // if it is a king
    else{

    }
}
*/
// to check if the position is in the game board
bool isInTheBoard(int x, int y)
{
    if ((x < 9) && (x > 0) && (y < 9) && (y > 0))
        return true;
    else
        return false;
}
int checkRightSideOfWhite(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x + 1, y + 1))
        {
            // it's in the board
            if (getExistBeadIndex(whiteBeads, x + 1, y + 1) >= 0)
            {
                // there is a white bead
                finish = true;
                break;
            }
            else
            {
                // there is't any white bead
                if (getExistBeadIndex(blackBeads, x + 1, y + 1) >= 0)
                {
                    // there is a black bead there
                    if (isInTheBoard(x + 2, y + 2) && getExistBeadIndex(blackBeads, x + 2, y + 2) < 0 && getExistBeadIndex(whiteBeads, x + 2, y + 2) < 0)
                    {
                        // in the position (x+2 , y+2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x += 2;
                        y += 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkLeftSideOfWhite(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x - 1, y + 1))
        {
            // it's in the board
            if (getExistBeadIndex(whiteBeads, x - 1, y + 1) >= 0)
            {
                // there is a white bead
                finish = true;
                break;
            }
            else
            {
                // there is't any white bead
                if (getExistBeadIndex(blackBeads, x - 1, y + 1) >= 0)
                {
                    // there is a black bead there
                    if (isInTheBoard(x - 2, y + 2) && getExistBeadIndex(blackBeads, x - 2, y + 2) < 0 && getExistBeadIndex(whiteBeads, x - 2, y + 2) < 0)
                    {
                        // in the position (x-2 , y+2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x -= 2;
                        y += 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkLeftSideOfBlack(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x - 1, y - 1))
        {
            // it's in the board
            if (getExistBeadIndex(blackBeads, x - 1, y - 1) >= 0)
            {
                // there is a black bead
                finish = true;
                break;
            }
            else
            {
                // there is't any black bead
                if (getExistBeadIndex(whiteBeads, x - 1, y - 1) >= 0)
                {
                    // there is a white bead there
                    if (isInTheBoard(x - 2, y - 2) && getExistBeadIndex(blackBeads, x - 2, y - 2) < 0 && getExistBeadIndex(whiteBeads, x - 2, y - 2) < 0)
                    {
                        // in the position (x-2 , y-2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x -= 2;
                        y -= 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkRightSideOfBlack(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x + 1, y - 1))
        {
            // it's in the board
            if (getExistBeadIndex(blackBeads, x + 1, y - 1) >= 0)
            {
                // there is a black bead
                finish = true;
                break;
            }
            else
            {
                // there is't any black bead
                if (getExistBeadIndex(whiteBeads, x + 1, y - 1) >= 0)
                {
                    // there is a white bead there
                    if (isInTheBoard(x + 2, y - 2) && getExistBeadIndex(blackBeads, x + 2, y - 2) < 0 && getExistBeadIndex(whiteBeads, x + 2, y - 2) < 0)
                    {
                        // in the position (x-2 , y-2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x += 2;
                        y -= 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkUpRightSideOfWhiteKing(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x + 1, y - 1))
        {
            // it's in the board
            if (getExistBeadIndex(whiteBeads, x + 1, y - 1) >= 0)
            {
                // there is a white bead
                finish = true;
                break;
            }
            else
            {
                // there is't any white bead
                if (getExistBeadIndex(blackBeads, x + 1, y - 1) >= 0)
                {
                    // there is a black bead there
                    if (isInTheBoard(x + 2, y - 2) && getExistBeadIndex(blackBeads, x + 2, y - 2) < 0 && getExistBeadIndex(whiteBeads, x + 2, y - 2) < 0)
                    {
                        // in the position (x+2 , y-2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x += 2;
                        y -= 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkUpLeftSideOfWhiteKing(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x - 1, y - 1))
        {
            // it's in the board
            if (getExistBeadIndex(whiteBeads, x - 1, y - 1) >= 0)
            {
                // there is a white bead
                finish = true;
                break;
            }
            else
            {
                // there is't any white bead
                if (getExistBeadIndex(blackBeads, x - 1, y - 1) >= 0)
                {
                    // there is a black bead there
                    if (isInTheBoard(x - 2, y - 2) && getExistBeadIndex(blackBeads, x - 2, y - 2) < 0 && getExistBeadIndex(whiteBeads, x - 2, y - 2) < 0)
                    {
                        // in the position (x-2 , y+2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x -= 2;
                        y -= 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkDownRightSideOfBlackKing(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x + 1, y + 1))
        {
            // it's in the board
            if (getExistBeadIndex(blackBeads, x + 1, y + 1) >= 0)
            {
                // there is a black bead
                finish = true;
                break;
            }
            else
            {
                // there is't any black bead
                if (getExistBeadIndex(whiteBeads, x + 1, y + 1) >= 0)
                {
                    // there is a white bead there
                    if (isInTheBoard(x + 2, y + 2) && getExistBeadIndex(blackBeads, x + 2, y + 2) < 0 && getExistBeadIndex(whiteBeads, x + 2, y + 2) < 0)
                    {
                        // in the position (x-2 , y+2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x += 2;
                        y += 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
int checkDownLeftSideOfBlackKing(vector<Bead> whiteBeads, vector<Bead> blackBeads, Bead bead)
{
    // return is the length of the maximum move
    int moveResult = 0;
    bool finish = false;
    for (int x = bead.x, y = bead.y; (!finish) && (isInTheBoard(x, y));)
    {
        // step one
        if (isInTheBoard(x - 1, y + 1))
        {
            // it's in the board
            if (getExistBeadIndex(blackBeads, x - 1, y + 1) >= 0)
            {
                // there is a black bead
                finish = true;
                break;
            }
            else
            {
                // there is't any black bead
                if (getExistBeadIndex(whiteBeads, x - 1, y + 1) >= 0)
                {
                    // there is a white bead there
                    if (isInTheBoard(x - 2, y + 2) && getExistBeadIndex(blackBeads, x - 2, y + 2) < 0 && getExistBeadIndex(whiteBeads, x - 2, y + 2) < 0)
                    {
                        // in the position (x-2 , y+2) that is exist in the board , there isn't any bead.
                        moveResult += 2;
                        x -= 2;
                        y += 2;
                    }
                    // there isn't any position like this or it is occupied
                    else
                        finish = true;
                }
                else
                {
                    // there isn't any bead
                    if (moveResult == 0)
                        moveResult = 1;
                    finish = true;
                    break;
                }
            }
        }
        else
        {
            finish = true;
            break;
        }
    }

    return moveResult;
}
void moveAndRemoveBeadsWhite(vector<Bead> *whiteBeads, vector<Bead> *blackBeads, int toMoveBeadIndex, int moveLength, int moveSide)
{
    switch (moveSide)
    {
    case 4:
        // (down) right of the white beads
        if (moveLength == 1)
        {
            // don't have removing
            (*whiteBeads).at(toMoveBeadIndex).x += 1;
            (*whiteBeads).at(toMoveBeadIndex).y += 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*whiteBeads).at(toMoveBeadIndex).x += 2;
                (*whiteBeads).at(toMoveBeadIndex).y += 2;
                int deleteBlackIndex = getExistBeadIndex(*blackBeads, (*whiteBeads).at(toMoveBeadIndex).x - 1, (*whiteBeads).at(toMoveBeadIndex).y - 1);
                (*blackBeads).erase((*blackBeads).begin() + deleteBlackIndex);
                moveLength -= 2;
            }
        }
        break;
    case 3:
        // (down) left of the white beads
        if (moveLength == 1)
        {
            // don't have removing
            (*whiteBeads).at(toMoveBeadIndex).x -= 1;
            (*whiteBeads).at(toMoveBeadIndex).y += 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*whiteBeads).at(toMoveBeadIndex).x -= 2;
                (*whiteBeads).at(toMoveBeadIndex).y += 2;
                int deleteBlackIndex = getExistBeadIndex(*blackBeads, (*whiteBeads).at(toMoveBeadIndex).x + 1, (*whiteBeads).at(toMoveBeadIndex).y - 1);
                (*blackBeads).erase((*blackBeads).begin() + deleteBlackIndex);
                moveLength -= 2;
            }
        }
        break;
    case 1:
        // up right of white beads
        if (moveLength == 1)
        {
            // don't have removing
            (*whiteBeads).at(toMoveBeadIndex).x += 1;
            (*whiteBeads).at(toMoveBeadIndex).y -= 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*whiteBeads).at(toMoveBeadIndex).x += 2;
                (*whiteBeads).at(toMoveBeadIndex).y -= 2;
                int deleteBlackIndex = getExistBeadIndex(*blackBeads, (*whiteBeads).at(toMoveBeadIndex).x - 1, (*whiteBeads).at(toMoveBeadIndex).y + 1);
                (*blackBeads).erase((*blackBeads).begin() + deleteBlackIndex);
                moveLength -= 2;
            }
        }
        break;

    case 2:

        // up right of white beads
        if (moveLength == 1)
        {
            // don't have removing
            (*whiteBeads).at(toMoveBeadIndex).x -= 1;
            (*whiteBeads).at(toMoveBeadIndex).y -= 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*whiteBeads).at(toMoveBeadIndex).x -= 2;
                (*whiteBeads).at(toMoveBeadIndex).y -= 2;
                int deleteBlackIndex = getExistBeadIndex(*blackBeads, (*whiteBeads).at(toMoveBeadIndex).x + 1, (*whiteBeads).at(toMoveBeadIndex).y + 1);
                (*blackBeads).erase((*blackBeads).begin() + deleteBlackIndex);
                moveLength -= 2;
            }
        }
        break;
    }
    if ((!(*whiteBeads).at(toMoveBeadIndex).isKing)&&((*whiteBeads).at(toMoveBeadIndex).y == 8))
    {
        (*whiteBeads).at(toMoveBeadIndex).isKing = true;
        cout << "Your bead is a king now!" << endl;
    }
}
void moveAndRemoveBeadsBlack(vector<Bead> *whiteBeads, vector<Bead> *blackBeads, int toMoveBeadIndex, int moveLength, int moveSide)
{
    switch (moveSide)
    {
    case 4:
        // (down) right of the black beads
        if (moveLength == 1)
        {
            // don't have removing
            (*blackBeads).at(toMoveBeadIndex).x += 1;
            (*blackBeads).at(toMoveBeadIndex).y += 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*blackBeads).at(toMoveBeadIndex).x += 2;
                (*blackBeads).at(toMoveBeadIndex).y += 2;
                int deleteWhiteIndex = getExistBeadIndex(*whiteBeads, (*blackBeads).at(toMoveBeadIndex).x - 1, (*blackBeads).at(toMoveBeadIndex).y - 1);
                (*whiteBeads).erase((*whiteBeads).begin() + deleteWhiteIndex);
                moveLength -= 2;
            }
        }
        break;
    case 3:
        // (down) left of the black beads
        if (moveLength == 1)
        {
            // don't have removing
            (*blackBeads).at(toMoveBeadIndex).x -= 1;
            (*blackBeads).at(toMoveBeadIndex).y += 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*blackBeads).at(toMoveBeadIndex).x -= 2;
                (*blackBeads).at(toMoveBeadIndex).y += 2;
                int deleteWhiteIndex = getExistBeadIndex(*whiteBeads, (*blackBeads).at(toMoveBeadIndex).x + 1, (*blackBeads).at(toMoveBeadIndex).y - 1);
                (*whiteBeads).erase((*whiteBeads).begin() + deleteWhiteIndex);
                moveLength -= 2;
            }
        }
        break;
    case 1:
        // up right of white beads
        if (moveLength == 1)
        {
            // don't have removing
            (*blackBeads).at(toMoveBeadIndex).x += 1;
            (*blackBeads).at(toMoveBeadIndex).y -= 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*blackBeads).at(toMoveBeadIndex).x += 2;
                (*blackBeads).at(toMoveBeadIndex).y -= 2;
                int deleteWhiteIndex = getExistBeadIndex(*whiteBeads, (*blackBeads).at(toMoveBeadIndex).x - 1, (*blackBeads).at(toMoveBeadIndex).y + 1);
                (*whiteBeads).erase((*whiteBeads).begin() + deleteWhiteIndex);
                moveLength -= 2;
            }
        }
        break;

    case 2:

        // up right of black beads
        if (moveLength == 1)
        {
            // don't have removing
            (*blackBeads).at(toMoveBeadIndex).x -= 1;
            (*blackBeads).at(toMoveBeadIndex).y -= 1;
        }
        else
        {
            while (moveLength > 0)
            {
                (*blackBeads).at(toMoveBeadIndex).x -= 2;
                (*blackBeads).at(toMoveBeadIndex).y -= 2;
                int deleteWhiteIndex = getExistBeadIndex(*whiteBeads, (*blackBeads).at(toMoveBeadIndex).x + 1, (*blackBeads).at(toMoveBeadIndex).y + 1);
                (*whiteBeads).erase((*whiteBeads).begin() + deleteWhiteIndex);
                moveLength -= 2;
            }
        }
        break;
    }
    if ((!(*blackBeads).at(toMoveBeadIndex).isKing)&&((*blackBeads).at(toMoveBeadIndex).y == 1))
    {
        (*blackBeads).at(toMoveBeadIndex).isKing = true;
        cout << "Your bead is a king now!" << endl;
    }
}
void getBeadsMustMove(vector<Bead> whiteBeads, vector<Bead> blackBeads, vector<Bead> *mustMoveBeads, int status)
{
    if ((*mustMoveBeads).size() == 0)
    {
        // status ( 1: white || 2: black )
        switch (status)
        {
        case 1:
            for (int i = 0; i < whiteBeads.size(); i++)
            {
                if (!whiteBeads.at(i).isKing)
                {
                    // it's not a king bead
                    if ((checkRightSideOfWhite(whiteBeads, blackBeads, whiteBeads.at(i)) > 1) || (checkLeftSideOfWhite(whiteBeads, blackBeads, whiteBeads.at(i)) > 1))
                    {
                        (*mustMoveBeads).push_back(whiteBeads.at(i));
                    }
                }
                else
                {
                    // it's a king bead
                    if ((checkRightSideOfWhite(whiteBeads, blackBeads, whiteBeads.at(i)) > 1) || (checkLeftSideOfWhite(whiteBeads, blackBeads, whiteBeads.at(i)) > 1) || (checkUpRightSideOfWhiteKing(whiteBeads, blackBeads, whiteBeads.at(i)) > 1) || (checkUpLeftSideOfWhiteKing(whiteBeads, blackBeads, whiteBeads.at(i)) > 1))
                    {
                        (*mustMoveBeads).push_back(whiteBeads.at(i));
                    }
                }
            }
            break;

        case 2:
            for (int i = 0; i < blackBeads.size(); i++)
            {
                if (!blackBeads.at(i).isKing)
                {
                    // it's not a king bead
                    if ((checkRightSideOfBlack(whiteBeads, blackBeads, blackBeads.at(i)) > 1) || (checkLeftSideOfBlack(whiteBeads, blackBeads, blackBeads.at(i)) > 1))
                    {
                        (*mustMoveBeads).push_back(blackBeads.at(i));
                    }
                }
                else
                {
                    // it's a king bead
                    if ((checkRightSideOfBlack(whiteBeads, blackBeads, blackBeads.at(i)) > 1) || (checkLeftSideOfBlack(whiteBeads, blackBeads, blackBeads.at(i)) > 1) || (checkDownRightSideOfBlackKing(whiteBeads, blackBeads, blackBeads.at(i)) > 1) || (checkDownLeftSideOfBlackKing(whiteBeads, blackBeads, blackBeads.at(i)) > 1))
                    {
                        (*mustMoveBeads).push_back(blackBeads.at(i));
                    }
                }
            }
            break;
        }
    }
}
void printMustMoveBead(vector<Bead> mustMoveBead)
{
    if (mustMoveBead.size() > 0)
    {
        cout << "You have some choices to jump so you must choose a bead between these beads: ";
        for (int i = 0; i < mustMoveBead.size(); i++)
        {
            cout << "(" << englishWords[mustMoveBead.at(i).x - 1] << "," << mustMoveBead.at(i).y << ")";
            if (i != mustMoveBead.size() - 1)
                cout << ", ";
            else
                cout << endl;
        }
    }
}
bool isBeadInTheList(Bead wantMoveBead, vector<Bead> beadList)
{
    bool isInTheList = false;
    for (int i = 0; i < beadList.size(); i++)
    {
        if ((beadList.at(i).x == wantMoveBead.x) && (beadList.at(i).y == wantMoveBead.y))
            isInTheList = true;
    }
    return isInTheList;
}
