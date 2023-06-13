//File : GameManager.h
//Name : §fª@®p ¼B®a¦¨ ¤ý¬Rµ¾ ³¯©|¿A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon

#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Monster.h"
#include "Move.h"
#include "TypeEffect.h"
#include <map>
#include <string>
using namespace std;


class GameManager
{
private:
	int turns;
	int TURN;
	bool win = false;	//to check whether win
	int nowPlayer = 0;
	int dodgeRate = 1;
	int critRate = 4;
	int appliedOnEffectRate = 7;
    int paralyzedRate = 25;
	//player1's information
	vector<Monster> player1;	//to save all player1's monster
	int player1PowerPoint;
	bool player1MonsterParalyzed = false;
	bool player1MonsterBurned = false;
	bool player1MonsterPoisoned = false;
	int player1MonsterParalyzedRound = 0;
	int player1MonsterBurnedRound = 0;
	int player1MonsterPoisonedRound = 0;
	map<string, int> player1Bag = { {"Potion", 5}, {"SuperPotion", 3}, {"HyperPotion", 2}, {"MaxPotion", 1} };
	//player2's information
	vector<Monster> player2;	//to save all player2's monster
	int nextMonster = 1;
	int player2PowerPoint;
	bool player2MonsterParalyzed = false;
	bool player2MonsterBurned = false;
	bool player2MonsterPoisoned = false;
	bool player2FirstRoundFreeze = false;
	int player2MonsterParalyzedRound = 0;
	int player2MonsterBurnedRound = 0;
	int player2MonsterPoisonedRound = 0;
	Monster* player1Active;	//save player1's current monster
	Monster* player2Active;	//save player2's current monster
	TypeEffect typeEff = TypeEffect();
	string turnMessage = "[Turn " + to_string(turns) + "] ";
	string blank = "          ";
public:
	bool player1MonsterFainted = false;

	GameManager(vector<Monster> player1, vector<Monster> player2) : player1(player1), player2(player2) {};
	void GameStart();
	void TestModeActive();
	void swapMonster(string chosenMonster);
	map<string, int> browseMonster();
	map<string, int> browseBag();
	void browseMove();
	void checkCondition(vector<Monster> player, string playername);
	void checkMonsterEffects();
	void RoundStart();
	void showStatus();
	double CalculateDamage(Move usedMove, Monster* defender, Monster* attacker);
	bool Player1Battle(string moves);
	bool Player2Battle(string moves, bool& player1MonsterFainted);
	void useItem(string item, string chosenMonster);
	int getNowPlayer() { return nowPlayer; }
};