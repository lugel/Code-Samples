#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "character.h"

class enemy : public character
{
public:
	enemy(const std::string&, bool);
	void shootPlayer(std::vector<Bullet>&, Bullet&, player);
	void runtoPlayer(player);

	void checkBoundsMob(float, float, std::vector<terrain>&);

	bool getType();
	Vector2f getMov(player isaac);

private:
	bool type;
};
