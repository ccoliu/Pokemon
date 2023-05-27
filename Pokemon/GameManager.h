#pragma once
#include <iostream>
#include <stdlib.h>
#include "Monster.h"
#include "Move.h"
using namespace std;

class GameManager
{
private:
	int turns;
	bool win = false;
	int nowPlayer = 0;
	int dodgeRate = 1;
	vector<Monster> player1;
	int player1PowerPoint;
	vector<Monster> player2;
	int player2PowerPoint;
	Monster *player1Active;
	Monster *player2Active;
public:
	GameManager(vector<Monster> player1, vector<Monster> player2) : player1(player1), player2(player2) {};
	void GameStart()
	{
		turns = 1;
		player1PowerPoint = 4;
		player2PowerPoint = 4;
		player1Active = &player1[0];
		player2Active = &player2[0];
		nowPlayer = (player1Active->getSpeed() >= player2Active->getSpeed()) ? 1 : 2;
		cout << "Game start!" << endl;
		if (nowPlayer == 1)
		{
			cout << "Player1's turn!" << endl;
		}
		else
		{
			cout << "Player2's turn!" << endl;
		}
	}
	int CalculateDamage() { return 0; };
	bool Player1Battle(string moves)
	{
		Move currentMove = Move();
		for (int i = 0; i < player1Active->MonsterMove.size(); i++)
		{
			if (moves == player1Active->MonsterMove[i].getName())
			{
				currentMove = player1Active->MonsterMove[i];
				if (currentMove.getPhys() == Special)
				{
					if (player1PowerPoint == 0)
					{
						cout << "No PP left!" << endl;
						return false;
					}
					else
					{
						player1PowerPoint--;
						int dodge = rand() % 100 + 1;
						if (dodge <= dodgeRate) 
						{ 
							cout << "Miss!" << endl; 
						}
						else
						{
							player2Active->HP -= CalculateDamage();
							cout << moves << " deals " << CalculateDamage() << " damage!" << endl;
							if (player2Active->HP <= 0)
							{
								cout << player2Active->getName() << " fainted!" << endl;
							}
						}
						return true;
					}
				}
				else
				{
					int dodge = rand() % 100 + 1;
					if (dodge <= dodgeRate)
					{
						cout << "Miss!" << endl;
					}
					else
					{
						player2Active->HP -= CalculateDamage();
						cout << moves << " deals " << CalculateDamage() << " damage!" << endl;
						if (player2Active->HP <= 0)
						{
							cout << player2Active->getName() << " fainted!" << endl;
						}
					}
					return true;
				}
			}
		}
		if (currentMove.getName() == "NULL")
		{
			cout << "No such move!" << endl;
			return false;
		}
	}
	bool Player2Battle(string moves)
	{
		Move currentMove = Move();
		for (int i = 0; i < player2Active->MonsterMove.size(); i++)
		{
			if (moves == player2Active->MonsterMove[i].getName())
			{
				currentMove = player2Active->MonsterMove[i];
				if (currentMove.getPhys() == Special)
				{
					if (player2PowerPoint == 0)
					{
						cout << "No PP left!" << endl;
						return false;
					}
					else
					{
						player2PowerPoint--;
						int dodge = rand() % 100 + 1;
						if (dodge <= dodgeRate)
						{
							cout << "Miss!" << endl;
						}
						else
						{
							player1Active->HP -= CalculateDamage();
							cout << moves << " deals " << CalculateDamage() << " damage!" << endl;
							if (player1Active->HP <= 0)
							{
								cout << player1Active->getName() << " fainted!" << endl;
							}
						}
						return true;
					}
				}
				else
				{
					int dodge = rand() % 100 + 1;
					if (dodge <= dodgeRate)
					{
						cout << "Miss!" << endl;
					}
					else
					{
						player1Active->HP -= CalculateDamage();
						cout << moves << " deals " << CalculateDamage() << " damage!" << endl;
						if (player1Active->HP <= 0)
						{
							cout << player1Active->getName() << " fainted!" << endl;
						}
					}
					return true;
				}
			}
		}
		if (currentMove.getName() == "NULL")
		{
			cout << "No such move!" << endl;
			return false;
		}
	}
	int getNowPlayer() { return nowPlayer; }
};