#pragma once
#include <SFML/Graphics.hpp>


float VectorMagnitude(sf::Vector2f a);

float VectorMagnitude(sf::Vector3f a);

sf::Vector2f VectorNormalize(sf::Vector2f a);

sf::Vector3f VectorNormalize(sf::Vector3f a);

float VectorDot(sf::Vector2f a, sf::Vector2f b);

float VectorDot(sf::Vector3f a, sf::Vector3f b);