cmake_minimum_required(VERSION 3.1)
project(pandaExpress)

# Set c++11
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED)

# nice hierarchichal structure in MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Find OS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(IS_OS_MAC 1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(IS_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(IS_OS_WINDOWS 1)
else()
    message(FATAL_ERROR "OS ${CMAKE_SYSTEM_NAME} was not recognized")
endif()

# Add source files as we code (QWERTY)
# Generate the shader folder location to the header
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp")


#file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)

set(SOURCE_FILES
        src/main.cpp
        src/scene/scene_manager.cpp
        src/scene/scene.cpp
        src/util/input_manager.cpp
        src/graphics/window.cpp
        src/graphics/texture.cpp
        src/graphics/texture_manager.cpp
        src/graphics/shader.cpp
        src/graphics/shader_manager.cpp
        src/util/gl_utils.cpp
        src/graphics/sprite.cpp
        src/graphics/mesh.cpp
        src/graphics/camera.cpp
        src/systems/player_movement_system.cpp
        src/systems/sprite_render_system.cpp
        src/systems/sprite_transform_system.cpp
        src/util/constants.h
        src/systems/physics_system.cpp
        src/systems/physics_system.h
        src/components/bread.h
        src/util/random.cpp
        src/util/random.h
        src/scene/main_menu_scene.h
        src/scene/main_menu_scene.cpp
        src/components/obstacle.h
        src/graphics/background.cpp
        src/systems/background_render_system.cpp
        src/systems/background_render_system.h
        src/systems/background_transform_system.cpp
        src/systems/background_transform_system.h
        src/scene/vertical_scene.cpp
        src/scene/vertical_scene.h
        src/util/csv_reader.cpp
        src/util/csv_reader.h
        src/systems/level_system.cpp
        src/systems/level_system.h
        src/scene/horizontal_scene.cpp
        src/scene/horizontal_scene.h
        src/scene/boss_scene.cpp
        src/scene/boss_scene.h
        src/systems/horizontal_level_system.h
        src/systems/horizontal_level_system.cpp
        src/components/ghost.h
        src/components/llama.h src/components/spit.h
        src/components/tutorial.h
        src/systems/vertical_level_system.cpp
        src/systems/vertical_level_system.h
        src/components/chases.h
        src/systems/chase_system.cpp
        src/systems/chase_system.h
        src/util/node.cpp
        src/util/node.h
        src/components/falling_platform.h
        src/util/selector_node.h
        src/util/selector_node.cpp
        src/systems/jacko_ai_system.cpp
        src/systems/jacko_ai_system.h
        src/components/evades.h
        src/systems/boss_level_system.h
        src/systems/boss_level_system.cpp
        src/systems/ghost_movement_system.cpp
        src/systems/ghost_movement_system.h
        src/graphics/mesh_manager.cpp
        src/systems/player_animation_system.cpp
        src/systems/player_animation_system.h
        src/components/timer.cpp
        src/components/timer.h
        src/systems/timer_system.cpp
        src/systems/timer_system.h
        src/systems/falling_platform_system.cpp
        src/systems/falling_platform_system.h
        src/systems/panda_damage_system.cpp
        src/systems/enemy_system.cpp
        src/systems/enemy_system.h
        src/systems/enemy_animation_system.cpp
        src/systems/enemy_animation_system.h
        src/util/sound_manager.cpp
        src/util/sound_manager.h
        src/graphics/health_bar.cpp
        src/graphics/health_bar.h
        src/systems/health_bar_transform_system.cpp
        src/systems/health_bar_transform_system.h
        src/systems/health_bar_render_system.cpp
        src/systems/health_bar_render_system.h
        src/graphics/cave.cpp src/graphics/cave.h 
        src/systems/cave_render_system.cpp 
        src/systems/cave_render_system.h
        src/graphics/text.cpp
        src/graphics/text.h
        src/graphics/font.cpp
        src/graphics/font.h
        src/systems/text_render_system.cpp
        src/systems/text_render_system.h
        src/systems/text_transform_system.cpp
        src/systems/text_transform_system.h
        src/systems/score_system.cpp
        src/systems/score_system.h
        src/components/score.h
        src/components/hud_element.h
        src/systems/hud_transform_system.cpp
        src/systems/hud_transform_system.h
        src/graphics/font_manager.cpp
        src/graphics/font_manager.h
        )


# Create executable target

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Added this so policy CMP0065 doesn't scream
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 0)


# External header-only libraries in the ext/

target_include_directories(${PROJECT_NAME} PUBLIC ext/stb_image/)
target_include_directories(${PROJECT_NAME} PUBLIC ext/entt/)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/freetype2/)
# Find OpenGL
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
endif()

# Find FreeType
find_package(Freetype REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${FREETYPE_LIBRARIES})

if (IS_OS_LINUX OR IS_OS_MAC)
    # Try to find packages rather than to use the precompiled ones
    # Since we're on OSX or Linux, we can just use pkgconfig.
    find_package(PkgConfig REQUIRED)

    pkg_search_module(GLEW REQUIRED glew)
    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)

    # Link Frameworks on OSX
    if (IS_OS_MAC)
        find_library(COCOA_LIBRARY Cocoa)
        find_library(CF_LIBRARY CoreFoundation)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_LIBRARY} ${CF_LIBRARY})
    endif()
elseif (IS_OS_WINDOWS)
    # https://stackoverflow.com/questions/17126860/cmake-link-precompiled-library-depending-on-os-and-architecture
    set(GLEW_FOUND TRUE)
    set(SDL2_FOUND TRUE)

    set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/include/GL")
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/include/SDL")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
        set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/lib/Release/x64/glew32s.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.lib")
        set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.lib")

        set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.dll")
        set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.dll")
    else()
        set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/lib/Release/Win32/glew32s.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.lib")
        set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.lib")

        set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.dll")
        set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.dll")
    endif()

    # Copy and rename dlls
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDLMIXER_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2_mixer.dll")
endif()

# Can't find the include and lib. Quit.
if (NOT SDL2_FOUND)
    message(FATAL_ERROR "Can't find SDL." )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

if($ENV{USER} STREQUAL "Avery")
    target_link_libraries(${PROJECT_NAME} PUBLIC "/usr/local/lib/libGLEW.dylib"
            "/usr/local/lib/libSDL2.dylib"
            "/usr/local/lib/libSDL2_mixer.dylib"
            "-framework Foundation"
            "-framework Cocoa"
            "-framework CoreAudio"
            "-framework AVFoundation"
            "-framework CoreGraphics"
            "-framework MediaPlayer"
            "-framework QuartzCore")
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES})
endif()

# Needed to add this
if(IS_OS_LINUX)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
endif()
