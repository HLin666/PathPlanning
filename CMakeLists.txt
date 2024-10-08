cmake_minimum_required(VERSION 3.10)
project(PathPlanning)

# 添加可执行文件
add_executable(pathplanning src/main.cpp)

file(GLOB LIB_SOURCE_FILES
    "src/include/*.h"
    "src/lib/*.c"
    "src/*.h")

# 添加源文件到可执行文件
target_sources(pathplanning PRIVATE ${LIB_SOURCE_FILES})

# # 设置 GDAL 的安装路径
# set(GDAL_DIR "ThirdParty/GDAL322")

# # 添加 GDAL 的路径
# list(APPEND CMAKE_PREFIX_PATH "${GDAL_DIR}")

# # 查找 GDAL 包
# find_package(GDAL REQUIRED)
# # 链接 GDAL 库
# target_link_libraries(pathplanning PRIVATE GDAL::GDAL)

# 包含头文件目录
# target_include_directories(pathplanning PRIVATE ${CMAKE_SOURCE_DIR}/src)