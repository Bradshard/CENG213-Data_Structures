cmake_minimum_required(VERSION 3.10)
project(FileSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the main executable
add_executable(FileSystem_Main
    src/main.cpp
    src/Node.cpp
    src/File.cpp
    src/Folder.cpp
    src/Link.cpp
    src/FileSystem.cpp
)

# Enable testing
enable_testing()

# Google Test
find_package(GTest QUIET)
if(NOT GTEST_FOUND)
    # Download and build GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Create the test executable
add_executable(FileSystem_Tests
    tests/FileSystemTests.cpp
    src/Node.cpp
    src/File.cpp
    src/Folder.cpp
    src/Link.cpp
    src/FileSystem.cpp
)

# Link Google Test libraries
target_link_libraries(FileSystem_Tests GTest::gtest_main)

# Add the test
add_test(NAME FileSystemTests COMMAND FileSystem_Tests)

# Include CTest for testing features
include(CTest)

# Add custom target for running tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Running tests"
    DEPENDS FileSystem_Tests
)

# Valgrind support
find_program(VALGRIND "valgrind")
if(VALGRIND)
    # Add valgrind target for main executable
    add_custom_target(valgrind_main
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ${CMAKE_CURRENT_BINARY_DIR}/FileSystem_Main
        DEPENDS FileSystem_Main
        COMMENT "Running Valgrind on main executable"
    )

    # Add valgrind target for tests
    add_custom_target(valgrind_tests
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ${CMAKE_CURRENT_BINARY_DIR}/FileSystem_Tests
        DEPENDS FileSystem_Tests
        COMMENT "Running Valgrind on tests"
    )

    # Add suppressions file target (if needed)
    add_custom_target(valgrind_generate_suppressions
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=valgrind_suppressions.txt ${CMAKE_CURRENT_BINARY_DIR}/FileSystem_Main
        DEPENDS FileSystem_Main
        COMMENT "Generating Valgrind suppressions file"
    )

    # Generate XML report for CI integration (if needed)
    add_custom_target(valgrind_xml
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --xml=yes --xml-file=valgrind_report.xml ${CMAKE_CURRENT_BINARY_DIR}/FileSystem_Tests
        DEPENDS FileSystem_Tests
        COMMENT "Running Valgrind with XML output for CI integration"
    )
else()
    message(STATUS "Valgrind not found, memory check targets will not be available")
endif()

# Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Set Doxygen input and output directories
    set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)

    # Configure the Doxyfile from the template
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    # Add a custom target to run Doxygen
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    # Add a custom target to open the documentation
    if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
        add_custom_target(open_docs
            COMMAND xdg-open ${DOXYGEN_OUTPUT_DIR}/html/index.html
            DEPENDS docs
            COMMENT "Opening documentation in browser"
        )
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
        add_custom_target(open_docs
            COMMAND open ${DOXYGEN_OUTPUT_DIR}/html/index.html
            DEPENDS docs
            COMMENT "Opening documentation in browser"
        )
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
        add_custom_target(open_docs
            COMMAND start ${DOXYGEN_OUTPUT_DIR}/html/index.html
            DEPENDS docs
            COMMENT "Opening documentation in browser"
        )
    endif()

    # Install documentation to a standard location (optional)
    install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION share/doc/${PROJECT_NAME}
        OPTIONAL
    )

    # Let the user know documentation is available
    message(STATUS "Doxygen found: 'make docs' to generate API documentation")
else()
    message(STATUS "Doxygen not found: API documentation will not be generated")
endif()
