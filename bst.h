#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <vector>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(nullptr)
	, mRight(nullptr)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	private:
		Node<Key,Value>* getPredecessor(Node<Key, Value>* node);
		void heightUpdate(Node<Key, Value>* node, int h);
	
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to nullptr.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(nullptr)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != nullptr)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != nullptr)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == nullptr)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != nullptr && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to nullptr.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	// EDITED
	this->clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(nullptr);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
//isLeaf**************
// template<typename Key, typename Value>
// bool BinarySearchTree<Key,Value>::leafer(Node<Key,Value>* node)
// {
// 	if (node->getRight() == NULL && node->getLeft() == NULL)
// 	{
// 		return true;
// 	}

	
// 	else //if (node->getRight() != NULL && node->getLeft() != NULL)
// 	{
// 		return false;
// 	}
// }

template<typename Key, typename Value>
int getMaxHeight(Node<Key, Value>* node)
{
	int rHeight = 0;
	int lHeight = 0;

	if(node->getRight() != NULL)
	{
		rHeight = node->getRight()->getHeight();
	}

	if(node->getLeft() != NULL)
	{
		lHeight = node->getLeft()->getHeight();
	}

	if (rHeight >= lHeight)
	{
		return rHeight;
	}
	else 
	{
		return lHeight;
	}
}
template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::heightUpdate(Node<Key, Value>* node, int h)
{
	node->setHeight(h);

	Node<Key, Value>* temp = node->getParent();
	while(temp != NULL)
	{
		temp->setHeight(getMaxHeight(temp)+1);
		temp = temp->getParent();
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// EDITED
	if(mRoot == nullptr)
	{
		return 0;
	}
	else
	{
		return mRoot->getHeight();
	}
}




/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	// EDITED
	return isBalance(mRoot);

}

template<typename Key, typename Value>
bool isBalance(Node<Key, Value>* node_)
{
	if (node_ == nullptr)
	{
		return true;
	}
	
	else if (isBalance(node_->getLeft()) == false)
	{
		return false;
	}	
	else if (isBalance(node_->getRight()) == false)
	{
		return false;
	}
	else
	{
		if ((node_->getLeft()) == nullptr && (node_->getRight()) == nullptr)
		{
			return true;
		}
		else if((node_->getLeft()) == nullptr)
		{
			return ((node_->getRight())->getHeight()<=1);
		}

		else if ((node_->getRight()) == nullptr)
		{
			return ((node_->getLeft())->getHeight()<=1);
			/* code */
		}

		int x = abs((node_->getLeft())->getHeight() - (node_->getRight())->getHeight());

		return (x <= 1);
	}
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
/////*******************************ADD AN UPDATE FOR HEIGHT FOR INSERT IN TREE AND INSERT



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
	if (mRoot == nullptr)
	{
		//Node<Key, Value>* temp = node;
		
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);

		//delete temp;
	
		return;
	}
	
	else
	{
		Node<Key, Value>* prev = mRoot;
		Node<Key, Value>* curr = mRoot;

		if (prev->getKey() > keyValuePair.first)
		{
			curr = prev->getLeft();
			
		}
		else if (prev->getKey() < keyValuePair.first )
		{
			curr = prev->getRight();
		
		}

		else if(prev->getKey() == keyValuePair.first)
		{
					
			return;
		}

			while(curr != nullptr && (mRoot->getKey() != keyValuePair.first))
			{
				prev = curr;
				if(curr->getKey() == keyValuePair.first)
				{
					return;
				}
				else
				{
					if (prev->getKey() > keyValuePair.first)
					{
						curr = prev->getLeft();
						
					}
					else if (prev->getKey() < keyValuePair.first )
					{
						curr = prev->getRight();
					
					}	
				}
			}


		

			if(prev->getKey() > keyValuePair.first)
			{
				//Node<Key, Value>* node = ;
				prev->setLeft(new Node<Key,Value>(keyValuePair.first,keyValuePair.second, prev));
				prev->getLeft()->setParent(prev);
				prev->getLeft()->setRight(NULL);
				prev->getLeft()->setLeft(NULL);
				//heightUpdate(prev->getLeft(), 1);
				
			}
			else if(prev->getKey() < keyValuePair.first)
			{
				//Node<Key, Value>* node = new Node<Key,Value>(keyValuePair.first,keyValuePair.second, prev);
				prev->setRight(new Node<Key,Value>(keyValuePair.first,keyValuePair.second, prev));
				prev->getRight()->setParent(prev);
				prev->getRight()->setRight(NULL);
				prev->getRight()->setLeft(NULL);
				//node->setParent(prev);
				//heightUpdate(prev->getRight(), 1);
			}


			

		//	delete curr;
			return;


	}
		
}


