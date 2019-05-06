#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <cmath>
#include <vector>
#include <utility>

std::pair<std::string,std::string> splitFirst(std::string input, char separator) {
    auto pos = input.find(separator);

    if (pos == std::string::npos) {
        return std::pair<std::string, std::string>(
            input, 
            std::string()
        );
    } else {
        return std::pair<std::string, std::string>(
            input.substr(0, pos), 
            input.substr(pos + 1, input.length() - pos -1)
        );
    }
}

std::vector<std::string> split(std::string input, char separator) {
    std::vector<std::string> result = std::vector<std::string>();
    std::string remain = input;
    while(!remain.empty()){
        std::pair<std::string,std::string> pair = splitFirst(remain, separator);
        result.push_back(pair.first);
        remain = pair.second;
    }
    return result;
}

std::pair<std::string,double> parseData(std::string row) {
    std::pair<std::string,std::string> splitted = splitFirst(row, ',');
    return std::pair<std::string, double>(splitted.first, std::stod(splitted.second));
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

std::vector<double> alldata(std::pair<std::string,double> data,std::vector<double> place){

}


std::pair<std::string,double> parseRow(std::string row) {   
    if (isDigit(row[0])) {
        std::vector<std::string> r = split(row, ' ');
        int year = std::stoi(r[0]);
        int month = std::stoi(r[1]);
        int day = std::stoi(r[2]);
        std::pair<std::string,double> data = parseData(r[r.size() - 1]);
        return data;
    } else {
        std::pair<std::string,double> data = parseData(row);
    return data;
    }
}

int main() {
    std::ifstream input("data_2.txt");
    if(input.is_open()) { 
        std::string line;
        int ref = 0;
        while( std::getline(input, line, ';') ) {
            std::pair<std::string,double> data = parseRow(line);
            
        }
    }
}