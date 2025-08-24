cmake_minimum_required(VERSION 3.10)
project("serialmonitor")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")


add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    ../CSerial.cpp
)





