#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>


/**
 * @brief Read the file `path` parses every line into one report
 */
std::vector<std::vector<int>> read_level_log(const std::string& path) {
    std::vector<std::vector<int>> level_list;
    std::ifstream file(path);
    std::string line;

    if (!file)
        throw std::runtime_error("Error: Couldn't open file: " + path);

    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::vector<int> level;
        int num;

        while (line_stream >> num)
            level.push_back(num);

        level_list.push_back(std::move(level));
    }

    return level_list;
}


/**
 * @brief Checks wether a report is safe or not (levels are increasing or decreasing,
 * difference between levels has to be in 1-3)
 */
bool is_safe(const std::vector<int>& report) {
    for (std::size_t i = 0; i < report.size() - 1; ++i) {
        int diff = report[i + 1] - report[i];

        if (std::abs(diff) < 1 || std::abs(diff) > 3)
            return false;
        if (i > 0 && (diff > 0) != (report[i] - report[i - 1] > 0))
            return false;
    }

    return true;
}


/**
 * @brief Checks wether a report is safe even if one bad level exists
 */
bool is_safe_dampener(const std::vector<int>& report) {
    for (std::size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modifiedReport;

        for (std::size_t j = 0; j < report.size(); ++j)
            if (j != i)
                modifiedReport.push_back(report[j]);

        if (is_safe(modifiedReport))
            return true;
    }

    return false;
}


int main() {
    auto report_lists = read_level_log("../data/day-02-input");


    /* ---------- Task One ---------- */

    std::size_t safe_reports = 0;

    for (const auto& report : report_lists) {
        safe_reports += is_safe(report);
    }

    std::printf("Safe Reports: %li\n", safe_reports);


    /* ---------- Task Two ---------- */

    std::size_t safe_reports_tolerance = 0;

    for (const auto& report : report_lists) {
        safe_reports_tolerance += is_safe(report) || is_safe_dampener(report);
    }

    std::printf("Safe Reports (with tolerance): %li\n", safe_reports_tolerance);

    return 0;
}
