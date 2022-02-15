cmake_minimum_required(VERSION 3.11)
project(chess
				VERSION 0.1
				LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
	fxtui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/fxtui
	GIT_TAG 81b7207121e41c3b838eca6f54396e4f676fa3d8
)
FetchContent_GetProperties(fxtui)
if(NOT fxtui_POPULATED)
	FetchContent_Populate(fxtui)
	add_subdirectory(${fxtui_SOURCE_DIR} ${fxtui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include_directories()


add_executable(chess src/main.cpp src/board.cpp)
target_link_libraries(chess
	PRIVATE fxtui::screen
	PRIVATE fxtui::dom
	PRIVATE fxtui::component)
