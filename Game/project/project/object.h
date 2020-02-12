#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class object
{
public:
	sf::Texture tx;
	sf::Sprite	sp;
	object();
	object(const std::string&);
	void setTexture(const std::string&);

};