#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Monster.h"
#include "Move.h"
#include "TypeEffect.h"
using namespace std;


class GameManager
{
private:
	int turns;
	bool win = false;
	int nowPlayer = 0;
	int dodgeRate = 1;
	int critRate = 4;
	int appliedOnEffectRate = 7;
	vector<Monster> player1;
	int player1PowerPoint;
	vector<Monster> player2;
	int player2PowerPoint;
	Monster* player1Active;
	Monster* player2Active;
	TypeEffect typeEff = TypeEffect();
	string turnMessage = "[Turn " + to_string(turns) + "] ";
	string blank = "         ";
public:
	GameManager(vector<Monster> player1, vector<Monster> player2) : player1(player1), player2(player2) {};
	void GameStart()
	{
		turns = 1;
		player1PowerPoint = 100;
		player2PowerPoint = 100;
		player1Active = &player1[0];
		player2Active = &player2[0];
		nowPlayer = (player1Active->getSpeed() >= player2Active->getSpeed()) ? 1 : 2;
		cout << "Game start!" << endl;
		if (nowPlayer == 1)
		{
			cout << "Player1 attack first!" << endl;
		}
		else
		{
			cout << "Player2 attack first!" << endl;
		}
	}
	void showStatus()
	{
		cout << "Status: " << endl;
		cout << player1Active->getName() << " " << player1Active->HP << "/" << player1Active->maxHP << " ";
		for (int i = 0; i < player1Active->appliedEffect.size(); i++)
		{
			if (player1Active->appliedEffect[i] == 0) cout << "PAR" << " ";
			if (player1Active->appliedEffect[i] == 1) cout << "BRN" << " ";
			if (player1Active->appliedEffect[i] == 2) cout << "PSN" << " ";
		}
		cout << player2Active->getName() << " " << player2Active->HP << "/" << player2Active->maxHP << " ";
		for (int i = 0; i < player2Active->appliedEffect.size(); i++)
		{
			if (player2Active->appliedEffect[i] == 0) cout << "PAR" << " ";
			if (player2Active->appliedEffect[i] == 1) cout << "BRN" << " ";
			if (player2Active->appliedEffect[i] == 2) cout << "PSN" << " ";
		}
		cout << endl;
	}
	double CalculateDamage(Move usedMove, Monster* defender, Monster* attacker)
	{
		double damage;
		damage = 0;
		damage = (2.0 * (double)attacker->level + 10.0) / 250.0 * (double)usedMove.power;
		
		if (usedMove.phys == Physical)
		{
			damage = damage * (double)attacker->attack / (double)defender->defense + 2.0;
		}
		else
		{
			damage = damage * (double)attacker->SPattack / (double)defender->SPdefense + 2.0;
		}

		double typeEffect = 1.0;
		Type moveType = usedMove.type;
		for (int i = 0; i < defender->type.size(); i++)
		{
			typeEffect = typeEffect * typeEff.typeEff[moveType][defender->type[i]];
		}
		if (typeEffect >= 2)
		{
			cout << blank << "It's super effective!" << endl;
		}
		else if (typeEffect <= 0.5)
		{
			cout << blank << "It's not very effective..." << endl;
		}
		else if (typeEffect == 0)
		{
			cout << blank << "It's not effective!" << endl;
		}
		damage = damage * typeEffect;

		int critDice = rand() % 100 + 1;
		if (critDice <= critRate) { damage *= 1.5; cout << "Critical hit!" << endl; }

		for (int i = 0; i < attacker->type.size(); i++)
		{
			if (moveType == attacker->type[i])
			{
				damage = damage * 1.5;
			}
		}

		int appliedOnEffectDice = rand() % 100 + 1;
		if (appliedOnEffectDice <= appliedOnEffectRate && usedMove.effect != NOR)
		{
			if (usedMove.effect == PSN)
			{
				cout << blank << "The target is poisoned!" << endl;
				defender->appliedEffect.push_back(PSN);
			}
			else if (usedMove.effect == BRN)
			{
				cout << blank << "The target is burned!" << endl;
				defender->appliedEffect.push_back(BRN);
			}
			else if (usedMove.effect == PAR)
			{
				cout << blank << "The target is paralyzed!" << endl;
				defender->appliedEffect.push_back(PAR);
			}
		}

		return damage;
	}
	bool Player1Battle(string moves)
	{
		Move currentMove = Move();
		turnMessage = "[Turn " + to_string(turns) + "] ";
		for (int i = 0; i < player1Active->MonsterMove.size(); i++)
		{
			if (moves == player1Active->MonsterMove[i].getName())
			{
				currentMove = player1Active->MonsterMove[i];
				if (player1PowerPoint < currentMove.PP)
				{
					cout << turnMessage << "Not enough PP!" << endl;
					return false;
				}
				else
				{
					cout << turnMessage << player1Active->getName() << " used " << moves << "!" << endl;
					player1PowerPoint -= currentMove.PP;
					int dodge = rand() % 100 + 1;
					int accuracyDice = rand() % 100 + 1;
					if (dodge <= dodgeRate)
					{
						cout << blank << "Miss!" << endl;
					}
					else if (accuracyDice > currentMove.accuracy)
					{
						cout << blank << player2Active->getName() << " avoided the attack!" << endl;
					}
					else
					{
						int dealtdamage = CalculateDamage(currentMove, player2Active, player1Active);
						player2Active->HP -= dealtdamage;
						cout << blank << moves << " deals " << dealtdamage << " damage!" << endl;
						if (player2Active->HP <= 0)
						{
							player2Active->HP = 0;
							cout << blank << player2Active->getName() << " fainted!" << endl;
						}
					}
					player1PowerPoint += 20;
					turns++;
					return true;
				}
			}
		}
		if (currentMove.getName() == "NULL")
		{
			cout << turnMessage << "No such move!" << endl;
			return false;
		}
	}
	bool Player2Battle(string moves)
	{
		Move currentMove = Move();
		turnMessage = "[Turn " + to_string(turns) + "] ";
		for (int i = 0; i < player2Active->MonsterMove.size(); i++)
		{
			if (moves == player2Active->MonsterMove[i].getName())
			{
				currentMove = player2Active->MonsterMove[i];
				if (player2PowerPoint < currentMove.PP)
				{
					cout << turnMessage << "Not enough PP!" << endl;
					return false;
				}
				else
				{
					cout << turnMessage << player2Active->getName() << " used " << moves << "!" << endl;
					player2PowerPoint--;
					int dodge = rand() % 100 + 1;
					int accuracyDice = rand() % 100 + 1;
					if (dodge <= dodgeRate)
					{
						cout << blank << "Miss!" << endl;
					}
					else if (accuracyDice > currentMove.accuracy)
					{
						cout << blank << player2Active->getName() << " avoided the attack!" << endl;
					}
					else
					{
						int dealtdamage = CalculateDamage(currentMove, player1Active, player2Active);
						player1Active->HP -= dealtdamage;
						cout << blank << moves << " deals " << dealtdamage << " damage!" << endl;
						if (player1Active->HP <= 0)
						{
							player1Active->HP = 0;
							cout << blank << player1Active->getName() << " fainted!" << endl;
						}
					}
					player2PowerPoint += 20;
					turns++;
					return true;
				}
			}
		}
		if (currentMove.getName() == "NULL")
		{
			cout << turnMessage << "No such move!" << endl;
			return false;
		}
	}
	int getNowPlayer() { return nowPlayer; }
};