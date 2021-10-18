#ifndef AIPUZZLE_H_
#define AIPUZZLE_H_

#include <vector>

class Tiles {
public:
	void showPuzzle(std::vector<int>puzzle);
	bool checkPuzzle(std::vector<int>puzzle);
	int findBlank(std::vector<int>puzzle);
	std::vector<int> blankUp(std::vector<int>puzzle);
	std::vector<int> blankDown(std::vector<int>puzzle);
	std::vector<int> blankLeft(std::vector<int>puzzle);
	std::vector<int> blankRight(std::vector<int>puzzle);
	std::vector<int> PlayPuzzle(std::vector<int>puzzle);

	void treeTraversal(struct Node *root);
	//int checkDistUniform(std::vector<int>puzzle, std::vector<int>correct);
	//int checkDistMisplaced(std::vector<int>puzzle, std::vector<int>correct);
	//int checkDistManhat(std::vector<int>puzzle, std::vector<int>correct);
	void expandNode(struct Node *root, std::vector<int>puzzle);
	
	
	
};

#endif

