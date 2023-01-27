cmake_minimum_required(VERSION 3.20)
project(thgame)

set(CMAKE_CXX_STANDARD 20)

find_package(ZLIB REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

aux_source_directory(src/game SRC_GAME)
aux_source_directory(src/sprite SRC_SPRITE)
aux_source_directory(src/ui SRC_UI)
aux_source_directory(src/math SRC_MATH)
aux_source_directory(src/player SRC_PLAYER)
aux_source_directory(src/scene SRC_SCENE)

add_executable(${PROJECT_NAME}
        src/main.cpp
        ${SRC_GAME}
        ${SRC_SPRITE}
        ${SRC_UI}
        ${SRC_MATH}
        ${SRC_PLAYER}
        ${SRC_SCENE}
        )

target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)

target_link_libraries(${PROJECT_NAME}
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        )

target_link_libraries(${PROJECT_NAME}
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        )

target_link_libraries(${PROJECT_NAME}
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        )