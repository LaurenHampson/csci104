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
	
	// virtual ~rotateBST();
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;


protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
//			Node<Key, Value>* mRoot;

private:
		void transformHelper(Node<Key,Value>* root, Node<Key, Value>* goal, rotateBST& t2) const;

};


// template<typename Key, typename Value>
// rotateBST<Key, Value>::~rotateBST()
// {
// 	this->clear();
// }

template<typename Key, typename Value>
void inOrderTraversalHelper(std::vector<Key>& list, Node<Key, Value>* node){
	// TODO
	// implement in order
	   if(node->getLeft() != NULL) {
        inOrderTraversalHelper(list, node->getLeft());
    }
     list.push_back(node->getKey());
    if(node->getRight() != NULL) {
        inOrderTraversalHelper(list, node->getRight());
    }
    //list.push_back(node->val);
}
// template<typename Key, typename Value>
// int getMaxHeightRot(Node<Key, Value>* node)
// {
// 	int rHeight = 0;
// 	int lHeight = 0;

// 	if(node->getRight() != NULL)
// 	{
// 		rHeight = node->getRight()->getHeight();
// 	}

// 	if(node->getLeft() != NULL)
// 	{
// 		lHeight = node->getLeft()->getHeight();
// 	}

// 	if (rHeight >= lHeight)
// 	{
// 		return rHeight;
// 	}
// 	else 
// 	{
// 		return lHeight;
// 	}
// }
// template<typename Key, typename Value>
// void heightUpdateRot(Node<Key, Value>* node, int h)
// {
// 	node->setHeight(h);

// 	Node<Key, Value>* temp = node->getParent();
// 	while(temp != NULL)
// 	{
// 		temp->setHeight(getMaxHeightRot(temp)+1);
// 		temp = temp->getParent();
// 	}
// }

//make sure that it is updating the root correctly

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




	//Recursively do rotations on the left child 
	//and the right child until they match the node at that position of this.
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
	
	// // check if root
	//if root parent = NULL set new root
	if (r->getLeft()==NULL)
	{
		return;
	}
	else
	{
		//heightUpdateRot(r, r->getParent()->getHeight());
		Node<Key, Value>* temp = r->getLeft();
		r->setLeft(temp->getRight());


		//Node<Key, Value>* pred = NULL;

		if (r->getLeft() != NULL)
		{
			r->getLeft()->setParent(r);
			//pred = r->getRight();
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
			//figure out how to do this
		}
		


		return;

		
	}
}






#endif