template<typename Key, typename Value>
void inOrdTraversalHelper(std::vector<Key>& list, Node<Key, Value>* node){
	// TODO
	// implement in order
	if (node == NULL)
	{
		return;
	}
	 if(node->getLeft() != NULL) {
        inOrdTraversalHelper(list, node->getLeft());
    }
     list.push_back(node->getKey());
    if(node->getRight() != NULL) {
        inOrdTraversalHelper(list, node->getRight());
    }
    //list.push_back(node->val);
}


template<typename Key, typename Value>
Node<Key,Value>* BinarySearchTree<Key,Value>::getPredecessor(Node<Key, Value>* node)
{

	std::vector<Key> list;
	//list.push_back(nullptr);


	
	inOrdTraversalHelper(list, node);

	
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i] == node->getKey() && i!=0)
		{
			return internalFind(list[i-1]);
		}
	}

	 return internalFind(list[0]);

}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
	//see if key existss

	Node<Key, Value>* temp = internalFind(key);
	if (temp == nullptr)
	{
		return;
	}
//no children

	

	if (temp->getRight() == nullptr && temp->getLeft() == nullptr)
	{
		if(temp == mRoot)
		{
			//heightUpdate(temp, 0);
			delete temp;
			mRoot = nullptr;
			//heightUpdate(temp, (temp->getHeight()-1));
			//mRoot->setHeight(0);
			return;
		}

		else if (temp->getParent()->getKey()> key)
		{
		//	heightUpdate(temp, 0);
			temp->getParent()->setLeft(nullptr);
			temp->setParent(nullptr);
			temp->setLeft(nullptr);
			temp->setRight(nullptr);
			//heightUpdate(temp, 0);
			delete temp;
			return;
		}
		else
		{

			//heightUpdate(temp, 0);
			temp->getParent()->setRight(nullptr);
			temp->setParent(nullptr);
			temp->setLeft(nullptr);
			temp->setRight(nullptr);
			//heightUpdate(temp, 0);
			delete temp;
			return;
		}
		return;
	}

