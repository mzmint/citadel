#include "Grid.h"

Grid::Grid(int width, int height, float cellSize, bool showLines)
    : cellSize(cellSize),
      showLines(showLines),
      lines(sf::PrimitiveType::Lines)
{
    columns = static_cast<int>(width / cellSize);
    rows = static_cast<int>(height / cellSize);

    cells.resize(columns * rows, 0);

    for (int x = 0; x <= columns; x++) {
        float xpos = x * cellSize;

        lines.append(sf::Vertex{{xpos, 0.f}});
        lines.append(sf::Vertex{{xpos, rows * cellSize}});
    }

    for (int y = 0; y <= rows; y++) {
        float ypos = y * cellSize;

        lines.append(sf::Vertex{ {0.f, ypos}});
        lines.append(sf::Vertex{{columns * cellSize, ypos}});
    }
}

void Grid::draw(sf::RenderWindow& window) {
    if (showLines) window.draw(lines);
}

void Grid::setCell(int x, int y, int value) {
    if (x < 0 || x >= columns || y < 0 || y >= rows) return;
    cells[y * columns + x] = value;
}

int Grid::getCell(int x, int y) const {
    if (x < 0 || x >= columns || y < 0 || y >= rows) return 0;
    return cells[y * columns + x];
}

sf::Vector2f Grid::getPosition(int x, int y) const {
    return {
        x * cellSize,
        y * cellSize
    };
}

int Grid::getColumns() const {
    return columns;
}

int Grid::getRows() const {
    return rows;
}

float Grid::getCellSize() const {
    return cellSize;
}

void Grid::setShowLines(bool show) {
    showLines = show;
}

void Grid::setCellRect(int x1, int y1, int x2, int y2, int value) {
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            setCell(x, y, value);
        }
    }
}