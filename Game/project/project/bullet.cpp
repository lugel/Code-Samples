#include "precomH.h"

Bullet::Bullet(float radius, float maxSpeed, int R, int G, int B, int src) :currVelocity(0.f, 0.f), dmg(0)
{
	this->maxSpeed = maxSpeed;
	this->bulletShape.setRadius(radius);
	this->bulletShape.setFillColor(Color::Color(R, G, B));
	this->source = src;
}

void Bullet::setDmg(int dmg)
{
	this->dmg = dmg;
}

void Bullet::setSource(int src)
{
	this->source = src;
}

int Bullet::getDmg()
{
	return dmg;
}

int Bullet::getSource()
{
	return source;
}