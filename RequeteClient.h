#pragma once

#include <iostream>
#include <string>

#include "Membre.h"
#include "Message.h"

template <class T>

class RequeteClient
{
public:
	std::string m_nom;
	std::string m_clientUuid;
	T m_data;
};

