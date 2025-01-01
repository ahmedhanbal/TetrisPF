# Tetris C++ SFML
![Tetris](https://github.com/user-attachments/assets/095efa2d-e418-4d7c-9342-4f39d35e5518)
## FEATURES

           * Left,Right and Down Movements Possible
           * Press Space key to instantly move block till end
           * Ability to rotate blocks
           * Shadow of a block that will tell user where block will fall 
           * Next Block will also be shown to help the user

## COMPILE AND RUN

* GNU LINUX: 

               # Note you should have g++ compiler installed
            1. install sfml using : sudo apt install libsfml-dev
            then either use compile.sh or do this : 
            2. g++ -c main.cpp
            3. g++ main.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
            4. ./tetris
