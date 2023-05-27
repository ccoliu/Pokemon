#include <iostream>
#include <fstream>
#include <map>
#include "Monster.h"
#include "Move.h"
using namespace std;

map<string, int> TypeMap = { {"Normal", 0}, {"Fire", 1}, {"Water", 2}, {"Electric", 3}, {"Grass", 4}, {"Ice", 5}, {"Fighting", 6}, {"Poison", 7}, {"Ground", 8}, {"Flying", 9}, {"Psychic", 10}, {"Bug", 11}, {"Rock", 12}, {"Ghost", 13}, {"Dragon", 14}, {"Dark", 15}, {"Steel", 16}, {"Fairy", 17} };

int main()
{
	vector<Monster> MonsterLib;
	ifstream PokemonLib;
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
}