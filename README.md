# Multiplayer-ItemGrabbing-2D-Game
A 2D multiplayer game where 2 players race to grab the most items. It is built using c++. The graphics are made using SFML library and the multiplayer functionality is created by multiple threads using pthread library.

You need to use Ubuntu/Linux to run the project. You need to have the g++ compiler and sfml library installed.  
Open terminal and type the command:  
g++ -o g game.cpp -lpthread -lx11 -lsfml-graphics -lsfml-window -lsfml-window  
This will compile the code. To run the game type the command:  
./g  

The code for the game is in the game.cpp file. The other files are for image objects used in the game and the font used in the game.
