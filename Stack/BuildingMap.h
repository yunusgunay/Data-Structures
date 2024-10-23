/*
    Name: Yunus Gunay
    Section: 2
    ID: 22203758
*/

#ifndef BUILDINGMAP_H
#define BUILDINGMAP_H
#include <string>
#include <iostream>
using namespace std;

class BuildingMap {
public:
    BuildingMap(const string buildingMapFile);
    ~BuildingMap();
    void displayAllCubicles() const;
    void displayAdjacentCubicles(const int row, const int col) const;
    void displayBuildingMap() const;
    void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
    void findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol);

private:
    struct Cubicle {
        bool leftWall;
        bool bottomWall;
    };

    struct Coordinate {
        int row, col;
        bool operator==(const Coordinate& other) const{
            return (row == other.row && col == other.col);
        }
        bool operator!=(const Coordinate& other) const{
            return !(*this == other);
        }
    };

    int rows, cols;
    Cubicle** building;
    void parseFile(const string buildingMapFile);
    bool isValidMove(const Coordinate& from, int direction) const;
    void findPathsHelper(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol, bool avoiding);

private:
    struct Node {
        Coordinate coord;
        bool gone[4] = {false};
        Node* next;
    };

    class Stack {
    public:
        Stack() : top(nullptr) {}
        ~Stack(){
            clear();
        }

        void push(const Node& node) {
            Node* newNode = new Node{node.coord, {}, top};
            top = newNode;
        }

        Node pop() {
            if(isEmpty()){
                return Node{{-1, -1}, {}, nullptr};
            }
            Node* temp = top;
            Node node = *top;
            top = top->next;
            delete temp;
            return node;
        }

        Node peek() const{
            return *top;
        }

        bool isEmpty() const {
            return top == nullptr;
        }

        void clear() {
            while(!isEmpty()) {
                pop();
            }
        }

        Node* getTop() const {
            return top;
        }
    private:
        Node* top;
    };
    // End of Stack Class
};

#endif // BUILDINGMAP_H
