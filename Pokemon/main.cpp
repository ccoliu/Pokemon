#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Monster.h"
#include "Move.h"
using namespace std;

map<string, int> TypeMap = { {"Normal", 0}, {"Fire", 1}, {"Water", 2}, {"Electric", 3}, {"Grass", 4}, {"Ice", 5}, {"Fighting", 6}, {"Poison", 7}, {"Ground", 8}, {"Flying", 9}, {"Psychic", 10}, {"Bug", 11}, {"Rock", 12}, {"Ghost", 13}, {"Dragon", 14}, {"Dark", 15}, {"Steel", 16}, {"Fairy", 17} };

int main()
{
	vector<Monster> MonsterLib;
	vector<Move> MoveLib;
	ifstream PokemonLib;
	ifstream Moves;
	PokemonLib.open("PokemonLib.txt");
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
	Moves.open("MoveLib.txt");
	string line = "";
	string movename;
	Type movetype;
	PhysicalSpecial phys;
	int power;
	int accuracy;
	int PP;
	AdditionalEffect effect = NOR;
	while (getline(Moves,line))
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
	}
	Moves.close();
	vector<Monster> Player1Monster;
	vector<Monster> Player2Monster;
	ifstream GameData("GameData.txt");
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
		cout << Player1Monster[i] << endl;
	}
	cout << endl;
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
		cout << Player2Monster[i] << endl;
	}
}