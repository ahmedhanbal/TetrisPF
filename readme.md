Improving my first Semester Programming Fundamentals Project
Tetris Game Based in C++ and SFML
Based on Minimial OOP, mostly basic concepts of C++

# FEATURES

## Current:
           
           * Left,Right and Down Movements Possible
           * Press Space key to instantly move block till end
           * Ability to rotate blocks
           * Shadow of a block that will tell user where block will fall 
           * Next Block will also be shown to help the user

# COMPILE AND RUN

* GNU LINUX: 

               # Note you should have g++ compiler installed
            1. install sfml and g++ using : sudo apt install libsfml-dev g++
            2. g++ -c main.cpp
            3. g++ main.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
            4. ./tetris
* Windows:

             # You can install msys2 and run the command 2 and 3 from GNU Linux and then
             1. .\tetris.exe
