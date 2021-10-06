#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.h"

#define RATIO_COHESION_DEFAULT 
#define RATIO_REPULSION_DEFAULT 
#define RATIO_ALIGNEMENT_DEFAULT 

/// <summary>
/// The manager is the object wich contain a group of boid, update each boid using other boids who are near the one we are updating
/// </summary> 
class BoidManager : public sf::Drawable
{
	/// <summary>
	/// The ratio of the cohesion, the greater it is, the more the boids will stay near the other
	/// </summary>
	float ratioCohesionRule;
	/// <summary>
	/// The ratio of the repulsion, the greater it is, the more the boids will "avoid" collision with the very near others
	/// </summary>
	float ratioRepulsionRule;
	/// <summary>
	/// The ratio of the Alignement, the greater it is, the more the boids will align themselves with the others
	/// </summary>
	float ratioAlignmentRule;
	std::vector<Boid> boids;

public :

	/// <summary>
	/// Construct a BoidManager using a tab
	/// </summary>
	/// <param name="boids">The array where the boids are</param>
	BoidManager(std::vector<Boid> const boids_);

	/// <summary>
	/// Construct a BoidManager with a number of boids and the size of the Box where they will spawn
	/// </summary>
	/// <param name="boidNumber">Number of boids</param>
	/// <param name="spawningBoxSize">Size of the square box where the boids will spawn, 0 if you want all of them spawning at the same location</param>
	/// <param name="randomnlySpace">'true' if you want a randomn position for each boids</param>
	/// <param name="randomnVelocity">'true' if you want a randomn velocity for each boids</param>
	BoidManager(unsigned int const& boidNumber, float spawningBoxSize = 0,bool const& randomnlySpace = false,bool const& randomnVelocity = true);
	
	/// <summary>
	/// Move the boids using the velocity and elapsed time.
	/// Velocities of the boids are modified before getting updated
	/// </summary>
	/// <param name="dt">Delta Time, the time used</param>
	void update(sf::Time const& dt);
	/// <summary>
	/// Refresh the velocity of a boids using their neighbors
	/// </summary>
	/// <param name="index">The index of boid</param>
	void updateVelocity(unsigned int const& index = 0);
	/// <summary>
	/// Refresh the velocity of each boids using their neighbors
	/// </summary>
	/// <param name="dt">Elapsed time</param>
	void updateAllVelocities(sf::Time const& dt);
	/// <summary>
	/// Draw all the boids on the target using the 'states' param
	/// </summary>
	/// <param name="target">The target to draw on</param>
	/// <param name="states">The states to draw on</param>
	void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	/// <summary>
	/// Return the distance between 2 point	
	/// </summary>
	/// <param name="a">Point A</param>
	/// <param name="b">Point B</param>
	/// <returns>The distance between the 2 points</returns>
	float distance(sf::Vector2f const& a, sf::Vector2f const& b);
	/// <summary>
	/// Return the distance between the 2 point pow(2) : it's more efficient than the distance function and still can be used to compare distance
	/// </summary>
	/// <param name="a">Point A</param>
	/// <param name="b">Point B</param>
	/// <returns>The distance^2 between the 2 point</returns>
	float distanceP2(sf::Vector2f const& a, sf::Vector2f const& b);
};

