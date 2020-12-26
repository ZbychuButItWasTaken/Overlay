cmake_minimum_required (VERSION 3.0.0)

project (Overlay)
file(GLOB_RECURSE Overlay_CPPS src/*.cpp)

add_executable(Overlay ${Overlay_CPPS})

target_include_directories(Overlay PUBLIC src)

target_link_libraries(Overlay PUBLIC m)

find_package(Threads REQUIRED)
target_link_libraries(Overlay PUBLIC Threads::Threads)

if(WIN32 AND NOT MINGW)
    find_package(PNG CONFIG REQUIRED)
else()
    find_package(PNG REQUIRED)
endif()
target_link_libraries(Overlay PUBLIC PNG::PNG)

install(TARGETS Overlay DESTINATION bin)