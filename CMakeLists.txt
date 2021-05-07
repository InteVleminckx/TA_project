cmake_minimum_required(VERSION 3.17)
project(projectTA)

set(CMAKE_CXX_STANDARD 14)

add_executable(projectTA
        main.cpp
        Datastructuur.cpp
        Datastructuur.h
        Maksim.h
        Maksim.cpp
        Importer.cpp
        Importer.h
        txml/tinyxml.h
        txml/tinystr.h
        txml/tinyxmlparser.cpp
        txml/tinyxmlerror.cpp
        txml/tinyxml.cpp
        txml/tinystr.cpp
        Bestemming.cpp
        Bestemming.h
        )