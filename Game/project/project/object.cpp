#include "precomH.h"

object::object() {};

object::object(const std::string& filepath)
{
	tx.loadFromFile(filepath);
	sp = sf::Sprite(this->tx);
}

void object::setTexture(const std::string& filepath)
{
	(this->tx).loadFromFile(filepath);
	this->sp = sf::Sprite(this->tx);
}