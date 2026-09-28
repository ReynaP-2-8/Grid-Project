#include <string>
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

std::map<std::string, std::string> const pieceDictionary = {{"P-Piece", "(0,0)(0,1)(1,0)(1,1)(1,2)"},{"T-Piece", "ref (0,0)(0,1)(0,2)(1,1)(2,1)"},
{"U-Piece", "ref (0,0)(0,1)(1,0)(2,0)(2,1)"}, {"Z-Piece", "rot (0,0)(0,1)(1,1)(2,1)(2,2)"}, {"L-Piece", "(0,0)(0,1)(1,0)(0,2)(0,3)"}, 
{"I-Piece", "ref rot (0,0)(0,1)(0,2)(0,3)"}, {"V-Piece", "(0,0)(0,1)(0,2)(1,0)(2,0)"}, {"N-Piece", "(0,0)(0,1)(1,1)(1,2)(1,3)"},
{"J-Piece", "(0,0)(0,1)(1,0)(2,0)"}, {"S-Piece", "rot (0,0)(0,1)(1,1)(1,2)"}, {"o-Piece", "ref rot (0,0)"}, 
{"i-Piece", "ref rot (0,0)(0,1)(0,2)"}, {"F-Piece", "(0,0)(1,0)(1,1)(2,1)(1,2)"},{"W-Piece", "(0,0)(1,0)(1,1)(2,1)(2,2)"}, 
{"X-Piece", "ref rot (1,0)(1,1)(0,1)(1,2)(2,1)"}, {"Y-Piece", "(0,0)(1,0)(2,0)(3,0)(2,1)"}, {"O-Piece", "ref rot (0,0)(0,1)(1,0)(1,1)"},
{"C-Piece", "ref (0,0)(0,1)(0,2)(1,2)(2,2)(1,0)(2,0)"}, {"H-Piece", "ref rot (0,0)(0,1)(0,2)(1,1)(2,0)(2,1)(2,2)"},
{"/-Piece", "(0,0)(0,1)(0,2)(1,1)(1,2)(2,2)"}, {"--Piece", "ref rot (0,0)(1,0)"}, {",-Piece", "(0,0)(0,1)(1,1)"}};

//Open argv[1]
//Features in argv[2] (fnr, fe, del, apnd, ins)
//find and replace (argv[3] = num occurences / all, argv[4] = text to replace between quotations, argv[5] = text to be replaces with between quotations)
//fast edit (argv[3] = axb (for board.txt), argv[3+] = piece names (for pieces.txt)(defined in dictionary somewhere))
//delete (argv[3+] = line number(s))
//append (argv[3] = text between quotations)
//insert (argv[3] = line number, argv[4] = text between quotations)

