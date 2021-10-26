// AIPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include "AIPuzzle.h"



struct Node {
    std::vector<int> puzzle;
    std::vector<Node*>child;
    int cost;
};

Node* newNode(std::vector<int> puzzle) {
    Node* tmp = new Node;
    tmp->puzzle = puzzle;
    tmp->cost = 0;
    return tmp;
}


int main()
{
    //needed variables to set up puzzle
    Tiles Puzzle;
    int input;
    const int maxNum = 3;
    std::vector<int> eightPuz;

    //Intro Message
    std::cout << "Welcome to my 8-Puzzle solver. Type 1 for a default puzzle and 2 to create your own \n";
    std::cin >> input;

    if (input == 1) {
        //eightPuz = { 1,0,3,4,2,6,7,5,8 };     //Easy
        //eightPuz = { 1,2,3,4,8,0,7,6,5 };     //Easy for manDist (ppt 2 slide 27)
        //eightPuz = { 4,1,0,7,2,3,5,8,6 };     //  
        eightPuz = { 4,0,1,7,2,3,5,8,6 };     //
        //eightPuz = { 1,2,3,4,5,8,6,7,0 };     //Difficult(from notes ppt 3 slide 27)
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
    for(;;){
        Node* root = newNode(eightPuz);

        //user input message for what type of search is to be performed

        do {
            std::cout << "Select Algorithm:\n(1) Uniform Cost Search\n(2) A* with Misplaced Tile Heuristic \n(3) A* with Manhattan Distance Heuristic\n";
            std::cin >> input;
            switch (input) {
            case 1:
                //perform Uniform Cost Search
                Puzzle.uniDist(root);
                break;
            case 2:
                //perform Misplaced Tile Search
                Puzzle.misTile(root);
                break;
            case 3:
                //perform Manhattan Distance Search
                Puzzle.manTile(root);
                break;
            default:
                //Not a valid input
                std::cout << "Not a valid input. Try again\n\n\n";
                break;
            }
        } while (input <= 0 || input > 3);
    }
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

bool Tiles::checkDoubles(std::vector<int> n, std::vector<int> o)
{
    if (n == o) {
        std::cout << "DOUBLE\n";
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

//
// findMTCost function is meant to find the estimated cost to get to the final state of the puzzle by 
// using the missing tile heuristic. 
//
int Tiles::findMTCost(std::vector<int> puzzle)
{
    int cost = 0;
    std::vector<int> tmp = puzzle;
    if (tmp[8] != 0) {
        cost++;
    }
    for (unsigned int i = 0; i < tmp.size()-1; i++) {
        if (tmp[i] != i+1) {
            cost++;
        }
    }
    return cost;
}

int Tiles::findManCost(std::vector<int> puzzle)
{
    int cost = 0;
    int diff;
    int val;
    std::vector<int> tmp = puzzle;
    for (unsigned int i = 0; i < tmp.size(); i++) {
        switch (i) {
        case 0:
            if (tmp[i] == 0) {
                cost += 4;
                break;
            }
            diff = abs((0 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 1:
            if (tmp[i] == 0) {
                cost += 3;
                break;
            }
            diff = abs((1 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 2:
            if (tmp[i] == 0) {
                cost += 2;
                break;
            }
            diff = abs((2 - tmp[i]) + 1);
            val = getCost(diff);

            cost += val;
            break;
        case 3:
            if (tmp[i] == 0) {
                cost += 3;
                break;
            }
            diff = abs((3 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 4:
            if (tmp[i] == 0) {
            cost += 2;
            break;
        }
            diff = abs((4 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 5:
            if (tmp[i] == 0) {
                cost += 1;
                break;
            }
            diff = abs((5 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 6:
            if (tmp[i] == 0) {
                cost += 2;
                break;
            }
            diff = abs((6 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 7:
            if (tmp[i] == 0) {
                cost += 1;
                break;
            }
            diff = abs((7 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        case 8:
            if (tmp[i] == 0) {
                cost += 1;
                break;
            }
            diff = abs((8 - tmp[i]) + 1);
            val = getCost(diff);
            cost += val;
            break;
        default:
            std::cout << "should not be another value\n";
            break;
        }
    }
    return cost;
}

int Tiles::getCost(int diff)
{
    int val = 0;
    if (diff >= 0 && diff < 3) {
        val = diff;
    }
    else if (diff >= 3 && diff < 6) {
        val = 1 + (diff - 3);
    }
    else if (diff >= 6 && diff < 9) {
        val = 2 + (diff - 6);
    }
    return val;
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

struct Node* Tiles::getSmallCost(std::vector<Node*> currNode)
{
    std::vector<Node*>tmp = currNode;
    int currSmall = INT_MAX;
    Node* tmpNode = nullptr;
    for (unsigned int i = 0; i < tmp.size(); i++) {
        if (tmp[i]->cost < currSmall) {
            currSmall = tmp[i]->cost;
            tmpNode = tmp[i];
        }
    }
    return tmpNode;
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
//function used to return the depth of the tree that is being worked on. used to report once puzzle is
//  solved what the size of the tree is in which the node was found that6 had the correct puzzle.
//
int Tiles::findDepth(Node* root)
{
    int maxDepth = -1;
    if (!root) {
        return 0;
    }
    for (std::vector<Node*>::iterator it = root->child.begin(); it != root->child.end(); it++) {
        maxDepth = std::max(maxDepth, findDepth(*it));
    }
    return maxDepth + 1;
}

//
// function that takes in a node as a parameter as well as a vector of node
// pointers and expands the node one move in every direction if the puzzle 
// in that node has not been seen before. every direction will get checked to
// see if expansion in that direction is possible before being expanded.
//
bool Tiles::expandNode(struct Node* root, std::vector<Node*> v)
{
    bool exp = true;
    for (unsigned int i = 0; i < v.size(); i++) {
        if (checkDoubles(root->puzzle, v[i]->puzzle)) {
            exp = false;
            return exp;
            break;
        }
    }
    if (exp) {
        if (canMoveUp(root->puzzle)) {
            (root->child).push_back(newNode(blankUp(root)->puzzle));
            blankDown(root)->puzzle;
        }
        if (canMoveDown(root->puzzle)) {
            (root->child).push_back(newNode(blankDown(root)->puzzle));
            blankUp(root)->puzzle;
        }
        if (canMoveLeft(root->puzzle)) {
            (root->child).push_back(newNode(blankLeft(root)->puzzle));
            blankRight(root)->puzzle;
        }
        if (canMoveRight(root->puzzle)) {
            (root->child).push_back(newNode(blankRight(root)->puzzle));
            blankLeft(root)->puzzle;
        }
    }
    return true;
}

//
// function for the uniform Distance Algorithm. takes in the root node with contains the starting
// puzzle vector sets it to the root node then traverses through it and expands it when it doesnt 
// match with any puzzle configuration that weve seen before. then checks all the children for the
// same thing and continues until if finds a matching vector to the solved puzzle vector. 
/////
// NOTE: uniDist works the same as Breadth first search in this case because all the tiles movements 
// have a cost of 1. this means that regardless of using the cost as a variable to search for, all
// the nodes at any given depth will be searched first before looking at any nodes that are further 
// down the tree.
/////
//
struct Node* Tiles::uniDist(struct Node* initialState)
{
    int expanded = 0;                       //used to keep track of how many nodes were expanded
    std::queue<Node*>currNode;              //queue of Nodes which will be filled will the trees nodes
    std::vector<Node*>oldNodes;             //vector of old nodes to be checked for already checked nodes
    currNode.push(initialState);            //push the node containing the puzzles init state
        
    if (initialState == nullptr) {          //if initial state is empty return
        return nullptr;
    }
    while (!currNode.empty()) {             //while our queue is not empty perform expansion and checks
        int qSize = currNode.size();        
        while (qSize > 0) {
            Node* p = currNode.front();     //node to be checked gets putlled from queue front
            currNode.pop();
            if (expandNode(p, oldNodes)) {  //if the node was expanded, increment 'expanded'
                expanded++;
            }
            oldNodes.push_back(p);          //push the node(p) to the vector of nodes that weve already checked
            for (unsigned int i = 0; i < p->child.size(); i++) {        //iterate through the children of the current node in question for a match
                showPuzzle(p->child[i]->puzzle);                        //show the nodes children in question
                if (checkPuzzle(p->child[i]->puzzle)) {                 //if child matched print out that its a match and the data of the match
                    std::cout << "ITS A MATCH\n";
                    std::cout << "Nodes expanded: " << expanded << std::endl;
                    std::cout << "Max queue size: " << currNode.size() << std::endl;
                    std::cout << "Solution depth: " << findDepth(initialState) << std::endl;
                    return p->child[i];                                 //return that child;
                }
                currNode.push(p->child[i]);                             //if the puzzle isnt a match, push the child in question to currNodes queue to be
            }                                                           //checked when it gets to the front of the queue
            qSize--;                        //decrease the qsize by 1;
        }
    }
    return nullptr;
}

//
// misTile is the function that will be used for missed tile heuristic search.  to get the 
// cost for the expansion in the missed tile heuristic we look at the overall puzzle and 
// see how many of the tiles are not in the correct spot each tile that is not in the correct
// spot counts as one. we look at every tile see how many as misplaced which gives us the cost 
// of that nodes expansion. We only expand the lowest costing nodes
//
Node* Tiles::misTile(Node* initialState)
{
    int expanded = 0;                       //used to keep track of how many nodes were expanded
    std::vector<Node*>currNode;               //list of Nodes which will be filled will the trees nodes
    std::vector<Node*>oldNodes;             //vector of old nodes to be checked for already checked nodes

    currNode.push_back(initialState);       //push the node containing the puzzles init state

    if (initialState == nullptr) {          //if initial state is empty return
        return nullptr;
    }
    while (!currNode.empty()) {             //while our queue is not empty perform expansion and checks
        int qSize = currNode.size();
        int currSmall = INT_MAX;
        for (unsigned int i = 0; i < currNode.size(); i++) {
            if (currNode[i]->cost < currSmall) {
                currSmall = currNode[i]->cost;
            }
            if (currNode[i]->cost == 0) {
                int depthCost, mtCost;
                mtCost = findMTCost(currNode[i]->puzzle);
                depthCost = findDepth(initialState);

                currNode[i]->cost = mtCost + depthCost;
            }
        }
        while (qSize > 0) {
            Node* p = getSmallCost(currNode);      //node to be checked gets pulled from queue front
            for (unsigned int i = 0; i < currNode.size(); i++) {
                if (p == currNode[i]) {
                    currNode.erase(currNode.begin() + i);
                }
            }
            if (expandNode(p, oldNodes)) {  //if the node was expanded, increment 'expanded'
                expanded++;
            }
            oldNodes.push_back(p);          //push the node(p) to the vector of nodes that weve already checked
            for (unsigned int i = 0; i < p->child.size(); i++) {        //iterate through the children of the current node in question for a match
                showPuzzle(p->child[i]->puzzle);                        //show the nodes children in question
                if (checkPuzzle(p->child[i]->puzzle)) {                 //if child matched print out that its a match and the data of the match
                    std::cout << "ITS A MATCH\n";
                    std::cout << "Nodes expanded: " << expanded << std::endl;
                    std::cout << "Max queue size: " << currNode.size() << std::endl;
                    std::cout << "Solution depth: " << findDepth(initialState) << std::endl;
                    return p->child[i];                                 //return that child;
                }
                currNode.push_back(p->child[i]);                        //if the puzzle isnt a match, push the child in question to currNodes queue to be
            }                                                           //checked when it gets to the front of the queue
            qSize--;                                                    //decrease the qsize by 1;
        }
    }
    return nullptr;
}

Node* Tiles::manTile(Node* initialState)
{
    int expanded = 0;                       //used to keep track of how many nodes were expanded
    std::vector<Node*>currNode;               //list of Nodes which will be filled will the trees nodes
    std::vector<Node*>oldNodes;             //vector of old nodes to be checked for already checked nodes

    currNode.push_back(initialState);       //push the node containing the puzzles init state

    if (initialState == nullptr) {          //if initial state is empty return
        return nullptr;
    }
    while (!currNode.empty()) {             //while our queue is not empty perform expansion and checks
        int qSize = currNode.size();
        int currSmall = INT_MAX;
        for (unsigned int i = 0; i < currNode.size(); i++) {
            if (currNode[i]->cost < currSmall) {
                currSmall = currNode[i]->cost;
            }
            if (currNode[i]->cost == 0) {
                int depthCost, manCost;
                manCost = findManCost(currNode[i]->puzzle);
                depthCost = findDepth(initialState);

                currNode[i]->cost = manCost + depthCost;
            }
        }
        while (qSize > 0) {
            Node* p = getSmallCost(currNode);      //node to be checked gets pulled from queue front
            for (unsigned int i = 0; i < currNode.size(); i++) {
                if (p == currNode[i]) {
                    currNode.erase(currNode.begin() + i);
                }
            }
            if (expandNode(p, oldNodes)) {  //if the node was expanded, increment 'expanded'
                expanded++;
            }
            oldNodes.push_back(p);          //push the node(p) to the vector of nodes that weve already checked
            for (unsigned int i = 0; i < p->child.size(); i++) {        //iterate through the children of the current node in question for a match
                showPuzzle(p->child[i]->puzzle);                        //show the nodes children in question
                if (checkPuzzle(p->child[i]->puzzle)) {                 //if child matched print out that its a match and the data of the match
                    std::cout << "ITS A MATCH\n";
                    std::cout << "Nodes expanded: " << expanded << std::endl;
                    std::cout << "Max queue size: " << currNode.size() << std::endl;
                    std::cout << "Solution depth: " << findDepth(initialState) << std::endl;
                    return p->child[i];                                 //return that child;
                }
                currNode.push_back(p->child[i]);                        //if the puzzle isnt a match, push the child in question to currNodes queue to be
            }                                                           //checked when it gets to the front of the queue
            qSize--;                                                    //decrease the qsize by 1;
        }
    }
    return nullptr;
}

