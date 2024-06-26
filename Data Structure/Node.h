
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private :
	T item; // A data item
	T priority;
	Node<T>* next; // Pointer to next node
	Node<T>* previous; // Pointer to previous node
public :
	Node() {
		next = nullptr;
		previous = nullptr;
	}
	Node( const T & r_Item)
	{
		item = r_Item;
		next = nullptr;
		previous = nullptr;

	}
	Node( const T & r_Item, Node<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
		previous = nullptr;

	}
	Node( const T & r_Item, Node<T>* nextNodePtr, Node<T>* previousNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
		previous = previousNodePtr;

	}
	void setItem( const T & r_Item)
	{
		item = r_Item;
	}

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}
	void setPrevious(Node<T>* previousNodePtr)
	{
		previous = previousNodePtr;
	}
	T getItem() const
	{
		return item;
	}
	Node<T>* getNext() const
	{
		return next;
	}
	Node<T>* getPrevious() const 
	{
		return previous;
	}
}; // end Node
#endif