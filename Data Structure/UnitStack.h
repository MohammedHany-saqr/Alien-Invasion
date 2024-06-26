#pragma once
#include<iostream>
#include"ArrayStack.h"
#include"../Units/Unit.h"
using namespace std;
class UnitStack :public ArrayStack<Unit*>
{
public:
	void print()
	{
		cout << top + 1 << " ET " << "[";
		for (int i = top; i >= 0; i--)
		{

			cout << items[i]->GetID();  //Unit
			if (i > 0)	cout << ", ";
		}
		cout << "]" << endl;
	}
};