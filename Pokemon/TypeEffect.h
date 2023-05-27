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