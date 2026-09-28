#ifndef __PIECE_H_
#define __PIECE_H_

#include <vector>
#include <string>

struct Point{
    public:
    int x;
    int y;
};

class Piece{
    public:
    Piece(std::string name, std::vector<Point> points, bool ref, bool rot){
        this->name = name;
        this->points = points;
        this->ref = ref;
        this->rot = rot;
    }
    void setPoints(std::vector<Point> points){
        this->points = points;
    }
    std::string print() const;
    int getMaxX() const;
    int getMaxY() const;
    int getMinX() const;
    int getMinY() const;

    void rotate270();
    void rotate90();
    void flip();

    int getNumPoints() const;
    Point getPoint(int index) const;
    bool getRef() const{
        return ref;
    }
    bool getRot() const{
        return rot;
    }

    std::string getName() const{
        return name;
    }

    private:
    std::string name;
    std::vector<Point> points;
    bool ref;
    bool rot;
};

#endif