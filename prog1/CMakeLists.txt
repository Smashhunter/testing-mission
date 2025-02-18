cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
									# Если версия установленной программы
									# старее указаной, произойдёт аварийный выход.

project(prog1)				        # Название проекта

set(SOURCE_EXE main.cpp)			# Установка переменной со списком исходников

include_directories(../lib)			# Расположение заголовочных файлов

add_executable(prog1 ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(../lib ./lib)			# Добавление подпроекта, указывается имя дирректории

target_link_libraries(prog1 lib)		# Линковка программы с библиотекой