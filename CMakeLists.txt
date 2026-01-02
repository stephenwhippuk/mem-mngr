cmake_minimum_required(VERSION 3.16)
project(mem_mngr VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

set(MEMMNGR_SOURCES
    ${PROJECT_SOURCE_DIR}/src/memalloc.cpp
    ${PROJECT_SOURCE_DIR}/src/memslice.cpp
    ${PROJECT_SOURCE_DIR}/src/pgcontext.cpp
    ${PROJECT_SOURCE_DIR}/src/seqcontext.cpp
    ${PROJECT_SOURCE_DIR}/src/seqaccess.cpp
    ${PROJECT_SOURCE_DIR}/src/memunit.cpp
    ${PROJECT_SOURCE_DIR}/src/primitives.cpp
    ${PROJECT_SOURCE_DIR}/src/engine.cpp
)

add_executable(mem_mngr ${MEMMNGR_SOURCES})

target_include_directories(mem_mngr PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Optionally, add tests if present
if(EXISTS "${PROJECT_SOURCE_DIR}/tests")
    enable_testing()
        # GoogleTest setup
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/heads/main.zip
        )
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
        # GoogleMock is included with GoogleTest

        file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
        # Also link main sources to test target for implementation
        file(GLOB MAIN_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
        # Remove engine.cpp (main) from test sources to avoid main conflict
        list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*engine.cpp$")
        add_executable(mem_mngr_tests ${TEST_SOURCES} ${MAIN_SOURCES})
        target_include_directories(mem_mngr_tests PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/build/_deps/googletest-src/googletest/include)
        target_link_libraries(mem_mngr_tests gtest_main)
        add_test(NAME mem_mngr_tests COMMAND mem_mngr_tests)
endif()
