#pragma once
#include <iostream>
#include "Type.h"
using namespace std;

enum PhysicalSpecial
{
	Physical,
	Special
};

enum AdditionalEffect
{
	PAR,
	BRN,
	PSN,
};

class Move
{
private:
	string name;
	Type type;
	PhysicalSpecial phys;
	int power;
	int accuracy;
	int PP;
	AdditionalEffect effect;
public:
	Move(string name, Type type, PhysicalSpecial phys, int power, int accuracy, int PP, AdditionalEffect effect) : name(name), type(type), phys(phys), power(power), accuracy(accuracy), PP(PP), effect(effect) {};
};