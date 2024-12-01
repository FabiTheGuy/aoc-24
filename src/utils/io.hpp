#ifndef AOC_24_UTILS_IO_HPP
#define AOC_24_UTILS_IO_HPP

#include <vector>
#include <string>

/**
 * @brief Reads all lines of content from `path`
 * 
 * @return std::string Content of `path
 */
std::vector<std::string> read_file_lines(const std::string& path);

#endif /* AOC_24_UTILS_IO_HPP */