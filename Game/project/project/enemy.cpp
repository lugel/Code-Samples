#include "precomH.h"

enemy::enemy(const std::string& filepath, bool type) : character(filepath, MOBHP, MOBSPEED, RANGEMOBDMG, MOBAS, 0.f, 0.f)
{
	this->type = type;
}

void enemy::shootPlayer(std::vector<Bullet>& Bullets, Bullet& b2, player isaac)
{

	b2.setDmg(this->getDmg() * 10);
	b2.setSource(0);
	b2.bulletShape.setPosition(this->getPos());
	b2.currVelocity = (sf::Vector2f(isaac.getPos()) - this->getPos()) * b2.maxSpeed /
		sqrt(pow((sf::Vector2f(isaac.getPos()) - this->getPos()).x, 2) +
			pow((sf::Vector2f(isaac.getPos()) - this->getPos()).y, 2));
	Bullets.push_back(Bullet(b2));

}

void enemy::runtoPlayer(player isaac)
{
	this->sp.move(getMov(isaac)*0.1f);
}

void enemy::checkBoundsMob(float x, float y, std::vector<terrain>& environment)
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

Vector2f enemy::getMov(player isaac)
{
	return (sf::Vector2f(isaac.getPos()) - this->getPos()) * this->getSpeed() /
		sqrt(pow((sf::Vector2f(isaac.getPos()) - this->getPos()).x, 2) +
			pow((sf::Vector2f(isaac.getPos()) - this->getPos()).y, 2));
}

bool enemy::getType()
{
	return type;
}