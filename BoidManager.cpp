#include "BoidManager.h"
#include <iostream>

BoidManager::BoidManager(std::vector<Boid> const boids_):boids(boids_)
{
}

BoidManager::BoidManager(unsigned int const& boidNumber, float spawningBoxSize, bool const& randomnlySpace, bool const& randomnVelocity)
{
	boids = std::vector<Boid>(boidNumber);
}

void BoidManager::update(sf::Time const& dt)
{
	updateAllVelocities(dt);
	for (size_t i = 0; i < boids.size(); i++)
	{
		boids[i].update(dt);
	}
}

void BoidManager::updateVelocity(unsigned int const& index)
{
	for (size_t i = 0; i < boids.size(); i++)
	{

	}
}

void BoidManager::updateAllVelocities(sf::Time const& dt)
{
	for (size_t i = 0; i < boids.size(); i++)
	{
		updateVelocity(i);
	}
}

void BoidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < boids.size(); i++)
	{
		target.draw(boids[i]);
	}
}

float BoidManager::distance(sf::Vector2f const& a, sf::Vector2f const& b)
{
    sf::Vector2f v(b.x - a.x, b.y - a.y);
    return sqrt(v.x * v.x + v.y * v.y);
}

float BoidManager::distanceP2(sf::Vector2f const& a, sf::Vector2f const& b)
{
    sf::Vector2f v(b.x - a.x, b.y - a.y);
    return v.x * v.x + v.y * v.y;
}