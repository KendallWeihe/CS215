//----------------------------------------------------------------------
//						Lab 8 - Linked List Phone Book
//----------------------------------------------------------------------
// Author: Sensei Joiner and the Bluebelt Mutant Ninja Hackers
// Date:   Oct. 25, 2016
// Implements a simple phone book using a linked list
//----------------------------------------------------------------------
// INSTRUCTIONS: complete the following program by writing the
//               the unwritten functions as specified in the comments.
//               Look for TODO in the comments to determine what
//               you need to do.
//               Two instructions needs to be added to deletePhone()
//----------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// phone record structure
struct phone {
	string first;	// first name
	string last;	// last name
	string number;	// phone number
	phone* next;	// pointer to next node in the list
};

//----------------------------------------------------------------------
//                              makeNewPhone()
//----------------------------------------------------------------------
// TODO: dynamically allocate a new phone node. Ask the user to enter the
//       names and number and put them in the new node (hint: see how
//       members are referenced in the cout in printList()).
//       Since the node is not yet in the list, the NEXT pointer should
//       be set to NULL.
//		 RETURN: a pointer to the newly-created node.
//----------------------------------------------------------------------
phone *makeNewPhone(){

	//read user input
	string fname, lname, number;
	cout << "Enter the first name: ";
	cin >> fname;
	cout << "Enter the last name: ";
	cin >> lname;
	cout << "Enter the phone number: ";
	cin >> number;

	// allocate new node and input data
	phone *new_node = new phone;
	new_node->first = fname;
	new_node->last = lname;
	new_node->number = number;
	new_node->next = NULL; // set next to null

	return new_node; // return the new node

}

//----------------------------------------------------------------------
//                              append()
//----------------------------------------------------------------------
// TODO: Given the head of the current linked list, and a pointer to
//       an already-allocated and populated node, attach the new node to
//       the tail node of the current list (making it the new tail node).
//       RETURN: head of the (now extended) list
//       Example:
//       Given:  head -> N1 -> N2 -> N3      and     p -> NN
//       Make N3 point to NN:  head -> N1 -> N2 -> N3 -> NN
//       Be sure to handle "Empty List":   head=NULL   and p -> NN
//                               result:   head -> NN
//----------------------------------------------------------------------
phone *append(phone *head, phone *new_node){

	if (head == NULL){ // case where the list is empty
		return new_node;
	}

	phone *current_node = new phone;
	current_node = head;

	while (current_node->next != NULL){ // loop until the end of the list
		current_node = current_node->next;
	}

	current_node->next = new_node; // append to the end of the list

	return head;

}

//----------------------------------------------------------------------
//                              printList()
//----------------------------------------------------------------------
// Given a linked list of phone nodes, nicely print the contents
//----------------------------------------------------------------------
void printList(phone * head)			// given: a pointer to the first node of the list
{
	phone * p = head;					// to start, p points to the first node in the list
	cout << "\nPhone List:\n";
	cout << "First           Last            Phone\n";
	cout << "--------------- --------------- ---------------\n";
	while (p != NULL)					// while not past the end of the list
	{									// note: if head is NULL, so is P, so loop doesn't execute.
		cout << setw(15) << left << p->first << " " << setw(15) << p->last << " " << p->number << endl;
		p = p->next;					// make p point to the next node in the list
	}
	cout << endl;
} // printList()

//----------------------------------------------------------------------
//                              search()
//----------------------------------------------------------------------
// TODO: given the head of the list, a first name and a last name to search
//       for, go down the list and check each node to see if its first and last
//       equal the given search-first and search-last.
//       RETURN: a pointer to the node that is found, OR
//               NULL meaning "not found"
//----------------------------------------------------------------------
phone *search(phone *head, string fname, string lname){
	phone *current_node = new phone;
	current_node = head;
	while (current_node != NULL){ // loop until end of list
		if (current_node->first == fname && current_node->last == lname){ // if the current node matches the parameters, then return current node
			return current_node;
		}
		current_node = current_node->next; // else move current node to next node
	}
	return NULL; // case where the entry was not found
}

//----------------------------------------------------------------------
//                              getChoice()
//----------------------------------------------------------------------
// Display the user menu and get the user's choice. Does NOT validate
// the choice because that is done in main().
//----------------------------------------------------------------------
char getChoice()
{
	char choice;

	// print menu of operations
	cout << "\n-----------------------\n";
	cout << "A - Add new person\n";
	cout << "D - Delete person\n";
	cout << "S - Search for person\n";
	cout << "P - Print List\n";
	cout << "X - Exit\n\n";

	// ask for user's choice
	cout << "Enter choice: ";
	cin >> choice;
	choice = toupper(choice);	// convert to upper case: so 'a' becomes 'A'

	return choice;
} // getChoice()

