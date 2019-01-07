/*
This file contains an implementation of a
linked list class, a stack class, and 
queue class, and includes a small driver
program.

For the exam, individual functions in this
file will be removed, and you will need to
re-create the missing parts.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

//a node for the linked list
template <class T>
struct Node{
	T data;
	Node * next;
};

//linked list class specification
template <class T>
class LinkList{
public:
	LinkList();
	void insertFront(T newdata);
	void insertOrdered(T newdata);
	void insertBack(T newdata);
	void deleteFront();
	void deleteTarget(T target);
	void printList();
	T atFront();
	T atBack();

private:
	void recursivePrintList(Node<T> * head);
	Node<T> * recursiveInsert(Node<T> * head, T newdata);
	Node<T> * recursiveDeleteTarget(Node<T> * head, T target);
	Node<T> * insertLocalFront(Node<T> * head,T newdata);
	Node<T> * deleteLocalFront(Node<T> * head);
	Node<T> * head;
	Node<T> * tail;
};

// stack class specification and implementation
template <class T>
class Stack:private LinkList<T>{
public:
	void push(T newdata){this->insertFront(newdata);}
	T pop(){
		T retval;
		retval=this->atFront();
		this->deleteFront();
		return retval;
	}
};

// queue class specification and implementation
template <class T>
class Queue:private LinkList<T>{
public:
	void enqueue(T newdata){this->insertBack(newdata);}
	T dequeue(){
		T retval;
		retval=this->atFront();
		this->deleteFront();
		return retval;
	}
};


//constructor
template <class T>
LinkList<T>::LinkList(){
	head=0;
	tail=0;
}

// insert a new node at the back of the list
// (I won't ask you to re-create this one)
template <class T>
void LinkList<T>::insertBack(T newdata){
	if(!head){
		insertFront(newdata);
	}else{
		Node<T> * newnode = new Node<T>;
		newnode->data = newdata;
		newnode->next = 0;
		tail->next=newnode;
		tail = newnode;
	}
}

// insert a new node at the front of the list
template <class T>
void LinkList<T>::insertFront(T newdata){
	//call the private function that knows
	//where the head of the list is
	head=insertLocalFront(head,newdata);
}

// insert a new node in an ordered list
template <class T>
void LinkList<T>::insertOrdered(T newdata){
	//call the private recursive function
	head=recursiveInsert(head, newdata);
}

// remove the node at the front of the list
template <class T>
void LinkList<T>::deleteFront(){
	//call the private function that knows
	//where the head of the list is
	head=deleteLocalFront(head);
}

// search through the list to remove a node
// equal to <target>
template <class T>
void LinkList<T>::deleteTarget(T target){
	//call the private recursive function
	head=recursiveDeleteTarget(head, target);
}

// return the value at the front of the list
template <class T>
T LinkList<T>::atFront(){
	if(head==0)exit(0);
	return head->data;
}

// return the value at the back of the list
template <class T>
T LinkList<T>::atBack(){
	if(tail==0)exit(0);
	return tail->data;
}

// print all the values in the list
template <class T>
void LinkList<T>::printList(){
	//call the private recursive function
	recursivePrintList(head);
}

// recursively print all the values in the list
template <class T>
void LinkList<T>::recursivePrintList(Node<T> * head){
	if(head==0)return;
	cout<<head->data<<endl;
	recursivePrintList(head->next);
}

// recursive insert.  because the head pointer may
// change, the new (or old) value is returned
template <class T>
Node<T> * LinkList<T>::recursiveInsert(Node<T> * head, T newdata){
	if(!head || head->data >= newdata){
		head=insertLocalFront(head,newdata);
	}else{
		head->next=recursiveInsert(head->next,newdata);
	}
	return head;
}

// recursive delete.  because the head pointer may
// change, the new (or old) value is returned
template <class T>
Node<T> * LinkList<T>::recursiveDeleteTarget(Node<T> * head, T target){
	if(!head){
		 return head;
	}else if(head->data == target){
		head=deleteLocalFront(head);
	}else{
		head->next=recursiveDeleteTarget(head->next,target);
	}
	return head;
}

// put a new node at the front of the list
// (I won't ask you to re-create this one)
template <class T>
Node<T> * LinkList<T>::insertLocalFront(Node<T> * head,T newdata){
	Node<T> * newnode = new Node<T>;
	newnode->data = newdata;
	newnode->next = head;
	if(!this->tail)this->tail=newnode;
	if(!this->head)this->head=newnode;
	head = newnode;
	if(!head->next)tail=head;
	return head;
}

// remove the node at the front of the list
// (I won't ask you to re-create this one)
template <class T>
Node<T> * LinkList<T>::deleteLocalFront(Node<T> * head){
	if(head==0)return head;
	Node<T> * tempnode = head;
	head = head->next;
	delete tempnode;
	if(!head)tail=0;
	return head;
}

int main(){
	Queue<string> q;
	q.enqueue("how");
	q.enqueue("bout");
	q.enqueue("them");
	q.enqueue("cubbies");
	q.enqueue("Yeaaaaaahhhhhh");
	cout<<"=========\n";
	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;


	return 0;
}


