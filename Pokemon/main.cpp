#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Monster.h"
#include "Move.h"
#include "GameManager.h"
using namespace std;

map<string, int> TypeMap = { {"Normal", 0}, {"Fire", 1}, {"Water", 2}, {"Electric", 3}, {"Grass", 4}, {"Ice", 5}, {"Fighting", 6}, {"Poison", 7}, {"Ground", 8}, {"Flying", 9}, {"Psychic", 10}, {"Bug", 11}, {"Rock", 12}, {"Ghost", 13}, {"Dragon", 14}, {"Dark", 15}, {"Steel", 16}, {"Fairy", 17} };


int main()
{
	srand(time(NULL));
	ifstream CaseFile;
	CaseFile.open("case.txt");
	string MonsterLibName, MoveLibName, GameDataName;
	bool testModeActive = false;

	CaseFile >> MonsterLibName;
	CaseFile >> MoveLibName;
	CaseFile >> GameDataName;
	vector<Monster> MonsterLib;
	vector<Move> MoveLib;
	ifstream PokemonLib;
	ifstream Moves;
	PokemonLib.open(MonsterLibName);
	string name;
	int typenum;
	vector<Type> type;
	int HP;
	int attack;
	int defense;
	int SPattack;
	int SPdefense;
	int speed;
	while (PokemonLib >> name)
	{
		PokemonLib >> typenum;
		type.clear();
		for (int i = 0; i < typenum; i++)
		{
			string temp;
			PokemonLib >> temp;
			type.push_back(Type(TypeMap[temp]));
		}
		PokemonLib >> HP;
		PokemonLib >> attack;
		PokemonLib >> defense;
		PokemonLib >> SPattack;
		PokemonLib >> SPdefense;
		PokemonLib >> speed;
		MonsterLib.push_back(Monster(name, type, HP, attack, defense, SPattack, SPdefense, speed));
	}
	PokemonLib.close();
	Moves.open(MoveLibName);
	string line = "";
	string movename;
	Type movetype;
	PhysicalSpecial phys;
	int power;
	int accuracy;
	int PP;
	AdditionalEffect effect = NOR;
	while (getline(Moves, line))
	{
		if (line == "") continue;
		stringstream ss(line);
		ss >> movename;
		string temp;
		ss >> temp;
		movetype = Type(TypeMap[temp]);
		ss >> temp;
		phys = (temp == "Physical") ? Physical : Special;
		ss >> power;
		ss >> accuracy;
		ss >> PP;
		ss >> temp;
		if (temp == "PAR")
		{
			effect = PAR;
		}
		else if (temp == "BRN")
		{
			effect = BRN;
		}
		else if (temp == "PSN")
		{
			effect = PSN;
		}
		MoveLib.push_back(Move(movename, movetype, phys, power, accuracy, PP, effect));
		effect = NOR;
	}
	Moves.close();
	vector<Monster> Player1Monster;
	vector<Monster> Player2Monster;
	ifstream GameData(GameDataName);
	int Player1MonsterNum;
	GameData >> Player1MonsterNum;
	for (int i = 0; i < Player1MonsterNum; i++)
	{
		string temp;
		GameData >> temp;
		for (int j = 0; j < MonsterLib.size(); j++)
		{
			if (MonsterLib[j].getName() == temp)
			{
				Player1Monster.push_back(MonsterLib[j]);
				break;
			}
		}
		int skillnum;
		GameData >> skillnum;
		for (int j = 0; j < skillnum; j++)
		{
			GameData >> temp;
			for (int k = 0; k < MoveLib.size(); k++)
			{
				if (MoveLib[k].getName() == temp)
				{
					Player1Monster[i].addMove(MoveLib[k]);
					break;
				}
			}
		}
	}
	int Player2MonsterNum;
	GameData >> Player2MonsterNum;
	for (int i = 0; i < Player2MonsterNum; i++)
	{
		string temp;
		GameData >> temp;
		for (int j = 0; j < MonsterLib.size(); j++)
		{
			if (MonsterLib[j].getName() == temp)
			{
				Player2Monster.push_back(MonsterLib[j]);
				break;
			}
		}
		int skillnum;
		GameData >> skillnum;
		for (int j = 0; j < skillnum; j++)
		{
			GameData >> temp;
			for (int k = 0; k < MoveLib.size(); k++)
			{
				if (MoveLib[k].getName() == temp)
				{
					Player2Monster[i].addMove(MoveLib[k]);
					break;
				}
			}
		}
	}

	bool start = false;
	int nowPlayer = 0;
	GameManager GM(Player1Monster, Player2Monster);
	string command;
	while (CaseFile >> command)
	{
		if (command == "Test")
		{
			testModeActive = true;
			cout << "Attention: Test Mode Activated." << endl;
		}
		if (command == "Battle")
		{
			if (start == false)
			{
				start = true;
				GM.GameStart();
			}
			string command1, command2;
			CaseFile >> command1 >> command2;
			nowPlayer = GM.getNowPlayer();
			if (nowPlayer == 1)
			{
				while (GM.Player1Battle(command1) == false) CaseFile >> command1;
				while (GM.Player2Battle(command2) == false) CaseFile >> command2;
			}
			else
			{
				while (GM.Player2Battle(command1) == false) CaseFile >> command1;
				while (GM.Player1Battle(command2) == false) CaseFile >> command2;
			}
		}
		if (command == "Status")
		{
			if (start == false) cout << "Game is not started!" << endl;
			GM.showStatus();
		}
		if (command == "Run")
		{
			exit(1);
		}
	}
}