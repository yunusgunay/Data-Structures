/*
    Name: Yunus Gunay
    Section: 2
    ID: 22203758
*/

#include "BuildingMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

BuildingMap::BuildingMap(const string buildingMapFile) {
    parseFile(buildingMapFile);
    cout << rows << " rows and " << cols << " columns have been read." << endl;
}

BuildingMap::~BuildingMap() {
    for (int i = 0; i < rows; ++i) {
        delete[] building[i];
    }
    delete[] building;
}


void BuildingMap::parseFile(const string buildingMapFile) {
    ifstream file(buildingMapFile);
    if (file.is_open()) {
        file >> rows >> cols;
        file.ignore();
        building = new Cubicle*[rows];
        for (int i = 0; i < rows; ++i) {
            building[i] = new Cubicle[cols];
            string row{};
            file >> row;
            for (int j = 0; j < cols; ++j) {
                int cell = row[j] - '0';
                building[i][j].leftWall = cell & 1;
                building[i][j].bottomWall = cell & 2;
            }
        }
        file.close();
    } else {
        cerr << "Cannot open file." << endl;
    }
}


void BuildingMap::displayAllCubicles() const {
    cout << "The cubicles in the building are:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "(" << i << "," << j << ")";
            if (j < cols - 1) cout << ",";
        }
        cout << endl;
    }
}


void BuildingMap::displayAdjacentCubicles(const int row, const int col) const {
    cout << "The cubicles adjacent to (" << row << "," << col << ") are:" << endl;
    cout << "(" << row << "," << col << ") -> ";
    bool first = true;

    // For lexicographic order:
    if (row > 0 && !building[row - 1][col].bottomWall) { // Up
        if(!first) cout << ",";
        cout << "(" << row - 1 << "," << col << ")";
        first = false;
    }
    if (col > 0 && !building[row][col].leftWall) { // Left
        if(!first) cout << ",";
        cout << "(" << row << "," << col - 1 << ")";
        first = false;
    }
    if (col < cols - 1 && !building[row][col + 1].leftWall) { // Right
        if(!first) cout << ",";
        cout << "(" << row << "," << col + 1 << ")";
        first = false;
    }
    if (row < rows - 1 && !building[row][col].bottomWall) { // Down
        if(!first) cout << ",";
        cout << "(" << row + 1 << "," << col << ")";
        first = false;
    }
    cout << endl;
}


void BuildingMap::displayBuildingMap() const {
    cout << "The building map is as follows:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "(" << i << "," << j << ") -> ";
            bool first = true;

            // For lexicographic order:
            if (i > 0 && !building[i - 1][j].bottomWall) { // Up
                if (!first) cout << ",";
                cout << "(" << i - 1 << "," << j << ")";
                first = false;
            }
            if (j > 0 && !building[i][j].leftWall) { // Left
                if (!first) cout << ",";
                cout << "(" << i << "," << j - 1 << ")";
                first = false;
            }
            if (j < cols - 1 && !building[i][j + 1].leftWall) { // Right
                if (!first) cout << ",";
                cout << "(" << i << "," << j + 1 << ")";
                first = false;
            }
            if (i < rows - 1 && !building[i][j].bottomWall) { // Down
                if (!first) cout << ",";
                cout << "(" << i + 1 << "," << j << ")";
                first = false;
            }
            cout << endl;
        }
    }
}


void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol) {
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") are:" << endl;
    findPathsHelper(startRow, startCol, endRow, endCol, -1, -1, false);
}


void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol) {
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") ";
    cout << "avoiding (" << avoidRow << "," << avoidCol << ") are:" << endl;
    findPathsHelper(startRow, startCol, endRow, endCol, avoidRow, avoidCol, true);
}


bool BuildingMap::isValidMove(const Coordinate& from, int direction) const {
    if (direction == 0 && from.row > 0 && !building[from.row - 1][from.col].bottomWall) { // Up
        return true;
    }
    if (direction == 1 && from.col > 0 && !building[from.row][from.col].leftWall) { // Left
        return true;
    }
    if (direction == 2 && from.col < cols - 1 && !building[from.row][from.col + 1].leftWall) { // Right
        return true;
    }
    if (direction == 3 && from.row < rows - 1 && !building[from.row][from.col].bottomWall) { // Down
        return true;
    }
    return false;
}


void BuildingMap::findPathsHelper(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol, bool avoiding) {
    Stack pathStack;
    pathStack.push({{startRow, startCol}, {false, false, false, false}});

    bool** visited = new bool*[rows];
    for(int i = 0; i < rows; ++i){
        visited[i] = new bool[cols]{false};
    }

    if(avoidCol != -1) {
        visited[avoidRow][avoidCol] = true;
    }

    bool pathFound = false;
    while(!pathStack.isEmpty()){
        Node current = pathStack.peek();
        if(!visited[current.coord.row][current.coord.col]){
            visited[current.coord.row][current.coord.col] = true;

            if(current.coord.row == endRow && current.coord.col == endCol){
                pathFound = true;
                Stack reversePath;
                int counter[rows][cols];
                for(auto &tempCounter : counter){
                    for(int &cell : tempCounter){
                        cell = 0;
                    }
                }

                while(!pathStack.isEmpty()){
                    counter[pathStack.peek().coord.row][pathStack.peek().coord.col] += 1;
                    reversePath.push(pathStack.peek());
                    pathStack.pop();
                }

                while(!reversePath.isEmpty()){
                    pathStack.push(reversePath.peek());
                    Node node = reversePath.pop();
                    counter[node.coord.row][node.coord.col] -= 1;
                    if((!counter[node.coord.row][node.coord.col]) && visited[node.coord.row][node.coord.col]){
                        cout << "(" << node.coord.row << "," << node.coord.col << ")";
                        if(!reversePath.isEmpty()) cout << " -> ";
                    }
                }

                cout << endl;
            } else{
                int direction = 3;
                while(direction >= 0){
                    Coordinate nextCoord;
                    switch(direction){
                        case 0: // Up
                            nextCoord = {current.coord.row - 1, current.coord.col};
                            break;
                        case 1: // Left
                            nextCoord = {current.coord.row, current.coord.col - 1};
                            break;
                        case 2: // Right
                            nextCoord = {current.coord.row, current.coord.col + 1};
                            break;
                        case 3: // Down
                            nextCoord = {current.coord.row + 1, current.coord.col};
                            break;
                    }

                    if(isValidMove(current.coord, direction) && !visited[nextCoord.row][nextCoord.col]) {
                        pathStack.push({nextCoord, {false, false, false, false}}); // Push new node
                    }
                    direction--;
                }
                continue;
            }
        }
        visited[current.coord.row][current.coord.col] = false;
        pathStack.pop();
    }

    if (!pathFound) {
        cout << "None" << endl;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] visited[i];
    }
    delete[] visited;
}
