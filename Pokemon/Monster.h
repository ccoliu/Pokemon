#pragma once
#include <iostream>
#include <vector>
#include "Type.h"
using namespace std;

class Monster
{
private:
	string name;
	vector<Type> type;
	int HP;
	int attack;
	int defense;
	int SPattack;
	int SPdefense;
	int speed;
public:
	Monster(string name, vector<Type> type, int HP, int attack, int defense, int SPattack, int SPdefense, int speed) : name(name), type(type), HP(HP), attack(attack),
		defense(defense), SPattack(SPattack), SPdefense(SPdefense), speed(speed) {};

};