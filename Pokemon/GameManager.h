#pragma once
#include <iostream>
#include "Monster.h"
#include "Move.h"
using namespace std;

class GameManager
{
private:
	int turns;
	bool win = false;
	int nowPlayer = 0;
	vector<Monster> player1;
	vector<Monster> player2;
	Monster player1Active;
	Monster player2Active;
public:
	GameManager(vector<Monster> player1, vector<Monster> player2) : player1(player1), player2(player2) {};
	void GameStart()
	{
		turns = 1;
		player1Active = player1[0];
		player2Active = player2[0];
		nowPlayer = (player1Active.getSpeed() >= player2Active.getSpeed()) ? 1 : 2;
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
	void Player1Battle(string moves)
	{

	}
	void Player2Battle(string moves)
	{

	}
	int getNowPlayer() { return nowPlayer; }
};