#include "precomH.h"

character::character() {};

character::character(const std::string& filepath, int hp, float speed, int damage, float attackspeed, float x, float y) : object(filepath)
{
	this->hp = hp;
	this->speed = speed;
	this->damage = damage;
	this->attackspeed = attackspeed;
	this->sp.setPosition(x, y);
}

void character::checkBounds(float x , float y, std::vector<terrain>& environment)
{
	for (size_t i = 0; i < environment.size(); i++)
	{
		if ((this->sp.getGlobalBounds().intersects(environment[i].sp.getGlobalBounds())) &&
			!(environment[i].getpassable()))
		{
			this->sp.move(-x, -y);
		}
	}
}

//SETTERS
void character::setHp(int hp)
{
	this->hp = hp;
}

void character::setSpeed(float change)
{
	this->speed = change;
}

void character::setDmg(int dmg)
{
	this->damage = dmg;
}

void character::setAttackSpeed(float as)
{
	this->attackspeed = as;
}

//GETTERS
sf::Vector2f character::getPos()
{
	return sf::Vector2f(this->sp.getPosition().x + 25.f, this->sp.getPosition().y + 20.0);
}

int character::getHp()
{
	return hp;
}

float character::getSpeed()
{
	return speed;
}

int character::getDmg()
{
	return damage;
}

float character::getAttackSpeed()
{
	return attackspeed;
}