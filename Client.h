#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <map>

#include "UtilitaireClient.h"



class Client
{
private:
	std::string m_version;
	std::string m_uuid;
	std::string m_menu;
	Membre m_membreConnecter;
	std::chrono::time_point<std::chrono::system_clock> 
		m_clock{ std::chrono::system_clock::now() };
};

