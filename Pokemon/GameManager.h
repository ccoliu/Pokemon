#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Monster.h"
#include "Move.h"
#include "TypeEffect.h"
#include <map>
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
	bool player1MonsterParalyzed = false;
	bool player1MonsterBurned = false;
	bool player1MonsterPoisoned = false;
	int player1MonsterParalyzedRound = 0;
	int player1MonsterBurnedRound = 0;
	int player1MonsterPoisonedRound = 0;
	map<string,int> player1Bag = { {"Potion", 5}, {"Super Potion", 3}, {"Hyper Potion", 2}, {"Max Potion", 1} };

	vector<Monster> player2;
	int nextMonster = 1;
	int player2PowerPoint;
	bool player2MonsterParalyzed = false;
	bool player2MonsterBurned = false;
	bool player2MonsterPoisoned = false;
	int player2MonsterParalyzedRound = 0;
	int player2MonsterBurnedRound = 0;
	int player2MonsterPoisonedRound = 0;

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
	void browseMonster()
	{
		for (int i = 0; i < player1.size(); i++)
		{
			cout << player1[i].getName() << " HP: " << player1[i].HP << "/" << player1[i].maxHP << endl;
		}
	}
	void checkCondition(vector<Monster> player, string playername)
	{
		bool partyFainted = true;
		for (auto i = player.begin(); i != player.end(); i++)
		{
			if (i->HP != 0)
			{
				partyFainted = false;
				return;
			}
		}
		if (partyFainted)
		{
			win = true;
			if (playername == "player1")
			{
				cout << "You lose!" << endl;
			}
			else
			{
				cout << "You win!" << endl;
			}
			exit(1);
		}
	}
	void checkMonsterEffects()
	{
		if (player1MonsterBurned)
		{
			player1Active->HP -= player1Active->maxHP / 16;
			cout << blank << player1Active->getName() << " is hurt by burn!" << endl;
			player1MonsterBurnedRound--;
			if (player1MonsterBurnedRound == 0)
			{
				player1MonsterBurned = false;
				cout << blank << player1Active->getName() << " is no longer burned!" << endl;
				player1Active->appliedEffect.erase(find(player1Active->appliedEffect.begin(), player1Active->appliedEffect.end(), BRN));
			}
		}
		if (player1MonsterPoisoned)
		{
			player1Active->HP -= player1Active->maxHP / 16;
			cout << blank << player1Active->getName() << " is hurt by its poisoning!" << endl;
			player1MonsterPoisonedRound--;
			if (player1MonsterPoisonedRound == 0)
			{
				player1MonsterPoisoned = false;
				cout << blank << player1Active->getName() << " is no longer poisoned!" << endl;
				player1Active->appliedEffect.erase(find(player1Active->appliedEffect.begin(), player1Active->appliedEffect.end(), PSN));
			}
		}
		if (player1MonsterParalyzed)
		{
			player1Active->speed = player1Active->maxspeed / 2;
			player1MonsterParalyzedRound--;
			if (player1MonsterParalyzedRound == 0)
			{
				player1MonsterParalyzed = false;
				player1Active->speed = player1Active->maxspeed;
				cout << blank << player1Active->getName() << " is no longer paralyzed!" << endl;
				player1Active->appliedEffect.erase(find(player1Active->appliedEffect.begin(), player1Active->appliedEffect.end(), PAR));
			}
		}

		if (player2MonsterBurned)
		{
			player2Active->HP -= player2Active->maxHP / 16;
			cout << blank << player2Active->getName() << " is hurt by burn!" << endl;
			player2MonsterBurnedRound--;
			if (player2MonsterBurnedRound == 0)
			{
				player2MonsterBurned = false;
				cout << blank << player2Active->getName() << " is no longer burned!" << endl;
				player2Active->appliedEffect.erase(find(player2Active->appliedEffect.begin(), player2Active->appliedEffect.end(), BRN));
			}
		}
		if (player2MonsterPoisoned)
		{
			player2Active->HP -= player2Active->maxHP / 16;
			cout << blank << player2Active->getName() << " is hurt by its poisoning!" << endl;
			player2MonsterPoisonedRound--;
			if (player2MonsterPoisonedRound == 0)
			{
				player2MonsterPoisoned = false;
				cout << blank << player2Active->getName() << " is no longer poisoned!" << endl;
				player2Active->appliedEffect.erase(find(player2Active->appliedEffect.begin(), player2Active->appliedEffect.end(), PSN));
			}
		}
		if (player2MonsterParalyzed)
		{
			player2Active->speed = player2Active->maxspeed / 2;
			player2MonsterParalyzedRound--;
			if (player2MonsterParalyzedRound == 0)
			{
				player2MonsterParalyzed = false;
				player2Active->speed = player2Active->maxspeed;
				cout << blank << player2Active->getName() << " is no longer paralyzed!" << endl;
				player2Active->appliedEffect.erase(find(player2Active->appliedEffect.begin(), player2Active->appliedEffect.end(), PAR));
			}
		}
	}
	void RoundStart()
	{
		cout << "New Round!" << endl;
		checkMonsterEffects();
		nowPlayer = (player1Active->getSpeed() >= player2Active->getSpeed()) ? 1 : 2;
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
				if (defender == player1Active)
				{
					player1MonsterPoisoned = true;
					player1MonsterPoisonedRound = 3;
				}
				else
				{
					player2MonsterPoisoned = true;
					player2MonsterPoisonedRound = 3;
				}
				cout << blank << "The target was poisoned!" << endl;
				defender->appliedEffect.push_back(PSN);
			}
			else if (usedMove.effect == BRN)
			{
				if (defender == player1Active)
				{
					player1MonsterBurned = true;
					player1MonsterBurnedRound = 3;
				}
				else
				{
					player2MonsterBurned = true;
					player2MonsterBurnedRound = 3;
				}
				cout << blank << "The target was burned!" << endl;
				defender->appliedEffect.push_back(BRN);
			}
			else if (usedMove.effect == PAR)
			{
				if (defender == player1Active)
				{
					player1MonsterParalyzed = true;
					player1MonsterParalyzedRound = 3;
				}
				else
				{
					player2MonsterParalyzed = true;
					player2MonsterParalyzedRound = 3;
				}
				cout << blank << "The target was paralyzed, so it may be unable to move!" << endl;
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
					else if (player1MonsterParalyzed)
					{
						int paralyzeDice = rand() % 100 + 1;
						if (paralyzeDice <= 25)
						{
							cout << blank << player1Active->getName() << " is paralyzed!" << endl;
							cout << "It can't move!" << endl;
						}
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
							checkCondition(player2, "player2");
							player2Active = &player2[nextMonster];
							nextMonster++;
							cout << "Go! " << player2Active->getName() << "!" << endl;
						}
					}
					player1PowerPoint += 20;
					turns++;
					if ((turns - 1) % 2 == 0) RoundStart();
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
					cout << turnMessage << "The opposing " << player2Active->getName() << " used " << moves << "!" << endl;
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
					if ((turns - 1) % 2 == 0) RoundStart();
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
	bool useItem(string item)
	{
		turnMessage = "[Turn " + to_string(turns) + "] ";
		if (player1Bag.find(item) == player1Bag.end())
		{
			cout << "No such item!" << endl;
			return false;
		}
		else if (player1Bag[item] == 0)
		{
			cout << "Item depleted!" << endl;
			return false;
		}
		else
		{
			if (item == "Potion")
			{
				int recoveredHP = player1Active->maxHP - player1Active->HP;
				player1Active->HP += 20;
				if (player1Active->HP > player1Active->maxHP) player1Active->HP = player1Active->maxHP;
				cout << turnMessage << player1Active->getName() << " has used Potion!" << endl;
				cout << blank << player1Active->getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "Super Potion")
			{
				int recoveredHP = player1Active->maxHP - player1Active->HP;
				player1Active->HP += 60;
				if (player1Active->HP > player1Active->maxHP) player1Active->HP = player1Active->maxHP;
				cout << turnMessage << player1Active->getName() << " has used Super Potion!" << endl;
				cout << blank << player1Active->getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "Hyper Potion")
			{
				int recoveredHP = player1Active->maxHP - player1Active->HP;
				player1Active->HP += 120;
				if (player1Active->HP > player1Active->maxHP) player1Active->HP = player1Active->maxHP;
				cout << turnMessage << player1Active->getName() << " has used Hyper Potion!" << endl;
				cout << blank << player1Active->getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "Max Potion")
			{
				int recoveredHP = player1Active->maxHP - player1Active->HP;
				player1Active->HP = player1Active->maxHP;
				cout << turnMessage << player1Active->getName() << " has used Max Potion!" << endl;
				cout << blank << player1Active->getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			turns++;
			if ((turns - 1) % 2 == 0) RoundStart();
			return true;
		}
	}
	int getNowPlayer() { return nowPlayer; }
};