cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "png_toolkit.h" 
	"abstract_filter.h" "filters_collection.cpp" "filters_collection.h" "editor.h" "editor.cpp"
    "filters.cpp" "filters.h" "stb_image.h" "stb_image_write.h")
