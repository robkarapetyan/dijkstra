cmake_minimum_required(VERSION 3.14)

project(Dijkstra_shortest_path)

file(GLOB source_files
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PRIVATE "include")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 ")
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install)

enable_testing()

add_executable(
  testDijkstra
  test/fTest.cc
  src/node.cpp
  src/graph.cpp
)

target_link_libraries(
  testDijkstra
  gtest_main
)

target_include_directories(testDijkstra PRIVATE "include")
install(TARGETS testDijkstra DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/test)

include(GoogleTest)
gtest_discover_tests(testDijkstra)
