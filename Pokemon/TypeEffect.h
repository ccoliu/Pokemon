//File : TypeEffect.h
//Name : �f�@�p �B�a�� ���R�� ���|�A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon

#include<iostream>
#include"Type.h"

using namespace std;

class TypeEffect
{
public:
	float typeEff[18][18] = { 0 };
	TypeEffect();
	~TypeEffect();
	float TypePower(Type attacker, Type defender);
};