//----------------------------------------------------------------------
//                              searchPhone()
//----------------------------------------------------------------------
// Asks the user to enter a name to search for and invokes the linked-list
// search() to find it. If found, it prints the phone number and returns
// a pointer to the found node. If not found, it prints a "not found"
// message and returns NULL (meaning "not found").
//----------------------------------------------------------------------
phone * searchPhone(phone * head) {
	string first, last;
	cout << "Enter first and last name: ";
	cin >> first >> last;
	phone * p = search(head, first, last);
	if (p == NULL)
		cout << "No person with that name found.\n";
	else
		cout << "Phone number is: " << p->number << endl;
	return p;
} // searchPhone()

//----------------------------------------------------------------------
//                              remove()
//----------------------------------------------------------------------
// TODO:
// Given: the head of the list, and a pointer to some node in the list
//        to be removed.
// Removes (but does not deallocate) a node from the list.
// Removing from the list should include setting the removed node's
//      NEXT pointer to NULL, since it will no longer be in the list.
// RETURNS a pointer to the head of the modified list.
// To remove a node (other than the head), pointed to by r in the example,
//    you will need to find (similar to search) a pointer to the node BEFORE
//    the one being removed. That is, b4 should point to the node whose NEXT
//    pointer points to the node to be removed (b4->next == r).
//          head -> N1 -> N2 ==> N3 -> N4 ->N5
//                        ^      ^
//                        |      |
//                        b4     r
//    So B4's NEXT pointer should be set to the R's next pointer to bypass the
//    removed node, and R's NEXT pointer should be set to NULL since it is no
//    longer in the list: (NOTE: the same code will work if R points to the tail)
//          head -> N1 -> N2 ========> N4 -> N5
//                        ^     N3
//                        |     ^
//                        |     |
//                        b4    r
// To remove the HEAD node is simpler, since there is no node BEFORE it to find.
//    Simply set the head to point to its own next pointer to bypass the head node,
//    and remember to set the NEXT pointer in the removed node to NULL.
//          head -> N1 ==> N2 -> N3 -> N4 ->N5
//                  ^
//                  |
//                  r
//
//          head =======> N2 -> N3 -> N4 ->N5
//          r -> N1
//----------------------------------------------------------------------
phone *remove(phone *head, phone *delete_node){

	phone *current_node = new phone;
	current_node = head;

	if (head == delete_node){ // case where the head is the node to delete
		head = delete_node->next; // assign the head to the 2nd node
		delete_node->next = NULL; // set the delete node ptr to null
		return head; // return the head
	}

	while (current_node->next != NULL){ // loop over list
		if (current_node->next == delete_node){ // case where the current node ptr is pointing to the node to delete
			current_node->next = delete_node->next; // set the current node ptr to the delete nodes next ptr
			delete_node->next = NULL; // set the delete node ptr to null
			return head;
		}
		current_node = current_node->next; // increment the current node
	}

	return NULL;

}

//----------------------------------------------------------------------
//                              deletePhone()
//----------------------------------------------------------------------
// Invokes searchPhone() to get a pointer to the node to be deleted.
// if found, invokes remove() to remove the node from the list.
// TODO: DEALLOCATE THE NODE (don't leave any garbage!!)
phone * deletePhone(phone * head)
{
	phone * p = searchPhone(head);		// search for node to be removed and deallocated
										// returns NULL if not found
	if (p != NULL)						// if a node was found
	{
		head = remove(head, p);			// remove the found node from the list
										// TODO: DEALLOCATE THE NODE HERE!!!
										// TODO: guarantee there is no Dangling Reference!!!
		cout << "Entry deleted.\n";
	}
	return head;						// head was possibly modifed, so return it
} // deletePhone()

//----------------------------------------------------------------------
//                              main()
//----------------------------------------------------------------------
int main()
{
	// variable declarations
	char choice;			// user's choice from the menu
	phone * head = NULL;	// head of the linked list, INITIALIZED EMPTY
	phone * p = NULL;		// points to a phone node as needed

	// repeat operations until user wants to exit
	do {
		// get user's choice (always capitalized, but could be an invalid option)
		choice = getChoice();

		// perform user's choice
		switch (choice)
		{
		case 'A':
			p = makeNewPhone();						// create and populate a new node
			head = append(head, p);					// add the new node to the list
			break;
		case 'D': head = deletePhone(head); break;	// delete a node, possibly resulting in a new head
		case 'S': p = searchPhone(head);    break;  // search for a node by first/last name.
		case 'P': printList(head);          break;  //    Here, the p returned  by searchPhone isn't
		case 'X': cout << "Good Bye!\n";    break;  //    needed, but we still need to "catch" it.
		default: cout << "Invalid entry! Try again.\n";   // take care of invalid entry here.
		}
	} while (choice != 'X');						// repeat until user enters 'X'

	return 0;
} // main()
