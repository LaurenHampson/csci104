#ifndef ROTATE_BST_H
#define ROTATE_BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <vector>
#include "bst.h"


template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key,Value> // ask about this 
{
public:
	
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;


protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);

private:
		void transformHelper(Node<Key,Value>* root, Node<Key, Value>* goal, rotateBST& t2) const;

};



template<typename Key, typename Value>
void inOrderTraversalHelper(std::vector<Key>& list, Node<Key, Value>* node){
	
	   if(node->getLeft() != NULL) {
        inOrderTraversalHelper(list, node->getLeft());
    }
     list.push_back(node->getKey());
    if(node->getRight() != NULL) {
        inOrderTraversalHelper(list, node->getRight());
    }
}

template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const
{
	std::vector<Key> bstList;
	if(BinarySearchTree<Key,Value>::mRoot!= NULL)
		inOrderTraversalHelper(bstList, this->BinarySearchTree<Key,Value>::mRoot);
	std::vector<Key> rotList;
	if(t2.BinarySearchTree<Key,Value>::mRoot != NULL)
		inOrderTraversalHelper(rotList, t2.BinarySearchTree<Key,Value>::mRoot);
	if(bstList.size()!=rotList.size())
	{
		return false;
	}

	for(unsigned int i = 0; i < bstList.size(); i++)
	{
		if (bstList[i] != rotList[i])
		{
			return false;
		}
	}

	return true;


}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transformHelper(Node<Key,Value>* root, Node<Key, Value>* goal, rotateBST& t2) const
{
	if(root == NULL)
	{
		return;
	}
	while(root != goal)
	{
		t2.leftRotate(root);
	}

	transformHelper(root->getLeft(), goal->getLeft(), t2);

	transformHelper(root->getRight(), goal->getRight(), t2);
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
	if(sameKeys(t2) == false)
	{
		return;
	}
	else
	{
		while(t2.BinarySearchTree<Key,Value>::mRoot->getLeft()!= NULL)
		{
			t2.rightRotate(BinarySearchTree<Key,Value>::mRoot);
		}
		Node<Key,Value>* node = t2.BinarySearchTree<Key,Value>::mRoot->getRight();
			while(node!= NULL)
			{
				
				while(node->getLeft()!= NULL)
				{
					t2.rightRotate(node);
				}

				node = node->getRight();
			}

		while(BinarySearchTree<Key,Value>::mRoot != t2.BinarySearchTree<Key,Value>::mRoot)
		{
			t2.leftRotate(BinarySearchTree<Key,Value>::mRoot);
		}
	}

	Node<Key,Value>* root = t2.BinarySearchTree<Key,Value>::mRoot->getLeft();
	Node<Key,Value>* goal = BinarySearchTree<Key,Value>::mRoot->getLeft();

	transformHelper(root, goal, t2);

	root = t2.BinarySearchTree<Key,Value>::mRoot->getRight();
	goal = BinarySearchTree<Key,Value>::mRoot->getRight();

	transformHelper(root, goal, t2);



}

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
 {
		
	if (r->getRight() == NULL)
	{
		return;
	}

	Node<Key,Value>* temp = r->getRight();
  

    r ->setRight(temp->getLeft());

    if(temp->getLeft() != NULL){
      temp->getLeft()->setParent(r);
    }

    temp->setLeft(r);


    temp->setParent(r->getParent());
    r->setParent(temp);
    if(temp->getParent() == NULL)
    {
      BinarySearchTree<Key,Value>::mRoot = temp;
    } 
    else 
    {
      Node<Key,Value>* parent = temp->getParent();
      if(parent->getKey() < temp->getKey())
      {
        parent->setRight(temp);
      }
      else
      {
        parent->setLeft(temp);
      }

    }


}


template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{
	
	
	if (r->getLeft()==NULL)
	{
		return;
	}
	else
	{
		Node<Key, Value>* temp = r->getLeft();
		r->setLeft(temp->getRight());



		if (r->getLeft() != NULL)
		{
			r->getLeft()->setParent(r);
		}

		temp->setRight(r);

		temp->setParent(r->getParent());
		r->setParent(temp);

		if(temp->getParent() != NULL)
		{
			Node<Key, Value>* rent = temp->getParent();
			if(temp->getKey()< rent-> getKey())
			{
				rent->setLeft(temp);
			}
			else
			{
				rent->setRight(temp);
			}
		}
		else
		{
			BinarySearchTree<Key,Value>::mRoot = temp;
		}
		


		return;

		
	}
}






#endif