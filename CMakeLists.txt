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
        src/systems/collision_system.cpp
        src/systems/sprite_render_system.cpp
        src/systems/sprite_transform_system.cpp
        src/scene/test_scene.cpp
        src/util/constants.h
        src/systems/physics_system.cpp
        src/systems/physics_system.h
        src/components/bread.h
        src/util/random.cpp
        src/util/random.h
        src/components/obstacle.h
        src/graphics/background.cpp src/systems/background_render_system.cpp src/systems/background_render_system.h)

# Create executable target

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Added this so policy CMP0065 doesn't scream
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 0)


# External header-only libraries in the ext/

target_include_directories(${PROJECT_NAME} PUBLIC ext/stb_image/)
target_include_directories(${PROJECT_NAME} PUBLIC ext/entt/)

# Find OpenGL
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
endif()



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

target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES})

# Needed to add this
if(IS_OS_LINUX)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
endif()
