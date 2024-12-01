#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <unordered_map>


/**
 * @brief Reads the file `path` and puts every first number in the `left_list` and every second
 * number in the `right_list`
 */
std::tuple<std::vector<int>, std::vector<int>> read_file(const std::string& path) {
    std::ifstream file(path);
    std::vector<int> left_list, right_list;
    std::string leftEntry, rightEntry;

    if (!file)
        throw std::runtime_error("Error: Couldn't open file: " + path);

    while (file >> leftEntry >> rightEntry) {
        left_list.push_back(std::stoi(leftEntry));
        right_list.push_back(std::stoi(rightEntry));
    }

    return std::make_tuple(left_list, right_list);
}


int main() {
    auto file_data = read_file("../data/day-01-input");
    std::vector<int> left_side = std::move(std::get<0>(file_data));
    std::vector<int> right_side = std::move(std::get<1>(file_data));


    /* ---------- Task One ---------- */

    std::sort(left_side.begin(), left_side.end());
    std::sort(right_side.begin(), right_side.end());

    std::size_t sum = 0;
    for (std::size_t i = 0; i < left_side.size(); i++)
        sum += std::abs((int) left_side.at(i) - right_side.at(i));

    std::printf("Part One\nSum: %li\n", sum);


    /* ---------- Task Two ---------- */

    std::unordered_map<int, int> counter_map;
    sum = 0;

    for (int right_element : right_side)
        counter_map[right_element]++;

    for (int left_element : left_side)
        sum += left_element * counter_map[left_element];

    std::printf("Part Two\nSum: %li\n", sum);


    return 0;
}