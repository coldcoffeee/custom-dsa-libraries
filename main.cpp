#include<iostream>
#include"LinkedList.h"
#include<string>

int main()
{
	std::string A[] = {"Mano","y","Mano"};
	// int A[] = {1,2,3,2,1};
	// LinkedList<std::string> *l1 = new LinkedList<std::string>(A,3);
	LinkedList<std::string> l1(A,3);
	
	//aliter: LinkedList<std::string> l1(A,3); --> for static allocation
	
	// l1->printList();
	
	// l1->deleteKey("A");
	//l1->printList();
	
	/*
	std::cout<<l1->valueAtIndex(1)<<'\n';
	std::cout<<l1->valueAtIndex(2)<<'\n';
	std::cout<<l1->valueAtIndex(0)<<'\n';
	std::cout<<l1->valueAtIndex(-1)<<'\n';
	*/
	
	//l1->reverseList();
	
	// l1->rotateRight();
	// l1->rotateLeft();

	// l1->printList();

	LinkedList<std::string> list_x = l1;
	//list_x.reverseList();

	list_x.printList();

	std::cout<<list_x.isPalindrome()<<std::endl;

	// getchar();
	return 0;
}
