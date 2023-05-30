#pragma once
#include <iostream>
#include "Type.h"
using namespace std;

enum PhysicalSpecial
{
	Physical,
	Special
};

class Move
{
private:
	string name;
public:
	Type type;
	PhysicalSpecial phys;
	int power;
	int accuracy;
	int PP;
	AdditionalEffect effect;
	Move() { name = "NULL"; };
	Move(string name, Type type, PhysicalSpecial phys, int power, int accuracy, int PP, AdditionalEffect effect) : name(name), type(type), phys(phys), power(power), accuracy(accuracy), PP(PP), effect(effect) {};
	string getName() { return name; }
	PhysicalSpecial getPhys() { return phys; }
};