#include "precomH.h"
using namespace sf;

player isaac("isaac.png");
enemy mobR("enemyR.png", Ranged);
enemy mobM("enemyM.png", Melee);
terrain stone("stone.png", IMPASSABLE, 1.f);
terrain sand("sand.png", PASSABLE, 0.5f);
pickups hp("heart.png", HP, PICKUPSHP);
pickups dmg("star.png", DMG, PICKUPSDMG);
pickups as("aspeed.png", AS, PICKUPSAS);
Bullet bplayer(PLAYERBULLETSIZE, PLAYERBULLETSPEED, 91, 109, 0, Pb);
Bullet bmob(MOBBULLETSIZE, MOBBULLETSPEED, 255, 47, 109, Eb);

std::vector<Bullet> bullets;
std::vector<enemy> enemies;
std::vector<terrain> environment;
std::vector<pickups> bonuses;

game& game::getInstance()
{
	static game self;
	return self;
}

game::game() : window(VideoMode(WIDTH, HEIGHT), "Issac - shooter", Style::Default)
{
	srand(time(NULL));
	window.setFramerateLimit(FPS);

	background.loadFromFile("background.png");
	sbackground.setTexture(background);
	sbackground.setScale(Vector2f(1.5f, 1.5f));

	//Terrain
	stone.sp.setScale(SCALE, SCALE);
	sand.sp.setScale(SCALE, SCALE);

	//Player
	isaac.sp.setScale(SCALE, SCALE);

	//Bonus
	hp.sp.setScale(SCALE*0.5f, SCALE*0.5f);
	dmg.sp.setScale(SCALE*0.5f, SCALE*0.5f);
	as.sp.setScale(SCALE, SCALE);

	//Background
	background.loadFromFile("background.png");

	//Enemy
	mobR.sp.setScale(SCALE, SCALE);
	mobM.sp.setScale(0.4f, 0.4f);
	mobM.setDmg(MELEEMOBDMG);

}

void game::loadlevel(int number, Text& currHP, Text& currDMG, Text& currAS)
{
	std::fstream file;
	try
	{
		file.open("level" + std::to_string(number) + ".txt");
	}
	catch (...)
	{
		std::cout << "Couldn't open given filename";
	}

	//Blocks load - from file
	int loaded;

	for (size_t i = 0; i < (HEIGHT / SCALED); i++)
	{
		for (size_t j = 0; j < (WIDTH / SCALED); j++)
		{
			file >> loaded;
			switch (loaded)
			{
			case Nothing: break;
			case Stone:
				stone.sp.setPosition(Vector2f(j * SCALED, i * SCALED));
				environment.push_back(terrain(stone));
				break;
			case Sand:
				sand.sp.setPosition(Vector2f(j * SCALED, i * SCALED));
				environment.push_back(terrain(sand));
				break;
			}
		}
	}
	file.close();


	//Spawn enemies on board
	do
	{
		int isRanged = rand() % 2;

		if (isRanged)
		{
			mobR.sp.setPosition(Vector2f(rand() % (window.getSize().x - MOBBORDER), rand() % (window.getSize().y - MOBBORDER)));
			enemies.push_back(enemy(mobR));
		}
		else
		{
			mobM.sp.setPosition(Vector2f(rand() % (window.getSize().x - MOBBORDER), rand() % (window.getSize().y - MOBBORDER)));
			enemies.push_back(enemy(mobM));
		}

		//Check if spawing on walls
		for (size_t j = 0; j < environment.size(); j++)
		{
			if (enemies.back().sp.getGlobalBounds().intersects(environment[j].sp.getGlobalBounds()) &&
				(!(environment[j].getpassable())))
			{
				enemies.erase(enemies.end() - 1);
				break;
			}
		}

	} while (enemies.size() < (MOBCOUNT + number * 2));


	//Spawn bonuses
	do
	{
		int whichBonus = rand() % 5;

		switch (whichBonus)
		{
		case DMG:
			dmg.sp.setPosition(Vector2f(rand() % (window.getSize().x - 100), rand() % (window.getSize().y - 100)));
			bonuses.push_back(pickups(dmg));
			break;

		case AS:
			as.sp.setPosition(Vector2f(rand() % (window.getSize().x - 100), rand() % (window.getSize().y - 100)));
			bonuses.push_back(pickups(as));
			break;
		default:
			hp.sp.setPosition(Vector2f(rand() % (window.getSize().x - 100), rand() % (window.getSize().y - 100)));
			bonuses.push_back(pickups(hp));
			break;
		}

		//Check if spawing on walls
		for (size_t j = 0; j < environment.size(); j++)
		{
			if ((bonuses.back().sp.getGlobalBounds().intersects(environment[j].sp.getGlobalBounds())) &&
				(!(environment[j].getpassable())))
			{
				bonuses.erase(bonuses.end() - 1);
				break;
			}
		}

	} while (bonuses.size() < BONUSCOUNT);

	UIFont.loadFromFile("Homegarden_Sans.ttf");

	currHP.setFont(UIFont);
	currDMG.setFont(UIFont);
	currAS.setFont(UIFont);

	currHP.setFillColor(Color::Black);
	currDMG.setFillColor(Color::Black);
	currAS.setFillColor(Color::Black);

	currHP.setPosition(10, 600);
	currDMG.setPosition(230, 600);
	currAS.setPosition(430, 600);
}

