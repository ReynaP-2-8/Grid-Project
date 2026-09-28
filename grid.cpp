#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
#include <cstdint>
#include <algorithm>
#include "piece.h"

bool sortPieces(Piece &p1, Piece &p2){
    return p1.getNumPoints()>p2.getNumPoints();
}

int choose(int numSpaces, int numRevealed){
    int numerator = 1;
    if(numRevealed < numSpaces/2){
        for(int i=numSpaces; i>numSpaces-numRevealed; --i){
            numerator *= i;
        }
        for(int j=numRevealed; j>0; --j){
            numerator /= j;
        }
    }
    else{
        for(int i=numSpaces; i>numRevealed; --i){
            numerator *= i;
        }
        for(int j=numSpaces-numRevealed; j>0; --j){
            numerator /=j;
        }
    }
    return numerator;
}

class Square{
    public:
    std::string week;
    std::string month;
    std::string day;
    void setZero(){
        week = "";
        month = "";
        day = "";
    }
    std::string getMax(){
        if(week == ""){
            if(month == ""){
                if(day == ""){
                    return "NUL";
                }
                return day;
            }
            return month;
        }
        return week;
    }
};

bool place(std::vector<std::vector<Square>> &board, Piece p, int x, int y, std::set<std::string> conditions){
    int height = board.size();
    int width = board[0].size();
    for(int i=0; i<p.getNumPoints(); ++i){
        Point temp = p.getPoint(i);
        if(x+temp.x<0 || x+temp.x>width-1 || y+temp.y<0 || y+temp.y>height-1 || 
            board[y+temp.y][x+temp.x].getMax() == "NUL" || conditions.find(board[y+temp.y][x+temp.x].getMax()) != conditions.end()){
            return false;
        }
    }
    for(int i=0; i<p.getNumPoints(); ++i){
        Point temp = p.getPoint(i);
        board[y+temp.y][x+temp.x].week = "";
        board[y+temp.y][x+temp.x].month = "";
        board[y+temp.y][x+temp.x].day = "";
    }
    return true;
}

bool generateBoard(std::vector<std::vector<Square>> &board, std::list<Piece> pieces, std::set<std::string> &output, std::set<std::string> conditions){
    if(pieces.empty()){
        std::string outputLine;
        for(std::vector<Square> line : board){
            for(Square sq : line){
                if(sq.getMax() != "NUL"){
                    outputLine += sq.getMax()+" ";
                }
            }
        }
        output.insert(outputLine);
        return true;
    }
    if(pieces.front().getRef() && pieces.front().getRot()){
        for(int i=0; i<2; ++i){
            for(int j=0; j<board.size(); ++j){
                for(int k=0; k<board[0].size(); ++k){
                    std::vector<std::vector<Square>> boardCopy = board;
                    if(place(boardCopy, pieces.front(), j, k, conditions)){
                        std::list<Piece> piecesCopy = pieces;
                        piecesCopy.pop_front();
                        if(generateBoard(boardCopy, piecesCopy, output, conditions)){
                            return true;
                        }
                    }
                }
            }
            pieces.front().rotate90();
        }
    }
    else if(pieces.front().getRef()){
        for(int i=0; i<4; ++i){
            for(int j=0; j<board.size(); ++j){
                for(int k=0; k<board[0].size(); ++k){
                    std::vector<std::vector<Square>> boardCopy = board;
                    if(place(boardCopy, pieces.front(), j, k, conditions)){
                        std::list<Piece> piecesCopy = pieces;
                        piecesCopy.pop_front();
                        if(generateBoard(boardCopy, piecesCopy, output, conditions)){
                            return true;
                        }
                    }
                }
            }
            pieces.front().rotate90();
        }
    }
    else if(pieces.front().getRot()){
        for(int i=0; i<4; ++i){
            for(int j=0; j<board.size(); ++j){
                for(int k=0; k<board[0].size(); ++k){
                    std::vector<std::vector<Square>> boardCopy = board;
                    if(place(boardCopy, pieces.front(), j, k, conditions)){
                        std::list<Piece> piecesCopy = pieces;
                        piecesCopy.pop_front();
                        if(generateBoard(boardCopy, piecesCopy, output, conditions)){
                            return true;
                        }
                    }
                }
            }
            pieces.front().rotate90();
            if(i==1){
                pieces.front().flip();
            }
        }
    }
    else{
        for(int i=0; i<8; ++i){
            for(int j=0; j<board.size(); ++j){
                for(int k=0; k<board[0].size(); ++k){
                    std::vector<std::vector<Square>> boardCopy = board;
                    if(place(boardCopy, pieces.front(), j, k, conditions)){
                        std::list<Piece> piecesCopy = pieces;
                        piecesCopy.pop_front();
                        if(generateBoard(boardCopy, piecesCopy, output, conditions)){
                            return true;
                        }
                    }
                }
            }
            pieces.front().rotate90();
            if(i==3){
                pieces.front().flip();
            }
        }
    }
    return false;
}

