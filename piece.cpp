#include "piece.h"

int Piece::getMaxX() const{
    int max = points[0].x;
    for(Point p : points){
        if(p.x > max){
            max = p.x;
        }
    }
    return max;
}

int Piece::getMaxY() const{
    int max = points[0].y;
    for(Point p : points){
        if(p.y > max){
            max = p.y;
        }
    }
    return max;
}

int Piece::getMinX() const{
    int min = points[0].x;
    for(Point p : points){
        if(p.x < min){
            min = p.x;
        }
    }
    return min;
}

int Piece::getMinY() const{
    int min = points[0].y;
    for(Point p : points){
        if(p.y < min){
            min = p.y;
        }
    }
    return min;
}

std::string Piece::print() const{
    std::string r = name+"\n";
    for(int i=this->getMaxY(); i>=this->getMinY(); --i){
        for(int j=this->getMinX(); j<=this->getMaxX(); ++j){
            bool t = false;
            for(Point p : points){
                if(p.y == i && p.x == j){
                    t = true;
                }
            }
            if(t){
                r+="[]";
            }
            else{
                r+="  ";
            }
        }
        r+="\n";
    }
    return r;
}

void Piece::rotate270(){
    for(Point &p : points){
        int temp = p.x;
        p.x = -p.y;
        p.y = temp;
    }
}

void Piece::rotate90(){
    for(Point &p : points){
        int temp = p.y;
        p.y = -p.x;
        p.x =temp;
    }
    while (getMinY()<0){
        for(Point &p : points){
            p.y++;
        }
    }
}

void Piece::flip(){
    for(Point &p : points){
        p.x = -p.x;
    }
    while(getMinX()<0){
        for(Point &p : points){
            p.x++;
        }
    }
}

int Piece::getNumPoints() const{
    return points.size();
}

Point Piece::getPoint(int index) const{
    return points[index];
}