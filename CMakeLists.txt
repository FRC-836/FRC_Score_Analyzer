cmake_minimum_required(VERSION 3.5.0)

#Project name
project(FRC_2018_Point_Analyzer)

#setup qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#fine QtWidgets library
find_package(Qt5Widgets REQUIRED)

#setup include and linking directories
include_directories(inc
                    )

#setup source files
set(src src/main.cpp
        src/MainWindow.cpp
        )
        
#setup header files
set(include inc/MainWindow.h
            )
            
set(forms form/MainWindow.ui
          )
#create the library
add_library(${PROJECT_NAME} ${src} ${include} ${forms})

#linking
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)