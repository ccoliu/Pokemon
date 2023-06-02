//File : Move.h
//Name : §fª@®p ¼B®a¦¨ ¤ý¬Rµ¾ ³¯©|¿A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon

#pragma once
#include <iostream>
#include "Type.h"
using namespace std;

enum PhysicalSpecial
{
	Physical,
	Special,
	Status
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
	Move() { name = "NULL"; };//default constructure
	//constructure
	Move(string name, Type type, PhysicalSpecial phys, int power, int accuracy, int PP, AdditionalEffect effect) : name(name), type(type), phys(phys), power(power), accuracy(accuracy), PP(PP), effect(effect) {};
	string getName() { return name; }	//get the move name
	PhysicalSpecial getPhys() { return phys; }
};