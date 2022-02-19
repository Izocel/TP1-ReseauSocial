#pragma once

#include <iostream>
#include <string>


/// <summary>
/// Struct Message:
/// Représente la structure d'un message de conversation entre deux membres.
/// </summary>
struct Message
{
private:
	std::string m_texte;
	std::string m_source;
	std::time_t m_date;
};

