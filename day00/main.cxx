#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

#define FILEPATH "./day00/input.txt" 

int sum_distance(std::vector<int> a, std::vector<int> b);
void sort_pair(std::pair<std::vector<int>, std::vector<int> > *pv);
std::pair<std::vector<int>, std::vector<int> > generate_pair_vectors();
std::pair<int, int> get_two_values(std::string& s);
int calculate_similarity(std::vector<int> a, std::vector<int> b);

int main() 
{
    std::pair<std::vector<int>, std::vector<int> > pv;
    int distance, similarity;

    pv = generate_pair_vectors();
    sort_pair(&pv);

    distance = sum_distance(pv.first, pv.second);
    similarity = calculate_similarity(pv.first, pv.second);
    std::cout << "sum of distances: " <<  distance << std::endl;
    std::cout << "similarity score: " << similarity << std::endl;

    return 0;
}

int sum_distance(std::vector<int> a, std::vector<int> b) 
{
    int sum_distance = 0;

    for(auto i = a.begin(), j = b.begin(); j != b.end(); ++i, ++j) {
        if (*i > *j) {
            sum_distance += *i - *j;
            continue;
        }

        sum_distance += *j - *i;
    }   

    return sum_distance;
}

void sort_pair(std::pair<std::vector<int>, std::vector<int> > *pv) {
     // by default std::sort uses "<" operator
    std::sort(pv->first.begin(), pv->first.end());
    std::sort(pv->second.begin(), pv->second.end());
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
    std::unordered_map<int, int> counter;
    int similarity = 0;

    for (auto t:a)
         counter[t]++;

    for (auto k:b) {
        bool found = counter.count(k) != 0;
        if (found) {
            similarity += k * counter[k];
        } 
    }
    
    return similarity;
}
