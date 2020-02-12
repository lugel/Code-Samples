#include "precomH.h"

terrain::terrain(const std::string& filepath, bool passable, float speedChange) : object(filepath)
{
	this->passable = passable;
	this->speedChange = speedChange;
}

bool terrain::getpassable()
{
	return passable;
}

float terrain::getspeedChange()
{
	return speedChange;
}