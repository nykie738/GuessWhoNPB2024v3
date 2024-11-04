# Installation
You will need to start with installing the C++ and G++ compilers on your system if you don't have them. <br>
Next, install SFML following the instructions on the SFML homepage. Installing the library through brew <br>
is recommended: <br>
```
brew install sfml
```

# Setup
As mentioned in the previous README.md, copy and paste the files found in this directory <br>
into the previous one. Also, find your path the the SFML include and lib by:
```
brew info sfml
```

# Run the program
To run the program, you will need to compile the codes by pasting <br>
the lines below into the terminal: <br>
```
g++ -std=c++17 GWBaseball2024.cpp Game.cpp Player.cpp PlayerManager.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
./main
```
If it does not work, declare the path to the SFML include and lib:
```
g++ -std=c++17 -I/pathtoinclude -L/pathtolib GWBaseball2024.cpp Game.cpp Player.cpp PlayerManager.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
./main
```
