#include "GameManager.h"
#include <string>

void GameManager::GameStart()
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

void GameManager::swapMonster(string chosenMonster)
{
	turnMessage = "[Turn " + to_string(turns) + "] ";
	player1MonsterParalyzed = false;
	player1MonsterBurned = false;
	player1MonsterPoisoned = false;
	player1MonsterParalyzedRound = 0;
	player1MonsterBurnedRound = 0;
	player1MonsterPoisonedRound = 0;
	for (int i = 0; i < player1.size(); i++)
	{
		if (player1[i].getName() == chosenMonster)
		{
			if (player1Active->HP != 0)
			{
				cout << turnMessage << player1Active->getName() << " switch out!" << endl;
				cout << blank << "Come back!" << endl;
			}
			player1Active = &player1[i];
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
	if ((turns - 1) % 2 == 0) RoundStart();
}

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

void GameManager::checkCondition(vector<Monster> player, string playername)
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

void GameManager::checkMonsterEffects()
{
	if (player1MonsterBurned)
	{
		player1Active->HP -= player1Active->maxHP / 16;
		cout << blank << player1Active->getName() << " is hurt by burn!" << endl;
		player1MonsterBurnedRound--;
		player1Active->appliedEffect[BRN] = player1MonsterBurnedRound;
		if (player1MonsterBurnedRound == 0)
		{
			player1MonsterBurned = false;
			cout << blank << player1Active->getName() << " is no longer burned!" << endl;
		}
	}
	if (player1MonsterPoisoned)
	{
		player1Active->HP -= player1Active->maxHP / 16;
		cout << blank << player1Active->getName() << " is hurt by its poisoning!" << endl;
		player1MonsterPoisonedRound--;
		player1Active->appliedEffect[PSN] = player1MonsterPoisonedRound;
		if (player1MonsterPoisonedRound == 0)
		{
			player1MonsterPoisoned = false;
			cout << blank << player1Active->getName() << " is no longer poisoned!" << endl;
		}
	}
	if (player1MonsterParalyzed)
	{
		player1Active->speed = player1Active->maxspeed / 2;
		player1MonsterParalyzedRound--;
		player1Active->appliedEffect[PAR] = player1MonsterParalyzedRound;
		if (player1MonsterParalyzedRound == 0)
		{
			player1MonsterParalyzed = false;
			player1Active->speed = player1Active->maxspeed;
			cout << blank << player1Active->getName() << " is no longer paralyzed!" << endl;
		}
	}

	if (player2MonsterBurned)
	{
		player2Active->HP -= player2Active->maxHP / 16;
		cout << blank << "The opposing " << player2Active->getName() << " is hurt by burn!" << endl;
		player2MonsterBurnedRound--;
		player2Active->appliedEffect[BRN] = player2MonsterBurnedRound;
		if (player2MonsterBurnedRound == 0)
		{
			player2MonsterBurned = false;
			cout << blank << player2Active->getName() << " is no longer burned!" << endl;
		}
	}
	if (player2MonsterPoisoned)
	{
		player2Active->HP -= player2Active->maxHP / 16;
		cout << blank << "The opposing " << player2Active->getName() << " is hurt by its poisoning!" << endl;
		player2MonsterPoisonedRound--;
		player2Active->appliedEffect[PSN] = player2MonsterPoisonedRound;
		if (player2MonsterPoisonedRound == 0)
		{
			player2MonsterPoisoned = false;
			cout << blank << player2Active->getName() << " is no longer poisoned!" << endl;
		}
	}
	if (player2MonsterParalyzed)
	{
		player2Active->speed = player2Active->maxspeed / 2;
		player2MonsterParalyzedRound--;
		player2Active->appliedEffect[PAR] = player2MonsterParalyzedRound;
		if (player2MonsterParalyzedRound == 0)
		{
			player2MonsterParalyzed = false;
			player2Active->speed = player2Active->maxspeed;
			cout << blank << player2Active->getName() << " is no longer paralyzed!" << endl;
		}
	}
}

void GameManager::RoundStart()
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

double GameManager::CalculateDamage(Move usedMove, Monster* defender, Monster* attacker)
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
	if (critDice <= critRate) { damage *= 1.5; cout << blank << "Critical hit!" << endl; }

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

	return damage;
}

bool GameManager::Player1Battle(string moves)
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

bool GameManager::Player2Battle(string moves, bool& player1MonsterFainted)
{
	turnMessage = "[Turn " + to_string(turns) + "] ";
	if (player2FirstRoundFreeze)
	{
		cout << turnMessage << "Go! " << player2Active->getName() << "!" << endl;
		player2FirstRoundFreeze = false;
		turns++;
		if ((turns - 1) % 2 == 0) RoundStart();
		return true;
	}
	Move currentMove = Move();
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
				int paralyzeDice = rand() % 100 + 1;
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
					if (player1Active->HP <= 0)
					{
						player1Active->HP = 0;
						cout << blank << player1Active->getName() << " fainted!" << endl;
						checkCondition(player1, "player1");
						player1MonsterFainted = true;
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
		cout << turnMessage << "No such move! " << moves << endl;
		return false;
	}
}

void GameManager::useItem(string item, string chosenMonster)
{
	turnMessage = "[Turn " + to_string(turns) + "] ";
	for (int i = 0; i < player1.size(); i++)
	{
		if (chosenMonster == player1[i].getName())
		{
			if (item == "Potion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 20) ? player1[i].maxHP - player1[i].HP : 20;
				player1[i].HP += 20;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "SuperPotion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 60) ? player1[i].maxHP - player1[i].HP : 60;
				player1[i].HP += 60;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Super Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "HyperPotion")
			{
				int recoveredHP = (player1[i].maxHP - player1[i].HP < 120) ? player1[i].maxHP - player1[i].HP : 120;
				player1[i].HP += 120;
				if (player1[i].HP > player1[i].maxHP) player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Hyper Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			if (item == "MaxPotion")
			{
				int recoveredHP = player1[i].maxHP - player1[i].HP;
				player1[i].HP = player1[i].maxHP;
				cout << turnMessage << player1[i].getName() << " has used Max Potion!" << endl;
				cout << blank << player1[i].getName() << " recovered " << recoveredHP << " HP!" << endl;
				player1Bag[item]--;
			}
			turns++;
			if ((turns - 1) % 2 == 0) RoundStart();
		}
	}
}
