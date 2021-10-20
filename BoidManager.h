#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.h"
#include "Math.h"

#define RATIO_COHESION_DEFAULT 30
#define RATIO_REPULSION_DEFAULT 60
#define RATIO_ALIGNEMENT_DEFAULT 40

#define DISTANCE_VIEW_COHESION_DEFAULT 400
#define DISTANCE_VIEW_REPULSION_DEFAULT 100
#define DISTANCE_VIEW_ALIGNMENT_DEFAULT 150

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
	/// <summary>
	/// The angle of view of the boids (rad)
	/// </summary>
	float angleView;
	/// <summary>
	/// Distance of view used for cohesion rule
	/// </summary>
	float distanceViewCohesion;
	/// <summary>
	/// Distance of view used for Repulsion rule
	/// </summary>
	float distanceViewRepulsion;
	/// <summary>
	/// Distance of view used for Alignment rule
	/// </summary>
	float distanceViewAlignement;
	/// <summary>
	/// The boids array
	/// </summary>
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
	void updateVelocity(unsigned int const& index = 0,sf::Time const& dt = sf::seconds(0));
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
	/// Return 'true' if the point can be see by a boid using a disance view and the angle view
	/// </summary>
	/// <param name="b">The boids</param>
	/// <param name="point">The point</param>
	/// <param name="distance">The distance</param>
	/// <returns>'true' if the boids can see the point</returns>
	bool isVisible(Boid const& b, sf::Vector2f const& point, float const& distance)const;

	bool debugIsVisible(Boid const& b, sf::Vector2f const& point, float const& distance,sf::RenderTarget & target)const;
	sf::Vector2f getPosition(unsigned int const& index)const;
};

