#include <iostream>
#include <string>
//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::endl;
using std::cout;
using std::cin;
using std::string;


void pressAnyKeyToContinue() {
	printf("Press any key to continue\n");

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();
#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif

}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		return false;
	}
}



template <typename T>
struct TreeNode {
	T info;
	TreeNode<T> * llink{ nullptr };
	TreeNode<T> * rlink{ nullptr };
};

template <typename T>
class SortedBinaryTree {
public:

	SortedBinaryTree() {};
	void addItem(const T& data);
	void preOrder();   //public to get the recursion started
private:
	TreeNode<T> * root{ nullptr };
	void preOrder(TreeNode<T> * ptr);  //uses a pointer to keep track of recursion
};

template <typename T>
void SortedBinaryTree<T>::preOrder() {
	preOrder(root);
}

template <typename T>
void SortedBinaryTree<T>::preOrder(TreeNode<T> * ptr) {
	if (ptr != nullptr) {
		cout << ptr->info << " ";
		preOrder(ptr->llink);
		preOrder(ptr->rlink);
	}
}


template <typename T>
void SortedBinaryTree<T>::addItem(const T& data) {
	if (root == nullptr) {
		root = new TreeNode<T>();
		root->info = data;
	}
	else {
		bool foundSpot = false;
		TreeNode<T> * curr = root;
		do {
			if (data < curr->info) {
				if (curr->llink == nullptr) {
					//put it on in here
					TreeNode<T> * temp = new TreeNode<T>();
					temp->info = data;
					curr->llink = temp;
					foundSpot = true;
				}
				else {
					curr = curr->llink;
				}
			}
			else {
				if (curr->rlink == nullptr) {
					TreeNode<T> * temp = new TreeNode<T>();
					temp->info = data;
					curr->rlink = temp;
					foundSpot = true;
				}
				else {
					curr = curr->rlink;
				}
			}
		} while (!foundSpot);
	}
}


int main() {

	SortedBinaryTree<int> myTree;

	myTree.addItem(37);
	myTree.addItem(32);
	myTree.addItem(73);
	myTree.addItem(95);
	myTree.addItem(42);
	myTree.addItem(12);
	myTree.addItem(00);
	myTree.addItem(49);
	myTree.addItem(98);
	myTree.addItem(7);
	myTree.addItem(27);
	myTree.addItem(17);
	myTree.addItem(47);
	myTree.addItem(87);
	myTree.addItem(77);
	myTree.addItem(97);
	myTree.addItem(67);
	myTree.addItem(85);
	myTree.addItem(15);
	myTree.addItem(5);
	myTree.addItem(35);
	myTree.addItem(55);
	myTree.addItem(65);
	myTree.addItem(75);
	myTree.addItem(25);
	myTree.addItem(45);
	myTree.addItem(3);
	myTree.addItem(93);
	myTree.addItem(83);
	myTree.addItem(53);
	myTree.addItem(63);
	myTree.addItem(23);
	myTree.addItem(13);
	myTree.addItem(43);
	myTree.addItem(33);

	myTree.preOrder();

	/*checkTest("Test #1, number of nodes", 35, myTree.nodeCount());
	checkTest("Test #2, number of leaves, (i.e. nodes with no children)", 11, myTree.leavesCount());
	checkTest("Test #3, number of nodes with one child", 14, myTree.singleChildCount());
	checkTest("Test #4, number of nodes on level 1 (the root level)", 1, myTree.levelCount(1));
	checkTest("Test #5, number of nodes on level 2", 2, myTree.levelCount(2));
	checkTest("Test #6, number of nodes on level 3", 4, myTree.levelCount(3));
	checkTest("Test #7, number of nodes on level 4", 6, myTree.levelCount(4));
	checkTest("Test #8, number of nodes on level 5", 7, myTree.levelCount(5));
	checkTest("Test #9, number of nodes on level 6", 7, myTree.levelCount(6));
	checkTest("Test #10, number of nodes on level 7", 7, myTree.levelCount(7));
	checkTest("Test #11, number of nodes on level 8", 1, myTree.levelCount(8));
	checkTest("Test #12, number of nodes on level 9", 0, myTree.levelCount(9));
	*/

	pressAnyKeyToContinue();
	return 0;
}