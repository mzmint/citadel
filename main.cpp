#include <SFML/Graphics.hpp>
#include "Grid.h"


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    unsigned int width = desktop.size.x;
    unsigned int height = desktop.size.y;

    sf::RenderWindow window(
        desktop,
        "Citadel",
        sf::State::Fullscreen
    );

    int cellSize = width / 40;

    Grid grid(height + cellSize * 8, height, cellSize, true);

    sf::Font font;
    if (!font.openFromFile("assets/lemon_milk.ttf")) {
        return 1;
    }

    sf::RectangleShape cell({
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    });

    sf::Text title(font);
    title.setCharacterSize(96);
    title.setPosition({2020.f, 80.f});
    title.setString("Citadel");
    title.setFillColor(sf::Color::Black);

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouse->button == sf::Mouse::Button::Left) {

                    int x = mouse->position.x / cellSize;
                    int y = mouse->position.y / cellSize;

                    grid.setCell(x, y, grid.getCell(x, y) + 1);
                }
                }
        }

        window.clear(sf::Color::White);

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {

                if (grid.getCell(x, y) >= 3) grid.setCell(x, y, 0);

                cell.setPosition({
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                });

                if (grid.getCell(x, y) == 0) cell.setFillColor(sf::Color(0, 128, 255));
                else if (grid.getCell(x, y) == 1) cell.setFillColor(sf::Color::Green);
                else cell.setFillColor(sf::Color::Black);

                window.draw(cell);
            }
        }

        grid.draw(window);

        window.draw(title);
        window.display();
    }

    return 0;
}