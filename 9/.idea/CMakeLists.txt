cmake_minimum_required(VERSION 3.10)
project(_idea C)

set(CMAKE_C_STANDARD 11)

add_executable(_idea
        codeStyles/Project.xml
        9.iml
        misc.xml
        modules.xml
        workspace.xml)
