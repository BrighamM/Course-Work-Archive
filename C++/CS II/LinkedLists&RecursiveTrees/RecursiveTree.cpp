/*
This file contains an implementation of a
ordered binary tree class, and includes a
small driver program.

For the exam, individual functions in this
file will be removed, and you will need to
re-create the missing parts.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// a node for the tree
template <class T>
struct TreeNode{
	T data;
	TreeNode<T> * ltree;
	TreeNode<T> * rtree;
};

// ordered tree class specification
template <class T>
class Tree{
public:
	Tree();
	void Insert(T);
	void Delete(T);
	void Print();
	void PreOrderPrint();
	void PostOrderPrint();
	int  Size();
	int  Height();
	bool isInTree(T);

private:
	TreeNode<T> * RMinNode(TreeNode<T> *);
	bool RIsInTree(TreeNode<T> *, T);
	int  RSize(TreeNode<T> *);
	int  RHeight(TreeNode<T> *);
	void RPrint(TreeNode<T> *);
	void PreRPrint(TreeNode<T> *);
	void PostRPrint(TreeNode<T> *);
	TreeNode<T> * RInsert(TreeNode<T> *,T);
	TreeNode<T> * RDelete(TreeNode<T> *,T);
	TreeNode<T> * DeleteNode(TreeNode<T> *);
	TreeNode<T> * root;
};

// constructor
template <class T>
Tree<T>::Tree(){root=0;}

// call the function to
// recursively count all the nodes
template <class T>
int  Tree<T>::Size(){return RSize(root);}

// call the function to
// recursively determine the height of the tree
template <class T>
int  Tree<T>::Height(){return RHeight(root);}

// call the function to
// recursively determine if <target> is in the tree
template <class T>
bool Tree<T>::isInTree(T target){return RIsInTree(root,target);}

// call the function to
// recursively find a pointer to the min value
// node in the tree
template <class T>
TreeNode<T> * Tree<T>::RMinNode(TreeNode<T> * subRoot){
	if(!subRoot)return 0;
	if(!subRoot->ltree)return subRoot;
	return RMinNode(subRoot->ltree);
}

//recursive IsInTree function
template <class T>
bool Tree<T>::RIsInTree(TreeNode<T> * subRoot, T target){
	if(!subRoot)return false;
	if(subRoot->data==target)return true;
	else if(target<subRoot->data)return RIsInTree(subRoot->ltree,target);
	return RIsInTree(subRoot->rtree,target);
}

//recursive Size function
template <class T>
int  Tree<T>::RSize(TreeNode<T> * subRoot){
	if(!subRoot)return 0;
	return RSize(subRoot->ltree)+1+RSize(subRoot->rtree);
}

//recursive Height function
template <class T>
int  Tree<T>::RHeight(TreeNode<T> * subRoot){
	if(!subRoot)return 0;
	int r=RHeight(subRoot->rtree);
	int l=RHeight(subRoot->ltree);
	if(r>l)return r+1;
	else return l+1;
}

// to insert a node
// call the recursive function to do that
template <class T>
void Tree<T>::Insert(T newdata){ root = RInsert(root,newdata); }

// to delete a node
// call the recursive function to do that
template <class T>
void Tree<T>::Delete(T target){ root = RDelete(root,target); }

// to print the tree (in order print)
// call the recursive function to do that
template <class T>
void Tree<T>::Print(){ RPrint(root); }

// to print the tree (pre order print)
// call the recursive function to do that
template <class T>
void Tree<T>::PreOrderPrint(){ PreRPrint(root); }

// to print the tree (post order print)
// call the recursive function to do that
template <class T>
void Tree<T>::PostOrderPrint(){ PostRPrint(root); }

//recursive inOrder print
template <class T>
void Tree<T>::RPrint(TreeNode<T> * subRoot){
	if(!subRoot)return;
	RPrint(subRoot->ltree);
	cout<<subRoot->data<<endl;
	RPrint(subRoot->rtree);
}

//recursive preOrder print
template <class T>
void Tree<T>::PreRPrint(TreeNode<T> * subRoot){
	if(!subRoot)return;
	cout<<subRoot->data<<endl;
	PreRPrint(subRoot->ltree);
	PreRPrint(subRoot->rtree);
}

//recursive postOrder print
template <class T>
void Tree<T>::PostRPrint(TreeNode<T> * subRoot){
	if(!subRoot)return;
	PostRPrint(subRoot->ltree);
	PostRPrint(subRoot->rtree);
	cout<<subRoot->data<<endl;
}

//recursive insert function
//(yes, you may be asked to write this function)
template <class T>
TreeNode<T> * Tree<T>::RInsert(TreeNode<T> * subRoot, T newdata){
	if(!subRoot){
		TreeNode<T> * newNode = new TreeNode<T>;
		newNode->data = newdata;
		newNode->ltree = 0;
		newNode->rtree = 0;
		return newNode;
	}
	if(newdata<subRoot->data){
		subRoot->ltree = RInsert(subRoot->ltree, newdata);
	}else{
		subRoot->rtree = RInsert(subRoot->rtree, newdata);
	}
	return subRoot;
}


//delete a node from the tree
//(I won't ask you to re-create this on the exam)
template <class T>
TreeNode<T> * Tree<T>::DeleteNode(TreeNode<T> * subRoot){
	//case 1: no children
	if(!subRoot->ltree && !subRoot->rtree){
		delete subRoot;
		return 0;
	}
	//case 2: one child
	if(!subRoot->ltree){
		TreeNode<T> * returnNode = subRoot->rtree;
		delete subRoot;
		return returnNode;
	}
	if(!subRoot->rtree){
		TreeNode<T> * returnNode = subRoot->ltree;
		delete subRoot;
		return returnNode;
	}

	//case 3: two children
	TreeNode<T> * returnNode = subRoot->rtree;
	RMinNode(subRoot->rtree)->ltree=subRoot->ltree;			
	delete subRoot;
	return returnNode;
}

//recursive delete function
//(yes, you may be asked to write this function)
template <class T>
TreeNode<T> * Tree<T>::RDelete(TreeNode<T> * subRoot, T target){
	if(!subRoot)return subRoot;
	if(target==subRoot->data){
		subRoot=DeleteNode(subRoot);
		return subRoot;
	}
	if(target<subRoot->data){
		subRoot->ltree = RDelete(subRoot->ltree, target);
	}else{
		subRoot->rtree = RDelete(subRoot->rtree, target);
	}
	return subRoot;
}




int main(){
	vector <int> v;
	Tree <int> groot;
/*
	groot.Insert(42);
	groot.Insert(15);
	groot.Insert(6);
	groot.Insert(4);
	groot.Insert(3);
	groot.Insert(5);
	groot.Insert(19);
	groot.Insert(16);
	groot.Insert(25);
	groot.Insert(102);
	groot.Insert(88);
	groot.Insert(264);

	groot.Print();
	cout<<"===========\n";

	groot.Delete(264);
	groot.Print();
	cout<<"===========\n";

	groot.Delete(6);
	groot.Print();
	cout<<"===========\n";

	groot.Delete(19);
	groot.Print();
	cout<<"===========\n";

	groot.Delete(42);
	groot.Print();
	cout<<"===========\n";



*/
	srand(1972);
	for(int i=0;i<10000;++i)v.push_back(i);
	random_shuffle(v.begin(),v.end());	
	random_shuffle(v.begin(),v.end());	
	for(int i=0;i<10000;++i)groot.Insert(v[i]);
	cout<< "height: "<< groot.Height()<<endl;
	for(int i=0;i<10000000;++i){
		if(groot.isInTree(rand()%10000));
		else ;
	}

	return 0;
}


