#include "Math.h"


sf::Vector2f getPolarVector(sf::Vector2f const& a)
{
    if (a.x > 0 && a.y < 0)
    {
        return sf::Vector2f(atan(a.x / -a.y), sqrt(a.x * a.x + a.y * a.y));
    }
    else if (a.x > 0 && a.y > 0)
    {
        return sf::Vector2f(atan(a.y / a.x) + PI / 2, sqrt(a.x * a.x + a.y * a.y));
    }
    else if (a.x < 0 && a.y > 0)
    {
        return sf::Vector2f(atan(-a.x / a.y) + PI, sqrt(a.x * a.x + a.y * a.y));
    }
    return sf::Vector2f(atan(a.y / a.x) + 1.5 * PI, sqrt(a.x * a.x + a.y * a.y));
}

sf::Vector2f getVector(sf::Vector2f const& vPolar)
{
    sf::Vector2f a = vPolar;
    while (a.x > 2 * PI)
    {
        a.x -= 2 * PI;
    }

    if (a.x < PI / 2)
    {
        return sf::Vector2f(sin(a.x) * a.y, cos(a.x) * -a.y);
    }
    else if (a.x < PI)
    {
        return sf::Vector2f(cos(a.x - PI / 2) * a.y, sin(a.x - PI / 2) * a.y);
    }
    else if (a.x < PI * 1.5)
    {
        return sf::Vector2f(-sin(a.x - PI) * a.y, cos(a.x - PI) * a.y);
    }

    return sf::Vector2f(-cos(a.x - PI * 1.5) * a.y, -sin(a.x - PI * 1.5) * a.y);

}

float distanceP2(sf::Vector2f const& a, sf::Vector2f const& b)
{
    sf::Vector2f v(b.x - a.x, b.y - a.y);
    return v.x * v.x + v.y * v.y;
}

float distance(sf::Vector2f const& a, sf::Vector2f const& b)
{
    sf::Vector2f v(b.x - a.x, b.y - a.y);
    return sqrt(v.x * v.x + v.y * v.y);
}

float det(sf::Vector2f const& a, sf::Vector2f const& b)
{
    return a.x * b.y - a.y * b.x;
}

void rotate(sf::Vector2f& a, float angle)
{
    a = sf::Vector2f(cos(angle) * a.x - sin(angle) * a.y, sin(angle) * a.x + cos(angle) * a.y);
}
