project(HeavenlyEngine
        VERSION 0.0.0
        DESCRIPTION "Heavenly Game Engine"
        LANGUAGES CXX
)

option(HEAVENLY_TESTS "Enables Heavenly Engine tests target.")

# TODO: Once the engine part has been put into a separate repo, this work dir must be changed.
execute_process(
    COMMAND
        git rev-parse --short HEAD
    OUTPUT_VARIABLE
        HeavenlyEngine_REVISION
    WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
)
string(REGEX REPLACE "\n" "" HeavenlyEngine_REVISION "${HeavenlyEngine_REVISION}")
message(STATUS "Heavenly Engine Version: " ${HeavenlyEngine_VERSION} "-" ${HeavenlyEngine_REVISION})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

set(SPDLOG_DIR ${3RD_PARTY_DIR}/spdlog)
include_directories(${SPDLOG_DIR}/include/spdlog)

set(IMGUI_DIR ${3RD_PARTY_DIR}/imgui)

add_library(imgui STATIC
	${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/imgui_demo.cpp
	${IMGUI_DIR}/imgui_tables.cpp

    # included while we use some imgui helper functions
	${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
	${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_compile_definitions(imgui PUBLIC
	IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)

target_link_libraries(imgui PRIVATE
	glad
	glfw
)

set(GLAD_DIR thirdparty/glad)
add_library("glad" ${GLAD_DIR}/src/glad.c)

set(FMT_DIR ${3RD_PARTY_DIR}/fmt)

target_include_directories("glad" PRIVATE ${GLAD_DIR}/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
    ${3RD_PARTY_DIR}/glfw
)

add_subdirectory(
    ${SPDLOG_DIR}
)

add_subdirectory(
    ${FMT_DIR}
)

add_library(${ENGINE_LIB}
    ${SRC_DIR}/core/private/Engine.cpp

    ${SRC_DIR}/graphics/private/GUIManager.cpp
    ${SRC_DIR}/graphics/private/Renderer.cpp

    ${SRC_DIR}/logging/private/LogManager.cpp

    ${SRC_DIR}/resources/private/Shader.cpp

    ${SRC_DIR}/window_system/private/Window.cpp

    ${SRC_DIR}/world/private/Entity.cpp
    ${SRC_DIR}/world/private/WorldAdmin.cpp
)

target_include_directories(${ENGINE_LIB} PUBLIC
    ${SRC_DIR}/core
    ${SRC_DIR}/graphics
    ${SRC_DIR}/math
    ${SRC_DIR}/logging
    ${SRC_DIR}/resources
    ${SRC_DIR}/window_system
	${SRC_DIR}/world

    ${GLAD_DIR}/include
)

configure_file(
    ${SRC_DIR}/core/HeavenlyVersion.h.in
    ${SRC_DIR}/core/HeavenlyVersion.h
)

target_include_directories(${ENGINE_LIB} PUBLIC ${ENGINE_DIR}/include ${ENGINE_DIR}/src)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

target_link_libraries(${ENGINE_LIB} PUBLIC
	imgui
    glad
    glfw
    spdlog::spdlog
)

target_compile_features(${ENGINE_LIB} PRIVATE cxx_std_20)

set_target_properties(${ENGINE_LIB} PROPERTIES CXX_STANDARD 20)

target_compile_options(${ENGINE_LIB} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:preprocessor>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(HEAVENLY_TESTS)
	message(STATUS "Heavenly Engine tests enabled. Importing Catch2.")
	add_subdirectory(${ENGINE_DIR}/thirdparty/catch2)

	set(TESTS_DIR ${ENGINE_DIR}/tests)
	set(TESTS_EXE ${ENGINE_LIB}Tests)

	add_executable(${TESTS_EXE}
		${TESTS_DIR}/main.cpp
		${TESTS_DIR}/world/EntityComponentSystemTests.cpp
	)
	target_link_libraries(${TESTS_EXE} PRIVATE ${ENGINE_LIB} Catch2WithMain)

	target_compile_features(${TESTS_EXE} PRIVATE cxx_std_23)
	set_target_properties(${TESTS_EXE} PROPERTIES CXX_STANDARD 23)
endif(HEAVENLY_TESTS)