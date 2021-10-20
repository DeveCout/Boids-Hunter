#pragma once
#include <SFML/System.hpp>

#define PI 3.1415926535

sf::Vector2f getPolarVector(sf::Vector2f const& v);
sf::Vector2f getVector(sf::Vector2f const& vPolar);
float distanceP2(sf::Vector2f const& a, sf::Vector2f const& b);
float distance(sf::Vector2f const& a, sf::Vector2f const& b);
/// <summary>
/// Si le vecteur B est orienté vers la GAUCHE de A, alors il retourne VRAIE
/// </summary>
/// <param name="a">Vecteur A</param>
/// <param name="b">Vecteur B</param>
/// <returns></returns>
float det(sf::Vector2f const& a, sf::Vector2f const& b);

void rotate(sf::Vector2f& a,float angle);

sf::Vector2f normalize(sf::Vector2f const& a);