project(HeavenlyEditor VERSION 0.0.0.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

set(ICON_FONTS_HEADER_DIR ${3RD_PARTY_DIR}/icon-fonts)
add_library(icon-fonts INTERFACE)
target_sources(icon-fonts INTERFACE
	FILE_SET icon_headers TYPE HEADERS BASE_DIRS ${ICON_FONTS_HEADER_DIR} FILES
	IconsFontAwesome6.h
)

add_executable(${APP_EXE}
	${SRC_DIR}/main.cpp

	${SRC_DIR}/app/private/Runtime.cpp

	${SRC_DIR}/editor/private/GUI.cpp
	${SRC_DIR}/editor/private/MaterialInspector.hpp
	${SRC_DIR}/editor/private/RenderPrimitiveInspector.hpp
	${SRC_DIR}/editor/private/TransformInspector.hpp
	${SRC_DIR}/editor/private/EntityInspector.cpp
	${SRC_DIR}/editor/private/WorldExplorer.cpp
)

target_include_directories(${APP_EXE} PUBLIC
	${SRC_DIR}
	${SRC_DIR}/app
	${SRC_DIR}/editor
)

target_link_libraries(${APP_EXE}
	${ENGINE_LIB}
	icon-fonts
)

target_compile_features(${APP_EXE} PRIVATE cxx_std_20)

set_target_properties(${APP_EXE} PROPERTIES CXX_STANDARD 20)

target_compile_options(${APP_EXE} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:preprocessor>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

install(
	FILES
	${CMAKE_CURRENT_LIST_DIR}/assets/fonts/fa-regular-400.ttf
	${CMAKE_CURRENT_LIST_DIR}/assets/fonts/fa-solid-900.ttf
	DESTINATION
	${CMAKE_CURRENT_BINARY_DIR}/assets/fonts
)