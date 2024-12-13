#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

class itemOfRoulette {
public:
	itemOfRoulette(std::string path, float size, int numb);
	void render(sf::RenderWindow& window);
	void position(float x, float y);
	void move(float deltaTime, float speed);
private:
	std::string path;
	float size, x, y;
	int numb;
	sf::Texture* texture = new sf::Texture;
	sf::Sprite* sprite = new sf::Sprite;
};

class roulette {
public:
	roulette(std::string path, int numb, float startPosX, float startPosY);
	void render(sf::RenderWindow& window);
	void move(float deltaTime, float speed);
private:
	int numb, startPosX, startPosY;
	float speedOfScroll = 0;
	std::vector<itemOfRoulette> items;
	std::string path;
};