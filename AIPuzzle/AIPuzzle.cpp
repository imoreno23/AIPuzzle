// AIPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include "AIPuzzle.h"

struct Node {
    std::vector<int> puzzle;
    std::vector<Node *>child;
};

Node *newNode(std::vector<int> puzzle) {
    Node *tmp = new Node;
    tmp->puzzle = puzzle;
    return tmp;
}


int main()
{
    //needed variables to set up puzzle
    Tiles Puzzle;
    int input;
    const int maxNum = 3;
    std:: vector<int> eightPuz;

    //Intro Message
    std::cout << "Welcome to my 8-Puzzle solver. Type 1 for a default puzzle and 2 to create your own \n";
    std::cin >> input;
    
    if (input == 1) {
        eightPuz = { 4,1,3,2,6,8,7,5,0 };
        Puzzle.showPuzzle(eightPuz);
    }
    else {
        //User input messages and vector filling
        std::cout << "Enter your puzzle, using 0 represents the blank. Please only enter valid 8-Puzzles. Enter the puzzle delimiting the numbers by hitting ENTER.\n";

        for (int i = 0; i < 9; i++) {
            std::cin >> input;
            eightPuz.push_back(input);
        }
        Puzzle.showPuzzle(eightPuz);
    }

    //user input message for what type of search is to be performed
    do {
        std::cout << "Select Algorithm:\n(1) Uniform Cost Search\n(2) A* with Misplaced Tile Heuristic \n(3) A* with Manhattan Distance Heuristic\n";
        std::cin >> input;
        switch (input) {
        case 1:
            //perform Uniform Cost Search
            //Puzzle.checkPuzzle(eightPuz);
            break;
        case 2:
            //perform Misplaced Tile Search
            //Puzzle.checkPuzzle(eightPuz);
            break;
        case 3:
            //perform Manhattan Distance Search
            //Puzzle.checkPuzzle(eightPuz);
            break;
        default:
            //Not a valid input
            std::cout << "Not a valid input. Try again\n\n\n";
            break;
        }
    } while (input <= 0 || input > 3);

    Node* root = newNode(eightPuz);
    //Puzzle.PlayPuzzle(root);
    Puzzle.uniformCost(root);
    
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

//
//Function that simply prints out an input vector formatted as an 8-puzzle.
//
void Tiles::showPuzzle(std::vector<int> puzzle)
{
    std::cout << "\n=====\n";
    for (unsigned int i = 0; i < puzzle.size(); i++) {
        if (i == 3 || i == 6) {
            std::cout << "\n";
        }
        std::cout << puzzle[i] << " ";
    }
    std::cout << "\n=====\n";
}

//
// Function to check the vector against a correct puzzle vector. takes in a vector
// as the representation of my 8-puzzle and checks it against a vector representing
// a solved 8-puzzle. 
//
bool Tiles::checkPuzzle(std::vector<int> puzzle)
{
    //std::cout << "Do they match?\n";
    std::vector<int> vect{ 1,2,3,4,5,6,7,8,0 };
    if (puzzle == vect) {
        return true;
    }
    else {
        return false;
    }
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) up one slot. Also makes sure that a move up is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
struct Node* Tiles::blankUp(struct Node* root)
{
    Node* tmp = root;
    int blank = findBlank(tmp->puzzle);
    switch (blank) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        std::swap(tmp->puzzle[blank], tmp->puzzle[0]);
        break;
    case 4:
        std::swap(tmp->puzzle[blank], tmp->puzzle[1]);
        break;
    case 5:
        std::swap(tmp->puzzle[blank], tmp->puzzle[2]);
        break;
    case 6:
        std::swap(tmp->puzzle[blank], tmp->puzzle[3]);
        break;
    case 7:
        std::swap(tmp->puzzle[blank], tmp->puzzle[4]);
        break;
    case 8:
        std::swap(tmp->puzzle[blank], tmp->puzzle[5]);
        break;
    default:
        break;
    }
    checkPuzzle(tmp->puzzle);
    //showPuzzle(tmp->puzzle);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) down one slot. Also makes sure that a move down is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
struct Node* Tiles::blankDown(struct Node* root)
{
    Node* tmp = root;
    int blank = findBlank(tmp->puzzle);
    switch (blank) {
    case 0:
        std::swap(tmp->puzzle[blank], tmp->puzzle[3]);
        break;
    case 1:
        std::swap(tmp->puzzle[blank], tmp->puzzle[4]);
        break;
    case 2:
        std::swap(tmp->puzzle[blank], tmp->puzzle[5]);
        break;
    case 3:
        std::swap(tmp->puzzle[blank], tmp->puzzle[6]);
        break;
    case 4:
        std::swap(tmp->puzzle[blank], tmp->puzzle[7]);
        break;
    case 5:
        std::swap(tmp->puzzle[blank], tmp->puzzle[8]);
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    default:
        break;
    }
    checkPuzzle(tmp->puzzle);
    //showPuzzle(tmp->puzzle);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) to the left one slot. Also makes sure that a move to the left is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
struct Node* Tiles::blankLeft(struct Node* root)
{
    Node* tmp = root;
    int blank = findBlank(tmp->puzzle);
    switch (blank) {
    case 0:
        break;
    case 1:
        std::swap(tmp->puzzle[blank], tmp->puzzle[0]);
        break;
    case 2:
        std::swap(tmp->puzzle[blank], tmp->puzzle[1]);
        break;
    case 3:
        break;
    case 4:
        std::swap(tmp->puzzle[blank], tmp->puzzle[3]);
        break;
    case 5:
        std::swap(tmp->puzzle[blank], tmp->puzzle[4]);
        break;
    case 6:
        break;
    case 7:
        std::swap(tmp->puzzle[blank], tmp->puzzle[6]);
        break;
    case 8:
        std::swap(tmp->puzzle[blank], tmp->puzzle[7]);
        break;
    default:
        break;
    }
    checkPuzzle(tmp->puzzle);
    //showPuzzle(tmp->puzzle);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) to the right one slot. Also makes sure that a move to the right is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
struct Node* Tiles::blankRight(struct Node* root)
{
    Node* tmp = root;
    int blank = findBlank(tmp->puzzle);
    switch (blank) {
    case 0:
        std::swap(tmp->puzzle[blank], tmp->puzzle[1]);
        break;
    case 1:
        std::swap(tmp->puzzle[blank], tmp->puzzle[2]);
        break;
    case 2:
        break;
    case 3:
        std::swap(tmp->puzzle[blank], tmp->puzzle[4]);
        break;
    case 4:
        std::swap(tmp->puzzle[blank], tmp->puzzle[5]);
        break;
    case 5:
        break;
    case 6:
        std::swap(tmp->puzzle[blank], tmp->puzzle[7]);
        break;
    case 7:
        std::swap(tmp->puzzle[blank], tmp->puzzle[8]);
        break;
    case 8:
        break;
    default:
        break;
    }
    checkPuzzle(tmp->puzzle);
    //showPuzzle(tmp->puzzle);
    return tmp;
}

//
// takes in a vector which represents our 8-puzzle then looks for a 0 in the puzzle and outputs which 
// slot of the puzzle its in as an integer which is used to solve the puzzle.
//
int Tiles::findBlank(std::vector<int> puzzle)
{
    std::vector<int> tmp = puzzle;
    for (unsigned int i = 0; i < tmp.size(); i++) {
        if (tmp[i] == 0) {
            return i;
        }
        else {
            continue;
        }
    }
    return NULL;
}

bool Tiles::canMoveUp(std::vector<int> puzzle)
{
    int tmp = findBlank(puzzle);
    if (tmp == 0 || tmp == 1 || tmp == 2) {
        return false;
    }
    else {
        return true;
    }
    
}

bool Tiles::canMoveDown(std::vector<int> puzzle)
{
    int tmp = findBlank(puzzle);
    if (tmp == 6 || tmp == 7 || tmp == 8) {
        return false;
    }
    else {
        return true;
    }
}

bool Tiles::canMoveLeft(std::vector<int> puzzle)
{
    int tmp = findBlank(puzzle);
    if (tmp == 0 || tmp == 3 || tmp == 6) {
        return false;
    }
    else {
        return true;
    }
}

bool Tiles::canMoveRight(std::vector<int> puzzle)
{
    int tmp = findBlank(puzzle);
    if (tmp == 2 || tmp == 5 || tmp == 8) {
        return false;
    }
    else {
        return true;
    }
}



//
// I used this function to play the 8-puzzle myself to make sure it was working properly, also to check
// that each of my functions used to move the blank spot were working correctly. Takes in a vector to 
// represent the 8-puzzle and allows the user to play the puzzle.
//
std::vector<int> Tiles::PlayPuzzle(struct Node* root)
{
    Node* p = root;
    
    int input;
    std::vector<int> vect{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    showPuzzle(p->puzzle);
    do {
        std::cout << "(1) Move tile up\n(2) Move tile down\n(3) Move tile left\n(4) Move tile right\n ";
        std::cin >> input;
        switch (input) {
        case 1:
            p = blankUp(p);
            break;
        case 2:
            p = blankDown(p);
            break;
        case 3:
            p = blankLeft(p);
            break;
        case 4:
            p = blankRight(p);
            break;
        default:
            std::cout << "Not a valid input\n";
            break;
        }

    } while (p->puzzle != vect);
    std::cout << "Match!\n";
    return p->puzzle;
}

//
//function that takes in a node as a parameter and expands the node one move in every direction
//
void Tiles::expandNode(struct Node* root)
{
    if (canMoveUp(root->puzzle)) {
        //std::cout << "expanding up from\n";
        //showPuzzle(root->puzzle);
        //std::cout << "~~~~~~~~~~~~~~~~~~~~~~";
        (root->child).push_back(newNode(blankUp(root)->puzzle));
        blankDown(root)->puzzle;
    }
    if (canMoveDown(root->puzzle)) {
        //std::cout << "expanding down from\n";
        //showPuzzle(root->puzzle);
        //std::cout << "~~~~~~~~~~~~~~~~~~~~~~";
        (root->child).push_back(newNode(blankDown(root)->puzzle));
        blankUp(root)->puzzle;
    }
    if (canMoveLeft(root->puzzle)) {
        //std::cout << "expanding left from\n";
        //showPuzzle(root->puzzle);
        //std::cout << "~~~~~~~~~~~~~~~~~~~~~~";
        (root->child).push_back(newNode(blankLeft(root)->puzzle));
        blankRight(root)->puzzle;
    }
    if (canMoveRight(root->puzzle)) {
        //std::cout << "expanding right from\n";
        //showPuzzle(root->puzzle);
        //std::cout << "~~~~~~~~~~~~~~~~~~~~~~";
        (root->child).push_back(newNode(blankRight(root)->puzzle));
        blankLeft(root)->puzzle;
    } 
}

//
// function for the uniform Distance Algorithm. takes in the root node with contains the starting
// puzzle vector sets it to the root node then traverses through it and expands it when it doesnt 
// match with any puzzle configuration that weve seen before. then checks all the children for the
// same thing and continues until if finds a matching vector to the solved puzzle vector. 
//
struct Node* Tiles::uniformCost(struct Node* root)
{
    std::queue<Node*>currNode;
    std::vector<Node*>oldNodes;
    currNode.push(root);

    if (root == NULL) {
        return NULL;
    }
    while (!currNode.empty()) {
        int n = currNode.size();
        while (n > 0) {
            Node* p = currNode.front();
            expandNode(p);
            oldNodes.push_back(p);
            currNode.pop();

            for (unsigned int i = 0; i < p->child.size(); i++) {
                showPuzzle(p->child[i]->puzzle);
                if (checkPuzzle(p->child[i]->puzzle)) {
                    std::cout << "ITS A MATCH\n";
                    return p->child[i];
                }
                currNode.push(p->child[i]);
            }
            n--;
        }
    }
    return NULL;
}


