#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "BoidManager.h"

int main()
{
	sf::RenderWindow rWindow(sf::VideoMode(900,900),"Boids Hunter");
	sf::View view = sf::View(sf::Vector2f(0,0),sf::Vector2f(10,10));
	rWindow.setView(view);
	sf::Event event;
	sf::Clock clock;
	sf::Time dt;
	BoidManager bm(20);


	while (rWindow.isOpen())
	{
		while (rWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)rWindow.close();
		}
		dt = clock.restart();




		rWindow.display();
		rWindow.clear();
	}
	return 0;
}