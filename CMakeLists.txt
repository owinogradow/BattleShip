cmake_minimum_required(VERSION 3.4)

#Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set debug profile, also maximum level of debug info g3 and format of debug info to dwarf-4 (requires gdb in version 7)
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()

enable_language(CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)


project(Battleship)



set(SOURCE_FILES
	include/functions.h
    	include/GameLogic.h
    	include/Player.h
    	include/ComputerPlayer.h
    	include/HumanPlayer.h
    	include/HumanUI.h
    	include/Ship.h
    	include/Grid.h
		include/Square.h
    	include/MultipleFunnel.h
    	include/SingleFunnel.h
    	include/Segment.h
    	include/Strategy.h
    	include/Greedy.h
    	include/Random.h
		include/GridDisplay.h
		
    	src/functions.cpp
    	src/GameLogic.cpp
    	src/Player.cpp
    	src/ComputerPlayer.cpp
    	src/HumanPlayer.cpp
    	src/HumanUI.cpp
    	src/Ship.cpp
    	src/Grid.cpp
		src/Square.cpp
    	src/MultipleFunnel.cpp
		src/SingleFunnel.cpp
    	src/Segment.cpp
    	src/Strategy.cpp
    	src/Random.cpp
    	src/Greedy.cpp
	src/GridDisplay.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(BattleShip src/main.cpp)
add_library(BattleshipLib ${SOURCE_FILES})
target_link_libraries(BattleShip BattleshipLib)
#Unit Tests section

# Check if generating Visual Studio 14 2015 project
if(MSVC)
    if(NOT BOOST_ROOT)
        set(BOOST_ROOT "C:/local/boost_1_60_0")
    endif()
    set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
    set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib64-msvc-14.0")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)


    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})

else()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

set(SOURCE_TEST_FILES
    test/config.cpp
    test/SingleFunnelTest.cpp
	test/ComputerStrategyTest.cpp
	test/GridTest.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

add_executable (BattleshipTest ${SOURCE_TEST_FILES})


#link to Boost libraries and targets and dependencies
target_link_libraries (
	BattleshipTest
	BattleshipLib
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

	add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
    ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
enable_testing()
add_test(Test BattleshipTest)
