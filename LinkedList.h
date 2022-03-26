#include"NodeList.h"

/*

1. delete[] to delete an array of objects, delete to delete a single object.
 
2. Constructors can be called explicitly without assigning to any variable like so: 
 	int main()
	{
		LinkedList();				---> calling the constructor without assigning to a variable
							     this leads to creation of a temporary object which gets
							     destroyed instantaneously
	
		LinkedList object;					
		object.~LinkedList();			---> calling the destructor of the instance

		LinkedList().~LinkedList(); 		---> calling the destructor of the temporary object returned
							     by the LinkedList() constructor call.
							     Before getting destroyed immediately by the destructor,
							     the temp object is passed to this statement so the
							     .~LinkedList() part calls the destructor of this returned
							     temp variable.
							     So total of 1 Constructor call is made while 2 Destructor
							     calls are made.
	}

	This triggers creation of temporary object and the constructor is called, 
	then immediately after the destructor is called.

*/

template<class T>
class LinkedList{
	private:
		NodeList<T> *head;
		NodeList<T> *tail;
		LinkedList(NodeList<T> *head);

	public:
		int length;
		LinkedList(T A[],int n);
		LinkedList();
		void printList();
		void deleteKey(T key);
		void reverseList();
		void rotateRight();
		void rotateLeft();
		void operator =(const LinkedList<T> &orig_list);
		bool isPalindrome();
		T valueAtIndex(int index);
		~LinkedList()
		{
			if(this->head != nullptr){
				NodeList<T> *p = this->head;
				while(p)
				{
					head = head->next;
					delete p;				
					p = head;
				}
			}
		}
};

template<class T>
LinkedList<T>::LinkedList(NodeList<T> *head){
	this->head = new NodeList<T>;
	this->head->data = head->data;
	this->head->next = nullptr;

	NodeList<T> *p = this->head;
	NodeList<T> *q = head;
	q = q->next;
	while (q)
	{
		p->next = new NodeList<T>;
		p = p->next;
		p->data = q->data;
		p->next = nullptr;
		q = q->next;
	}
}

template<class T>
LinkedList<T>::LinkedList(){
	this->head = nullptr;
}

template<class T>
void LinkedList<T>::operator=(const LinkedList<T> &orig_list){
	if(this->head != nullptr)
		this->~LinkedList();
	this->head = new NodeList<T>;
	this->head->data = orig_list->head->data;
	this->head->next = nullptr;

	NodeList<T> *p = this->head;
	NodeList<T> *q = orig_list->head;

	while (q->next)
	{
		p->next = new NodeList<T>;
		p = p->next;
		p->data = q->data;
		q = q->next;
	}
	p->next = new NodeList<T>;
	p = p->next;
	p->data = q->data;
	p->next = nullptr;
}


template<class T>
LinkedList<T>::LinkedList(T A[],int n){
	this->head = new NodeList<T>;
	this->head->data = A[0];
	this->head->next = nullptr;
	NodeList<T> *p = this->head;
	for(int i=1;i<n;i++)
	{
		p->next = new NodeList<T>;
		p = p->next;
		p->data = A[i];
	}
	this->tail = p;
	p->next = nullptr;
	this->length = n;
}

#ifndef __IOSTREAM_H
#include <iostream>
#endif
template<class T>
void LinkedList<T>::printList(){
	if(this->head == nullptr)
		return;
	NodeList<T> *p = this->head;
	std::cout<<p->data<<" ";
	p = p->next;
	while(p)
	{
		std::cout<<"-> "<<p->data<<' ';
		p = p->next;
	}
	printf("\n");
}

template<class T>
void LinkedList<T>::deleteKey(T key)
{
	if(this->head == nullptr)
		return;
	NodeList<T> *previous,*curr = this->head;
	if(curr->data == key)
	{
		this->head = curr->next;
		delete curr;
		this->length--;
	}
	else
	{
		while(curr->data != key and curr != nullptr)
		{
			previous = curr;
			curr = curr->next;
		}
		if(curr == nullptr)
			return;
		if(curr->next ==nullptr)
			this->tail = previous;
		previous->next = curr->next;
		delete curr;
		this->length--;
	}
}
template<class T>
T LinkedList<T>::valueAtIndex(int index)
{
	if(this->head == nullptr)
		return;
	if(index >= this->length or index < 0)
	{
		std::cout<<"Index out of bounds for method valueAtIndex! Returned value at head!\n";
		return (this->head->data);
	}
	else
	{
		int i;
		NodeList<T> *p = this->head;
		for(i=0;i<index;i++)
			p = p->next;
		return p->data;
	}
}

template<class T>
void LinkedList<T>::reverseList()
{
	if(this->head == nullptr)
		return;
	NodeList<T> *p,*q,*r;

	q = this->head;
	r = q->next;
	p = nullptr;
	this->tail = this->head;

	while(r!=nullptr)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	this->head = q;
}
template<class T>
void LinkedList<T>::rotateRight()
{
	if(this->head == nullptr)
		return;
	NodeList<T> *p = head;
	while(p->next->next != nullptr)
		p = p->next;
	p->next->next = this->head;
	this->tail = p;
	this->head = p->next;
	p->next = nullptr;
}

template<class T>
void LinkedList<T>::rotateLeft()
{
	if(this->head == nullptr)
		return;
	this->tail->next = this->head;
	this->head = this->head->next;
	this->tail = this->tail->next;
	this->tail->next = nullptr;
}

template<class T>
bool LinkedList<T>::isPalindrome(){
	if(this->head == nullptr or this->head->next == nullptr)
		return true;
	
	//LinkedList<T> tempList = *this;

	NodeList<T> *slow = this->head;
	NodeList<T> *fast = this->head;

	while(fast->next)
	{
		fast = fast->next;
		if(fast->next){
			fast = fast->next;
			slow = slow->next;
		}
	}

	slow = slow->next;
	LinkedList<T> second_half(slow);
	second_half.reverseList();
	
	NodeList<T> *itr1 = this->head,*itr2 = second_half.head;

	while(itr2)
	{
		if(itr1->data != itr2->data)
			return false;
		itr1 = itr1->next;
		itr2 = itr2->next;
	}

	return true;
}