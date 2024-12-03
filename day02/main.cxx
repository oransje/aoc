#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

#define FILEPATH "./day02/input.txt"

std::string open_file(std::string filename);
std::vector<std::vector<int> > gen_expressions_list(std::string mem_code);
int eval(std::vector<std::vector<int> > expr_lst);

int main () {
    std::string code;
    std::vector<std::vector<int> > lst;
    int sum;
    
    code = open_file(FILEPATH);
    lst = gen_expressions_list(code);
    sum = eval(lst);

    std::cout << "value evaluated is: " << sum << '\n';
    
    return 0;
}

std::vector<std::vector<int> > gen_expressions_list(std::string mem_code) 
{
    std::regex mul_pattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    std::regex n_pattern("\[0-9]{1,3}");
    std::vector<std::vector<int> > list;
    for (std::smatch expr; std::regex_search(mem_code, expr, mul_pattern);) {
        std::vector<int> multipliers;

        std::string func = expr.str();
        for (std::smatch n_expr; std::regex_search(func, n_expr, n_pattern);) {            
            multipliers.push_back(std::atoi(n_expr.str().c_str()));

            func = n_expr.suffix();
        }
        list.push_back(multipliers);

        mem_code = expr.suffix();
    }

    return list;
}

std::string open_file(std::string filename) 
{
    std::ifstream file;
    std::string line;
    std::string text;
    
    file.open(filename);
    while(std::getline(file,line)) {
        text.append(line);
    }
    file.close();

    return text;
}

int eval(std::vector<std::vector<int> > expr_lst) 
{
    auto multiply = [](const std::vector<int>& a) { return a[0]*a[1]; };
    auto summation = [&](int sum, std::vector<int>& numbers) { 
        return sum + multiply(numbers);
    };

    return std::reduce( expr_lst.begin(), expr_lst.end(), 0, summation);
}