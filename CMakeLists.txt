cmake_minimum_required(VERSION 3.3)
project(cpp_babel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra")

set(INC_PATH inc)
set(SRC_PATH src)
set(SERVER_PATH server)
set(CLIENT_PATH client)
set(MODULES_PATH modules)
set(IMPLEMENTATIONS_PATH implementations)
set(NETWORK_PATH network)
set(COMMAND_PATH command)

set(IMPLEMENTATIONS_FILES
        ${MODULES_PATH}/${IMPLEMENTATIONS_PATH}/${SRC_PATH}/ImplementationFactory.cpp
)

set(NETWORK_FILES
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/BoostTCPNetwork.cpp
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/BoostTCPClient.cpp
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/BoostTCPServer.cpp
)

set(COMMAND_FILES
        ${MODULES_PATH}/${COMMAND_PATH}/${SRC_PATH}/Command.cpp
        ${MODULES_PATH}/${COMMAND_PATH}/${SRC_PATH}/ACommand.cpp)

include_directories(
        ${SERVER_PATH}/${INC_PATH}
        ${MODULES_PATH}/${IMPLEMENTATIONS_PATH}/${INC_PATH}
        ${MODULES_PATH}/${NETWORK_PATH}/${INC_PATH}
        ${MODULES_PATH}/${COMMAND_PATH}/${INC_PATH}
)

set(SERVER_FILES
        ${SERVER_PATH}/main.cpp
        ${SERVER_PATH}/${SRC_PATH}/Core.cpp
        ${IMPLEMENTATIONS_FILES}
        ${NETWORK_FILES}
        ${COMMAND_FILES}
)

add_executable(babel_server ${SERVER_FILES})
set_target_properties(babel_server PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -D _SERVER_")
set_target_properties(babel_server PROPERTIES LINK_FLAGS "${CMAKE_LINK_FLAGS} -lboost_system -pthread")