//one child
	
	 	
	

	if (temp->getRight() == nullptr && temp->getLeft() != nullptr)
	{
		//heightUpdate(temp, (temp->getHeight()-1));
		if(temp == mRoot)
		{
				mRoot = temp->getLeft();
				mRoot->setParent(nullptr);
					//mRoot->setRight(nullptr);
				temp->setLeft(nullptr);
				temp->setRight(nullptr);
				temp->setParent(nullptr);
			
			delete temp;
			return;
		}

		Node<Key, Value>* rent = temp->getParent();
		temp->getLeft()->setParent(rent);
		if (rent->getKey()> temp->getKey())
		{
				rent->setLeft(temp->getLeft());
		}
		else
		{
				rent->setRight(temp->getLeft());
		}

		temp->setLeft(nullptr);
				temp->setRight(nullptr);
				temp->setParent(nullptr);
	
		delete temp;
		return;
	}

	
	if (temp->getRight() != nullptr && temp->getLeft() == nullptr)
	{
		//heightUpdate(temp, (temp->getHeight()-1));

			if(temp == mRoot)
		{
				Node<Key, Value>* rent = nullptr;
				mRoot = temp->getRight();
				//mRoot->setRight(nullptr);
				mRoot->setParent(rent);
				temp->setLeft(nullptr);
				temp->setRight(nullptr);
				temp->setParent(nullptr);
			
			delete temp;
			return;
		}
		Node<Key, Value>* rent = temp->getParent();
		temp->getRight()->setParent(rent);

	
		
		if (rent->getKey()> temp->getKey())

		{

				rent->setLeft(temp->getRight());

		}

		else

		{

			rent->setRight(temp->getRight());



		}

		temp->setLeft(nullptr);
				temp->setRight(nullptr);
				temp->setParent(nullptr);
		delete temp;

		return;



	}

	Node<Key, Value>* pred = mRoot;
	Node<Key, Value>* tempKey = getPredecessor(temp);

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
		//heightUpdate(pred,pred->getHeight()-1);

		if(temp == mRoot)
		{
			
			if(pred->getParent()->getKey() > pred->getKey())
			{
				if(pred->getLeft()==NULL && pred->getRight()==NULL)
				{
					

					pred->getParent()->setLeft(nullptr);
				}
				else if(pred->getLeft()!=NULL && pred->getRight()==NULL)
				{
					if(pred->getParent() == temp)
					{

						pred->setRight(pred->getParent()->getRight());
						pred->getParent()->getRight()->setParent(pred);
						pred->getParent()->setRight(NULL);
						//pred->setHeight(temp->getHeight());
						
						pred->setParent(nullptr);
						mRoot->setParent(nullptr);
						mRoot = pred;

						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return;
					}
					else
					{
						pred->getParent()->setLeft(pred->getLeft());
						pred->getLeft()->setParent(pred->getParent());
					}
				}
				else if(pred->getLeft()==NULL && pred->getRight()!=NULL)
				{
					if(pred->getParent() == temp)
					{


						pred->setLeft(pred->getParent()->getLeft());
						pred->getParent()->getLeft()->setParent(pred);
						pred->getParent()->setLeft(NULL);
						//pred->setHeight(temp->getHeight());
					
						pred->setParent(nullptr);
						mRoot->setParent(nullptr);
						mRoot = pred;

						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return;
					}
					else
					{
						pred->getParent()->setLeft(pred->getRight());
						pred->getRight()->setParent(pred->getParent());
					}
				}
				// else
				// {

				// }
			}
			else
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
						mRoot->setParent(nullptr);
						mRoot = pred;


						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return;
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
						mRoot->setParent(nullptr);
						mRoot = pred;

						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setParent(nullptr);
						delete temp;
						return;
					}
					else
					{
						pred->getParent()->setRight(pred->getRight());
						pred->getRight()->setParent(pred->getParent());
					}
				}


			
			}

			pred->setParent(nullptr);
			pred->setLeft(temp->getLeft());
				if(pred->getLeft()!= NULL) pred->getLeft()->setParent(pred);
			
			pred->setRight(temp->getRight());
				if(pred->getRight()!= NULL)pred->getRight()->setParent(pred);
		//	pred->setHeight(temp->getHeight());
			//heightUpdate(mRoot, mRoot->getHeight()-1)
				//mRoot->setLeft(pred->getLeft());
				//temp->getRight()->setParent(mRoot);
				mRoot->setParent(nullptr);
						mRoot = pred;
			//heightUpdate(temp, temp->getHeight());

			temp->setLeft(nullptr);
				temp->setRight(nullptr);
				temp->setParent(nullptr);
			delete temp;
			return;
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
			return;
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

//			pred->setHeight(temp->getHeight());

			if (pred->getKey()<temp->getParent()->getKey())
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
			return;
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

		//	pred->setHeight(temp->getHeight());

			if (pred->getKey()<temp->getParent()->getKey())
			{
				pred->getParent()->setLeft(pred);
			}

			else
			{
				pred->getParent()->setRight(pred);
			}

		//	pred->setHeight(temp->getHeight());
		//	temp->setHeight(0);
			temp->setParent(NULL);
			temp->setLeft(NULL);
			temp->setRight(NULL);
			delete temp;
			return;
		}
		
}
		

	return;
	 
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	clearHelper(mRoot);	
	mRoot = nullptr;
}
template<typename Key, typename Value>
void clearHelper(Node<Key, Value>* node)
{
	if(node!= NULL)
	{
		clearHelper(node->getLeft());
		clearHelper(node->getRight());
		node->setParent(nullptr);
	    node->setRight(nullptr);
	    node->setLeft(nullptr);

		delete node;
	}
	
}
/**
* A helper function to find the smallest node in the tree.
*/

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// EDITED
	Node<Key, Value>* node = mRoot;

	while(node->getLeft()!=nullptr)
	{
		node = node->getLeft();
	}

	return node;


}  

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or nullptr if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	if ( this->BinarySearchTree<Key, Value>::mRoot == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* temp = this->mRoot;
	if(temp == NULL)
	{
		return NULL;
	}
	while(temp)
	{
		if (key == temp->getKey())
		{
			return temp;
		}

		else if (key < temp->getKey())
		{
			temp = temp->getLeft();

		}
		else 
		{
			temp = temp->getRight();
		}

	}

	// if key is not found return a nullptr pointer
	return NULL; // should I just return nullptr???	
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != nullptr)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
