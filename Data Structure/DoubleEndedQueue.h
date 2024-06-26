#ifndef _DOUBLE_ENDED_QUEUE_
#define _DOUBLE_ENDED_QUEUE_
#include "LinkedQueue.h"
template <typename T>
class DoubleEndedQueue :public LinkedQueue<T> {
public:
	bool dequeueLast(T& frntEntry) {
		if (this->isEmpty())
			return false;
		if (this->backPtr == this->frontPtr) this->frontPtr = nullptr;
		Node<T>* nodeToDeletePtr = this->backPtr;
		frntEntry = this->backPtr->getItem();
		this->backPtr = this->backPtr->getPrevious();
		if(this->backPtr != nullptr) this->backPtr->setNext(nullptr);
		// Queue is not empty; remove front

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		this->count--;
		return true;
	}

	bool enqueueFirst(T& NewEntry)
	{
		if (this->isEmpty())
		{
			LinkedQueue<T>::enqueue(NewEntry);
			return true;
		}
		else
		{
			Node<T>* NewNode = new Node<T>;
			NewNode->setItem(NewEntry);
			NewNode->setNext(this->frontPtr);
			NewNode->setPrevious(NULL);
			this->frontPtr->setPrevious(NewNode);
			this->frontPtr = NewNode;
			LinkedQueue<T>::count++;
			return true;
		}
	}

	bool peekLast(T& bckEntry) const
	{
		if (LinkedQueue<T>::isEmpty())
			return false;

		bckEntry = LinkedQueue<T>::backPtr->getItem();
		return true;

	}
};
#endif // !_DOUBLE_ENDED_QUEUE_

