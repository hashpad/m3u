cmake_minimum_required(VERSION 3.16)
project(myapp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src/ui)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Sql)

add_executable(myapp
    main.cpp
    include/ui/MainWindow.h
    src/MainWindow.cpp
    src/ui/MainWindow.ui

	include/ui/SettingsDialog.h
	src/SettingsDialog.cpp
	src/ui/SettingsDialog.ui

	include/ui/AddProviderDialog.h
	src/AddProviderDialog.cpp
	src/ui/AddProviderDialog.ui


	src/m3u/M3UUtils.cpp
	include/m3u/M3UUtils.h

	src/db/sql.cpp
	include/db/sql.h
)

target_include_directories(myapp PRIVATE include)

target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Sql)

