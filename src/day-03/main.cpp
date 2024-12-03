#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>


std::string read_file_blob(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;

    if (!file)
        throw std::runtime_error("Error: Couldn't open file. " + path);

    buffer << file.rdbuf();
    
    return buffer.str();
}


int main() {
    const std::string data = read_file_blob("../data/day-03-input");


    /* ---------- Task One ---------- */

    std::size_t sum = 0;
    std::regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    std::sregex_iterator data_begin = std::sregex_iterator(data.begin(), data.end(), pattern);
    std::sregex_iterator data_end = std::sregex_iterator();

    for (std::sregex_iterator i = data_begin; i != data_end; ++i) 
        sum += std::stoi((*i)[1].str()) * std::stoi((*i)[2].str());

    std::printf("Sum: %li\n", sum);


    /* ---------- Task Two ---------- */

    bool should_do = true;
    std::size_t refined_sum = 0;    
    std::regex refined_pattern(R"((mul\(([0-9]{1,3}),([0-9]{1,3})\)|do\(\))|don't\(\))");
    data_begin = std::sregex_iterator(data.begin(), data.end(), refined_pattern);
    data_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = data_begin; i != data_end; ++i) {
        if ((*i)[0].str() == "don't()")
            should_do = false;
        else if ((*i)[0].str() == "do()")
            should_do = true;
        else if (should_do) 
            refined_sum += std::stoi((*i)[2].str()) * std::stoi((*i)[3].str());        
    }
        

    std::printf("Refined Sum: %li\n", refined_sum);

    return 0;
}