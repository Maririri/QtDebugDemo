cmake_minimum_required(VERSION 3.10)
project(QtDebugDemo)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
    set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.1/lib/cmake/Qt5Widgets/")
elseif (UNIX)
    set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.13.1/gcc_64/lib/cmake)
endif ()

find_package(Qt5Widgets REQUIRED)
find_package(Boost COMPONENTS thread system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIR})

set(LIBS_TO_LINK
        Qt5::Widgets
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )

add_executable(DebugDemo main.cpp)
target_link_libraries(DebugDemo ${LIBS_TO_LINK})