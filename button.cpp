#include "button.h"


AnimatedButton::AnimatedButton(std::string pathToSprites, int countOfSprites, const sf::Vector2f & position, std::function<void()> onClickFunc)
    : position(position), onClick(onClickFunc), pathToSprites(pathToSprites), countOfSprites(countOfSprites){
    addSptrites();
    sprite.setTexture(frames[currentFrame]);
    sprite.setPosition(position);
    sprite.setScale(4, 4);
}

void AnimatedButton::update(float deltaTime) {
    if (isPressed) {
        frameTime += deltaTime;
        if (frameTime >= frameDuration) {
            frameTime = 0;
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTexture(frames[currentFrame]);
        }
    }
    else {
        sprite.setTexture(frames[0]);
    }
}

void AnimatedButton::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void AnimatedButton::handleClick(const sf::Vector2f& mousePos) {
    if (sprite.getGlobalBounds().contains(mousePos)) {
        isPressed = true;
        // Вызываем переданную функцию при нажатии
        if (onClick) {
            onClick();
        }
    }
}

void AnimatedButton::release() {
    isPressed = false;
    currentFrame = 0; // Сброс к первому кадру
    sprite.setTexture(frames[0]);
}

void AnimatedButton::addSptrites()
{
    for (int i = 1; i <= countOfSprites; ++i) {
        texture.loadFromFile(pathToSprites + std::to_string(i) + ".png");
        frames.push_back(texture);
    }
}
