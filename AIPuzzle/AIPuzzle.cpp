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
        eightPuz = { 1,2,3,4,0,6,7,5,8 };
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
        std::cout << "Select Algorithm:\n(1) Uniform Cost Search\n(2) A* with Misplaced Tile Heuristic \n(3) A* with Manhattan Distance Heuristic\n(4) Play the 8-Puzzle\n";
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
        case 4:
            eightPuz = Puzzle.PlayPuzzle(eightPuz);
            break;
        default:
            //Not a valif input
            std::cout << "Not a valid input. Try again\n\n\n";
            break;
        }
    } while (input <= 0 || input > 4);

    ///
    // Try Making a node, then showing the puzzle thats in that node
    ///
    Node* root = newNode(eightPuz);
    Puzzle.expandNode(root, eightPuz);
    Puzzle.treeTraversal(root);
    /*Puzzle.showPuzzle(root->puzzle);
    Puzzle.showPuzzle(root->child[0]->puzzle);
    Puzzle.showPuzzle(root->child[1]->puzzle);
    Puzzle.showPuzzle(root->child[2]->puzzle);
    Puzzle.showPuzzle(root->child[3]->puzzle);
    Puzzle.expandNode(root->child[0], root->child[0]->puzzle);
    Puzzle.expandNode(root->child[1], root->child[1]->puzzle);
    Puzzle.expandNode(root->child[2], root->child[2]->puzzle);
    Puzzle.expandNode(root->child[3], root->child[3]->puzzle);
    Puzzle.showPuzzle(root->child[0]->child[0]->puzzle);
    Puzzle.showPuzzle(root->child[0]->child[1]->puzzle);
    Puzzle.showPuzzle(root->child[0]->child[2]->puzzle);
    Puzzle.showPuzzle(root->child[0]->child[3]->puzzle);
    Puzzle.showPuzzle(root->child[1]->child[0]->puzzle);
    Puzzle.showPuzzle(root->child[1]->child[1]->puzzle);
    Puzzle.showPuzzle(root->child[1]->child[2]->puzzle);
    Puzzle.showPuzzle(root->child[1]->child[3]->puzzle);
    Puzzle.showPuzzle(root->child[2]->child[0]->puzzle);
    Puzzle.showPuzzle(root->child[2]->child[1]->puzzle);
    Puzzle.showPuzzle(root->child[2]->child[2]->puzzle);
    Puzzle.showPuzzle(root->child[2]->child[3]->puzzle);
    Puzzle.showPuzzle(root->child[3]->child[0]->puzzle);
    Puzzle.showPuzzle(root->child[3]->child[1]->puzzle);
    Puzzle.showPuzzle(root->child[3]->child[2]->puzzle);
    Puzzle.showPuzzle(root->child[3]->child[3]->puzzle);
    Puzzle.showPuzzle(root->puzzle);
    */
    
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
        //std::cout << "Puzzle's are a match! good job!\n";
        return true;
    }
    else {
        //std::cout << "Nope, got some work to do...\n";
    }
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) up one slot. Also makes sure that a move up is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
std::vector<int> Tiles::blankUp(std::vector<int> puzzle)
{
    std::vector<int> tmp = puzzle;
    int blank = findBlank(puzzle);
    switch (blank) {
    case 0:
        //std::cout << "Cannot move the blank space up!";
        break;
    case 1:
        //std::cout << "Cannot move the blank space up!";
        break;
    case 2:
        //std::cout << "Cannot move the blank space up!";
        break;
    case 3:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[0]);
        break;
    case 4:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[1]);
        break;
    case 5:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[2]);
        break;
    case 6:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[3]);
        break;
    case 7:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[4]);
        break;
    case 8:
        //std::cout << "Moving piece up...";
        std::swap(tmp[blank], tmp[5]);
        break;
    default:
        break;
    }
    checkPuzzle(tmp);
    //showPuzzle(tmp);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) down one slot. Also makes sure that a move down is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
std::vector<int> Tiles::blankDown(std::vector<int> puzzle)
{
    std::vector<int> tmp = puzzle;
    int blank = findBlank(puzzle);
    switch (blank) {
    case 0:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[3]);
        break;
    case 1:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[4]);
        break;
    case 2:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[5]);
        break;
    case 3:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[6]);
        break;
    case 4:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[7]);
        break;
    case 5:
        //std::cout << "Moving piece down...";
        std::swap(tmp[blank], tmp[8]);
        break;
    case 6:
        //std::cout << "Cannot move the blank space down!";
        break;
    case 7:
        //std::cout << "Cannot move the blank space down!";
        break;
    case 8:
        //std::cout << "Cannot move the blank space down!";
        break;
    default:
        break;
    }
    checkPuzzle(tmp);
    //showPuzzle(tmp);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) to the left one slot. Also makes sure that a move to the left is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
