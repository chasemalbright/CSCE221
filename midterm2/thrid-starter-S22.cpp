#include <iostream>


struct Node {
	Node* next;
	int data;
};

// DO NOT modify anything above this line!!!

void print_third(Node* node, int count = 0){
    if (node != nullptr){
        if (count % 3 == 0){ // if divisible by 3 print 
            std::cout << node->data << " ";
            print_third(node->next, count + 1);
        } else {
            print_third(node->next, count + 1);
        }
    }
    return;
}

// End of Code - Below here will be ignored when compiling

int main() {

	// Initializes the head of the list
	Node *head = new Node();
	head->data = 0;

	// Adding a bunch of elements to the linked list
	Node *curr = head;
	for (int i = 1; i <= 19; i++){
		Node *temp = new Node();
		temp->data = i;
		curr->next = temp;
		curr = temp; 
	}

	// Calling your function
	print_third(head);
	std::cout << std::endl;

	// Frees the memory from the linked list
	curr = head;
	while (curr != nullptr){
		Node *next = curr->next;
		delete curr;
		curr = next;
	}

	return 0;

}
