cmake_minimum_required(VERSION 3.0)

project("pixify")

set(source_files
    "pixelate.cpp"
    "main.cpp"
)

set(source_paths)
foreach(file IN LISTS source_files)
    set(source_paths ${source_paths} "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}")
endforeach(file)

add_executable(${PROJECT_NAME} ${source_paths})
target_link_libraries(${PROJECT_NAME} "SDL2" "SDL2_image")

