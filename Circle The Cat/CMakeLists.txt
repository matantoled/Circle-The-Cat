cmake_minimum_required (VERSION 3.20)

project (Circle_The_Cat)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline /analyze)
endif ()

add_executable (${CMAKE_PROJECT_NAME})

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)
set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)
configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)