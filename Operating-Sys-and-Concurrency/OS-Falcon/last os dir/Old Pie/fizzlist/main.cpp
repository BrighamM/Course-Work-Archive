#include <string>
#include <iostream>

template <class T>
struct Node
{
	T data;
	Node* next;
};

template <class T>
struct LinkedList
{
public:
	LinkedList();

private:

	Node<T>* head;
	Node<T>* tail;


protected:


};



int main()
{

	std::cout << "Hello World!" << std::endl;



	return 0;
}
