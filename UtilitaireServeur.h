#pragma once

#include <iostream>
#include <string>
#include <random>

#include "Membre.h"

/// <summary>
/// Instances pour la génération de nombre aléatoire
/// </summary>
std::random_device rd;
std::mt19937 RNG(rd());



/// <summary>
/// Génére un nombre aléatoire normaliser entre min et max
/// </summary>
/// <param name="min">minimum</param>
/// <param name="max">maximum</param>
/// <returns>Le nombre généré</returns>
const int rndInt(int min, int max)
{
	// dist sert à normaliser le nombre généré entre min et max
	std::uniform_int_distribution<> dist(min, max);
	return dist(RNG);
};



/// <summary>
/// Permet de générer un uuid de membre
/// </summary>
/// <param name="membre"></param>
/// <returns></returns>
const std::string uuidMembre(Membre& membre)
{
	return std::string();
}
