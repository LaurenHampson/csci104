#ifndef CACHE_LRU_H
#define CACHE_LRU_H


#include <iostream>
#include <fstream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <stdexcept>
//#include <exception>
#include "rotateBST.h"
#include "bst.h"
#include "splayTree.h"


template <typename Key, typename Value>
class cacheLRU : public SplayTree<Key, Value>
{
public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);

protected:
private:
	int capacity_;
	Node<Key, Value>* getLeafNode();
	void insertHelp(const std::pair<const Key, Value>& keyValuePair);//, std::ofstream& output);
	void splay(Node<Key, Value> *r);//, std::ofstream& output);
	Node<Key, Value>* finde(const Key& key) const ;
	
	void inOrderTraversal(Node<Key, Value>* node);
	//std::deque<std::string> word;
	int size;



}; 

template <typename Key, typename Value>
cacheLRU<Key,Value>::cacheLRU(int capacity)
{
		this->BinarySearchTree<Key, Value>::mRoot = NULL;

	capacity_ = capacity;
	size = 0;


}
template <typename Key, typename Value>
cacheLRU<Key,Value>::~cacheLRU()
{
	
}

template <typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key)
{
	

	if(BinarySearchTree<Key,Value>::internalFind(key) == NULL) {
		std::cout << "logic_error" << std::endl;
          throw(std::logic_error("Invalid Key"));
        }
      
     else
     {
     	Node<Key, Value>* node = BinarySearchTree<Key, Value>::internalFind(key);
    	std::pair<const Key, Value> keyValuePair = std::make_pair(node->getKey(), node->getValue());
    	cacheLRU<Key, Value>::splay(node);//, outputGet);
    	return keyValuePair;	
     }
     
}
template<typename Key, typename Value>
void cacheLRU<Key, Value>::inOrderTraversal(Node<Key, Value>* node){
	if (node == NULL)
	{
		return;
	}
	 if(node->getLeft() != NULL) {
        inOrderTraversal(node->getLeft());
    }
     size++;//list.push_back(node->getKey());
    if(node->getRight() != NULL) {
        inOrderTraversal(node->getRight());
    }
    
}

template<typename Key, typename Value>
Node<Key, Value>* cacheLRU<Key, Value>::getLeafNode() 
{
	if (BinarySearchTree<Key, Value>::mRoot == NULL)
	{
		return NULL;
	}

	Node<Key, Value>* node = BinarySearchTree<Key,Value>::mRoot;

	while(node->getLeft()!=nullptr)
	{
		node = node->getLeft();
	}

	while(node->getLeft()!= NULL && node->getRight() != NULL)
	{
		while(node->getRight()!= NULL)
		{
			node = node->getRight();
		}
		if (node->getLeft() == NULL && node->getRight()==NULL)
		{
			return node;
		}
		while(node->getLeft()!=NULL)
		{
			node = node->getLeft();
		}
	}

	

	return node;


}  

template <typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair)
{
	if(this->BinarySearchTree<Key, Value>::mRoot == NULL)
	{
		//word.push_back(keyValuePair.first);
		size++;
		insertHelp(keyValuePair);
		
		return;

	}

	if(this->BinarySearchTree<Key,Value>::internalFind(keyValuePair.first) != NULL)
	{
		
		Node<Key, Value>* node = this->cacheLRU<Key, Value>::finde(keyValuePair.first);
		this->cacheLRU<Key, Value>::splay(node);//, output);
		return;
	}
		



	if (size == capacity_)
	{
			Node<Key, Value>* node = this->getLeafNode();
		
			BinarySearchTree<Key, Value>::remove(node->getKey());
			
			size --;

	}

	
	cacheLRU<Key, Value>::insertHelp(keyValuePair);
	size++;
	
	return;

}

template <typename Key, typename Value>
void cacheLRU<Key, Value>::insertHelp(const std::pair<const Key, Value>& keyValuePair)//, std::ofstream& output)
{
	this->BinarySearchTree<Key, Value>::insert(keyValuePair);
	Node<Key, Value>* node = this->cacheLRU<Key, Value>::finde(keyValuePair.first);
	this->cacheLRU<Key, Value>::splay(node);//, output);
	return;
	
}


template <typename Key, typename Value>
void cacheLRU<Key, Value>::splay(Node<Key, Value> *r)//, std::ofstream& output)
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
			
			//output << "Right " << std::endl;
		}
		else
		{
			this->leftRotate(this->BinarySearchTree<Key,Value>::mRoot);

	//						output << "Left " << std::endl;

		}

	}

	else
	{
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* grand = parent->getParent();

		if (r == parent->getLeft() && parent == grand->getLeft())
		{
			this->rightRotate(grand);

				//		output << "Right " << std::endl;

			this->rightRotate(parent);

					//	output << "Right " << std::endl;

		}

		else if(r == parent->getRight() && parent==grand->getRight())
		{
			this->leftRotate(grand);
			//						output << "Left " << std::endl;

			this->leftRotate(parent);
						

		}

		else if(r == parent->getRight() && parent == grand->getLeft())
		{
			this->leftRotate(parent);
						//			output << "Left " << std::endl;

			this->rightRotate(grand);

//						output << "Right " << std::endl;

		}

		else if(r == parent->getLeft() && parent == grand->getRight())
		{
			this->rightRotate(parent);

					//	output << "Right " << std::endl;

			this->leftRotate(grand);
						//			output << "Left " << std::endl;

		}

		cacheLRU<Key, Value>::splay(r);//, output);
	}
}


template<typename Key, typename Value>
Node<Key, Value>* cacheLRU<Key, Value>::finde(const Key& key) const 
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

#endif