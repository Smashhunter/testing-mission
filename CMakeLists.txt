cmake_minimum_required(VERSION 3.10)

project(test_task)

include_directories(./lib)			# Расположение заголовочных файлов

add_executable(prog1 ./prog1/main.cpp)	# Создает исполняемый файл с именем main
add_executable(prog2 ./prog2/main.cpp)	# Создает исполняемый файл с именем main

add_subdirectory(./lib)			# Добавление подпроекта, указывается имя дирректории

target_link_libraries(prog1 lib)		# Линковка программы с библиотекой
target_link_libraries(prog2 lib)		# Линковка программы с библиотекой
