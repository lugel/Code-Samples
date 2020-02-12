#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;

class Bullet
{
public:
	CircleShape bulletShape;
	Vector2f currVelocity;
	float maxSpeed;

	void setDmg(int);
	void setSource(int);

	int getDmg();
	int getSource();

	Bullet(float, float, int, int, int, int);
private:
	int dmg;
	int source;

};
