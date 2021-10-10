cmake_minimum_required (VERSION 3.8)
project(WraithOfTheDead VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WraithOfTheDead)
set (CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.12)
find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5)
find_package(SDL2_TTF REQUIRED PATHS ${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.15)
find_package(SDL2_MIXER REQUIRED PATHS ${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

file(GLOB SOURCE
     "src/*.h"
     "src/*.cpp"
)

add_executable (WraithOfTheDead ${SOURCE})


target_link_libraries(WraithOfTheDead ${SDL2_LIBRARIES})
target_link_libraries(WraithOfTheDead ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(WraithOfTheDead ${SDL2_TTF_LIBRARIES})
target_link_libraries(WraithOfTheDead ${SDL2_MIXER_LIBRARIES})