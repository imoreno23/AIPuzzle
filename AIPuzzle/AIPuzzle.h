#ifndef AIPUZZLE_H_
#define AIPUZZLE_H_

#include <vector>

class Tiles {
public:
	void showPuzzle(std::vector<int>puzzle);
	bool checkPuzzle(std::vector<int>puzzle);
	int findBlank(std::vector<int>puzzle);
	bool canMoveUp(std::vector<int>puzzle);
	bool canMoveDown(std::vector<int>puzzle);
	bool canMoveLeft(std::vector<int>puzzle);
	bool canMoveRight(std::vector<int>puzzle);
	struct Node* blankUp(struct Node *root);
	struct Node* blankDown(struct Node* root);
	struct Node* blankLeft(struct Node* root);
	struct Node* blankRight(struct Node* root);
	std::vector<int> PlayPuzzle(struct Node* root);

	struct Node* uniformCost(struct Node *root);
	//int checkDistMisplaced(std::vector<int>puzzle, std::vector<int>correct);
	//int checkDistManhat(std::vector<int>puzzle, std::vector<int>correct);
	void expandNode(struct Node *root);
	
	
	
};

#endif