std::vector<int> Tiles::blankLeft(std::vector<int> puzzle)
{
    std::vector<int> tmp = puzzle;
    int blank = findBlank(puzzle);
    switch (blank) {
    case 0:
        //std::cout << "Cannot move the blank space left!";
        break;
    case 1:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[0]);
        break;
    case 2:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[1]);
        break;
    case 3:
        //std::cout << "Cannot move the blank space left!";
        break;
    case 4:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[3]);
        break;
    case 5:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[4]);
        break;
    case 6:
        //std::cout << "Cannot move the blank space left!";
        break;
    case 7:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[6]);
        break;
    case 8:
        //std::cout << "Moving piece left...";
        std::swap(tmp[blank], tmp[7]);
        break;
    default:
        break;
    }
    checkPuzzle(tmp);
    //showPuzzle(tmp);
    return tmp;
}

//
// Function which takes in a vector that represents our puzzle and moves the blank spot
// (a.k.a the 0) to the right one slot. Also makes sure that a move to the right is a valid move,
// if it is then it will return the 8-puzzle after the move as a vector.
//
std::vector<int> Tiles::blankRight(std::vector<int> puzzle)
{
    std::vector<int> tmp = puzzle;
    int blank = findBlank(puzzle);
    switch (blank) {
    case 0:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[1]);
        break;
    case 1:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[2]);
        break;
    case 2:
        //std::cout << "Cannot move the blank space right!";
        break;
    case 3:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[4]);
        break;
    case 4:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[5]);
        break;
    case 5:
        //std::cout << "Cannot move the blank space right!";
        break;
        break;
    case 6:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[7]);
        break;
    case 7:
        //std::cout << "Moving piece right...";
        std::swap(tmp[blank], tmp[8]);
        break;
    case 8:
        //std::cout << "Cannot move the blank space right!";
        break;
    default:
        break;
    }
    checkPuzzle(tmp);
    //showPuzzle(tmp);
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
}

//
// I used this function to play the 8-puzzle myself to make sure it was working properly, also to check
// that each of my functions used to move the blank spot were working correctly. Takes in a vector to 
// represent the 8-puzzle and allows the user to play the puzzle.
//
std::vector<int> Tiles::PlayPuzzle(std::vector<int> puzzle)
{
    int input;
    std::vector<int> vect{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    showPuzzle(puzzle);
    do {
        std::cout << "(1) Move tile up\n(2) Move tile down\n(3) Move tile left\n(4) Move tile right\n ";
        std::cin >> input;
        switch (input) {
        case 1:
            puzzle = blankUp(puzzle);
            break;
        case 2:
            puzzle = blankDown(puzzle);
            break;
        case 3:
            puzzle = blankLeft(puzzle);
            break;
        case 4:
            puzzle = blankRight(puzzle);
            break;
        default:
            std::cout << "Not a valid input\n";
            break;
        }

    } while (puzzle != vect);
    return puzzle;
}

void Tiles::expandNode(struct Node * root, std::vector<int> puzzle)
{
    (root->child).push_back(newNode(blankUp(puzzle)));
    (root->child).push_back(newNode(blankDown(puzzle)));
    (root->child).push_back(newNode(blankLeft(puzzle)));
    (root->child).push_back(newNode(blankRight(puzzle)));
}

void Tiles::treeTraversal(Node* root)
{
    std::queue<Node*>currNode;
    std::vector<Node*>oldNodes;
    currNode.push(root);

    if (root == NULL) {
        return;
    }
    while (!currNode.empty()) {
        int n = currNode.size();
        while (n > 0) {
            Node* p = currNode.front();
            expandNode(p, p->puzzle);
            oldNodes.push_back(p);
            currNode.pop();

            for (unsigned int i = 0; i < p->child.size(); i++) {
                showPuzzle(p->child[i]->puzzle);
                for (unsigned int j = 0; j < oldNodes.size(); j++) {
                    if (p->child[i]->puzzle == oldNodes[j]->puzzle) {                       
                        std::cout << "this is an puzzle format we've seen before\n";
                        continue;
                    }
                    else if (checkPuzzle(p->child[i]->puzzle)) {                       
                        std::cout << "ITS A MATCH\n";
                        return;
                    }
                    else {
                        currNode.push(p->child[i]);
                    }
                }  
            }
            n--;
        }
        std::cout << "\n";
    }
}



