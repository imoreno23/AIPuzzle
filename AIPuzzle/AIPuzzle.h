#ifndef AIPUZZLE_H_
#define AIPUZZLE_H_

#include <vector>

class Tiles {
public:
	void showPuzzle(std::vector<int>puzzle);
	int findBlank(std::vector<int>puzzle);
	int findMTCost(std::vector<int>puzzle);
	int findManCost(std::vector<int>puzzle);
	int getCost(int diff);
	bool expandNode(struct Node* root, std::vector<Node*> v);
	bool checkPuzzle(std::vector<int>puzzle);
	bool checkDoubles(std::vector<int>n, std::vector<int>o);
	bool canMoveUp(std::vector<int>puzzle);
	bool canMoveDown(std::vector<int>puzzle);
	bool canMoveLeft(std::vector<int>puzzle);
	bool canMoveRight(std::vector<int>puzzle);
	int findDepth(struct Node* root);
	struct Node* getSmallCost(std::vector<Node*>currNode);
	struct Node* blankUp(struct Node* root);
	struct Node* blankDown(struct Node* root);
	struct Node* blankLeft(struct Node* root);
	struct Node* blankRight(struct Node* root);
	struct Node* uniDist(struct Node* initialState);
	struct Node* misTile(struct Node* initialState);
	struct Node* manTile(struct Node* initialState);
	std::vector<int> PlayPuzzle(struct Node* root);






};

#endif

