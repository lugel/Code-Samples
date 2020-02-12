#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "object.h"

class character : public object
{
public:
	character();
	character(const std::string&, int, float, int, float, float x, float y);
	void checkBounds(float, float, std::vector<terrain>&);

	void setHp(int);
	void setSpeed(float);
	void setDmg(int);
	void setAttackSpeed(float);


	sf::Vector2f getPos();
	int getHp();
	float getSpeed();
	int getDmg();
	float getAttackSpeed();

private:
	int hp;
	float speed;
	int damage;
	float attackspeed;
};