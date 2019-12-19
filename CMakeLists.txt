cmake_minimum_required(VERSION 3.13)
project(Heavenly VERSION 0.0.0)

set(APP_EXE ${PROJECT_NAME}App)

set(ENGINE_LIB ${PROJECT_NAME}Engine)
set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/${ENGINE_LIB})

add_subdirectory(${ENGINE_LIB})
add_subdirectory(${APP_EXE})