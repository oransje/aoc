#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <numeric>

#define FILEPATH "./day02/input.txt"

std::string open_file(std::string filename);
std::vector<std::vector<int> > gen_expressions_list(std::string mem_code);
int eval(std::vector<std::vector<int> > expr_lst);
std::vector<std::vector<int> > scan(std::string mem_code);

int main () {
    std::string code;
    std::vector<std::vector<int> > lst;
    int sum;
    
    code = open_file(FILEPATH);

    lst = gen_expressions_list(code);
    sum = eval(lst);
    std::cout << "value evaluated is: " << sum << '\n';

    lst = scan(code);
    sum = eval(lst);
    std::cout << "value evaluated with do is: " << sum << '\n';
    
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

    return std::reduce(expr_lst.begin(), expr_lst.end(), 0, summation);
}

std::vector<std::vector<int> > scan(std::string mem_code)
{
    std::vector<std::vector<int> > lst;
    bool should_do = true;

    for (auto ch = mem_code.begin(); ch != mem_code.end(); ++ch) {
        if(*ch == 'd') {
            auto f_o = std::next(ch);
            if((*f_o == 'o') && (f_o != mem_code.end())) {
                auto f_lparen = std::next(f_o);
                if((*f_lparen == '(') && (f_lparen != mem_code.end())) {
                    auto f_rparen = std::next(f_lparen);
                    if((*f_rparen == ')') && (f_rparen != mem_code.end()))
                        should_do = true;
                }

                if((*f_lparen == 'n') && (f_lparen != mem_code.end())) {
                    auto f_apos = std::next(f_lparen);
                    if((*f_apos == '\'') && (f_apos != mem_code.end())) {
                        auto f_t = std::next(f_apos);
                        if((*f_t == 't') && (f_t != mem_code.end())) {
                            auto f_parenl = std::next(f_t);
                            if((*f_parenl == '(') && (f_parenl != mem_code.end())) {
                                auto f_parenr = std::next(f_parenl);
                                if ((*f_parenr == ')') && (f_parenr != mem_code.end()))
                                    should_do = false;
                            }
                        }
                    }
                }
            }
        }

        if (should_do) {
            auto m = ch; 
            auto u = std::next(m);
            auto l = std::next(u);
            auto lparen = std::next(l);
            bool is_open = false;

            if((*m == 'm') && (*u == 'u') && (*l == 'l') && (*lparen == '(')) {
                is_open = true;

                while(is_open) {
                    std::string fst_number;
                    std::string snd_number;
                    auto cursor = std::next(lparen);

                    while(std::isdigit(*cursor) && fst_number.length() <= 3) {
                        fst_number += *cursor;
                        ++cursor;
                    }

                    if(*cursor == ',') {
                        cursor = std::next(cursor);
                        while(std::isdigit(*cursor) && fst_number.length() <= 3) {
                            snd_number += *cursor;
                            ++cursor;
                        }
                    } else {
                        is_open = false;
                    }

                    if(*cursor == ')') {
                        std::vector<int> multipliers;
                        multipliers.push_back(std::atoi(fst_number.c_str()));
                        multipliers.push_back(std::atoi(snd_number.c_str()));
                        lst.push_back(multipliers);

                        is_open = false;
                    }

                    is_open = false;
                }
            }
        }
    }

    return lst;
}
