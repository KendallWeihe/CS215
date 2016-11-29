#include <iostream>
#include "node.h"

using namespace std;

int main() {
	node *a, *b, *c;
	a = new node;
	b = new node(2, "two");
	c = new node(3, "three");
	a->setKey(1);
	a->setData("one");
	a->setLeft(b);
	a->setRight(c);
	a->print();
	a->getLeft()->print();
	a->getRight()->print();
	delete a; // should delete all 3, leaving b and c as dangling refs
	// system("pause");
	return 0;
}
