cmake_minimum_required(VERSION 3.23)
project(ProCourseDesign)

set(CMAKE_CXX_STANDARD 14)
#主要配置
include_directories(D:\\MySQL8\\MySQL\\MySQL\ Server\ 8.0\\include)  #include文件夹位置
link_directories(D:\\MySQL8\\MySQL\\MySQL\ Server\ 8.0\\lib) #lib文件夹位置
link_libraries(libmysql)  #lib下dll文件名

add_executable(ProCourseDesign main.cpp)

target_link_libraries(ProCourseDesign libmysql)