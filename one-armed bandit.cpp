#include "one-armed bandit.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(interfaceSprite);
        window.display();
    }

    return 0;
}
