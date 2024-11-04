# Installation
Believe it or not, ubuntu environment is the one with the least issues amongst these 3 OS options. <br>
You will need to start with installing the C++ and G++ compilers on your system if you don't have them. <br>
Next, install SFML following the instructions on the SFML homepage. Otherwise, you can paste the lines below <br>
into the terminal: <br>
```
sudo apt-get install libsfml-dev
```

# Setup
As mentioned in the previous README.md, all you need to do is simply copy and paste the files found in this directory <br>
into the previous one. Yeah, it's literally just that!

# Run the program
There should be an executable in this directory. As long as it is in the same location as font file (misaki_gothic_2nd.ttf), <br>
player list (players.csv), and the img directory, the code should work as intended. If not, try compiling the codes by pasting <br>
the lines below into the terminal: <br>
```
g++ GWBaseball2024.cpp Game.cpp Player.cpp PlayerManager.cpp -o main.exe -lsfml-graphics -lsfml-window -lsfml-system
```
