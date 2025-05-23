#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

class itemOfRoulette {
public:
	itemOfRoulette(std::string path, float size, int numb);
	void render(sf::RenderWindow& window);
	void position(float x, float y, int endOfColumn, int startOfColumn);
	void position(float x, float y);
	void move(float deltaTime, float speed);
	float getSizeOfItem();
	float getYPosition();
	float getXPosition();
	std::string getName();
	int getNumb();
private:
	std::string path;
	float size, x, y;
	int numb, indent, startOfColumn, endOfColumn;
	sf::Texture* texture = new sf::Texture;
	sf::Sprite* sprite = new sf::Sprite;
};

class roulette {
public:
	roulette(std::string path, int numb, float startPosX, float startPosY, float indent);
	void render(sf::RenderWindow& window);
	void move(float deltaTime, float speed);
	int rouletteIsStopped(float PosOfCenter);
	void moveToPoint(float deltaTime, float speed, float elapsedTime, float duration);
private:
	int numb, startPosX, startPosY;
	float speedOfScroll = 0, indent, stopPoint, difOfPos = 0, speed, PosOfCenter, nowDifOfPos, elapsedTime;
	std::vector<itemOfRoulette> items;
	std::string path;
};