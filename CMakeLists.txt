cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME Dijkstra_shortest_path)

file(GLOB source_files
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
install(TARGETS Dijkstra_shortest_path DESTINATION install)
