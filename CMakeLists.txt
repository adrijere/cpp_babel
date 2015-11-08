cmake_minimum_required(VERSION 3.3)
project(cpp_babel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -g")

set(INC_PATH inc)
set(SRC_PATH src)
set(SERVER_PATH server)
set(CLIENT_PATH client)
set(MODULES_PATH modules)
set(IMPLEMENTATIONS_PATH implementations)
set(NETWORK_PATH network)
set(COMMAND_PATH command)
set(ERRORS_PATH errors)

set(IMPLEMENTATIONS_FILES
        ${MODULES_PATH}/${IMPLEMENTATIONS_PATH}/${SRC_PATH}/ImplementationFactory.cpp
)

set(NETWORK_FILES
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/UnixTCPClient.cpp
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/UnixUDPClient.cpp
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/BoostTCPNetwork.cpp
        ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/BoostTCPServer.cpp
)

#file(GLOB NETWORK_FILES ${MODULES_PATH}/${NETWORK_PATH}/${SRC_PATH}/*.cpp)

set(COMMAND_FILES
        ${MODULES_PATH}/${COMMAND_PATH}/${SRC_PATH}/CommandInterpreter.cpp
        ${MODULES_PATH}/${COMMAND_PATH}/${SRC_PATH}/Command.cpp
        ${MODULES_PATH}/${COMMAND_PATH}/${SRC_PATH}/ACommand.cpp)

set(ERRORS_FILES
        ${MODULES_PATH}/${ERRORS_PATH}/${SRC_PATH}/Errors.cpp)

include_directories(
        ${SERVER_PATH}/${INC_PATH}
        ${MODULES_PATH}/${IMPLEMENTATIONS_PATH}/${INC_PATH}
        ${MODULES_PATH}/${NETWORK_PATH}/${INC_PATH}
        ${MODULES_PATH}/${COMMAND_PATH}/${INC_PATH}
        ${MODULES_PATH}/${ERRORS_PATH}/${INC_PATH}
)

set(SERVER_FILES
        ${SERVER_PATH}/main.cpp
        ${SERVER_PATH}/${SRC_PATH}/ServerCore.cpp
        ${IMPLEMENTATIONS_FILES}
        ${NETWORK_FILES}
        ${COMMAND_FILES}
        ${ERRORS_FILES}
)

add_executable(babel_server ${SERVER_FILES})
set_target_properties(babel_server PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -D _SERVER_")
set_target_properties(babel_server PROPERTIES LINK_FLAGS "${CMAKE_LINK_FLAGS} -lboost_system -pthread")

include_directories(
        ${Qt5Network_INCLUDE_DIRS}
        ${CLIENT_PATH}/${INC_PATH}
        ${MODULES_PATH}/${IMPLEMENTATIONS_PATH}/${INC_PATH}
        ${MODULES_PATH}/${NETWORK_PATH}/${INC_PATH}
        ${MODULES_PATH}/${COMMAND_PATH}/${INC_PATH}
        ${MODULES_PATH}/${ERRORS_PATH}/${INC_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CLIENT_FILES
        ${CLIENT_PATH}/main.cpp
        ${CLIENT_PATH}/${SRC_PATH}/ClientCore.cpp
        ${CLIENT_PATH}/${SRC_PATH}/addFont.cpp
        ${CLIENT_PATH}/${SRC_PATH}/usage.cpp
        ${IMPLEMENTATIONS_FILES}
        ${NETWORK_FILES}
        ${COMMAND_FILES}
        ${ERRORS_FILES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5_EXECUTABLE_COMPILE_FLAGS}")
add_definitions(${Qt5_DEFINITIONS})
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
qt5_wrap_cpp(CPP_HDRS
        ${CLIENT_PATH}/inc/MainWindow.hpp
        ${CLIENT_PATH}/inc/Login.hpp
)
qt5_wrap_ui(UIS_HDRS
        ${CLIENT_PATH}/login.ui
        ${CLIENT_PATH}/mainwindow.ui
)
set(CMAKE_AUTORCC ON)#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(babel_client ${CLIENT_FILES} ${CLIENT_PATH}/resources.qrc ${UIS_HDRS} ${CPP_HDRS})
TARGET_LINK_LIBRARIES(babel_client ${Qt5Network_LIBRARIES} ${Qt5Widgets_LIBRARIES})
set_target_properties(babel_client PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -D _CLIENT_")
set_target_properties(babel_client PROPERTIES LINK_FLAGS "${CMAKE_LINK_FLAGS} -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread")
