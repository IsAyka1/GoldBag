CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(GoldBag)

add_executable(${PROJECT_NAME}
        main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE /)