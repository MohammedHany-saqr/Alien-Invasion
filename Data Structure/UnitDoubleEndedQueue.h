#pragma once
#include<iostream>
#include"DoubleEndedQueue.h"
#include"../Units/Unit.h"
using namespace std;
class UnitDoubleEndedQueue :public DoubleEndedQueue<Unit*>
{
public:
	void print()
	{
		cout << getCount() << " AD " << "[";
		Node<Unit*>* temp = frontPtr;
		while (temp) {
			cout << temp->getItem()->GetID();
			if (temp != backPtr)
				cout << ", ";
			temp = temp->getNext();
		}
		cout << "]" << endl;
	}

};
