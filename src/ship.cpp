#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "ship.h"
#include "bullet.h"

Ship::Ship(sf::Texture& texture, sf::RenderWindow& window, float X, float Y)
    : ship(texture), vel(0.f    ), alpha(sf::degrees(0.f)), angularVel(sf::degrees(180.f)), x(X), y(Y)
{
    sf::Vector2u shipSize = ship.getTexture().getSize();

    auto textureSize = texture.getSize();
    ship.setOrigin({
        static_cast<float>(textureSize.x) / 2.f,
        static_cast<float>(textureSize.y) / 2.f
        });

    ship.setScale({ 0.2f, 0.2f });
    width = shipSize.x * ship.getScale().x;
    height = shipSize.y * ship.getScale().y;

    ship.setPosition({ x, y });
}

void Ship::move(sf::Time dt) 
{
    float alphaRads = alpha.asRadians(), t = dt.asSeconds();
    sf::Vector2f direction({ std::cos(alphaRads), std::sin(alphaRads) });

    ship.move({ direction * vel * t });
}

void Ship::rotate(sf::Time dt) 
{
    float t = dt.asSeconds();

    alpha += angularVel * t;
    ship.setRotation(alpha);
}

/*
void Ship::exitWindow(sf::RenderWindow& window)
{
    float x = ship.getPosition().x, y = ship.getPosition().y;
    unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;

    if (x <= -width / 2.f) ship.setPosition({ windowWidth + width / 2.f, y });
    else if (x >= windowWidth + width / 2.f) ship.setPosition({ -width / 2.f, y });
    if (y <= -height / 2.f) ship.setPosition({ x, windowHeight + height / 2.f });
    else if (y >= windowHeight + height / 2.f) ship.setPosition({ x, -height / 2.f });
}
*/

void Ship::update(sf::RenderWindow &window, sf::Time dt) 
{ 
    //exitWindow(window);
    move(dt);
    rotate(dt); 
}  

void Ship::shoot(std::vector<Bullet*> &bullets, sf::RenderWindow &window, sf::Texture &bulletTexture) const
{
    float x = ship.getPosition().x, y = ship.getPosition().y;
    sf::Angle angle = ship.getRotation();
    
    bullets.push_back(new Bullet(bulletTexture, window, x, y, angle));
}

void Ship::draw(sf::RenderWindow& window)
{
    window.draw(ship);
}