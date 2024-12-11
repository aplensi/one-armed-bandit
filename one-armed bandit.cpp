#include "one-armed bandit.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "one-armed bandit", sf::Style::Close);

    if (!interfaceTexture.loadFromFile("images/menuOfOne-armedBandit.png")){
        return -1;
    }

    interfaceSprite.setTexture(interfaceTexture);

    sf::Vector2u windowSize = window.getSize();

    interfaceSprite.setScale(
        static_cast<float>(windowSize.x) / interfaceTexture.getSize().x,
        static_cast<float>(windowSize.y) / interfaceTexture.getSize().y
    );

    AnimatedButton startButton("images/startButton", 3, sf::Vector2f(810, 100), []() {
        std::cout << "Start button clicked!" << std::endl;
        });
    AnimatedButton stopButton("images/stopButton", 3, sf::Vector2f(810, 150), []() {
        std::cout << "Stop button clicked!" << std::endl;
        });
    sf::Clock clock;

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    startButton.handleClick(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                    stopButton.handleClick(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    startButton.release();
                    stopButton.release();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        startButton.update(deltaTime);
        stopButton.update(deltaTime);

        window.clear();
        window.draw(interfaceSprite); // добавление фона
        startButton.render(window);  // добавление кнопки старт
        stopButton.render(window);  // добавление кнопки стоп
        window.display();
    }

    return 0;
}
