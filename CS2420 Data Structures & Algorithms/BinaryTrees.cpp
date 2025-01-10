// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;

void TreeParser::initialize() {
	expression = "";
	position = 0;
	while (!mathStack.empty()) {
		mathStack.pop();
	}

}

double TreeParser::castStrToDouble(const string &s) {
	istringstream iss(s);
	double x;
	iss >> x;
	return x;
} 

string TreeParser::castDoubleToStr(const double d) {
	ostringstream oss;
	oss << d;
	return oss.str();

} 

TreeParser::TreeParser() {
	initialize();
}


void TreeParser::displayParseTree() {
	cout << "The expression seen using in-order traversal: "; 
	inOrderTraversal();
	cout << endl;
	cout << "The expression seen using post-order traversal: "; 
	postOrderTraversal();
	cout << endl;
	
}

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


int main() {
	TreeParser *tp = new TreeParser;
	
	string expression = "(4+7)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11
	
	expression = "(7-4)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3

	expression = "(4^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64

	expression = "((2-5)-5)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8
	
	expression = "(5*(6/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15
	
	expression = "((1 + 2) * (3 + 4))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 21

	expression = "(543+321)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864

	expression = "(((((3+12)-7)*120)/(2+3))^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 7077888
	
	expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 1337
	
	pressAnyKeyToContinue();
	return 0;
}
