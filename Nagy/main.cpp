#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <cmath>
#include <vector>
#include <utility>

struct TemperatureData 
{
    std::string name;
    double value;
};

struct TimeData 
{
    int time;
    std::vector<TemperatureData> data;
};

struct DateData {
    int date;
    std::vector<TimeData> times;
};

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
        auto pair = splitFirst(remain, separator);
        result.push_back(pair.first);
        remain = pair.second;
    }
    return result;
}

std::pair<std::string,double> parseData(std::string row) {
    auto splitted = splitFirst(row, ',');
    return std::pair<std::string, double>(splitted.first, std::stod(splitted.second));
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

std::variant<> parseRow(std::string row) {   
    if (isDigit(row[0])) {
        auto r = split(row, ' ');
        auto year = r[0];
        auto month = r[1];
        auto day = r[2];        
        auto data = parseData(r[r.size() - 1]);
    } else {
        auto data = parseData(row);
    }
}
 

int main() {

    std::ifstream input("data_2.txt");
    if(input.is_open()) { 
        std::string line;
        while( std::getline(input, line, ';') ) {
            parseRow(line);
        }
    }
}