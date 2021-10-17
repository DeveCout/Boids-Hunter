#include "BoidManager.h"
#include "Math.h"
#include <iostream>

BoidManager::BoidManager(std::vector<Boid> const boids_):boids(boids_)
{
	ratioAlignmentRule = RATIO_ALIGNEMENT_DEFAULT;
	ratioCohesionRule = RATIO_COHESION_DEFAULT;
	ratioRepulsionRule = RATIO_REPULSION_DEFAULT;

	angleView = ANGLE_VIEW;
}

BoidManager::BoidManager(unsigned int const& boidNumber, float spawningBoxSize, bool const& randomnlySpace, bool const& randomnVelocity)
{
	srand(time(NULL));
	ratioAlignmentRule = RATIO_ALIGNEMENT_DEFAULT;
	ratioCohesionRule = RATIO_COHESION_DEFAULT;
	ratioRepulsionRule = RATIO_REPULSION_DEFAULT;

	distanceViewCohesion = DISTANCE_VIEW_COHESION_DEFAULT;
	distanceViewRepulsion = DISTANCE_VIEW_REPULSION_DEFAULT;
	distanceViewAlignement= DISTANCE_VIEW_ALIGNMENT_DEFAULT;

	angleView = ANGLE_VIEW;
	boids = std::vector<Boid>(0);

	if(spawningBoxSize)
		for (size_t i = 0; i < boidNumber; i++)
		{
			boids.push_back(Boid(sf::Vector2f((rand() * 1000) % int(spawningBoxSize * 1000) - spawningBoxSize / 2
											 ,(rand() * 1000) % int(spawningBoxSize * 1000) - spawningBoxSize / 2),
				sf::Vector2f(rand()%50 - 25,rand()%50 - 25)));
		}
	else
		for (size_t i = 0; i < boidNumber; i++)
		{
			boids.push_back(Boid(sf::Vector2f(0,0),
				sf::Vector2f(rand() % 50 - 25, rand() % 50 - 25)));
		}
}

void BoidManager::update(sf::Time const& dt)
{
	updateAllVelocities(dt);
	for (size_t i = 0; i < boids.size(); i++)
	{
		boids[i].update(dt);
	}
}

void BoidManager::updateVelocity(unsigned int const& index, sf::Time const& dt)
{
	/*-------------------------------------*/
	/*--------------COHESION---------------*/
	/*-------------------------------------*/
	sf::Vector2f forceCohesion;
	/*-------------------------------------*/
	/*--------------DISPERSION-------------*/
	/*-------------------------------------*/
	sf::Vector2f forceRepulsion;
	/*-------------------------------------*/
	/*--------------ALLIGNEMENT------------*/
	/*-------------------------------------*/
	sf::Vector2f forceAlignment;

	std::vector<sf::Vector2f> forcesCohesion;
	std::vector<sf::Vector2f> forcesRepulsion;
	std::vector<sf::Vector2f> forcesAlignment;

	for (size_t i = 0; i < boids.size(); i++)
	{
		//Le boid ne doit se prendre en compte
		if (index != i)
		{
			sf::Vector2f u = sf::Vector2f(boids[i].getPosition().x - boids[index].getPosition().x,
				boids[i].getPosition().y - boids[index].getPosition().y);
			
			//----------------------------------------COHESION 
			
			if (isVisible(boids[index], boids[i].getPosition(), distanceViewCohesion))
			{
				forcesCohesion.push_back((u));
			}

			//----------------------------------------REPULSION 

			if (isVisible(boids[index], boids[i].getPosition(), distanceViewRepulsion))
			{
				forcesRepulsion.push_back(-(u));
			}

			//----------------------------------------ALIGNEMENT

			if (isVisible(boids[index], boids[i].getPosition(), distanceViewAlignement))
			{
				forcesAlignment.push_back((u));
			}
		}
	}

	//COHESION GLOBAL
	for (size_t i = 0; i < forcesCohesion.size(); i++)
	{
		forceCohesion += forcesCohesion[i];
	}

	if (forcesCohesion.size())
	{

		forceCohesion.x /= forcesCohesion.size();
		forceCohesion.y /= forcesCohesion.size();

		forceCohesion.x *= ratioCohesionRule;
		forceCohesion.y *= ratioCohesionRule;
	}

	//REPULSION GLOBAL
	for (size_t i = 0; i < forcesRepulsion.size(); i++)
	{
		forceRepulsion += forcesRepulsion[i];
	}
	if (forcesRepulsion.size())
	{
		forceRepulsion.x /= forcesRepulsion.size();
		forceRepulsion.y /= forcesRepulsion.size();

		forceRepulsion.x *= ratioRepulsionRule;
		forceRepulsion.y *= ratioRepulsionRule;
	}

	//ALIGNEMENT GLOBAL
	for (size_t i = 0; i < forcesAlignment.size(); i++)
	{
		forceAlignment += forcesAlignment[i];
	}
	if (forcesAlignment.size())
	{
		forceAlignment.x /= forcesAlignment.size();
		forceAlignment.y /= forcesAlignment.size();
		forceAlignment.x *= ratioAlignmentRule;
		forceAlignment.y *= ratioAlignmentRule;
	}
	
	sf::Vector2f force = forceCohesion + forceRepulsion + forceAlignment;
	
	if (!index)
	{
		std::cout << "FORCE Y : " << force.y << std::endl;
	}

	force.x *= dt.asSeconds();
	force.y *= dt.asSeconds();


	boids[index].applyForceVector(force);

}

