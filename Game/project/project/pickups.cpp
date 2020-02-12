#include "precomH.h"

pickups::pickups()
{

}

pickups::pickups(const std::string& filename, int type, float amount) : object(filename)
{
	this->type = type;
	this->amount = amount;
}

int pickups::getType()
{
	return type;
}

float pickups::getAmount()
{
	return amount;
}
