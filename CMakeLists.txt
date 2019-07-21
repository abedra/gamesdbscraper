cmake_minimum_required(VERSION 3.10)
project(gamesdbscraper VERSION 0.0.1 DESCRIPTION "Scraper for thegamesdb.net")

set(CMAKE_CXX_STANDARD 17)

find_package(CURL)
if (CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIR})
else(CURL_FOUND)
  message(FATAL_ERROR "CURL not found")
endif(CURL_FOUND)

add_executable(gamesdbscraper src/main.cpp src/json.hpp src/HttpClient.h src/HttpClient.cpp)
target_link_libraries(gamesdbscraper curl)