std::vector<std::set<std::string>> getCombinations(std::vector<std::string> options, int num){
    std::vector<std::set<std::string>> combinations;
    for(int i=0; i<options.size(); ++i){
        std::set<std::string> combination;
        if(num>1){
            for(int j=i+1; j<options.size(); ++j){
                if(num>2){
                    for(int k=j+1; k<options.size(); ++k){
                        if(num>3){
                            for(int l=k+1; l<options.size(); ++l){
                                combination = {};
                                combination.insert(options[l]);
                                combination.insert(options[k]);
                                combination.insert(options[j]);
                                combination.insert(options[i]);
                                combinations.push_back(combination);
                            }
                        }
                        else{
                            combination = {};
                            combination.insert(options[k]);
                            combination.insert(options[j]);
                            combination.insert(options[i]);
                            combinations.push_back(combination);
                        }
                    }
                }
                else{
                    combination = {};
                    combination.insert(options[j]);
                    combination.insert(options[i]);
                    combinations.push_back(combination);
                }
            }   
        }
        else{
            combination.insert(options[i]);
            combinations.push_back(combination);
        }
    }
    return combinations;
}

int main(int argc, char* argv []){
    std::vector<std::vector<Square>> board;
    std::ifstream boardFile("board.txt");
    std::ofstream outputFile("output.txt");
    std::string boardLine;
    std::vector<std::string> squares;
    int totalSpaces = 0;
    while(getline(boardFile, boardLine)){
        std::vector<Square> line;
        int size = boardLine.size();
        for(int i=1; i<size; i+=5){
            std::string temp = boardLine.substr(i,3);
            Square sq;
            if(!(temp == "   ")){
                totalSpaces++;
                if(!std::isalpha(temp[0])){
                    sq.day = temp;
                }
                else{
                    if(temp == "Mon" || temp == "Tue" || temp == "Wed" || temp == "Thu" || temp == "Fri" || temp == "Sat" || temp == "Sun"){
                        sq.week = temp;
                    }
                    else{
                        sq.month = temp;
                    }
                }
            }
            line.push_back(sq);
            squares.push_back(sq.getMax());
        }
        board.push_back(line);
    }

    std::list<Piece> pieces;

    std::ifstream pieceFile("pieces.txt");
    std::string pieceLine;
    int takenSpaces = 0;
    while(getline(pieceFile, pieceLine)){
        int size = pieceLine.size();
        std::vector<Point> points;
        int begin = pieceLine.find('(', 0)+1;
        for(int i=begin; i<size; i+=5){
            Point temp;
            temp.x = stoi(pieceLine.substr(i,1));
            temp.y = stoi(pieceLine.substr(i+2,1));
            points.push_back(temp);
            takenSpaces++;
        }
        pieces.push_back(Piece(pieceLine.substr(0,pieceLine.find(" ",0)), points, pieceLine.substr(8,3) == "ref", pieceLine.substr(8,3) == "rot" || pieceLine.substr(12,3) == "rot"));
    }
    pieces.sort(sortPieces);

    if(std::string(argv[1]) == "all"){

        if(takenSpaces > totalSpaces){
            std::cout<<"Spaces available: "<<totalSpaces<<std::endl<<"Spaces taken: "<<takenSpaces<<std::endl<<"Not possible to fill board"<<std::endl;
            return 1;
        }

        std::set<std::string> output;

        std::vector<std::set<std::string>> options = getCombinations(squares, totalSpaces-takenSpaces);
        for(std::set<std::string> option : options){
            if(!generateBoard(board, pieces, output, option)){
                for(std::string thing : option){
                    std::cout<<thing<<" ";
                }
                std::cout<<"Doesn't work"<<std::endl;
            }
        }

        std::cout<<"Spaces available: "<<totalSpaces<<std::endl<<"Spaces taken: "<<takenSpaces<<std::endl;
        int possibilities = choose(totalSpaces, takenSpaces);
        std::cout<<"Total combinations: "<<possibilities<<std::endl<<"Combinations found: "<<output.size()<<std::endl;

        if(possibilities == output.size()){
            std::cout<<"This board and piece combination works for each set of configurations."<<std::endl;
        }
        else{
            std::cout<<"This board and piece combination doesn't work for each set of configurations."<<std::endl;
        }

        for(std::string line : output){
            outputFile<<line<<std::endl;
        }
    }
    else{
        std::set<std::string> output;
        std::set<std::string> condition;
        for(int i=1; i<argc; ++i){
            condition.insert(argv[i]);
            std::cout<<argv[i]<<std::endl;
        }
        if(!generateBoard(board, pieces, condition, output)){
            std::cout<<"Doesn't work"<<std::endl;
        }
        else{
            std::cout<<"Works"<<std::endl;
        }
    }

    boardFile.close();
    outputFile.close();
    pieceFile.close();
    return 0;
}