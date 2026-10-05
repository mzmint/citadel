#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
private:
    int columns;
    int rows;
    float cellSize;

    bool showLines;

    std::vector<int> cells;
    sf::VertexArray lines;

public:
    Grid(int width, int height, float cellSize, bool showLines = true);

    void draw(sf::RenderWindow& window);

    void setCell(int x, int y, int value = 0);
    int getCell(int x, int y) const;

    sf::Vector2f getPosition(int x, int y) const;

    int getColumns() const;
    int getRows() const;
    float getCellSize() const;

    void setShowLines(bool show);

    void setCellRect(int x1, int y1, int x2, int y2, int value);
};