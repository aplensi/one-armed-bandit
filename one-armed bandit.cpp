#include "one-armed bandit.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "one-armed bandit");

    if (!interfaceTexture.loadFromFile("images/menuOfOne-armedBandit.png")){
        return -1;
    }

    interfaceSprite.setTexture(interfaceTexture);

    sf::Vector2u windowSize = window.getSize();

    interfaceSprite.setScale(
        static_cast<float>(windowSize.x) / interfaceTexture.getSize().x,
        static_cast<float>(windowSize.y) / interfaceTexture.getSize().y
    );

    AnimatedButton startButton("images/startButton", 4, sf::Vector2f(810, 100), [&]() {
        std::cout << "Start button clicked!" << std::endl;
        speedOfRoulette = 300;
        });
    AnimatedButton stopButton("images/stopButton", 4, sf::Vector2f(810, 150), [&]() {
        std::cout << "Stop button clicked!" << std::endl;
        speedOfRoulette = 0;
        });
    sf::Clock clock;

    roulette column1("images/itemOfRoulette", 5, 97, 230);
    roulette column2("images/itemOfRoulette", 5, 327, 230);
    roulette column3("images/itemOfRoulette", 5, 557, 230);

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
        column1.move(deltaTime, speedOfRoulette);
        column2.move(deltaTime, speedOfRoulette);
        column3.move(deltaTime, speedOfRoulette);

        window.clear(sf::Color(242, 204, 143));
        column1.render(window);
        column2.render(window);
        column3.render(window);
        window.draw(interfaceSprite); // добавление фона
        startButton.render(window);  // добавление кнопки старт
        stopButton.render(window);  // добавление кнопки стоп
        window.display();
    }

    return 0;
}
