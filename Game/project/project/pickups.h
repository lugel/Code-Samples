#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "object.h"

class pickups :public object
{
public:
	pickups();
	pickups(const std::string&, int, float);
	int getType();
	float getAmount();

private:
	int type;
	float amount;
};