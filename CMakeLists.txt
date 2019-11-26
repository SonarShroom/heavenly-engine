cmake_minimum_required(VERSION 3.13)
project(HeavenlyEngine VERSION 0.0.0)

set(SRC_DIR src)
set(3RD_PARTY_DIR thirdparty)

set(IMGUI_DIR ${3RD_PARTY_DIR}/imgui)
include_directories(${IMGUI_DIR})

set(GLAD_DIR thirdparty/glad)
add_library("glad" ${GLAD_DIR}/src/glad.c)

target_include_directories("glad" PRIVATE ${GLAD_DIR}/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
	thirdparty/glfw
)

add_executable(${PROJECT_NAME}
	${SRC_DIR}/main.cpp
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/imgui_demo.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR})
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)