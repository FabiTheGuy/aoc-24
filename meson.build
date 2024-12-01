project(
  'aoc-24',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++11']
)

utils_lib = library(
  'utils_lib',
  sources: [
    './src/utils/io.hpp',
    './src/utils/io.cpp',  # Ensure io.cpp is included here
  ]
)

day_01_exe = executable(
  'day-01',
  sources: './src/day-01/main.cpp',
  link_with: utils_lib
)

test('day-01', day_01_exe)