void BoidManager::updateAllVelocities(sf::Time const& dt)
{
	for (size_t i = 0; i < boids.size(); i++)
	{
		updateVelocity(i,dt);
	}
}

void BoidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < boids.size(); i++)
	{
		target.draw(boids[i]);
	}
}

bool BoidManager::isVisible(Boid const& b, sf::Vector2f const& point,float const& distance_) const
{
	sf::Vector2f polarVelocity = getPolarVector(b.getVelocity());
	sf::Vector2f u = polarVelocity, v = polarVelocity;

	u.x -= angleView / 2;
	v.x += angleView / 2;

	u = getVector(u);
	v = getVector(v);

	sf::Vector2f w = sf::Vector2f(point.x - b.getPosition().x, point.y - b.getPosition().y);

	if (distance(b.getPosition(), point) < distance_) {//In RANGE
		if (det(u, w) >= 0
			|| det(v, w) <= 0)
		{
			return true;
		}
	}
	return false;
}

bool BoidManager::debugIsVisible(Boid const& b, sf::Vector2f const& point, float const& distance_, sf::RenderTarget& target) const
{


	sf::Vector2f polarVelocity = getPolarVector(b.getVelocity());
	sf::Vector2f u = polarVelocity, v = polarVelocity;

	u.x -= angleView / 2;
	v.x += angleView / 2;

	u = getVector(u);
	v = getVector(v);
	
	sf::VertexArray line(sf::PrimitiveType::LinesStrip, 3);
	sf::VertexArray lineV(sf::PrimitiveType::LinesStrip, 2);

	sf::Vector2f uPos = b.getPosition() + sf::Vector2f(u.x * distance_, u.y * distance_);
	sf::Vector2f vPos = b.getPosition() + sf::Vector2f(v.x * distance_, v.y * distance_);

	line[0] = sf::Vertex(uPos);
	line[1] = sf::Vertex(b.getPosition());
	line[2] = sf::Vertex(vPos);

	lineV[0] = b.getPosition();
	lineV[1] = b.getPosition() + sf::Vector2f(b.getVelocity().x * distance_, b.getVelocity().y * distance_);


	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
	line[2].color = sf::Color::Red;

	lineV[0].color = sf::Color::Green;
	lineV[1].color = sf::Color::Green;

	sf::CircleShape c;
	c.setRadius(distance_);
	c.setPosition(sf::Vector2f(b.getPosition().x - distance_, b.getPosition().y - distance_ ));
	c.setFillColor(sf::Color(255, 0, 0, 100));

	target.draw(line);
	target.draw(c);
	target.draw(lineV);

	sf::Vector2f w = sf::Vector2f(point.x - b.getPosition().x, point.y - b.getPosition().y);

	if(distance(b.getPosition(), point) < distance_) {//In RANGE
		if (det(u, w) >= 0
			|| det(v, w) <= 0)
		{
			return true;
		}
	}
	return false;
}

sf::Vector2f BoidManager::getPosition(unsigned int const& index) const
{
	return boids[index].getPosition();
}