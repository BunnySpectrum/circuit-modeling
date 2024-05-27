cmake_minimum_required(VERSION 3.13)


project(pgrm_host)

#set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


include_directories(../../lib)
add_executable(${PROJECT_NAME}
    main.cpp
    ../../lib/comp/resistor.cpp
    ../../lib/prime/terminal_2way.cpp
    ../../lib/prime/terminal_4way.cpp
)

