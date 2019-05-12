#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

class Date
{
public: 
    int year;
    int month;
    int day;

    Date(int year, int month, int day): year(year), month(month), day(day) {}
};

class Measurment
{
public: 
    std::string name;
    double value;

    Measurment(std::string name, double value): name(name), value(value) {}
};

class Time_data
{
public: 
    Date date;
    std::vector<Measurment> measurments;

    Time_data(Date & date): date(date), measurments({}) {}
    
    Time_data& addMeasurment(Measurment m) {
        this -> measurments.push_back(m);
        return *this;
    }
};

std::vector<Time_data> remove(std::vector<Time_data> & data, std::string name) {
    for (Time_data& d: data) {
        for (int i = d.measurments.size() - 1; i >= 0; i--) {
            auto v = d.measurments[i];
            if (v.name == name) {
                d.measurments.erase(d.measurments.begin() + i);
            }
        }
    }
    return data;
} 

std::pair<std::string, std::string> splitFirst(std::string& input, char separator)
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

std::vector<std::string> split(std::string& input, char separator, int maxSplit = INT_MAX)
{
    std::vector<std::string> result;
    std::string remain = input;
    int i = 0;
    while (!remain.empty() && i < maxSplit - 1)
    {
        std::pair<std::string, std::string> pair = splitFirst(remain, separator);
        result.push_back(pair.first);
        remain = pair.second;
        i++;
    }

    if (!remain.empty()) {
        result.push_back(remain);
    }

    return result;
}

Measurment parse_data(std::string& row)
{
    std::pair<std::string, std::string> splitted = splitFirst(row, ',');
    return Measurment(splitted.first, std::stod(splitted.second));
}

Time_data parse_row(std::string& row)
{
    auto row_vec = split(row, ' ', 7);
    
    auto date = Date(std::stoi(row_vec[0]), std::stoi(row_vec[1]), std::stoi(row_vec[2]));
    auto time_data = Time_data(date);
        
    auto v = split(row_vec[row_vec.size()-1], ';');
    for (auto i: v) { 
        time_data.addMeasurment(parse_data(i)); 
    }

    return time_data;
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
    data_vector = remove(data_vector, "Balaton atlag");
    data_vector = remove(data_vector,"Tihany Rev tavj.");
    return data_vector;
}

Time_data calculateDayAverage(Date& date, std::vector<double> const& sum, std::vector<int> const& count, Time_data& d) {
    Time_data td = Time_data(date);
        
        for (int i = 0; i < sum.size(); i++) {
            double s = sum[i];
            int c = count[i];

            double day_average = c != 0 ? s / c : 0; 
            
            Measurment v = Measurment(d.measurments[i].name, day_average);
            
            td.measurments.push_back(v);
        }
    return td;
}

std::vector<Time_data> average(std::vector<Time_data>& data) 
{
    std::vector<Time_data> result = std::vector<Time_data>();
    
    std::vector<double> sum = std::vector<double>(data[0].measurments.size(), 0);
    std::vector<int> count = std::vector<int>(data[0].measurments.size(), 0);
    
    Date& date = data[0].date;
    for (Time_data d : data) {
        if (d.date.year != date.year || d.date.month != date.month || d.date.day != date.day) {
            result.push_back(calculateDayAverage(date, sum, count, d));
            sum = std::vector<double>(data[0].measurments.size(), 0);
            count = std::vector<int>(data[0].measurments.size(), 0);
        }
        
        date = d.date;

        for (int i = 0; i < d.measurments.size(); i++) {
            sum[i] += d.measurments[i].value;
        }
        
        for (int i = 0; i < d.measurments.size(); i++) {
            count[i] += std::abs(d.measurments[i].value) <= 0.001 ? 0 : 1;
        }
    }
    result.push_back(calculateDayAverage(date, sum, count, data[0]));
    return result;
}

double hoingas(std::vector<double> const& v, int i){
    double result = 0.0;
    if(v.size()-i < 7){result =0.0;}
    if(i != 0){
        int k =i-7;
        auto b = std::minmax_element(v.begin()+k,v.begin()+i);
        result = *b.second-*b.first;
    }
    return result;
}
    
void writeOut(std::vector<Time_data> const& data) {
        std::ofstream ofile("realdata.txt");
    for (auto d: data) {
        ofile << d.date.year << " ";
        ofile << d.date.month << " ";
        ofile << d.date.day << " ";

    ofile<<"Ferto átlag: "<< d.measurments[0].value<<";";
    ofile<<"Velence átlag: "<< d.measurments[1].value<<";";
    ofile<<"Balaton átlag: "<< (d.measurments[2].value+d.measurments[3].value)/2<<";";
    ofile << std::endl;
    }
    for(int i=0;i<4;i++){
        std::vector<double> v;
        for(auto e : data){
            v.push_back(e.measurments[i].value);
        }
        ofile <<data[0].measurments[i].name<<':'<<std::endl;
        auto b = std::minmax_element(v.begin(),v.end());
        ofile<<" A legkissebb hőmérséklete: "<< *b.first<<std::endl;
        ofile <<" A legnagyobb hőmérséklete: "<< *b.second<<std::endl;
    for(int r=0;r<v.size();r+=7){
        double h_ingas = hoingas(v,r);
        if(std::abs(h_ingas) >0.0000001){ofile<<(r)/7<<". heti hőingás "<<h_ingas<<std::endl;}
        }
    }
}

void interpolate_calculate_2(std::vector<Time_data> & data, int first,int last,int i){
    double m = (data[first].measurments[i].value-data[last].measurments[i].value)/(first-last);
    double b = (data[last].measurments[i].value-(m*last));
    for(int j=first+1;j<last;j++){
            data[j].measurments[i].value=m*j+b;
    }
}

void interpolate_calculate(std::vector<Time_data> & data,std::vector<int> n, int i){
    int first=n[0]-1;
    for(int e=1;e<n.size();e++){
        if((n[e]-n[e-1]) != 1)
        {
            interpolate_calculate_2(data,first,n[e-1]+1,i);
            first=n[e]-1;
        }
    }
}

void interpolate(std::vector<Time_data> & data){
    std::vector<int> n;
    for(int i =0; i<data[0].measurments.size();i++){
        for(int j=0;j<data.size()-1;j++){
            if(data[j].measurments[i].value < 0.000001){
            n.push_back(j);
            }
        }
        interpolate_calculate(data,n,i);
        n.resize(0);
    }
}

std::vector<Time_data> datamaker (std::vector<Time_data> & data){
    for(int i = 0;i<data.size();i++){
        if(data[i].measurments.size() != data[0].measurments.size()){
            data[i].measurments = data[i-1].measurments;
        }
    }
    return data;
}

int main()
{
    auto data = parse_file();
    data =datamaker(data);
    interpolate(data);
    data = average(data);
    writeOut(data); 
}