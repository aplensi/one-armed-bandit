#include "roulette.h"

roulette::roulette(std::string path, int numb, float startPosX, float startPosY, float indent) :
	numb(numb), startPosX(startPosX), startPosY(startPosY), indent(indent)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 1; i <= numb; i++)
	{
		items.emplace_back("images/itemOfRoulette", 7, i);
		
	}
	std::shuffle(items.begin(), items.end(), gen);

	int sizeOfItem = items[0].getSizeOfItem();
	int endOfColumn = startPosY + (sizeOfItem + indent) * items.size();

	for (int i = 0; i < items.size(); i++)
	{
		items[i].position(startPosX, startPosY + (sizeOfItem+indent) * i, endOfColumn, startPosY);
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
	this->speed = speed;
	for (int i = 0; i < items.size(); i++)
	{
		items[i].move(deltaTime, speed);
	}
}

int roulette::rouletteIsStopped(float PosOfCenter)
{
	this->PosOfCenter = PosOfCenter;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].getYPosition() <= PosOfCenter && items[i].getYPosition() > PosOfCenter - items[i].getSizeOfItem() - indent) {
			float difference = PosOfCenter - items[i].getYPosition();
			for (int j = 0; j < items.size(); j++) {
				difOfPos = PosOfCenter - items[i].getYPosition();
				nowDifOfPos = difOfPos;
			}
			return items[i].getNumb();
		}
	}
}

void roulette::moveToPoint(float deltaTime, float myspeed, float elapsedTime, float duration)
{
	if (nowDifOfPos > 0) {
		float remainingTime = duration - elapsedTime;
		speed = (difOfPos / duration) * (elapsedTime / duration);
		for (int i = 0; i < items.size(); i++)
		{
			items[i].move(deltaTime, speed);
		}
		nowDifOfPos -= deltaTime * speed;
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

void itemOfRoulette::position(float x, float y, int endOfColumn, int startOfColumn)
{
	this->endOfColumn = endOfColumn;
	this->startOfColumn = startOfColumn;
	this->x = x;
	this->y = y;
	sprite->setPosition(x, y);
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
	if (sprite->getPosition().y > endOfColumn)
	{
		sprite->setPosition(x, startOfColumn + sprite->getPosition().y - endOfColumn);
	}
}

float itemOfRoulette::getSizeOfItem()
{
	sf::FloatRect bounds = sprite->getGlobalBounds();
	return bounds.height;
}

float itemOfRoulette::getYPosition()
{
	return sprite->getPosition().y;
}

float itemOfRoulette::getXPosition()
{
	return sprite->getPosition().x;
}

std::string itemOfRoulette::getName()
{
	return path + std::to_string(numb);
}

int itemOfRoulette::getNumb()
{
	return numb;
}
