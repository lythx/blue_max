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
        src/entities/Player.c
        src/entities/Player.h
        src/geometry.h
        src/entities/Plane.c
        src/entities/Plane.h
        src/entities/Projectile.c
        src/entities/Projectile.h
        src/entities/Building.c
        src/entities/Building.h
        src/generate.c
        src/generate.h
        src/update.c
        src/update.h
        src/entities.h
        src/utils.c
        src/utils.h
        src/render.c
        src/render.h
        src/input.c
        src/input.h
        src/entities/Tree.c
        src/entities/Tree.h
)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

