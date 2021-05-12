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

        engine/easy_image.cc
        engine/engine.cc
        engine/engine.h
        engine/ini_configuration.cc
        engine/Lsysteem.cpp
        engine/Lsysteem.h
        engine/Hulpfuncties.cpp
        engine/Hulpfuncties.h
        engine/l_parser.cc
        engine/l_parser.h
        engine/L2Dsysteem.cpp
        engine/L2Dsysteem.h
        engine/L3Dsysteem.cpp
        engine/L3Dsysteem.h
        engine/vector3d.cc
        engine/vector3d.h
        engine/ZBuffer.cpp
        engine/ZBuffer.h
        engine/drawTriangles.cpp
        engine/drawTriangles.h
        
        Brzozowski.cpp 
        Brzozowski.h

        AlgoritmesControlesysteem/DFA.cpp
        AlgoritmesControlesysteem/DFA.h
        AlgoritmesControlesysteem/ENFA.cpp
        AlgoritmesControlesysteem/ENFA.h
        AlgoritmesControlesysteem/json.hpp
        AlgoritmesControlesysteem/RE.cpp
        AlgoritmesControlesysteem/RE.h
        AlgoritmesControlesysteem/State.cpp
        AlgoritmesControlesysteem/State.h
        Dzhem.cpp
        Dzhem.h

        TFA_Inte/TFA.cpp
        TFA_Inte/TFA.h
        TFA_Inte/json.hpp
        TFA_Inte/TFA_State.cpp
        TFA_Inte/TFA_State.h
        )
