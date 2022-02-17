#pragma once

#include <iostream>
#include <string>


class Message
{
private:
	int m_length{0};
	std::string m_texte;
	std::string m_cible;
	std::string m_source;
	std::time_t m_date;
};

