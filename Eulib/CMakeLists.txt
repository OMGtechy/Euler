cmake_minimum_required(VERSION 3.13)
project(Eulib)

add_library(Eulib ./eulib_primes.cpp)
target_include_directories(Eulib PRIVATE ./eulib_primes.h)