int main(int argc, char* argv []){
    if(std::string(argv[2]) == "fe"){
        if(std::string(argv[1]) == "board.txt"){
            std::string input = argv[3];
            int x = input.find("x", 0);
            int width = stoi(input.substr(0,x));
            int height  =stoi(input.substr(x+1,input.size()-x-1));

            std::vector<std::pair<int, int>> points;
            for(int i=4; i<argc; ++i){
                std::pair<int, int> temp;
                int comma = std::string(argv[i]).find(",", 0);
                temp.first = stoi(std::string(argv[i]).substr(0,comma));
                temp.second = stoi(std::string(argv[i]).substr(comma+1));
                points.push_back(temp);
            }

            std::ofstream boardFile("board.txt");

            for(int i=0; i<height; ++i){
                for(int j=0; j<width; ++j){
                    bool found = false;
                    for(std::pair<int, int> point : points){
                        if(point.first == i && point.second == j){
                            boardFile<<"[NUL]";
                            found = true;
                            break;
                        }
                    }
                    if(width*i+j+1 > 99 && !found){boardFile<<"["<<width*i+j+1<<"]";}
                    else if(width*i+j+1 > 9 && !found){boardFile<<"[ "<<width*i+j+1<<"]";}
                    else if(!found){boardFile<<"[  "<<width*i+j+1<<"]";}
                }
                if(i != height-1){boardFile<<std::endl;}
            }
            boardFile.close();
        }
        else if(std::string(argv[1]) == "pieces.txt"){
            std::ofstream piecesFile("pieces.txt");
            for(int i=3; i<argc; ++i){
                int num = 1;
                std::string temp = std::string(argv[i]);
                if(temp.find("x", 0) != std::string::npos){
                    num = stoi(temp.substr(0,temp.find("x",0)));
                    temp = temp.substr(temp.find("x",0)+1);
                }
                if(pieceDictionary.find(temp) != pieceDictionary.end()){
                    for(int i=0; i<num; ++i){
                        piecesFile<<pieceDictionary.find(temp)->first<<" "<<pieceDictionary.find(temp)->second<<std::endl;
                    }
                }
            }
            piecesFile.close();
        }
    }
    else if(std::string(argv[2]) == "fnr"){
        std::string fileName = std::string(argv[1]);
        std::ifstream inputFile(fileName);
        std::vector<std::string> originalText;
        std::string inputLine;
        while(getline(inputFile, inputLine)){originalText.push_back(inputLine);}
        inputFile.close();
        int num = 0;
        if(std::string(argv[3]) != "all"){num = stoi(argv[3]);}
        for(std::string &line : originalText){
            int index = 0;
            while(line.find(std::string(argv[4]), index) != std::string::npos && (num-->0 || std::string(argv[3]) == "all")){
                std::string lineBegin = line.substr(0,line.find(std::string(argv[4]), index));
                std::string lineEnd = line.substr(line.find(std::string(argv[4]), index)+std::string(argv[4]).size());
                index = line.find(std::string(argv[4]), index)+1;
                line = lineBegin+argv[5]+lineEnd;
            }
        }
        std::ofstream outputFile(fileName);
        for(int i=0; i<originalText.size(); ++i){
            if(i==originalText.size()-1){outputFile<<originalText[i];}
            else{outputFile<<originalText[i]<<std::endl;}
        }
        outputFile.close();
    }
    else if(std::string(argv[2]) == "del"){
        std::set<int> deleted;
        for(int i=3; i<argc; ++i){deleted.insert(stoi(argv[i]));}
        std::string fileName = std::string(argv[1]);
        std::ifstream inputFile(fileName);
        std::vector<std::string> originalText;
        std::string inputLine;
        while(getline(inputFile, inputLine)){originalText.push_back(inputLine);}
        inputFile.close();
        std::ofstream outputFile(fileName);
        for(int i=1; i<=originalText.size(); ++i){
            if(deleted.find(i) == deleted.end()){
                if(i == originalText.size()){outputFile<<originalText[i-1];}
                else{outputFile<<originalText[i-1]<<std::endl;}
            }
        }
        outputFile.close();
    }
    else if(std::string(argv[2]) == "apnd"){
        std::string fileName = std::string(argv[1]);
        std::ifstream inputFile(fileName);
        std::vector<std::string> originalText;
        std::string inputLine;
        while(getline(inputFile, inputLine)){originalText.push_back(inputLine);}
        inputFile.close();
        originalText.push_back(std::string(argv[3]));
        std::ofstream outputFile(fileName);
        for(int i=0; i<originalText.size(); ++i){
            if(i==originalText.size()-1){outputFile<<originalText[i];}
            else{outputFile<<originalText[i]<<std::endl;}
        }
        outputFile.close();
    }
    else if(std::string(argv[2]) == "ins"){
        std::string fileName = std::string(argv[1]);
        std::ifstream inputFile(fileName);
        std::vector<std::string> originalText;
        std::string inputLine;
        int lineNum = 0;
        while(getline(inputFile, inputLine)){
            if(++lineNum == stoi(argv[3])){originalText.push_back(std::string(argv[4]));}
            originalText.push_back(inputLine);
        }
        inputFile.close();
        if(stoi(argv[3]) > originalText.size()){originalText.push_back(std::string(argv[4]));}
        std::ofstream outputFile(fileName);
        for(int i=0; i<originalText.size(); ++i){
            if(i==originalText.size()-1){outputFile<<originalText[i];}
            else{outputFile<<originalText[i]<<std::endl;}
        }
        outputFile.close();
    }
    else if(std::string(argv[2]) == "print" || std::string(argv[2]) == "prnt"){
        std::string inputFileName = std::string(argv[1]);
        std::ifstream inputFile(inputFileName);
        std::string inputLine;
        while(getline(inputFile, inputLine)){std::cout<<inputLine<<std::endl;}
        inputFile.close();
    }
    return 0;
}