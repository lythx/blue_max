cmake_minimum_required(VERSION 3.27)
project(blue_max)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.c
        src/geometry/Vector.c
        src/geometry/Vector.h
        src/config.h
        src/geometry/Sphere.c
        src/geometry/Sphere.h
        src/geometry/Box.c
        src/geometry/Box.h
        src/defs.h
        src/init_SDL.c
        src/init_SDL.h
        src/draw.c
        src/draw.h
        src/Player.c
        src/Player.h
        src/geometry.h
        src/Plane.c
        src/Plane.h
        src/Projectile.c
        src/Projectile.h
        src/Building.c
        src/Building.h
)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

