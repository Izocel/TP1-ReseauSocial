#pragma once

#include <iostream>
#include <string>
#include <random>

#include "Membre.h"

/// <summary>
/// Instances pour la g�n�ration de nombre al�atoire
/// </summary>
std::random_device rd;
std::mt19937 RNG(rd());



/// <summary>
/// G�n�re un nombre al�atoire normaliser entre min et max
/// </summary>
/// <param name="min">minimum</param>
/// <param name="max">maximum</param>
/// <returns>Le nombre g�n�r�</returns>
const int rndInt(int min, int max)
{
	// dist sert � normaliser le nombre g�n�r� entre min et max
	std::uniform_int_distribution<> dist(min, max);
	return dist(RNG);
};



/// <summary>
/// Permet de g�n�rer un uuid de membre
/// </summary>
/// <param name="membre"></param>
/// <returns></returns>
const std::string uuidMembre(Membre& membre)
{
	return std::string();
}
