cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
									# Если версия установленной программы
									# старее указаной, произойдёт аварийный выход.

project(prog2)				        # Название проекта

set(SOURCE_EXE main.cpp)			# Установка переменной со списком исходников

include_directories(../lib)			# Расположение заголовочных файлов

add_executable(prog2 ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(../lib ./lib)			# Добавление подпроекта, указывается имя дирректории

target_link_libraries(prog2 lib)		# Линковка программы с библиотекой