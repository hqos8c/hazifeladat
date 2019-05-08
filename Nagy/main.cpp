#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <cmath>
#include <vector>
#include <utility>

struct Date
{
    int year;
    int month;
    int day;
};

struct Value
{
    std::string name;
    double value;
};

struct Time_data
{
    std::vector<Value> data;
    Date date;
};

std::pair<std::string, std::string> splitFirst(std::string input, char separator)
{
    auto pos = input.find(separator);

    if (pos == std::string::npos)
    {
        return std::pair<std::string, std::string>(
            input,
            std::string());
    }
    else
    {
        return std::pair<std::string, std::string>(
            input.substr(0, pos),
            input.substr(pos + 1, input.length() - pos - 1));
    }
}

std::vector<std::string> split(std::string input, char separator)
{
    std::vector<std::string> result = std::vector<std::string>();
    std::string remain = input;
    for(int i=0;i<7;i++)
    {
        std::pair<std::string, std::string> pair = splitFirst(remain, separator);
        result.push_back(pair.first);
        remain = pair.second;
    }
    return result;
}

Value parse_data(std::string row)
{
    std::pair<std::string, std::string> splitted = splitFirst(row, ',');

    auto value = Value();
    value.name = splitted.first;
    if(splitted.second.size() == 0){value.value = 0;}
    else{value.value = std::stod(splitted.second);}   
    return value;
}

Time_data parse_row(std::string row)
{
    auto row_vec = split(row, ' ');
    auto time_data = Time_data();
    time_data.data = {};

    auto v = split(row_vec[row_vec.size()-1], ';');
    for (auto i: v) {
        time_data.data.push_back(parse_data(i));
    }

    time_data.date = Date();
    time_data.date.year = std::stoi(row_vec[0]);
    time_data.date.month = std::stoi(row_vec[1]);
    time_data.date.day = std::stoi(row_vec[2]);

    return time_data;
}

Time_data average(Time_data kalap){
    
}

std::vector<Time_data> parse_file() {
    std::vector<Time_data> data_vector = std::vector<Time_data>();
        
    std::ifstream input("data.txt");
    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            auto time_data = parse_row(line);
            data_vector.push_back(time_data);
        }
    }

    return data_vector;
}

int main()
{
    auto data = parse_file();
}