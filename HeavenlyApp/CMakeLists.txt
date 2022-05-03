project(HeavenlyEditor VERSION 0.0.0.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${APP_EXE}
	${SRC_DIR}/main.cpp
	${SRC_DIR}/app/private/editorgui.cpp
	${SRC_DIR}/app/private/appruntime.cpp
)

target_include_directories(
	${APP_EXE} PUBLIC
	${SRC_DIR}/app
)

target_link_libraries(${APP_EXE} ${ENGINE_LIB})

target_compile_features(${APP_EXE} PRIVATE cxx_std_20)

set_target_properties(${APP_EXE} PROPERTIES CXX_STANDARD 20)

target_compile_options(${APP_EXE} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:preprocessor>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)