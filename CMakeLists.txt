project(RJSON)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp RJsonObject.h parser.h parser.cpp reader.h reader.cpp type.h)