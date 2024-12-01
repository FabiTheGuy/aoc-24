#include <fstream>
#include <sstream>
#include "io.hpp"


std::vector<std::string> read_file_lines(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::string> data;
    std::string buffer;

    if (file.fail())
        throw std::runtime_error("Unable to open the file: " + path);

    while (getline(file, buffer))
        data.push_back(std::move(buffer));

    if (!file.eof() && file.fail()) 
        throw std::runtime_error("Error reading file: " + path);

    return data;
}