cmake_minimum_required(VERSION 3.13)


project(pgrm_host)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


include_directories(../../lib)
include_directories(../../designs)

find_package(protobuf REQUIRED CONFIG) # use lowercase protobuf for building and linking the application
find_package(Protobuf REQUIRED) # use uppercase Protobuf for the generate_cpp lol

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../../../protobuf/netlist.proto)
protobuf_generate_python(PROTO_PY ../../../protobuf/netlist.proto)
message(${PROTO_PY})
message(${CMAKE_CXX_COMPILER_ID})
message("***")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
    main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    ${PROTO_PY}
    ../../designs/sallen_key/sallen_key.cpp
    ../../designs/rlc_lp/rlc_lp.cpp
    ../../lib/circuit/circuit.cpp
    ../../lib/comp/resistor.cpp
    ../../lib/prime/terminal_2way.cpp
    ../../lib/prime/element.cpp    
    ../../lib/prime/voltage_source.cpp    
    ../../lib/prime/terminal_4way.cpp
    ../../lib/prime/node.cpp    
    ../../lib/prime/net.cpp    
    ../../lib/utils/uid.cpp

)

target_link_libraries(${PROJECT_NAME} protobuf::libprotobuf)