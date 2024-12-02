#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

#define FILEPATH "./day01/input.txt"

std::vector<int> make_line_vector(std::string& s);
bool is_safe(std::vector<int> v);
std::vector<std::vector<int> > parse_file(std::string filename);
int calculate_safeness(std::vector<std::vector<int> > data);


int main () {
    std::vector<std::vector<int> > table;
    int number_of_safe;

    table = parse_file(FILEPATH);
    number_of_safe = calculate_safeness(table);

    std::cout << "safe reports: " << number_of_safe << std::endl;

    return 0;
}

std::vector<int> make_line_vector(std::string& s) {
    std::string line;
    std::vector<int> numbers;
    char delimiter = ' ';
    std::stringstream ss(s);

    while(std::getline(ss, line, delimiter)) {
        numbers.push_back(std::atoi(line.c_str()));
    }

    return numbers;
}

bool is_safe(std::vector<int> v) 
{
    bool is_decreasing = std::is_sorted(v.begin(), v.end(), [](int a, int b) {
                             return a > b;
                         });
    bool is_increasing = std::is_sorted(v.begin(), v.end());
    bool is_sorted =  is_decreasing || is_increasing;

    if (!is_sorted)
        return false;

    for(auto i = v.begin(); i != v.end() - 1; ++i) {
        int curr = *i;
        int next = *(i+1);
        int difference = std::abs(curr - next);

        if(difference > 3 || difference < 1)
            return false;
    }

    return true;
}

std::vector<std::vector<int> > parse_file(std::string filename) 
{
    std::ifstream file;
    std::string line;
    std::vector<std::vector<int> > rows;

    file.open(filename);
    while(std::getline(file, line)) {
        std::vector<int> row = make_line_vector(line);
        rows.push_back(row);
    }
    file.close();

    return rows;
}

int calculate_safeness(std::vector<std::vector<int> > data) {
    int safe_data_counter = 0;

    for(auto vec:data)
        if(is_safe(vec))
            ++safe_data_counter;

    return safe_data_counter;
}