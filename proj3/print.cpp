//--------------------------------------------------------------------------
//                         printSorted
//--------------------------------------------------------------------------
void BST::printSorted() {
	printSorted(root);
}

//--------------------------------------------------------------------------
//                         printSorted
//--------------------------------------------------------------------------
// internal recursive version
void BST::printSorted(node* r) {
	if (r == NULL) return;
	printSorted(r->getLeft());
	cout << r->getKey() << "=" << r->getData() << endl;
	printSorted(r->getRight());
}

//--------------------------------------------------------------------------
//                         printKT
//--------------------------------------------------------------------------
// internal recursive version of printKeyTree()
void BST::printKT(node* r, int level) {
	if (r == NULL) {
		cout << endl;
		return;
	}
	printKT(r->getRight(), level + 1);
	for (int i = 1; i <= level * 5; i++) cout << " ";
	cout << r->getKey() << endl;
	printKT(r->getLeft(), level + 1);
}

//--------------------------------------------------------------------------
//                         printKeyTree
//--------------------------------------------------------------------------
void BST::printKeyTree() {
	printKT(root, 0);
}
