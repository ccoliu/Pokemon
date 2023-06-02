//File : Monster.h
//Name : §fª@®p ¼B®a¦¨ ¤ý¬Rµ¾ ³¯©|¿A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Move.h"
using namespace std;

class Monster
{
private:
	string name;
public:
	map<AdditionalEffect, int> appliedEffect = { {BRN,0},{PSN,0},{PAR,0} };
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
	vector<Move> MonsterMove;
	Monster() { name = "NULL"; };	//default constructure
	//constructure
	Monster(string name, vector<Type> type, int HP, int attack, int defense, int SPattack, int SPdefense, int speed) : name(name), type(type), maxHP(HP), HP(HP), attack(attack),
		defense(defense), SPattack(SPattack), SPdefense(SPdefense), maxspeed(speed), speed(speed) {};
	string getName() { return name; }	//get the monster name
	int getSpeed() { return speed; }	//get the monster speed to judge who first
	void addMove(Move move) { MonsterMove.push_back(move); }
};