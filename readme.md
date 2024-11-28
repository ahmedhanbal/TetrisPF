AhmedAZ14,CS,FASTNU
Tetris Game Based on C++
Based on Minimial OOP, mostly basic C++

---------FEATURES----------

--Current--:
           
           * Left,Right and Down Movements Possible
           * Press Space key to instantly move block till end
           * Ability to rotate blocks
           * Shadow of a block that will tell user where block will fall 
           * Next Block will also be shown to help the user
         
--Future--:
           
           * A bomb will fall after random time, giving player some advantages
           * A complete Menu
           * Scoring : Live Score, High Scores
                    

-----------COMPILE AND RUN-----------

* GNU LINUX: 

               # Note you should have g++ compiler installed
            1. install sfml using : sudo apt install libsfml-dev
            2. g++ -c main.cpp
            3. g++ main.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
            4. ./tetris

-----------End------------
