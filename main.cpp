#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "BoidManager.h"

int main()
{
	sf::RenderWindow rWindow(sf::VideoMode(900,900),"Boids Hunter");
	sf::View view = sf::View(sf::Vector2f(0,0),sf::Vector2f(1000,1000));
	rWindow.setView(view);
	sf::Event event;
	sf::Clock clock;
	sf::Time dt;
	sf::Vector2f mousePos;
	sf::Vector2i mousePosWindow;
	BoidManager bm(20,10);
	Boid b(sf::Vector2f(0,0),sf::Vector2f(-2,4));
	
	//------------TEST-------
	
	

	//-----------------------------------------
	while (rWindow.isOpen())
	{
		while (rWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)rWindow.close();
		}
		mousePosWindow = sf::Mouse::getPosition(rWindow);
		mousePos = rWindow.mapPixelToCoords(mousePosWindow);

		dt = clock.restart();

		bm.update(dt);
		view.setCenter(b.getPosition());

		if(bm.debugIsVisible(b,mousePos, 100, rWindow))
			std::cout << rand() << std::endl;

		rWindow.draw(b);
		rWindow.display();
		rWindow.clear(sf::Color(200,200,200,255));
	}
	return 0;
}