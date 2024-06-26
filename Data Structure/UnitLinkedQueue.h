#pragma once
#include<iostream>
#include "LinkedQueue.h"
#include"../Units/Unit.h"
#include"string"
using namespace std;
class UnitLinkedQueue :public LinkedQueue<Unit*>
{
public:
	void print(string soldierName)
	{
		cout << getCount() << soldierName << "[";
		Node<Unit*>* temp = frontPtr;
		while (temp) {
			cout << temp->getItem()->GetID();
			if (temp != backPtr)
				cout << ", ";
			temp = temp->getNext();
		}
		cout << "]" << endl;
	}

	void fightingPrint(string UnitType,int ID)
	{
		cout << UnitType <<ID<<" shots " << "[";
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
