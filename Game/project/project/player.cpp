#include "precomH.h"

player::player(const std::string& filepath) : character(filepath, PLAYERHP, STEP, PLAYERDMG, PLAYERAS, 0.f, 0.f)
{

}

void player::shooting(sf::RenderWindow& window, std::vector<Bullet>& bullets, Bullet& b)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		b.setDmg(this->getDmg());
		b.setSource(1);
		b.bulletShape.setPosition(this->getPos());
		b.currVelocity = (sf::Vector2f(Mouse::getPosition(window)) - this->getPos()) * b.maxSpeed /
			sqrt(pow((sf::Vector2f(sf::Mouse::getPosition(window)) - this->getPos()).x, 2) +
				pow((sf::Vector2f(sf::Mouse::getPosition(window)) - this->getPos()).y, 2));
		bullets.push_back(Bullet(b));
	}
}



void player::moving(sf::RenderWindow& window, std::vector<terrain>& environment)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->sp.move(-this->getSpeed(), 0.f);
		checkBounds(-this->getSpeed(), 0.f, environment);
	}
	if (this->sp.getPosition().x < 0)
		this->sp.move(this->getSpeed(), 0.f);

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->sp.move(this->getSpeed(), 0.f);
		checkBounds(this->getSpeed(), 0.f, environment);
	}
	if (this->sp.getPosition().x > window.getSize().x - this->sp.getGlobalBounds().width)
		this->sp.move(-this->getSpeed(), 0.f);

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->sp.move(0.f, -this->getSpeed());
		checkBounds(0.f, -this->getSpeed(), environment);
	}
	if (this->sp.getPosition().y < 0)
		this->sp.move(0.f, this->getSpeed());

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->sp.move(0.f, this->getSpeed());
		checkBounds(0.f, this->getSpeed(), environment);
	}
	if (this->sp.getPosition().y > window.getSize().y - this->sp.getGlobalBounds().height)
		this->sp.move(0.f, -this->getSpeed());
}

bool player::getAlive()
{
	return alive;
}
void player::dead()
{
	Vector2f currpos = this->getPos();
	this->setTexture("rip.png");
	this->sp.setScale(0.3f,0.3f);
	this->sp.setPosition(currpos);
	this->alive = false;
	this->setSpeed(0.f);
}