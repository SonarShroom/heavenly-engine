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

add_library(${ENGINE_LIB}
    ${SRC_DIR}/core/private/Heavenly.cpp
    ${SRC_DIR}/core/private/EntityComponentSystem.cpp
    ${SRC_DIR}/graphics/private/GUI.cpp
    ${SRC_DIR}/graphics/private/OpenGLRenderer.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp

    ${SRC_DIR}/core/Heavenly.h
)

target_include_directories(${ENGINE_LIB} PRIVATE
    ${SRC_DIR}/core
    ${SRC_DIR}/graphics
    ${SRC_DIR}/math

    ${GLAD_DIR}/include
    ${IMGUI_DIR}
)
target_include_directories(${ENGINE_LIB} PUBLIC ${ENGINE_DIR}/src/include)

target_link_libraries(${ENGINE_LIB}
    glad
    glfw
)