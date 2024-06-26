#pragma once
#include<iostream>
#include"../Data Structure/priQueue.h"
#include"../Units/Unit.h"
using namespace std;
class UnitpriQueue :public priQueue<Unit*>
{
public:
	void print()
	{
		int Pri;
		priNode<Unit*>* temp = head;

		cout << count << " EG " << "[";
		while (temp)
		{
			cout << temp->getItem(Pri)->GetID();
			if (temp->getNext() != nullptr)
				cout << ", ";
			temp = temp->getNext();
		}
		cout << "]" << endl;
	}
};
