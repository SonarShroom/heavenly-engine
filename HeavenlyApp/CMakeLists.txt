set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${APP_EXE} ${SRC_DIR}/main.cpp)

target_link_libraries(${APP_EXE} ${ENGINE_LIB})