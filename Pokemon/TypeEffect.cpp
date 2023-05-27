#include "TypeEffect.h"

TypeEffect::TypeEffect()
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			typeEff[i][j] = 1;
		}
	}
	//attacker normal
	{
		typeEff[Normal][Normal] = 0.5;
		typeEff[Normal][Ghost] = 0;
		typeEff[Normal][Steel] = 0.5;
	}
	//attacker Fire
	{
		typeEff[Fire][Fire] = 0.5;
		typeEff[Fire][Water] = 0.5;
		typeEff[Fire][Grass] = 2;
		typeEff[Fire][Ice] = 2;
		typeEff[Fire][Bug] = 2;
		typeEff[Fire][Rock] = 0.5;
		typeEff[Fire][Dragon] = 0.5;
		typeEff[Fire][Steel] = 2;
	}
	//attacker Water
	{
		typeEff[Water][Fire] = 2;
		typeEff[Water][Water] = 0.5;
		typeEff[Water][Grass] = 0.5;
		typeEff[Water][Ground] = 2;
		typeEff[Water][Rock] = 2;
		typeEff[Water][Dragon] = 0.5;
	}
	//attacker Electric
	{
		typeEff[Electric][Water] = 2;
		typeEff[Electric][Electric] = 0.5;
		typeEff[Electric][Grass] = 0.5;
		typeEff[Electric][Ground] = 0;
		typeEff[Electric][Flying] = 2;
		typeEff[Electric][Dragon] = 0.5;
	}
	//attacker Grass
	{
		typeEff[Grass][Fire] = 0.5;
		typeEff[Grass][Water] = 2;
		typeEff[Grass][Grass] = 0.5;
		typeEff[Grass][Poison] = 0.5;
		typeEff[Grass][Ground] = 2;
		typeEff[Grass][Flying] = 0.5;
		typeEff[Grass][Bug] = 0.5;
		typeEff[Grass][Rock] = 2;
		typeEff[Grass][Dragon] = 0.5;
		typeEff[Grass][Steel] = 0.5;
	}
	//attacker Ice
	{
		typeEff[Ice][Fire] = 0.5;
		typeEff[Ice][Water] = 0.5;
		typeEff[Ice][Grass] = 2;
		typeEff[Ice][Ice] = 0.5;
		typeEff[Ice][Ground] = 2;
		typeEff[Ice][Flying] = 2;
		typeEff[Ice][Dragon] = 2;
		typeEff[Ice][Steel] = 0.5;
	}
	//attacker Fighting
	{
		typeEff[Fighting][Normal] = 2;
		typeEff[Fighting][Ice] = 2;
		typeEff[Fighting][Poison] = 0.5;
		typeEff[Fighting][Flying] = 0.5;
		typeEff[Fighting][Psychic] = 0.5;
		typeEff[Fighting][Bug] = 0.5;
		typeEff[Fighting][Rock] = 2;
		typeEff[Fighting][Ghost] = 0;
		typeEff[Fighting][Dark] = 2;
		typeEff[Fighting][Steel] = 2;
		typeEff[Fighting][Fairy] = 0.5;
	}
	//attacker Poison
	{
		typeEff[Poison][Grass] = 2;
		typeEff[Poison][Poison] = 0.5;
		typeEff[Poison][Ground] = 0.5;
		typeEff[Poison][Rock] = 0.5;
		typeEff[Poison][Ghost] = 0.5;
		typeEff[Poison][Steel] = 0;
		typeEff[Poison][Fairy] = 2;
	}
	//attacker Ground
	{
		typeEff[Ground][Fire] = 2;
		typeEff[Ground][Electric] = 2;
		typeEff[Ground][Grass] = 0.5;
		typeEff[Ground][Poison] = 2;
		typeEff[Ground][Flying] = 0;
		typeEff[Ground][Bug] = 0.5;
		typeEff[Ground][Rock] = 2;
		typeEff[Ground][Steel] = 2;
	}
	//attacker Flying
	{
		typeEff[Flying][Electric] = 0.5;
		typeEff[Flying][Grass] = 2;
		typeEff[Flying][Fighting] = 2;
		typeEff[Flying][Bug] = 2;
		typeEff[Flying][Rock] = 0.5;
		typeEff[Flying][Steel] = 0.5;
	}
	//attacker Psychic
	{
		typeEff[Psychic][Fighting] = 2;
		typeEff[Psychic][Poison] = 2;
		typeEff[Psychic][Psychic] = 0.5;
		typeEff[Psychic][Dark] = 0;
		typeEff[Psychic][Steel] = 0.5;
	}
	//attacker Bug
	{
		typeEff[Bug][Fire] = 0.5;
		typeEff[Bug][Grass] = 2;
		typeEff[Bug][Fighting] = 0.5;
		typeEff[Bug][Poison] = 0.5;
		typeEff[Bug][Flying] = 0.5;
		typeEff[Bug][Psychic] = 2;
		typeEff[Bug][Ghost] = 0.5;
		typeEff[Bug][Dark] = 2;
		typeEff[Bug][Steel] = 0.5;
		typeEff[Bug][Fairy] = 0.5;
	}
	//attacker Rock
	{
		typeEff[Rock][Fire] = 2;
		typeEff[Rock][Ice] = 2;
		typeEff[Rock][Fighting] = 0.5;
		typeEff[Rock][Ground] = 0.5;
		typeEff[Rock][Flying] = 2;
		typeEff[Rock][Bug] = 2;
		typeEff[Rock][Steel] = 0.5;
	}
	//attacker Ghost
	{
		typeEff[Ghost][Normal] = 0;
		typeEff[Ghost][Psychic] = 2;
		typeEff[Ghost][Ghost] = 2;
		typeEff[Ghost][Dark] = 0.5;
	}
	//attacker Dragon
	{
		typeEff[Dragon][Ghost] = 2;
		typeEff[Dragon][Steel] = 0.5;
		typeEff[Dragon][Fairy] = 0;
	}
	//attacker Dark
	{
		typeEff[Dark][Fighting] = 0.5;
		typeEff[Dark][Psychic] = 2;
		typeEff[Dark][Rock] = 2;
		typeEff[Dark][Dark] = 0.5;
		typeEff[Dark][Fairy] = 0.5;
	}
	//attacker Steel
	{
		typeEff[Steel][Fire] = 0.5;
		typeEff[Steel][Water] = 0.5;
		typeEff[Steel][Electric] = 0.5;
		typeEff[Steel][Ice] = 2;
		typeEff[Steel][Rock] = 2;
		typeEff[Steel][Steel] = 0.5;
		typeEff[Steel][Fairy] = 2;
	}
	//attacker Fairy
	{
		typeEff[Fairy][Fire] = 0.5;
		typeEff[Fairy][Fighting] = 2;
		typeEff[Fairy][Poison] = 0.5;
		typeEff[Fairy][Ghost] = 2;
		typeEff[Fairy][Dragon] = 2;
		typeEff[Fairy][Steel] = 0.5;
	}
}
TypeEffect::~TypeEffect()
{
}
float TypeEffect::TypePower(Type attacker, Type deffender) {
	return typeEff[attacker][deffender];
}