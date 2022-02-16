#pragma once
#include <iostream>
#include <sstream>
#include <chrono>

#include "UtilitaireClient.h"



class Client
{
public:
	Client();
	std::map<std::string, std::string> formulaireMembre();
	std::map<std::string, std::string> formulaireMessage(std::string uuidMembre);
private:
	std::string m_version;
	std::string m_uuid;
	std::string m_menu;
	Membre m_membreConnecter;
	std::chrono::time_point<std::chrono::system_clock> 
		m_clock{ std::chrono::system_clock::now() };
};

