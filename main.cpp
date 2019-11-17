#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.cpp"

int main() {
        sf::RenderWindow window(sf::VideoMode(600, 600), "Goo");
        window.setFramerateLimit(4);

        Game::PlayingArea field = Game::PlayingArea(100, 150, 400, 300);
        Game game = Game(field);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(game.background_color);

            game.Draw(&window, field);
            game.Update();

            window.display();
        }

        return 0;
}