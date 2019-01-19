#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H


#include <iostream>
#include <fstream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <vector>
#include "rotateBST.h"
#include "bst.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
private:
	Node<Key, Value>* getSmallestNode() const;
	Node<Key, Value>* getLargestNode() const;
	Node<Key, Value>* getSmallestLeafNode() const;
	Node<Key, Value>* getLargestLeafNode() const;
	Node<Key, Value>* finder(const Key& key) const;
	Node<Key, Value>* getPredecessor(Node<Key, Value>* node);
	Node<Key, Value>* getSuccessor(Node<Key, Value>* node);
	void swap(Node<Key, Value>* pred, Node<Key, Value>* node);
	void insertHelper(const std::pair<const Key, Value>& keyValuePair);
	Node<Key, Value>* removeHelper(const Key& key);




};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{
	this->BinarySearchTree<Key, Value>::mRoot = NULL;
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	this->BinarySearchTree<Key, Value>::insert(keyValuePair);
	Node<Key, Value>* node = this->SplayTree<Key, Value>::finder(keyValuePair.first);
	this->splay(node);
	return;

	
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	//is leaf splay parent, is not leaf, get predecessor, remove
	if(this->BinarySearchTree<Key,Value>::mRoot == nullptr)
	{
		return;
	}
	Node<Key, Value>* node = this->SplayTree<Key, Value>::finder(key);
	if(node == NULL)
	{
		return;
	}

	else if (node == this->BinarySearchTree<Key,Value>::mRoot)
	{
		this->BinarySearchTree<Key, Value>::remove(key);
		return;
	}

	else if(node->getKey() != key)
	{
		splay(node);
		return;
	}

	
	else if (node->getRight() == NULL && node->getLeft() == NULL)
	{
		Node<Key, Value>* parent = node->getParent();
		BinarySearchTree<Key,Value>::remove(key);
		splay(parent);
		return;
	}
	else if (node->getRight() != NULL && node->getLeft() == NULL)
	{
		Node<Key, Value>* parent = node->getParent();
		BinarySearchTree<Key,Value>::remove(key);
		splay(parent);
		return;
	}
	else if (node->getRight() == NULL && node->getLeft() != NULL)
	{
		Node<Key, Value>* parent = node->getParent();
		BinarySearchTree<Key,Value>::remove(key);
		splay(parent);
		return;
	}

	else
	{
		Node<Key, Value>* parent = this->SplayTree<Key, Value>::removeHelper(key);
		if (parent == NULL)
		{
			return;
		}
		if(parent == BinarySearchTree<Key, Value>::mRoot)
		{
			return;
		}
		splay(parent);
		return;
	}

	
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	if (this->BinarySearchTree<Key, Value>::mRoot == NULL)
	{
		typename SplayTree<Key, Value>::iterator it(nullptr);
		return it;
	}

	Node<Key, Value>* node = this->SplayTree<Key, Value>::finder(key);
	if(node->getKey() != key)
	{
		splay(node);
		return this->end();
		
	}

	else
	{
		
		splay(node);
		return typename SplayTree<Key, Value>::iterator(node);

	}
	
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	Node<Key,Value>* node = this->SplayTree<Key, Value>::getSmallestNode();
	if (node!= NULL) splay(node);
	return typename SplayTree<Key, Value>::iterator(node);
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	Node<Key,Value>* node = this->SplayTree<Key, Value>::getLargestNode();
	if (node!= NULL) splay(node);
	return typename SplayTree<Key, Value>::iterator(node);
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	Node<Key,Value>* node = this->SplayTree<Key, Value>::getSmallestLeafNode();
	SplayTree<Key, Value>::remove(node->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	Node<Key,Value>* node = this->SplayTree<Key, Value>::getLargestLeafNode();
	SplayTree<Key, Value>::remove(node->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	if (r == this->BinarySearchTree<Key,Value>::mRoot)
	{
		return;
	}

	
	else if(r->getParent() == this->BinarySearchTree<Key,Value>::mRoot)
	{
		if (r == r->getParent()->getLeft())
		{
			this->rightRotate(this->BinarySearchTree<Key,Value>::mRoot);
		}
		else
		{
			this->leftRotate(this->BinarySearchTree<Key,Value>::mRoot);
		}

	}

	else
	{
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* grand = parent->getParent();

		if (r == parent->getLeft() && parent == grand->getLeft())
		{
			this->rightRotate(grand);
			this->rightRotate(parent);
		}

		else if(r == parent->getRight() && parent==grand->getRight())
		{
			this->leftRotate(grand);
			this->leftRotate(parent);
		}

		else if(r == parent->getRight() && parent == grand->getLeft())
		{
			this->leftRotate(parent);
			this->rightRotate(grand);
		}

		else if(r == parent->getLeft() && parent == grand->getRight())
		{
			this->rightRotate(parent);
			this->leftRotate(grand);
		}

		splay(r);
	}
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getSmallestNode() const
{
	if(this->BinarySearchTree<Key,Value>::mRoot == NULL)
	{
	
		return NULL;
	}
	Node<Key, Value>* node = BinarySearchTree<Key,Value>::mRoot;

	while(node->getLeft()!=nullptr)
	{
		node = node->getLeft();
	}

	return node;


}  

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getLargestNode() const
{
	if(this->BinarySearchTree<Key,Value>::mRoot == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* node = BinarySearchTree<Key,Value>::mRoot;

	while(node->getRight()!=nullptr)
	{
		node = node->getRight();
	}

	return node;


}  

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getSmallestLeafNode() const
{
	if(this->BinarySearchTree<Key,Value>::mRoot == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* node = BinarySearchTree<Key,Value>::mRoot;

	while(node->getLeft()!=nullptr)
	{
		node = node->getLeft();
	}

	if(node->getLeft() == NULL && node->getRight() == NULL)
	{
		return node;
	}

	else
	{
		while(node->getLeft()!= NULL || node->getRight() != NULL)
		{
			while(node->getLeft()!=NULL)
			{
				node = node->getLeft();
			}

			while(node->getRight()!= NULL)
			{
				node = node->getRight();
				if (node->getLeft() != NULL)
				{
					break;
				}
			}

			
		}

	}

	return node;


}  

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getLargestLeafNode() const
{
	if(this->BinarySearchTree<Key,Value>::mRoot == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* node = BinarySearchTree<Key,Value>::mRoot;

	while(node->getRight()!=nullptr)
	{
		node = node->getRight();
	}

	while(node->getLeft()!= NULL || node->getRight() != NULL)
	{
		while(node->getRight()!=NULL)
		{
			node = node->getRight();
		}
		while(node->getLeft()!= NULL)
		{
			node = node->getLeft();
				if (node->getRight() != NULL)
				{
					break;
				}
		}

		
	}
	return node;


}  

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::finder(const Key& key) const 
{
	if ( this->BinarySearchTree<Key, Value>::mRoot == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* temp = this->BinarySearchTree<Key, Value>::mRoot;
	// if (temp->getRight() == NULL && temp->getLeft() == NULL && temp!=NULL)
	// {
	// 	return this->BinarySearchTree<Key, Value>::mRoot;
	// }
	if (temp == NULL)
	{
		return NULL;
	}
	while(temp)
	{
		

		if (key < temp->getKey())// && temp != NULL)
		{ 
			if (temp->getLeft() == NULL  && temp != NULL)
			{
				return temp;
			}
			temp = temp->getLeft();

		}
		else if( key > temp->getKey())// && temp != NULL)
		{
			if(temp->getRight() == NULL && temp != NULL)
			{
				return temp;
			}

			temp = temp->getRight();
		}

		else if (key == temp->getKey() && temp != NULL)
		{
			return temp;
		}

	}

	return NULL; 
}

template<typename Key, typename Value>
void inOrderTraversal(std::vector<Key>& list, Node<Key, Value>* node){
	
	if (node == NULL)
	{
		return;
	}
	 if(node->getLeft() != NULL) {
        inOrderTraversal(list, node->getLeft());
    }
     list.push_back(node->getKey());
    if(node->getRight() != NULL) {
        inOrderTraversal(list, node->getRight());
    }
}

template<typename Key, typename Value>
void revOrderTraversal(std::vector<Key>& list, Node<Key, Value>* node){
	// TODO
	// implement in order
	if (node == NULL)
	{
		return;
	}
	 if(node->getRight() != NULL) {
        revOrderTraversal(list, node->getRight());
    }
     list.push_back(node->getKey());
    if(node->getLeft() != NULL) {
        revOrderTraversal(list, node->getLeft());
    }
}

template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key,Value>::getPredecessor(Node<Key, Value>* node)
{

	std::vector<Key> list;


	
	inOrderTraversal(list, node);

	
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i] == node->getKey() && i!=0)
		{
			return BinarySearchTree<Key, Value>::internalFind(list[i-1]);
		}
	}

	 return BinarySearchTree<Key, Value>::internalFind(list[0]);

}

template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key,Value>::getSuccessor(Node<Key, Value>* node)
{

	std::vector<Key> list;


	
	revOrderTraversal(list, node);

	
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i] == node->getKey() && i!=0)
		{
			return BinarySearchTree<Key, Value>::internalFind(list[i-1]);
		}
	}

	 return BinarySearchTree<Key, Value>::internalFind(list[0]);

}

template<typename Key, typename Value>
void SplayTree<Key, Value>::insertHelper(const std::pair<const Key, Value>& keyValuePair)
{

	Node<Key, Value>* prev = this->BinarySearchTree<Key, Value>::mRoot;
	Node<Key, Value>* curr = this->BinarySearchTree<Key, Value>::mRoot;

		while(curr)
		{
			
				if (curr->getKey() > keyValuePair.first)
				{
					prev = curr;
					curr = prev->getLeft();
					
				}
				else 
				{
					prev = curr;
					curr = prev->getRight();
									
				}	
	
		}


		if(prev->getKey() > keyValuePair.first)
		{
			prev->setLeft(new Node<Key,Value>(keyValuePair.first,keyValuePair.second, prev));
			prev->getLeft()->setParent(prev);
			prev->getLeft()->setRight(NULL);
			prev->getLeft()->setLeft(NULL);
			splay(prev->getLeft());
			
		}
		else 
		{
			prev->setRight(new Node<Key,Value>(keyValuePair.first,keyValuePair.second, prev));
			prev->getRight()->setParent(prev);
			prev->getRight()->setRight(NULL);
			prev->getRight()->setLeft(NULL);
			splay(prev->getRight());
			
		}


		

		return;


	
		
}
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::removeHelper(const Key& key)
{
	// TODO
	//see if key existss

	Node<Key, Value>* temp = BinarySearchTree<Key, Value>::internalFind(key);
	if (temp == NULL)
	{
		return NULL;
	}
	if (temp == this->BinarySearchTree<Key, Value>::mRoot)
	{
		BinarySearchTree<Key, Value>::remove(key);
		return NULL;
	}
	
	Node<Key, Value>* pred = BinarySearchTree<Key,Value>::mRoot;
	Node<Key, Value>* tempKey = SplayTree<Key, Value>::getPredecessor(temp);


	if (tempKey->getKey() == temp->getKey())
	{
		pred = NULL;
	}

	else
	{
	 	pred = tempKey;
	}

	if (temp->getRight() != nullptr && temp->getLeft() != nullptr)
	{

			if( temp != BinarySearchTree<Key, Value>::mRoot)
			{
				if(pred->getLeft()==NULL && pred->getRight()==NULL)
				{
					pred->getParent()->setRight(nullptr);
				}
				else if(pred->getLeft()!=NULL && pred->getRight()==NULL)
				{
					if(pred->getParent() == temp)
					{

						pred->setRight(pred->getParent()->getLeft());
						pred->getParent()->getLeft()->setParent(pred);
						pred->getParent()->setLeft(NULL);
						//pred->setHeight(temp->getHeight());
						pred->setParent(nullptr);
						BinarySearchTree<Key,Value>::mRoot->setParent(nullptr);
						BinarySearchTree<Key,Value>::mRoot = pred;


						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return pred;
					}
					else
					{
						pred->getParent()->setRight(pred->getLeft());
						pred->getLeft()->setParent(pred->getParent());
					}
				}
				else if(pred->getLeft()==NULL && pred->getRight()!=NULL)
				{
					if(pred->getParent() == temp)
					{

						pred->setLeft(pred->getParent()->getRight());
						pred->getParent()->getRight()->setParent(pred);
						pred->getParent()->setRight(NULL);
						pred->setParent(nullptr);
						//pred->setHeight(temp->getHeight());
						BinarySearchTree<Key,Value>::mRoot->setParent(nullptr);
						BinarySearchTree<Key,Value>::mRoot = pred;

						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return pred;
					}
					else
					{
						pred->getParent()->setRight(pred->getRight());
						pred->getRight()->setParent(pred->getParent());
					}
				}


			
		}
		

		
		if (pred->getLeft() == NULL && pred->getRight() == NULL)
		{

			if(pred->getParent()->getKey() > pred->getKey())
			{
				pred->getParent()->setLeft(NULL);
			}

			else
			{
				pred->getParent()->setRight(NULL);
			}


			pred->setParent(temp->getParent());

			
				pred->setLeft(temp->getLeft());
				if(pred->getLeft()!= NULL) pred->getLeft()->setParent(pred);
			
			pred->setRight(temp->getRight());
				if(pred->getRight()!= NULL)pred->getRight()->setParent(pred);
			//pred->setHeight(temp->getHeight());

			if (pred->getKey()<temp->getKey())
			{
				pred->getParent()->setLeft(pred);
			}

			else
			{
				pred->getParent()->setRight(pred);
			}
		//	pred->setHeight(temp->getHeight());
			//temp->setHeight(0);
			temp->setParent(NULL);
			temp->setLeft(NULL);
			temp->setRight(NULL);
			delete temp;
			return pred;
		}

		else if(pred->getLeft()!= NULL && pred->getRight() == NULL)
		{
			if (pred->getKey()>pred->getParent()->getKey())
			{
				pred->getParent()->setRight(pred->getLeft());
			}
			else
			{
				pred->getParent()->setLeft(pred->getLeft());
			}

			pred->getLeft()->setParent(pred->getParent());

			pred->setParent(temp->getParent());

			
				pred->setLeft(temp->getLeft());
			pred->getLeft()->setParent(pred);
			pred->setRight(temp->getRight());
			pred->getRight()->setParent(pred);



			if (pred->getKey()<temp->getParent()->getKey())
			{
				pred->getParent()->setLeft(pred);
			}

			else
			{
				pred->getParent()->setRight(pred);
			}
		
			temp->setParent(NULL);
			temp->setLeft(NULL);
			temp->setRight(NULL);
			delete temp;
			return pred;
		}

		else if(pred->getRight()!= NULL && pred->getLeft()== NULL)
		{
			if (pred->getKey()>pred->getParent()->getKey())
			{
				pred->getParent()->setRight(pred->getRight());
			}
			else
			{
				pred->getParent()->setLeft(pred->getRight());
			}

			pred->getRight()->setParent(pred->getParent());


			pred->setParent(temp->getParent());

				
				pred->setLeft(temp->getLeft());
				pred->getLeft()->setParent(pred);
			pred->setRight(temp->getRight());
							pred->getRight()->setParent(pred);


			if (pred->getKey()<temp->getParent()->getKey())
			{
				pred->getParent()->setLeft(pred);
			}

			else
			{
				pred->getParent()->setRight(pred);
			}

			temp->setParent(NULL);
			temp->setLeft(NULL);
			temp->setRight(NULL);
			delete temp;
			return pred;
		}
		
}
		

	return nullptr;
	 
}



#endif