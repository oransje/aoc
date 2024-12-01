#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

#define FILEPATH "./day00/input.txt" 

int sum_distance(std::vector<int> a, std::vector<int> b);
std::pair<std::vector<int>, std::vector<int> > generate_pair_vectors();
std::pair<int, int> get_two_values(std::string& s);
int calculate_similarity(std::vector<int> a, std::vector<int> b);

int main() {
    std::pair<std::vector<int>, std::vector<int> > pv;
    int distance;

    pv = generate_pair_vectors();

    distance = sum_distance(pv.first, pv.second);
    std::cout << "sum of distances is: " <<  distance << std::endl;
    std::cout << "similarity score is:" << 42 << std::endl;

    return 0;
}

int sum_distance(std::vector<int> a, std::vector<int> b) {
    int sum_distance = 0;

    // by default std::sort uses '<' operator
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    for(auto i = a.begin(), j = b.begin(); j != b.end(); ++i, ++j) {
        if (*i > *j) {
            sum_distance += *i - *j;
            continue;
        }

        sum_distance += *j - *i;
    }   

    return sum_distance;
}

std::pair<std::vector<int>, std::vector<int> > generate_pair_vectors() 
{
    std::ifstream file;
    std::string line;
    std::string full_file;
    std::vector<int> first_column;
    std::vector<int> second_column;

    file.open(FILEPATH);
    if(file.is_open()) {
        while(std::getline(file, line)) {
            std::pair<int, int> temp = get_two_values(line);
            first_column.push_back(temp.first);
            second_column.push_back(temp.second);
        }
    }
    file.close();
    
    return std::make_pair(first_column, second_column);
}

std::pair<int, int> get_two_values(std::string& s) 
{
    std::string delimiter = " ";
    size_t pos = 0;

    std::string token;
    while((pos = s.find(delimiter) != (std::string::npos))) {
        token.append(s.substr(0, pos));
        s.erase(0, delimiter.length());
    }

    return std::make_pair(std::atoi(token.c_str()), std::atoi(s.c_str()));
}

int calculate_similarity(std::vector<int> a, std::vector<int> b)
{
    int similarity = 0;

    return similarity;
}