void game::GameLoop()
{
	AnnouncementFont.loadFromFile("IsaacScript2.ttf");
	levelcompleted.setFont(AnnouncementFont);
	levelcompleted.setFillColor(Color::Black);
	levelcompleted.setString("Congratulations!\nLevel completed");
	levelcompleted.setPosition(470, 250);
	levelcompleted.setScale(1.5f, 1.5f);

	int lvCount = 1;

	do
	{
		enemies.clear();
		environment.clear();
		loadlevel(lvCount, currHP, currDMG, currAS);
		lvCount++;

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			processInput(clk1, clk2);
			render();

			if (!enemies.size())
			{
				processInput(clk1, clk2);
				render();

				clk3.restart();
				window.draw(levelcompleted);
				window.display();
				while (clk3.getElapsedTime().asSeconds() < 3)
				{

				}	
				break;
			}
		}
	} while (lvCount < MAXLV);
}

void game::processInput(Clock &clk1,Clock &clk2)
{

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();

	if (!isaac.getAlive())
	{
		return;
	}

	//Check for movement speed changing blocks
	isaac.setSpeed(STEP);

	for (size_t i = 0; i < environment.size(); i++)
	{
		if ((isaac.sp.getGlobalBounds().intersects(environment[i].sp.getGlobalBounds())) &&
			(environment[i].getpassable()))
		{
			isaac.setSpeed(isaac.getSpeed() * environment[i].getspeedChange());
			break;
		}
	}

	//Player
	isaac.moving(window, environment);

	if (clk1.getElapsedTime().asSeconds() > isaac.getAttackSpeed())
	{
		isaac.shooting(window, bullets, bplayer);
		clk1.restart();
	}

	//Bonuses
	for (size_t i = 0; i < bonuses.size(); i++)
	{
		if (bonuses[i].sp.getGlobalBounds().intersects(isaac.sp.getGlobalBounds()))
		{
		switch (bonuses[i].getType())
			{
			case HP:
				isaac.setHp(isaac.getHp() + bonuses[i].getAmount());
				break;

			case DMG:
				isaac.setDmg(isaac.getDmg() + bonuses[i].getAmount());
				break;

			case AS:
				isaac.setAttackSpeed(isaac.getAttackSpeed() * bonuses[i].getAmount());
				break;
			}
			bonuses.erase(bonuses.begin() + i);
			break;
		}	
	}


	//Enemies actions
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].getType())
		{
			continue;
		}

		enemies[i].runtoPlayer(isaac);
		enemies[i].checkBounds(enemies[i].getMov(isaac).x, enemies[i].getMov(isaac).y, environment);
	}
	
	if (clk2.getElapsedTime().asSeconds() > MOBAS)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].getType())
			{
				enemies[i].shootPlayer(bullets, bmob, isaac);
			}
		}
		clk2.restart();
	}

	//Bullets movement and collision with walls and screen edges
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].bulletShape.move(bullets[i].currVelocity);

		if (bullets[i].bulletShape.getPosition().x < 0 || bullets[i].bulletShape.getPosition().x > window.getSize().x
			|| bullets[i].bulletShape.getPosition().y < 0 || bullets[i].bulletShape.getPosition().y > window.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}

		for (size_t m = 0; m < environment.size(); m++)
		{
			if ((bullets[i].bulletShape.getGlobalBounds().intersects(environment[m].sp.getGlobalBounds())) &&
				(!(environment[m].getpassable())))
			{
				bullets.erase(bullets.begin() + i);
				break;
			}
		}

	}


	//Player hitting enemies
	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t k = 0; k < enemies.size(); k++)
		{
			if ((bullets[i].getSource()) && (bullets[i].bulletShape.getGlobalBounds().intersects(enemies[k].sp.getGlobalBounds())))
			{
				enemies[k].setHp(enemies[k].getHp() - bplayer.getDmg());
				bullets.erase(bullets.begin() + i);
				if (enemies[k].getHp() <= 0)
				{
					enemies.erase(enemies.begin() + k);
					break;
				}
				break;
			}
		}
	}


	//Ranged enemies hitting player
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if ((bullets[i].bulletShape.getGlobalBounds().intersects(isaac.sp.getGlobalBounds())) && !(bullets[i].getSource()))
		{
			bullets.erase(bullets.begin() + i);
			isaac.setHp(isaac.getHp() - bmob.getDmg());
			if (isaac.getHp() <= 0)
			{
				isaac.dead();
				break;
			}
		}
	}


	//Melee enemies hitting player
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].sp.getGlobalBounds().intersects(isaac.sp.getGlobalBounds()))
		{
			isaac.setHp(isaac.getHp() - enemies[i].getDmg());
			if (isaac.getHp() <= 0)
			{
				isaac.dead();
				break;
			}
		}
	}
}

void game::render()
{
	window.clear();
	window.draw(sbackground);

	for (size_t i = 0; i < environment.size(); i++)
	{
		window.draw(environment[i].sp);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].sp);
	}

	for (size_t i = 0; i < bonuses.size(); i++)
	{
		window.draw(bonuses[i].sp);
	}

	window.draw(isaac.sp);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i].bulletShape);
	}

	std::stringstream temp;
	std::string asp;
	temp << std::fixed << std::setprecision(0) << (1 / isaac.getAttackSpeed());
	asp = temp.str();

	currHP.setString("Health: " + std::to_string(isaac.getHp()));
	currDMG.setString("Damage: " + std::to_string(isaac.getDmg()));
	currAS.setString("Attacks/sec: " + asp);

	window.draw(currHP);
	window.draw(currDMG);
	window.draw(currAS);

	window.display();
}

void game::playmusic()
{
	PlaySound(TEXT("soundtrack.wav"), NULL, SND_LOOP);
}