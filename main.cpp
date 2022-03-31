#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.cpp"

int main() {
        sf::RenderWindow window(sf::VideoMode(600, 600), "Goo");

        int game_speed = 10;
        window.setFramerateLimit(game_speed);

        Game::PlayingArea field = Game::PlayingArea(50, 150, 500, 400);
        Game game = Game(field);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed){
                    switch (event.key.code) {
                        case sf::Keyboard::A:
                            game.setGameMode(Game::GameMode::PLAY);
                            break;
                        case sf::Keyboard::E:
                            game.setGameMode(Game::GameMode::EDIT);
                            break;
                        case sf::Keyboard::S:
                            game.setGameMode(Game::GameMode::EDIT);
                            game.step();
                            break;
                        case sf::Keyboard::R:
                            game.reset();
                            break;
                        case sf::Keyboard::PageUp:
                            game_speed = (game_speed < 10) ? game_speed + 1 : 10;
                            window.setFramerateLimit(game_speed);
                            break;
                        case sf::Keyboard::PageDown:
                            game_speed = (game_speed > 1) ? game_speed - 1 : 1;
                            window.setFramerateLimit(game_speed);
                            break;
                        default:
                            break;
                    }
                } else if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    switch (event.mouseButton.button) {
                        case sf::Mouse::Left:
                            game.alterCell(coords.x, coords.y, Game::EditMode::SET);
                            break;
                        case sf::Mouse::Right:
                            game.alterCell(coords.x, coords.y, Game::EditMode::REMOVE);
                            break;
                        default:
                            break;
                    }
                }

            }
            window.clear(game.background_color);

            game.draw(&window);
            game.update();

            window.display();
        }

        return 0;
}