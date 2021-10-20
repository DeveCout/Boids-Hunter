#include "Boid.h"
#include "Math.h"
#include <iostream>


Boid::Boid(sf::Vector2f const& position_, sf::Vector2f const& velocity_):position(position_),velocity(velocity_)
{

}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray triangles(sf::PrimitiveType::TrianglesStrip,4);
	triangles[0].color = sf::Color::Black;
	triangles[1].color = sf::Color::Black;
	triangles[2].color = sf::Color::Black;
	triangles[3].color = sf::Color::Black;

	float modVel = 1;
	sf::Vector2f nVel = sf::Vector2f(1,0);

	modVel = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	nVel = sf::Vector2f(velocity.x * 1 / modVel * 30, velocity.y * 1 / modVel * 30);
	

	sf::Vector2f nVel1 = sf::Vector2f(COS4 * nVel.x - SIN4 * nVel.y, SIN4 * nVel.x + COS4* nVel.y);
	sf::Vector2f nVel2 = sf::Vector2f(COS4 * nVel.x - (-SIN4) * nVel.y, (-SIN4) * nVel.x + COS4* nVel.y);


	triangles[0].position = position + nVel1;
	triangles[1].position = position + nVel;
	triangles[2].position = position;
	triangles[3].position = position + nVel2;

	target.draw(triangles);

	//----------------------------------------------------------------DEBUG

	sf::Vector2f polarVelocity = getPolarVector(velocity);
	sf::Vector2f u = polarVelocity, v = polarVelocity;

	u.x -= ANGLE_VIEW / 2;
	v.x += ANGLE_VIEW / 2;

	u = getVector(u);
	v = getVector(v);

	float distance = 400;

	sf::VertexArray line(sf::PrimitiveType::LinesStrip, 3);
	sf::VertexArray lineV(sf::PrimitiveType::LinesStrip, 2);

	sf::Vector2f uPos = position + normalize(sf::Vector2f(u.x , u.y)) * distance;
	sf::Vector2f vPos = position + normalize(sf::Vector2f(v.x, v.y)) * distance;

	line[0] = sf::Vertex(uPos);
	line[1] = sf::Vertex(position);
	line[2] = sf::Vertex(vPos);

	lineV[0] = position;
	lineV[1] = position + normalize(sf::Vector2f(velocity.x, velocity.y)) * distance;


	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
	line[2].color = sf::Color::Red;

	lineV[0].color = sf::Color::Green;
	lineV[1].color = sf::Color::Green;

	sf::CircleShape c;
	c.setRadius(distance);
	c.setPosition(sf::Vector2f(position.x - distance, position.y - distance));
	c.setFillColor(sf::Color(255, 0, 0, 30));

	target.draw(line);
	target.draw(c);
	target.draw(lineV);
}

void Boid::update(sf::Time const& dt)
{
	position.x += velocity.x * dt.asSeconds();
	position.y += velocity.y * dt.asSeconds();
}

sf::Vector2f Boid::getPosition() const
{
	return position;
}

sf::Vector2f Boid::getVelocity() const
{
	return velocity;
}

void Boid::applyForceVector(sf::Vector2f const& force)
{
	velocity += force;
	if (velocity.x > SPEED_LIMIT) velocity.x = SPEED_LIMIT;
	if (velocity.y > SPEED_LIMIT) velocity.y = SPEED_LIMIT;

	if (velocity.x < -SPEED_LIMIT) velocity.x = -SPEED_LIMIT;
	if (velocity.y < -SPEED_LIMIT) velocity.y = -SPEED_LIMIT;

}

void Boid::setVelocity(sf::Vector2f const& vel)
{
	velocity = vel;
}
