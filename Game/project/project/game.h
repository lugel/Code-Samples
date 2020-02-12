#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class game
{
public:
	static game& getInstance();
	static void playmusic();
	void GameLoop();

	sf::RenderWindow window;
	sf::Texture background;
	sf::Sprite sbackground;

	sf::Clock clk1;
	sf::Clock clk2;
	sf::Clock clk3;

	sf::Text levelcompleted;
	sf::Text currHP;
	sf::Text currDMG;
	sf::Text currAS;

	sf::Font AnnouncementFont;
	sf::Font UIFont;


private:
	game();
	void loadlevel(int, sf::Text&, sf::Text&, sf::Text&);
	void processInput(sf::Clock&,sf::Clock&);
	void render();
	
};