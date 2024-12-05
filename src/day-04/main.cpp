#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>


std::vector<std::string> read_lines(const std::string& path) {
    std::vector<std::string> data;
    std::string line;
    std::ifstream file(path);

    if (!file)
        throw std::runtime_error("Error: Couldn't open file: " + path);

    while (std::getline(file, line))
        data.push_back(line);

    return data;
}


std::size_t pattern_in_data(const std::string& pattern, const std::vector<std::string>& data, const std::size_t x, const std::size_t y) {
    /* States, which operations are possible  */
    bool is_right_possible = data[0].size() - x >= pattern.size();
    bool is_left_possible = x + 1 >= pattern.size();
    bool is_top_possible = y >= pattern.size() - 1;
    bool is_bot_possible = data.size() - y >= pattern.size();

    /* States if pattern matches in specific direction */
    bool is_horizontal_right = true;
    bool is_horizontal_left = true;
    bool is_vertical_top = true;
    bool is_vertical_bot = true;
    bool is_top_right = true;
    bool is_top_left = true;
    bool is_bot_left = true;
    bool is_bot_right = true;


    for (std::size_t i = 0; i < pattern.size(); i++) {
            is_horizontal_right &= (is_right_possible) ? data[y][x + i] == pattern[i] : false;
            is_horizontal_left &= (is_left_possible) ? data[y][x - i] == pattern[i] : false;
            is_vertical_top &= (is_top_possible) ? data[y - i][x] == pattern[i] : false;
            is_vertical_bot &= (is_bot_possible) ? data[y + i][x] == pattern[i] : false;
            is_top_right &= (is_right_possible && is_top_possible) ? data[y - i][x + i] == pattern[i] : false;
            is_top_left &= (is_left_possible && is_top_possible) ? data[y - i][x - i] == pattern[i] : false;
            is_bot_left &= (is_left_possible && is_bot_possible) ? data[y + i][x - i] == pattern[i] : false;
            is_bot_right &= (is_right_possible && is_bot_possible) ? data[y + i][x + i] == pattern[i] : false;
    }


    return is_horizontal_right + is_horizontal_left + is_vertical_top + is_vertical_bot + is_top_right + is_top_left + is_bot_left + is_bot_right;
}


std::size_t x_mas_in_data(const std::vector<std::string>& data, const std::size_t x, std::size_t y) {
    if (y == 0 || y == data.size() - 1 || x == 0 || x == data[0].size() - 1)
        return 0;
    
    /* Values of char around each 'A'  */
    char ch_top_left = data[y - 1][x - 1];
    char ch_top_right = data[y - 1][x + 1];
    char ch_bot_left = data[y + 1][x - 1];
    char ch_bot_right = data[y + 1][x + 1];

    /* Possible patterns  */
    bool x_mas_from_top = ch_top_left == 'M' && ch_top_right == 'M' && ch_bot_left == 'S' && ch_bot_right == 'S';
    bool x_mas_from_left = ch_top_left == 'M' && ch_bot_left == 'M' && ch_top_right == 'S' && ch_bot_right == 'S';
    bool x_mas_from_bot = ch_bot_left == 'M' && ch_bot_right == 'M' && ch_top_left == 'S' && ch_top_right == 'S';
    bool x_mas_from_right = ch_top_right == 'M' && ch_bot_right == 'M' && ch_top_left == 'S' && ch_bot_left == 'S';


    return x_mas_from_top + x_mas_from_left + x_mas_from_bot + x_mas_from_right;
}


int main() {
    std::vector<std::string> data = read_lines("../data/day-04-input");


    /* ---------- Task One ---------- */

    const std::string pattern = "XMAS";
    std::size_t pattern_occurence = 0;

    for (std::size_t i = 0; i < data.size(); i++) {
        for (std::size_t j = 0; j < data[i].size(); j++) {
            if (data[i][j] == pattern[0]) 
                pattern_occurence += pattern_in_data(pattern, data, j, i);
        }
    }   

    std::printf("Pattern %s occurs: %li times\n", pattern.c_str(), pattern_occurence);


    /* ---------- Task Two ---------- */

    std::size_t x_mas_occurence = 0;

    for (std::size_t y = 0; y < data.size(); y++) {
        for (std::size_t x = 0; x < data.size(); x++) {
            if (data[y][x] == 'A')
                x_mas_occurence += x_mas_in_data(data, x, y);
        }
    }

    std::printf("X-MAS occurs: %li times\n", x_mas_occurence);


    return 0;
}
