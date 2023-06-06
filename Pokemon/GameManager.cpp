//File : GameManager.cpp
//Name : §fª@®p ¼B®a¦¨ ¤ý¬Rµ¾ ³¯©|¿A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon

#include "GameManager.h"
#include <string>

//start game and initialize
void GameManager::GameStart()
{
	turns = 1;
	TURN = 1;
	player1PowerPoint = 100;
	player2PowerPoint = 100;
	player1Active = &player1[0];
	player2Active = &player2[0];
	//judge which one pokemon move first
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
//TestMode
void GameManager::TestModeActive()
{
	critRate = 0;
	appliedOnEffectRate = 100;
	for (int i = 0; i < player1.size(); i++)
	{
		for (int j = 0; j < player1[i].MonsterMove.size(); j++)
		{
			player1[i].MonsterMove[j].accuracy = 100;
		}
	}
	for (int i = 0; i < player2.size(); i++)
	{
		for (int j = 0; j < player2[i].MonsterMove.size(); j++)
		{
			player2[i].MonsterMove[j].accuracy = 100;
		}
	}
}
//change player's pokemon
void GameManager::swapMonster(string chosenMonster)
{
	turnMessage = "[Turn " + to_string(TURN) + "] ";
	player1MonsterParalyzed = false;
	player1MonsterBurned = false;
	player1MonsterPoisoned = false;
	player1MonsterParalyzedRound = 0;
	player1MonsterBurnedRound = 0;
	player1MonsterPoisonedRound = 0;
	for (int i = 0; i < player1.size(); i++)
	{
		//check which one pokemon be chosen
		if (player1[i].getName() == chosenMonster)
		{
			//check the current monster hasn't die
			if (player1Active->HP != 0)
			{
				cout << turnMessage << player1Active->getName() << " switch out!" << endl;
				cout << blank << "Come back!" << endl;
			}
			//swap pokemon
			player1Active = &player1[i];
			//if be chosen pokemon have additional effect then set it
			if (player1Active->appliedEffect[PSN] != 0)
			{
				player1MonsterPoisoned = true;
				player1MonsterPoisonedRound = player1Active->appliedEffect[PSN];
			}
			if (player1Active->appliedEffect[PAR] != 0)
			{
				player1MonsterParalyzed = true;
				player1MonsterParalyzedRound = player1Active->appliedEffect[PAR];
			}
			if (player1Active->appliedEffect[BRN] != 0)
			{
				player1MonsterBurned = true;
				player1MonsterBurnedRound = player1Active->appliedEffect[BRN];
			}
			cout << blank << "Go! " << player1Active->getName() << "!" << endl;
			break;
		}
	}
	turns++;
	if ((turns - 1) % 2 == 0) RoundStart(); //new round
}
//print all player's pokemon
map<string, int> GameManager::browseMonster()
{
	map<string, int> player1Monster;
	cout << "Player1's Monsters: " << endl;
	for (int i = 0; i < player1.size(); i++)
	{
		cout << player1[i].getName() << " " << player1[i].HP << "/" << player1[i].maxHP << endl;
		player1Monster[player1[i].getName()] = player1[i].HP;
	}
	return player1Monster;
}
//return player's bag
map<string, int> GameManager::browseBag()
{
	return player1Bag;
}

void GameManager::browseMove()
{
	for (int i = 0; i < player1Active->MonsterMove.size(); i++)
	{
		cout << player1Active->MonsterMove[i].getName() << " " << player1Active->MonsterMove[i].PP << " ";
	}
	cout << endl;
}
//check pokemon whether have all die
void GameManager::checkCondition(vector<Monster> player, string playername)
{
	bool partyFainted = true;
	//check every pokemon's hp
	for (auto i = player.begin(); i != player.end(); i++)
	{
		if (i->HP != 0)
		{
			partyFainted = false;
			return;
		}
	}
	//if all pokemon die then judge who win
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
//check whether monster have specail effect
void GameManager::checkMonsterEffects()
{
	//pokemon have burn effect
	if (player1MonsterBurned)
	{
		player1Active->HP -= player1Active->maxHP / 16;
		cout << blank << player1Active->getName() << " is hurt by burn!" << endl;
		if (player1Active->HP <= 0)
		{
			player1Active->HP = 0;
			cout << blank << player1Active->getName() << " fainted!" << endl;
			player1MonsterFainted = true;
			checkCondition(player1, "player1");
			return;
		}
		else
		{
			player1MonsterBurnedRound--;	//after effect affect the pokemon its effect round minus one 
			player1Active->appliedEffect[BRN] = player1MonsterBurnedRound;
			//if special effect have over than print the information
			if (player1MonsterBurnedRound == 0)
			{
				player1MonsterBurned = false;
				cout << blank << player1Active->getName() << " is no longer burned!" << endl;
			}
		}
	}
	//pokemon have Poisoned effect
	if (player1MonsterPoisoned)
	{
		player1Active->HP -= player1Active->maxHP / 16;
		cout << blank << player1Active->getName() << " is hurt by its poisoning!" << endl;
		if (player1Active->HP <= 0)
		{
			player1Active->HP = 0;
			cout << blank << player1Active->getName() << " fainted!" << endl;
			player1MonsterFainted = true;
			checkCondition(player1, "player1");
			return;
		}
		else
		{
			player1MonsterPoisonedRound--;
			player1Active->appliedEffect[PSN] = player1MonsterPoisonedRound;
			//if special effect have over than print the information
			if (player1MonsterPoisonedRound == 0)
			{
				player1MonsterPoisoned = false;
				cout << blank << player1Active->getName() << " is no longer poisoned!" << endl;
			}
		}
	}
	//pokemon have Paralyzed effect
	if (player1MonsterParalyzed)
	{
		player1Active->speed = player1Active->maxspeed / 2;
		player1MonsterParalyzedRound--;	//after effect affect the pokemon its effect round minus one 
		player1Active->appliedEffect[PAR] = player1MonsterParalyzedRound;
		//if special effect have over than print the information
		if (player1MonsterParalyzedRound == 0)
		{
			player1MonsterParalyzed = false;
			player1Active->speed = player1Active->maxspeed;
			cout << blank << player1Active->getName() << " is no longer paralyzed!" << endl;
		}
	}
	//pokemon have burn effect
	if (player2MonsterBurned)
	{
		player2Active->HP -= player2Active->maxHP / 16;
		cout << blank << "The opposing " << player2Active->getName() << " is hurt by burn!" << endl;
		if (player2Active->HP <= 0)
		{
			player2Active->HP = 0;
			cout << blank << player2Active->getName() << " fainted!" << endl;
			checkCondition(player2, "player2");

			player2MonsterBurned = false;
			player2MonsterBurnedRound = 0;
			player2MonsterPoisoned = false;
			player2MonsterPoisonedRound = 0;
			player2MonsterParalyzed = false;
			player2MonsterParalyzedRound = 0;

			player2Active = &player2[nextMonster];
			nextMonster++;
			player2FirstRoundFreeze = true;
			return;
		}
		else
		{
			player2MonsterBurnedRound--;	//after effect affect the pokemon its effect round minus one 
			player2Active->appliedEffect[BRN] = player2MonsterBurnedRound;
			//if special effect have over than print the information
			if (player2MonsterBurnedRound == 0)
			{
				player2MonsterBurned = false;
				cout << blank << player2Active->getName() << " is no longer burned!" << endl;
			}
		}
	}
	//pokemon have Poisoned effect
	if (player2MonsterPoisoned)
	{
		player2Active->HP -= player2Active->maxHP / 16;
		cout << blank << "The opposing " << player2Active->getName() << " is hurt by its poisoning!" << endl;
		if (player2Active->HP <= 0)
		{
			player2Active->HP = 0;
			cout << blank << player2Active->getName() << " fainted!" << endl;
			checkCondition(player2, "player2");

			player2MonsterBurned = false;
			player2MonsterBurnedRound = 0;
			player2MonsterPoisoned = false;
			player2MonsterPoisonedRound = 0;
			player2MonsterParalyzed = false;
			player2MonsterParalyzedRound = 0;

			player2Active = &player2[nextMonster];
			nextMonster++;
			player2FirstRoundFreeze = true;
		}
		else
		{
			player2MonsterPoisonedRound--;	//after effect affect the pokemon its effect round minus one 
			player2Active->appliedEffect[PSN] = player2MonsterPoisonedRound;
			//if special effect have over than print the information
			if (player2MonsterPoisonedRound == 0)
			{
				player2MonsterPoisoned = false;
				cout << blank << player2Active->getName() << " is no longer poisoned!" << endl;
			}
		}
	}
	//pokemon have Paralyzed effect
	if (player2MonsterParalyzed)
	{
		player2Active->speed = player2Active->maxspeed / 2;
		player2MonsterParalyzedRound--;	//after effect affect the pokemon its effect round minus one 
		player2Active->appliedEffect[PAR] = player2MonsterParalyzedRound;
		//if special effect have over than print the information
		if (player2MonsterParalyzedRound == 0)
		{
			player2MonsterParalyzed = false;
			player2Active->speed = player2Active->maxspeed;
			cout << blank << player2Active->getName() << " is no longer paralyzed!" << endl;
		}
	}
}
//after two player move start a new round
void GameManager::RoundStart()
{
	cout << "New Round!" << endl;
	checkMonsterEffects();
	nowPlayer = (player1Active->getSpeed() >= player2Active->getSpeed()) ? 1 : 2;	//every round have to check the speed of pokemon
	if (nowPlayer == 1)
	{
		cout << "Player1 attack first!" << endl;
	}
	else
	{
		cout << "Player2 attack first!" << endl;
	}
}
//print the status of current pokemon
void GameManager::showStatus()
{
	cout << "Status: " << endl;
	cout << player1Active->getName() << " " << player1Active->HP << "/" << player1Active->maxHP << " ";
	if (player1Active->appliedEffect[PAR] != 0) cout << "PAR" << " ";
	if (player1Active->appliedEffect[BRN] != 0) cout << "BRN" << " ";
	if (player1Active->appliedEffect[PSN] != 0) cout << "PSN" << " ";
	cout << player2Active->getName() << " " << player2Active->HP << "/" << player2Active->maxHP << " ";
	if (player2Active->appliedEffect[PAR] != 0) cout << "PAR" << " ";
	if (player2Active->appliedEffect[BRN] != 0) cout << "BRN" << " ";
	if (player2Active->appliedEffect[PSN] != 0) cout << "PSN" << " ";
	cout << endl;
}
//calculate the damage of pokemon cause
double GameManager::CalculateDamage(Move usedMove, Monster* defender, Monster* attacker)
{
	double damage;
	damage = 0;
	if (usedMove.phys != Status)
	{
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
		//multiplicate the type effect to damage
		damage = damage * typeEffect;
		//check whether have crit
		int critDice = rand() % 100 + 1;
		if (critDice <= critRate) { damage *= 1.5; cout << blank << "Critical hit!" << endl; }
		//if crit then damage*1.5
		for (int i = 0; i < attacker->type.size(); i++)
		{
			if (moveType == attacker->type[i])
			{
				damage = damage * 1.5;
			}
		}
	}
	//check whether use special effect skill
	if (usedMove.phys == Status)
	{
		//cause poison
		if (usedMove.effect == PSN)
		{
			if (defender == player1Active)
			{
				player1MonsterPoisoned = true;
				player1MonsterPoisonedRound = 3;
				cout << blank << "Your monster was poisoned!" << endl;
			}
			else
			{
				player2MonsterPoisoned = true;
				player2MonsterPoisonedRound = 3;
				cout << blank << "The opposing target was poisoned!" << endl;
			}
			defender->appliedEffect[PSN] = 3;
		}
		//cause burn
		else if (usedMove.effect == BRN)
		{
			if (defender == player1Active)
			{
				player1MonsterBurned = true;
				player1MonsterBurnedRound = 3;
				cout << blank << "Your monster was burned!" << endl;
			}
			else
			{
				player2MonsterBurned = true;
				player2MonsterBurnedRound = 3;
				cout << blank << "The opposing target was burned!" << endl;
			}
			defender->appliedEffect[BRN] = 3;
		}
		//cause par
		else if (usedMove.effect == PAR)
		{
			if (defender == player1Active)
			{
				player1MonsterParalyzed = true;
				player1MonsterParalyzedRound = 3;
				cout << blank << "Your monster was paralyzed, so it may be unable to move!" << endl;
			}
			else
			{
				player2MonsterParalyzed = true;
				player2MonsterParalyzedRound = 3;
				cout << blank << "The opposing target was paralyzed, so it may be unable to move!" << endl;
			}
			defender->appliedEffect[PAR] = 3;
		}
	}
	else
	{
		int appliedOnEffectDice = rand() % 100 + 1;
		//check whether miss
		if (appliedOnEffectDice <= appliedOnEffectRate && usedMove.effect != NOR)
		{
			//cause poison
			if (usedMove.effect == PSN)
			{
				if (defender == player1Active)
				{
					player1MonsterPoisoned = true;
					player1MonsterPoisonedRound = 3;
					cout << blank << "Your monster was poisoned!" << endl;
				}
				else
				{
					player2MonsterPoisoned = true;
					player2MonsterPoisonedRound = 3;
					cout << blank << "The opposing target was poisoned!" << endl;
				}
				defender->appliedEffect[PSN] = 3;
			}
			//cause burn
			else if (usedMove.effect == BRN)
			{
				if (defender == player1Active)
				{
					player1MonsterBurned = true;
					player1MonsterBurnedRound = 3;
					cout << blank << "Your monster was burned!" << endl;
				}
				else
				{
					player2MonsterBurned = true;
					player2MonsterBurnedRound = 3;
					cout << blank << "The opposing target was burned!" << endl;
				}
				defender->appliedEffect[BRN] = 3;
			}
			//cause par
			else if (usedMove.effect == PAR)
			{
				if (defender == player1Active)
				{
					player1MonsterParalyzed = true;
					player1MonsterParalyzedRound = 3;
					cout << blank << "Your monster was paralyzed, so it may be unable to move!" << endl;
				}
				else
				{
					player2MonsterParalyzed = true;
					player2MonsterParalyzedRound = 3;
					cout << blank << "The opposing target was paralyzed, so it may be unable to move!" << endl;
				}
				defender->appliedEffect[PAR] = 3;	
			}
		}
	}
	return damage;
}
bool GameManager::Player1Battle(string moves)
{
	Move currentMove = Move();
	turnMessage = "[Turn " + to_string(TURN) + "] ";
	for (int i = 0; i < player1Active->MonsterMove.size(); i++)
	{
		if (moves == player1Active->MonsterMove[i].getName())
		{
			currentMove = player1Active->MonsterMove[i];
			if (player1Active->MonsterMove[i].PP == 0)
			{
				cout << turnMessage << "Not enough PP!" << endl;
				return false;
			}
			else
			{
				cout << turnMessage << player1Active->getName() << " used " << moves << "!" << endl;
				player1Active->MonsterMove[i].PP--;
				int dodge = rand() % 100 + 1;
				int accuracyDice = rand() % 100 + 1;
				int paralyzeDice = rand() % 100 + 1;
				if (dodge <= dodgeRate)
				{
					cout << blank << "Miss!" << endl;
				}
				else if (accuracyDice > currentMove.accuracy)
				{
					cout << blank << player2Active->getName() << " avoided the attack!" << endl;
				}
				else if (paralyzeDice <= 25 && player1MonsterParalyzed)
				{
					cout << blank << player1Active->getName() << " is paralyzed!" << endl;
					cout << blank << "It can't move!" << endl;
				}
				//if no miss then cause damage
				else
				{
					int dealtdamage = CalculateDamage(currentMove, player2Active, player1Active);
					player2Active->HP -= dealtdamage;
					cout << blank << moves << " deals " << dealtdamage << " damage!" << endl;
					//if defender's pokemon die
					if (player2Active->HP <= 0)
					{
						player2Active->HP = 0;
						cout << blank << player2Active->getName() << " fainted!" << endl;
						checkCondition(player2, "player2");
						player2MonsterBurned = false;
						player2MonsterBurnedRound = 0;
						player2MonsterPoisoned = false;
						player2MonsterPoisonedRound = 0;
						player2MonsterParalyzed = false;
						player2MonsterParalyzedRound = 0;
						player2Active = &player2[nextMonster];//turn current pokemon to next one pokemon
						nextMonster++;
						player2FirstRoundFreeze = true;
					}
				}
				turns++;
				if ((turns - 1) % 2 == 0)
				{
					TURN = (turns - 1) / 2 + 1;
					RoundStart();
				}
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

bool GameManager::Player2Battle(string moves, bool& player1MonsterFainted)
{
	turnMessage = "[Turn " + to_string(TURN) + "] ";
	if (player2FirstRoundFreeze)
	{
		cout << turnMessage << "Go! " << player2Active->getName() << "!" << endl;
		player2FirstRoundFreeze = false;
		turns++;
		if ((turns - 1) % 2 == 0)
		{
			TURN = (turns - 1) / 2 + 1;
			RoundStart();
		}
		return true;
	}
	Move currentMove = Move();
	for (int i = 0; i < player2Active->MonsterMove.size(); i++)
	{
		if (moves == player2Active->MonsterMove[i].getName())
		{
			currentMove = player2Active->MonsterMove[i];
			if (player2Active->MonsterMove[i].PP == 0)
			{
				cout << turnMessage << "Not enough PP!" << endl;
				return false;
			}
			else
			{
				cout << turnMessage << "The opposing " << player2Active->getName() << " used " << moves << "!" << endl;
				player2Active->MonsterMove[i].PP--;
				int dodge = rand() % 100 + 1;
				int accuracyDice = rand() % 100 + 1;
				int paralyzeDice = rand() % 100 + 1;
				//check whether any miss
				if (dodge <= dodgeRate)
				{
					cout << blank << "Miss!" << endl;
				}
				else if (accuracyDice > currentMove.accuracy)
				{
					cout << blank << player1Active->getName() << " avoided the attack!" << endl;
				}
				else if (paralyzeDice <= 25 && player2MonsterParalyzed)
				{
					cout << blank << "The opposing " << player2Active->getName() << " is paralyzed!" << endl;
					cout << blank << "It can't move!" << endl;
				}
				else
				{
					int dealtdamage = CalculateDamage(currentMove, player1Active, player2Active);
					player1Active->HP -= dealtdamage;
					cout << blank << moves << " deals " << dealtdamage << " damage!" << endl;
					//if player1 pokemon die
					if (player1Active->HP <= 0)
					{
						player1Active->HP = 0;
						cout << blank << player1Active->getName() << " fainted!" << endl;
						checkCondition(player1, "player1");
						player1MonsterFainted = true;
					}
				}
				turns++;
				if ((turns - 1) % 2 == 0)
				{
					TURN = (turns - 1) / 2 + 1;
					RoundStart();
				}
				return true;
			}
		}
	}
	if (currentMove.getName() == "NULL")
	{
		cout << turnMessage << "No such move! " << moves << endl;
		return false;
	}
}
//use potion to Pokemon
void GameManager::useItem(string item, string chosenMonster)
{
	turnMessage = "[Turn " + to_string(TURN) + "] ";
	for (int i = 0; i < player1.size(); i++)
	{
		//use potion to chosen pokemon
		if (chosenMonster == player1[i].getName())
		{
			//use potion
			if (item == "Potion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 20) ? player1[i].maxHP - player1[i].HP : 20;
				player1[i].HP += 20;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			//use super potion
			if (item == "SuperPotion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 60) ? player1[i].maxHP - player1[i].HP : 60;
				player1[i].HP += 60;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Super Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			//use hyper potion
			if (item == "HyperPotion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 120) ? player1[i].maxHP - player1[i].HP : 120;
				player1[i].HP += 120;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Hyper Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			//use Max potion
			if (item == "MaxPotion")
			{
				int recoveredHP = player1[i].maxHP - player1[i].HP;
				player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Max Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			turns++;
			if ((turns - 1) % 2 == 0)
			{
				TURN = (turns -1) / 2 + 1;
				RoundStart();
			}
		}
	}
}