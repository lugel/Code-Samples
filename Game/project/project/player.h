#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "character.h"

class player : public character
{
public:
	player(const std::string&);
	void shooting(sf::RenderWindow&, std::vector<Bullet>&, Bullet&);
	void moving(sf::RenderWindow&, std::vector<terrain>&);
	void dead();
	bool getAlive();

private:
	bool alive = 1;

};