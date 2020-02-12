#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "object.h"

class terrain : public object
{
public:
	terrain(const std::string&, bool, float);

	bool getpassable();
	float getspeedChange();

private:
	bool passable;
	float speedChange;
};