cmake_minimum_required(VERSION 3.9)
project(HeavenlyEngine)

set(ENGINE_VERSION_MAJOR	0)
set(ENGINE_VERSION_MINOR	0)
set(ENGINE_VERSION_REVISION	0)

set(GLAD_DIR thirdparty/glad)
add_library("glad" ${GLAD_DIR}/src/glad.c)

target_include_directories("glad" PRIVATE ${GLAD_DIR}/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
	thirdparty/glfw
)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)