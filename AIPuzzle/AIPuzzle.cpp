// AIPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "AIPuzzle.h"



struct Node {
    Node* parent;
    std::vector<int> puzzle;
    std::vector<Node*>child;
    int cost;
    int depth;
};

Node* newNode(std::vector<int> puzzle) {
    Node* tmp = new Node;
    tmp->parent = nullptr;
    tmp->puzzle = puzzle;
    tmp->cost = 0;
    tmp->depth = 0;
    return tmp;
}

Node* newNode(std::vector<int> puzzle, Node* par) {
    Node* tmp = new Node;
    tmp->parent = par;
    tmp->puzzle = puzzle;
    tmp->cost = 0;
    tmp->depth = 0;
    return tmp;
}


int main()
{
    //needed variables to set up puzzle
    Tiles Puzzle;
    int input;
    const int maxNum = 3;
    std::vector<int> eightPuz;
    clock_t start, stop;
    double duration;

    //Intro Message
    std::cout << "Welcome to my 8-Puzzle solver.\n\n";
    for (;;) {
        eightPuz.clear();  //<-This clears the last puzzle in the vector
        std::cout << "Type 1 for a default puzzle and 2 to create your own \n\n";
        std::cin >> input;
        if (input == 1) {
            std::cout << "\nWhich difficulty level puzzle would you like?\n(1) Trivial -0-\n(2) Very Easy -2-\n(3) Easy -4-\n(4) Medium -8-\n(5) Slightly Difficult -12-\n";
            std::cout << "(6) Difficult -16-\n(7) More Difficult -20- (8)Most Difficult -24-\n\nPlease make a selection: ";
            std::cin >> input;
            switch (input) {
            case 1:
                eightPuz = { 1,2,3,4,5,6,7,8,0 };     //Depth 0
                break;
            case 2:
                eightPuz = { 1,2,3,4,5,6,0,7,8 };     //Depth 2
                break;
            case 3:
                eightPuz = { 1,2,3,5,0,6,4,7,8 };     //Depth 4
                break;
            case 4:
                eightPuz = { 1,3,6,5,0,2,4,7,8 };     //Depth 8
                break;
            case 5:
                eightPuz = { 1,3,6,5,0,7,4,8,2 };     //Depth 12
                break;
            case 6:
                eightPuz = { 1,6,7,5,0,3,4,8,2 };     //Depth 16
                break;
            case 7:
                eightPuz = { 7,1,2,4,8,5,6,3,0 };     //Depth 20
                break;
            case 8:
                eightPuz = { 0,7,2,4,6,1,3,5,8 };     //Depth 24
                break;
            default:
                std::cout << "Not a valid selection!\n";
                break;
            }
            std::cout << "\nthis is you puzzle\n";
            Puzzle.showPuzzle(eightPuz);
            std::cout << "\n^^^^^^^^^^^^^^^^^^\n\n\n";
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
        do {
            Node* root = newNode(eightPuz);
            //user input message for what type of search is to be performed
            std::cout << "Select Algorithm:\n(1) Uniform Cost Search\n(2) A* with Misplaced Tile Heuristic \n(3) A* with Manhattan Distance Heuristic\n(4) Select New Puzzle\n(5) Quit\n\n\n";
            std::cin >> input;
            
            switch (input) {
            case 1:
                //perform Uniform Cost Search
                start = clock();
                Puzzle.uniDist(root);
                stop = clock();
                duration = double(stop - start)/double (CLOCKS_PER_SEC);
                std::cout << "time taken: " << std::fixed << duration << std::setprecision(4) << " seconds.\n";
                break;
            case 2:
                //perform Misplaced Tile Search
                start = clock();
                Puzzle.misTile(root);
                stop = clock();
                duration = double(stop - start) / double(CLOCKS_PER_SEC);
                std::cout << "time taken: " << std::fixed << duration << std::setprecision(4) << " seconds.\n";
                break;
            case 3:
                //perform Manhattan Distance Search
                start = clock();
                Puzzle.manTile(root);
                stop = clock();
                
                duration = double(stop - start) / double(CLOCKS_PER_SEC);
                std::cout << "time taken: " << std::fixed << duration << std::setprecision(4) << " seconds.\n";
                break;
            case 4:
                break;
            case 5:
                return 0;
            default:
                //Not a valid input
                std::cout << "Not a valid input. Try again\n\n\n";
                break;
            }
            if (input == 4) {
                break;
            }
        } while (input > 0 || input < 6);
    }    
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

//
//Function that simply prints out an input vector formatted as an 8-puzzle. takes in a vector representation of a puzzle 
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
// This function checks for two vectors being equal to each other. this is a helper function
// that assists in another function in the program. its main use is to check for the current 
// nodes puzzle to match the node in the old nodes also used to pop off a node from the vector
// of Nodes to be checked.
//
bool Tiles::checkDoubles(std::vector<int> n, std::vector<int> o)
{
    if (n == o) {
        return true;
    }
    else {
        return false;
    }
}

//
// Function which takes in a Node structure and looks at the puzzle within it and moves the zero
// in the up direction. This is done by swapping the two values that would be swapped depending 
// on where the zero is located within the puzzle.
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
// Function which takes in a Node structure and looks at the puzzle within it and moves the zero
// in the down direction. This is done by swapping the two values that would be swapped depending 
// on where the zero is located within the puzzle.
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
// Function which takes in a Node structure and looks at the puzzle within it and moves the zero
// in the left direction. This is done by swapping the two values that would be swapped depending 
// on where the zero is located within the puzzle.
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
// Function which takes in a Node structure and looks at the puzzle within it and moves the zero
// in the right direction. This is done by swapping the two values that would be swapped depending 
// on where the zero is located within the puzzle.
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
// This function is a helper function that takes in a vector which represents 
// our 8-puzzle then looks for a 0 in the puzzle and outputs which 
// slot of the puzzle its in as an integer which is used to solve the puzzle by 
// moving the zero around in other functions
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
// using the missing tile heuristic. If the puzzle is correct already the function will return zero 
// as its cost which is the case for missing tile; as all the tiles are in their correct place. if the 
// puzzle isnt correct it will check to see if zero is in the bottom right ([8]) if its not then cost 
// will increment, then it will check the rest of the puzzle if the location of the vectors value doesnt
// correspond with what should be there cost will be incremented. once done cost will be returned.
//
int Tiles::findMTCost(std::vector<int> puzzle)
{
    int cost = 0;
    std::vector<int> tmp = puzzle;
    if (checkPuzzle(puzzle)) {
        return cost;
    }
    else {
        if (tmp[8] != 0) {
            cost++;
        }
        for (unsigned int i = 0; i < tmp.size() - 1; i++) {
            if (tmp[i] != i + 1) {
                cost++;
            }
        }
        return cost;
    }
    
}

//
// The findManCost function will find the cost at each node using the manhattan distance heuristic. if the
// puzzle is correct the finction will return 0 as that is the cost. if the puzzle doesnt match it will iterate 
// through the puzzle vector and depending on where each node is, it will increment cost by how many tiles that
// number is misplaced. it will do this for every tile and depending on which number is there it will calculate
// what its necessary distance to target is. once every spot in the puzzle is checked it will return the cost 
// accumulated.
//
int Tiles::findManCost(std::vector<int> puzzle)
{
    int cost = 0;
    int diff;
    int val;
    std::vector<int> tmp = puzzle;
    if (checkPuzzle(puzzle)) {
        return cost;
    }
    else {
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
    
}

//
// This is a helper function for the manhattan distance function. it will return the cost of the necessary moves
// to get a piece to its target location. this was my way of solving for the fact that in a vector the numbers are
// organized linearly but in the puzzle they are arranged as a 2D array. so for example; if 0 was in slot 0 then 
// it would have to go 8 spaces over in the vector but in a puzzle format this is only a misplacement of 4 slots.
// This function accounts for that and returns the correct cost of a misplacement.
//
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

//
// The following four functions are helper functions that check to see if a puzzle can indeed move in the direction 
// it was instructed to move
//
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
// This function takes in a vector of Nodes and finds the node within them that 
// has the smallest cost. this is used for uniformed distance search due to the 
// fact that all the moves have a cost of one, this function will simply end up 
// just checking which node in the tree at the current depth hasnt been checked. 
// 
// The function just below this one accounts for heuristics and how they effect 
// the searching procedure. at their core both functions do the same thing, one 
// one simply accounts for the depth and cost of any given node as those are the
// important elements to heuristic searches
//
struct Node* Tiles::getSmallCost(std::vector<Node*> currNode)
{
    int currSmall = INT_MAX;
    Node* tmpNode = nullptr;
    for (unsigned int i = 0; i < currNode.size(); i++) {
        if (currNode[i]->cost < currSmall) {
            currSmall = currNode[i]->cost;
            tmpNode = currNode[i];
        }
    }
    return tmpNode;
}

Node* Tiles::getSmallCostHeur(std::vector<Node*> currNode)
{
    int currSmall = INT_MAX;
    int heurcost, depth, cost, diff;
    Node* tmpNode = nullptr;
    for (unsigned int i = 0; i < currNode.size(); i++) {
        heurcost = currNode[i]->cost + currNode[i]->depth;
        depth = currNode[i]->depth;
        cost = currNode[i]->cost;
        if (heurcost <= currSmall) {
            currSmall = heurcost;
            tmpNode = currNode[i];
        }
    }
    heurcost = tmpNode->cost + tmpNode->depth;
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
// function that takes in a node as a parameter as well as a vector of node
// pointers and expands the node one move in every direction if the puzzle 
// in that node has not been seen before. every direction will get checked to
// see if expansion in that direction is possible before being expanded. before 
// expanding the function will check if the puzzle is a puzzle weve seen before
// by checking it against a vector of nodes containing the already checked puzzles.
//
bool Tiles::expandNode(struct Node* root, std::vector<Node*> v)
{
    struct Node* tmpNode = root;
    bool exp = true;
    for (unsigned int i = 0; i < v.size(); i++) {
        if (checkDoubles(tmpNode->puzzle, v[i]->puzzle)) {
            exp = false;
            return exp;
            break;
        }
    }
    if (exp) {
        if (canMoveUp(tmpNode->puzzle)) {
            (root->child).push_back(newNode(blankUp(tmpNode)->puzzle));
            blankDown(tmpNode)->puzzle;
        }
        if (canMoveDown(tmpNode->puzzle)) {
            (root->child).push_back(newNode(blankDown(tmpNode)->puzzle));
           blankUp(tmpNode)->puzzle;
        }
        if (canMoveLeft(tmpNode->puzzle)) {
            (root->child).push_back(newNode(blankLeft(tmpNode)->puzzle));
            blankRight(tmpNode)->puzzle;
        }
        if (canMoveRight(tmpNode->puzzle)) {
            (root->child).push_back(newNode(blankRight(tmpNode)->puzzle));
            blankLeft(tmpNode)->puzzle;
        }
    }
    return true;
}

//
// function for the uniform Distance Algorithm. takes in the root node with contains the starting
// puzzle vector sets it to the root node then traverses through it and expands it when it doesnt 
// match with any puzzle configuration that weve seen before. then checks which of teh remaining 
// nodes has the lowest cost value which for this is equal to its depth since all of the moves come
// at a cost of 1, and continues in this fashion until if finds a matching vector to the solved 
// puzzle vector. 
/////
// NOTE: uniDist works the same as Breadth first search in this case because all the tiles movements 
// have a cost of 1. this means that regardless of using the cost as a variable to search for, all
// the nodes at any given depth will be searched first before looking at any nodes that are further 
// down the tree.
/////
//
struct Node* Tiles::uniDist(struct Node* initialState)
{   
    int expanded = 0;                       
    std::vector<Node*>currNode;             
    std::vector<Node*>oldNodes;             

    currNode.push_back(initialState);       
    if (initialState == nullptr) {          
        return nullptr;
    }

    //while our queue is not empty perform expansion and checks
    while (!currNode.empty()) {             
        Node* p = getSmallCost(currNode);              
        for (unsigned int i = 0; i < currNode.size(); i++) {
            if (checkDoubles(currNode[i]->puzzle, p->puzzle)) {
                currNode.erase(currNode.begin() + i);
            }
        }
        std::cout << "the best state to expand with a f(n) = " << p->depth << " is...";
        showPuzzle(p->puzzle);

        //if child matched print out that its a match and the data of the match
        if (checkPuzzle(p->puzzle)) {                 
            std::cout << "ITS A MATCH\n";
            std::cout << "Nodes expanded: " << expanded << std::endl;
            std::cout << "Max queue size: " << currNode.size() << std::endl;
            std::cout << "Solution depth: " << p->depth << std::endl;
            return p;                               //return that child;
        }

        //if the node was expanded, increment 'expanded'
        if (expandNode(p, oldNodes)) {  
            expanded++;
        }
        
        //go through p's children and assign their cost and depth and push them into currNode
        for (unsigned int i = 0; i < p->child.size(); i++) {
            p->child[i]->parent = p;
            p->child[i]->depth = p->depth + 1;
            currNode.push_back(p->child[i]);
        }   
        
        //push the node(p) to the vector of nodes that weve already checked
        oldNodes.push_back(p); 
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
    int expanded = 0;                       
    std::vector<Node*>currNode;             
    std::vector<Node*>oldNodes;             

    currNode.push_back(initialState);       
    if (initialState == nullptr) {          
        return nullptr;
    }
    while (!currNode.empty()) {             
        Node* p = getSmallCostHeur(currNode);               
        for (unsigned int i = 0; i < currNode.size(); i++) {
            if (checkDoubles(p->puzzle, currNode[i]->puzzle)) {
                currNode.erase(currNode.begin() + i);
            }
        }
        std::cout << "the best state to expand with a g(n) = " << p->cost << " and h(n) = " << p->depth << " is...\n";
        showPuzzle(p->puzzle);

        //if child matched print out that its a match and the data of the match
        if (checkPuzzle(p->puzzle)) {                
            std::cout << "ITS A MATCH\n";
            std::cout << "Nodes expanded: " << expanded << std::endl;
            std::cout << "Max queue size: " << currNode.size() << std::endl;
            std::cout << "Solution depth: " << p->depth << std::endl;
            return p;                               //return that child;
        }

        //if the node was expanded, increment 'expanded'
        if (expandNode(p, oldNodes)) {  
            expanded++;
        }

        //go through p's children and assign their parent, cost and depth and push them into currNode
        for (unsigned int i = 0; i < p->child.size(); i++) {
            p->child[i]->parent = p;
            p->child[i]->cost = findMTCost(p->child[i]->puzzle);
            p->child[i]->depth = p->depth + 1;
            currNode.push_back(p->child[i]);
        }                                                      
        
        //push the node(p) to the vector of nodes that weve already checked
        oldNodes.push_back(p);         
    }
    return nullptr;
}

Node* Tiles::manTile(Node* initialState)
{
    int expanded = 0;                      
    std::vector<Node*>currNode;            
    std::vector<Node*>oldNodes;            

    currNode.push_back(initialState);       
    if (initialState == nullptr) {          
        return nullptr;
    }

    //while our queue is not empty perform expansion and checks
    while (!currNode.empty()) {             
        Node* p = getSmallCostHeur(currNode);              
        for (unsigned int i = 0; i < currNode.size(); i++) {
            if (checkDoubles(p->puzzle, currNode[i]->puzzle)) {
                currNode.erase(currNode.begin() + i);
            }
        }
        std::cout << "the best state to expand with a g(n) = " << p->cost << " and h(n) = " << p->depth << " is...\n";
        showPuzzle(p->puzzle);

        //if child matched print out that its a match and the data of the match
        if (checkPuzzle(p->puzzle)) {                 
            std::cout << "ITS A MATCH\n";
            std::cout << "Nodes expanded: " << expanded << std::endl;
            std::cout << "Max queue size: " << currNode.size() << std::endl;
            std::cout << "Solution depth: " << p->depth << std::endl;
            return p;                               //return that child;
        }

        //if the node was expanded, increment 'expanded'
        if (expandNode(p, oldNodes)) {  
            expanded++;
        }

        //go through p's children and assign their parent, cost and depth and push them into currNode
        for (unsigned int i = 0; i < p->child.size(); i++) {
            p->child[i]->parent = p;
            p->child[i]->cost = findManCost(p->child[i]->puzzle);
            p->child[i]->depth = p->depth + 1;
            currNode.push_back(p->child[i]);
        }            

        //push the node(p) to the vector of nodes that weve already checked
        oldNodes.push_back(p);          
    }
    return nullptr;
}

