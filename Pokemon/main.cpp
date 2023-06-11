//File : main.cpp
//Name : §fª@®p ¼B®a¦¨ ¤ý¬Rµ¾ ³¯©|¿A
//First Update : 2023/5/27
//Last Update : 2023/6/4
//Description : Pokemon
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
	srand(time(NULL));//set random seed
	string caseFileName;
	cout << "Enter case file name: ";
	cin >> caseFileName;
	ifstream CaseFile;
	CaseFile.open(caseFileName);
	string MonsterLibName, MoveLibName, GameDataName;//save the file name
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
	string tp;
	string ps;
	Type movetype = Normal;
	PhysicalSpecial phys;
	int power;
	int accuracy;
	int PP;
	string eff;
	AdditionalEffect effect = NOR;
	while (getline(Moves, line))
	{
		if (line == "") continue;//no input
		stringstream ss(line);
		ss >> movename;
		ss >> tp;
		movetype = Type(TypeMap[tp]);
		ss >> ps;
		phys = (ps == "Physical") ? Physical : (ps == "Special" ? Special : Status);
		ss >> power;
		ss >> accuracy;
		ss >> PP;
		ss >> eff;
		if (eff == "PAR")
		{
			effect = PAR;
		}
		else if (eff == "BRN")
		{
			effect = BRN;
		}
		else if (eff == "PSN")
		{
			effect = PSN;
		}
		else effect = NOR;
		MoveLib.push_back(Move(movename, movetype, phys, power, accuracy, PP, effect));
		effect = NOR;
		eff = "";
	}
	Moves.close();
	vector<Monster> Player1Monster;	//save all player1 monster then it will be use on constructure of GameManager
	vector<Monster> Player2Monster;	//save all player2 monster then it will be use on constructure of GameManager
	ifstream GameData(GameDataName);
	int Player1MonsterNum;
	//read the number of monster
	GameData >> Player1MonsterNum;
	for (int i = 0; i < Player1MonsterNum; i++)
	{
		//read the monster from GaemDataName
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
		//read the skill from GaemDataName
		int skillnum;
		//read the number of skill
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
	//read the number of monster
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
		//read the number of skill
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
	bool player1MonsterFainted = false;
	map<string, int> Player1Item;
	map<string, int> Player1MonLib;
	int nowPlayer = 0;
	GameManager GM(Player1Monster, Player2Monster);
	string command;
	while (CaseFile >> command && !CaseFile.eof())
	{
		if (start) nowPlayer = GM.getNowPlayer();
		if (player1MonsterFainted || GM.player1MonsterFainted)
		{
			if (command != "Pokemon")
			{
				cout << "Player 1's monster has fainted. Please switch to another monster." << endl;
				continue;
			}
		}
		//test mode
		if (command == "Test")
		{
			testModeActive = true;
			GM.TestModeActive();
			cout << "Attention: Test Mode Activated." << endl;
		}
		//command is pokemon then swap pokemon
		if (command == "Pokemon")
		{
			if (start == false)
			{
				cout << "Game is not started!" << endl;
				continue;
			}
			Player1MonLib = GM.browseMonster();
			string command1, command2;
			CaseFile >> command1;//chose monster
			while (Player1MonLib.find(command1) == Player1MonLib.end() && !CaseFile.eof())
			{
				cout << "Invalid monster name. Please enter again." << endl;
				CaseFile >> command1;	//read pokemon name again to it is correct
			}
			while (Player1MonLib[command1] == 0 && !CaseFile.eof())
			{
				cout << "The Monster you have chosen has fainted. Please choose another one." << endl;
				CaseFile >> command1;	//read pokemon name again to it is correct
			}
			GM.swapMonster(command1);
			player1MonsterFainted = false;
			GM.player1MonsterFainted = false;
			if (!CaseFile.eof()) CaseFile >> command2;
			while (GM.Player2Battle(command2, player1MonsterFainted) == false && !CaseFile.eof()) CaseFile >> command2;
		}
		if (command == "Battle")
		{
			if (start == false)
			{
				start = true;
				GM.GameStart();
			}
			string command1, command2;
			if (!CaseFile.eof()) CaseFile >> command1 >> command2;
			nowPlayer = GM.getNowPlayer();
			if (nowPlayer == 1)
			{
				while (GM.Player1Battle(command1) == false && !CaseFile.eof()) CaseFile >> command1;
				while (GM.Player2Battle(command2, player1MonsterFainted) == false && !CaseFile.eof()) CaseFile >> command2;
			}
			else
			{
				while (GM.Player2Battle(command2, player1MonsterFainted) == false && !CaseFile.eof()) CaseFile >> command2;
				if (player1MonsterFainted) continue;
				while (GM.Player1Battle(command1) == false && !CaseFile.eof()) CaseFile >> command1;
			}
		}
		if (command == "Bag")
		{
			//game hasn't start
			if (start == false)
			{
				cout << "Game is not started!" << endl;
				continue;
			}
			//player cannot use bag
			if (nowPlayer != 1)
			{
				cout << "It's not your turn!" << endl;
			}
			else
			{
				cout << "Item's available: \"Potion\", \"SuperPotion\", \"HyperPotion\", \"MaxPotion\"." << endl;
				Player1Item = GM.browseBag();//show all player can use potion
				string item;
				CaseFile.ignore();
				if (!CaseFile.eof()) getline(CaseFile, item);
				//cannnot find this item
				while (Player1Item.find(item) == Player1Item.end() && !CaseFile.eof())
				{
					cout << "No such item!" << endl;
					getline(CaseFile, item);	//read again
				}
				while (Player1Item[item] == 0 && !CaseFile.eof())
				{
					cout << "The item you have chosen is depleted!" << endl;
					getline(CaseFile, item);	//read again
				}
				Player1MonLib = GM.browseMonster();
				string chosenMonster;
				if (!CaseFile.eof()) CaseFile >> chosenMonster;//chose use potion to waht monster
				while (Player1MonLib.find(chosenMonster) == Player1MonLib.end() && !CaseFile.eof())
				{
					cout << "Invalid monster name. Please enter again." << endl;
					CaseFile >> chosenMonster;//read again
				}
				while (Player1MonLib[chosenMonster] == 0 && !CaseFile.eof())
				{
					cout << "The Monster you have chosen has fainted. Please choose another one." << endl;
					CaseFile >> chosenMonster;	//read pokemon name again to it is correct
				}
				GM.useItem(item, chosenMonster);
				string player2move;
				if (!CaseFile.eof()) CaseFile >> player2move;
				while(GM.Player2Battle(player2move, player1MonsterFainted) == false && !CaseFile.eof()) CaseFile >> player2move;
			}
		}
		//check game status 
		if (command == "Status")
		{
			if (start == false)
			{
				cout << "Game is not started!" << endl;
				continue;
			}
			GM.showStatus();
		}
		if (command == "Check") //DEV ONLY
		{
			GM.browseMove();
		}
		if (command == "Run")
		{
			system("pause");
			exit(1);
		}
	}
	system("pause");
}