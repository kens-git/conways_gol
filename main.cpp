#include <iostream>
#include <vector>
#include <memory>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

unsigned short numNeighbors(const vector<vector<bool>> &cells, unsigned int x, unsigned int y);
void updateGrid(vector<vector<bool>> &cells);
void drawGrid(const vector<vector<bool>> &cells);

int main() {
    vector<vector<bool>> cells;

    random_device dev;
    mt19937 eng(dev());
    uniform_int_distribution<int> dist(0, 5);

    for (int i = 0; i < 20; i++) {
        cells.push_back(vector<bool>());
        for (int j = 0; j < 30; j++) {
            if (dist(eng)) {
                cells.at(i).push_back(false);
            } else {
                cells.at(i).push_back(true);
            }
        }
    }

    drawGrid(cells);

    for (int i = 0; i < 30; i++) {
        updateGrid(cells);
        drawGrid(cells);
    }

    return 0;
}

unsigned short numNeighbors(const vector<vector<bool>> &cells, unsigned int x, unsigned int y) {
    unsigned short num = 0;

    // Northwest
    if (y > 0 && x > 0) {
        if (cells.at(y - 1).at(x - 1)) num++;
    }
    // North
    if (y > 0) {
        if (cells.at(y - 1).at(x)) num++;
    }
    // Northeast
    if (y > 0 && x < cells.at(0).size() - 2) {
        if (cells.at(y - 1).at(x + 1)) num++;
    }
    // West
    if (x > 0) {
        if (cells.at(y).at(x - 1)) num++;
    }
    // East
    if (x < cells.at(0).size() - 2) {
        if (cells.at(y).at(x + 1)) num++;
    }
    // Southwest
    if (y < cells.size() - 2 && x > 0) {
        if (cells.at(y + 1).at(x - 1)) num++;
    }
    // South
    if (y < cells.size() - 2) {
         if (cells.at(y + 1).at(x)) num++;
    }
    // Southeast
    if (y < cells.size() - 2 && x < cells.at(0).size() - 2) {
        if (cells.at(y + 1).at(x + 1 )) num++;
    }

    return num;
}

void updateGrid(vector<vector<bool>> &cells) {
    // we can't change the current cells in place because it would affect
    // the rest of the unvisited cells, so create a copy to evaluate the
    // game of life rules on while performing the actual operations on the
    // real cells
    vector<vector<bool>> oldCells = cells;

    for (int i = 0; i < oldCells.size(); i++) {
        for (int j = 0; j < oldCells.at(0).size(); j++) {
            unsigned int numN = numNeighbors(oldCells, j, i);

            if (oldCells.at(i).at(j)) { // check if cell is alive
                if (numN < 2) {
                    cells.at(i).at(j) = false;
                }
                else if (numN > 3) {
                    cells.at(i).at(j) = false;
                }
            } else { // it's dead
                if (numN == 3) {
                    cells.at(i).at(j) = true;
                }
            }

            // kill anything that touches the walls
            if (j <= 0 || j >= cells.at(0).size() - 1) {
                cells.at(i).at(j) = false;
            }
            if (i <= 0 || i >= cells.size() - 1) {
                cells.at(i).at(j) = false;
            }
        }
    }
}

void drawGrid(const vector<vector<bool>> &cells) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells.at(0).size(); j++) {
            //Check if it's a wall cell
            if (i == 0 || i == cells.size() - 1
                || j == 0 || j == cells.at(0).size() - 1) {
                cout << "#";
            }
            else if (cells.at(i).at(j) == true) {
                cout << "O";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
