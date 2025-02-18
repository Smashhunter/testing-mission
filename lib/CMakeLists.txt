cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
									# Если версия установленной программы
									# старее указаной, произойдёт аварийный выход.

project(lib)				# Название проекта

set(SOURCE_LIB lib.cpp)		# Установка переменной со списком исходников

add_library(lib SHARED ${SOURCE_LIB})# Создание динамической библиотеки