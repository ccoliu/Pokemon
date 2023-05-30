#pragma once
#include <iostream>
#include <vector>
#include "Type.h"
#include "Move.h"
using namespace std;

class Monster
{
private:
	string name;
public:
	vector<Type> type;
	int maxHP;
	int HP;
	int attack;
	int defense;
	int SPattack;
	int SPdefense;
	int maxspeed;
	int speed;
	int level = 50;
	map<AdditionalEffect, int> appliedEffect = { {BRN,0},{PSN,0},{PAR,0} };
	vector<Move> MonsterMove;
	Monster() { name = "NULL"; };
	Monster(string name, vector<Type> type, int HP, int attack, int defense, int SPattack, int SPdefense, int speed) : name(name), type(type), maxHP(HP), HP(HP), attack(attack),
		defense(defense), SPattack(SPattack), SPdefense(SPdefense), maxspeed(speed), speed(speed) {};
	string getName() { return name; }
	int getSpeed() { return speed; }
	void addMove(Move move) { MonsterMove.push_back(move); }
	friend ostream& operator<< (ostream& out, const Monster& monster)
	{
		out << monster.name << endl;
		for (int i = 0; i < monster.type.size(); i++)
		{
			out << monster.type[i] << " ";
		}
		out << endl;
		out << monster.HP << " ";
		out << monster.attack << " ";
		out << monster.defense << " ";
		out << monster.SPattack << " ";
		out << monster.SPdefense << " ";
		out << monster.speed << endl;
		for (int i = 0; i < monster.MonsterMove.size(); i++)
		{
			out << monster.MonsterMove[i];
		}
		return out;
	}
};