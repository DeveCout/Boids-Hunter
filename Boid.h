#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define COS4 -0.653
#define SIN4 -0.756
#define ANGLE_VIEW 4
#define SPEED_LIMIT 100

/// <summary>
/// The Boid class, used to create some group simulation
/// </summary>
class Boid : public sf::Drawable 
{
	sf::Vector2f position;
	/// <summary>
	/// Velocity determine the speed of the boid AND so it orientation
	/// </summary>
	sf::Vector2f velocity;

public :
	
	/// <summary>
	/// Contructor of a boid
	/// </summary>
	/// <param name="pos">Position of the Boid</param>
	/// <param name="velocity"> Velocity of the boids, per seconds</param>
	Boid(sf::Vector2f const& position_ = sf::Vector2f(0,0),sf::Vector2f const& velocity_ = sf::Vector2f(0,0));
	
	/// <summary>
	/// Draw all the boids on the target
	/// </summary>
	/// <param name="target">The target to draw on</param>
	/// <param name="states">The states to uses</param>
	void draw(sf::RenderTarget & target,sf::RenderStates states)const;

	/// <summary>
	/// Move the boid using the velocity and elapsed time
	/// </summary>
	/// <param name="dt">Delta Time, the time used</param>
	void update(sf::Time const& dt);

	/// <summary>
	/// Return the position of the boid
	/// </summary>
	/// <returns>The position of the boid</returns>
	sf::Vector2f getPosition()const;
	/// <summary>
	/// Return the velocity of the boid
	/// </summary>
	/// <returns>The velocity of the boid</returns>
	sf::Vector2f getVelocity()const;

	/// <summary>
	/// Add a force on the velocity of the boid
	/// </summary>
	/// <param name="force">the force vector</param>
	void applyForceVector(sf::Vector2f const& force);

	void setVelocity(sf::Vector2f const& vel);
};