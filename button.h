#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <iostream>


class AnimatedButton {
public:

    AnimatedButton(std::string pathToSprites, int countOfSprites, const sf::Vector2f& position, std::function<void()> onClickFunc);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void handleClick(const sf::Vector2f& mousePos);
    void release();

private:
    
    std::vector<sf::Texture> frames;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    int currentFrame = 0, countOfSprites;
    bool isPressed = false;
    float frameTime = 0.0f;
    const float frameDuration = 0.06f;
    std::string pathToSprites;
    std::function<void()> onClick;

    void addSptrites();
};