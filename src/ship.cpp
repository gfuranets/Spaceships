#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "ship.h"
#include "bullet.h"

Ship::Ship(sf::RenderWindow& window, sf::Texture& texture, float X, float Y)
    : ship(texture), vel(300.f), alpha(sf::degrees(0.f)), angularVel(sf::degrees(0.f))
{
    sf::Vector2u shipSize = ship.getTexture().getSize();

    auto textureSize = texture.getSize();
    ship.setOrigin({
        static_cast<float>(textureSize.x) / 2.f,
        static_cast<float>(textureSize.y) / 2.f
        });

    ship.setScale({ 0.2f, 0.2f });
    width = static_cast<float>(shipSize.x * ship.getScale().x);
    height = static_cast<float>(shipSize.y * ship.getScale().y);

    ship.setPosition({ X, Y });
}

// virtual void Ship::move(sf::Time dt) - default;

void Ship::rotate(sf::Time dt) 
{
    float t = dt.asSeconds();

    alpha += angularVel * t;
    ship.setRotation(alpha);
}

void Ship::exitWindow(sf::RenderWindow& window)
{
    float x = ship.getPosition().x, y = ship.getPosition().y;
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    if (x > windowWidth + width / 2.f)
        x = -width / 2.f;
    else if (x < -width / 2.f)
        x = windowWidth + width / 2.f;

    if (y > windowHeight + height / 2.f)
        y = -height / 2.f;
    else if (y < -height / 2.f)
        y = windowHeight + height / 2.f;

    ship.setPosition({ x, y });
}

void Ship::update(sf::RenderWindow &window, sf::Time dt) 
{ 
    move(dt);
    rotate(dt); 
    exitWindow(window);
}  

void Ship::shoot(sf::RenderWindow& window, std::vector<std::unique_ptr<Bullet>> &bullets, sf::Texture &bulletTexture) const
{
    sf::Angle angle = ship.getRotation();
    float spawnX = ship.getPosition().x + width * std::cos(angle.asRadians()) / 2.f, spawnY = ship.getPosition().y + width * std::sin(angle.asRadians()) / 2.f;
    
    bullets.push_back(std::make_unique<Bullet>(bulletTexture, window, spawnX, spawnY, angle, vel));
}

void Ship::draw(sf::RenderWindow& window)
{
    window.draw(ship);
}