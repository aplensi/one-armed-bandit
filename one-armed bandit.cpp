#include "one-armed bandit.h"

using namespace std;

void win(int res1, int res2, int res3, int& balance, sf::Clock& overclockingOfSpeed) {
    overclockingOfSpeed.restart();
    if (res1 == res2 && res1 == res3) {
        if (res1 == 1) {
            balance += 1000;
        }
        else if (res1 == 2) {
            balance += 800;
        }
        else if (res1 == 3) {
            balance += 600;
        }
        else if (res1 == 4) {
            balance += 400;
        }
        else {
            balance += 200;
        }
        std::cout << "Congratulations! Your balance: " << balance << endl;
    }
}

int main()
{
    std::cout << "stars: 1000 | apples: 800 | oranges: 600 | bananas: 400 | watermelons: 200\n";
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1500, 3000);
    int speedOfRoulete1, startOfSpeed1 = 0;
    int speedOfRoulete2, startOfSpeed2 = 0;
    int speedOfRoulete3, startOfSpeed3 = 0;

    sf::Clock clock, scrollTimer, overclockingOfSpeed;

    AnimatedButton startButton("images/startButton", 4, sf::Vector2f(810, 100), [&]() {
        overclockingOfSpeed.restart();
        isRouletteEnabled = true;
        speedOfRoulete1 = distr(gen);
        speedOfRoulete2 = distr(gen);
        speedOfRoulete3 = distr(gen);
        int startOfSpeed1 = 0;
        int startOfSpeed2 = 0;
        int startOfSpeed3 = 0;
        scrollTimer.restart();
        });


    roulette column1("images/itemOfRoulette", 5, 97, -290, 6);
    roulette column2("images/itemOfRoulette", 5, 327, -290, 6);
    roulette column3("images/itemOfRoulette", 5, 557, -290, 6);


    AnimatedButton stopButton("images/stopButton", 4, sf::Vector2f(810, 150), [&]() {
        isRouletteEnabled = false;
        win(column1.rouletteIsStopped(170), column2.rouletteIsStopped(170), column3.rouletteIsStopped(170), balance, overclockingOfSpeed);
        });

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isRouletteEnabled == false){
                        startButton.handleClick(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                    }
                    if (isRouletteEnabled == true) {
                        stopButton.handleClick(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                    }
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
        if (isRouletteEnabled == true)
        {
            float elapsedTime = overclockingOfSpeed.getElapsedTime().asSeconds();
            if (elapsedTime < duration) {
                startOfSpeed1 = (speedOfRoulete1 / duration) * elapsedTime;
                startOfSpeed2 = (speedOfRoulete2 / duration) * elapsedTime;
                startOfSpeed3 = (speedOfRoulete3 / duration) * elapsedTime;
            }
            column1.move(deltaTime, startOfSpeed1);
            column2.move(deltaTime, startOfSpeed2);
            column3.move(deltaTime, startOfSpeed3);

            sf::Time elapsed = scrollTimer.getElapsedTime();
            if (elapsed.asSeconds() >= timeOfScroll) {
                isRouletteEnabled = false;
                win(column1.rouletteIsStopped(170), column2.rouletteIsStopped(170), column3.rouletteIsStopped(170), balance, overclockingOfSpeed);
            }
        }
        else {
            float elapsedTime = overclockingOfSpeed.getElapsedTime().asSeconds();
            column1.moveToPoint(deltaTime, startOfSpeed1, elapsedTime, duration);
            column2.moveToPoint(deltaTime, startOfSpeed2, elapsedTime, duration);
            column3.moveToPoint(deltaTime, startOfSpeed3, elapsedTime, duration);
        }

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
