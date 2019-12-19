set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

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

add_library(${ENGINE_LIB} SHARED
	${SRC_DIR}/Heavenly.cpp
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/imgui_demo.cpp
)

target_compile_definitions(${ENGINE_LIB} PRIVATE HEAVENLY_BUILD_DLL)
target_include_directories(${ENGINE_LIB} PRIVATE ${GLAD_DIR}/include)
target_include_directories(${ENGINE_LIB} PRIVATE ${IMGUI_DIR})
target_link_libraries(${ENGINE_LIB} glad)
target_link_libraries(${ENGINE_LIB} glfw)