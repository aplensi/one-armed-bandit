#include "roulette.h"

roulette::roulette(std::string path, int numb, float startPosX, float startPosY) :
	numb(numb), startPosX(startPosX), startPosY(startPosY)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 1; i <= numb; i++)
	{
		items.emplace_back("images/itemOfRoulette", 7, i);
		
	}
	std::shuffle(items.begin(), items.end(), gen);

	for (int i = 0; i < items.size(); i++)
	{
		items[i].position(startPosX, (i * startPosY) - 60);
	}
	
}

void roulette::render(sf::RenderWindow& window)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].render(window);
	}
}

void roulette::move(float deltaTime, float speed)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].move(deltaTime, speed);
	}
}

itemOfRoulette::itemOfRoulette(std::string path, float size, int numb) :
	path(path), size(size), numb(numb)
{
	texture->loadFromFile(path + std::to_string(numb) + std::string(".png"));
	sprite->setTexture(*texture);
	sprite->setScale(size, size);
}

void itemOfRoulette::render(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void itemOfRoulette::position(float x, float y)
{
	this->x = x;
	this->y = y;
	sprite->setPosition(x, y);
}

void itemOfRoulette::move(float deltaTime, float speed)
{
	sprite->move(0, speed * deltaTime);
	if (sprite->getPosition().y > 540)
	{
		sprite->setPosition(x,  -300);
	}
}
