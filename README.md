# SFML Games
[SFML](https://www.sfml-dev.org/) provides a simple interface to the various components of your PC, to ease the development of games and multimedia applications. It is composed of five modules: system, window, graphics, audio and network. 
for installing SFML on ubuntu , enter the following in the terminal:

```
sudo apt-get install libsfml-dev
```
and for running the code enter the followings:
```
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```

for more tutorials refer to [SFML Tutorials](https://www.sfml-dev.org/tutorials/2.5/).

## AA 
AA Game is a simple accuracy game in which you must place several needles on the circle without touching any other bits. The speed of bits is increasing as you progress through the levels. 

For shooting the bits you should press the up key in keyboard

![aa](http://i63.tinypic.com/mjvokg.png)


## Rifle 
Rifle game is a simple accuracy game in which you must shoot a bullet to a first target then it reflects and it should hit a second moving target. number of bullets is limited.

For changing the direction of the rifle you should press the up or down key in your keyboard and for changing the position of the target you should press the left and right keys. For shooting the bullets you press the left click.

![rifle](http://i67.tinypic.com/2v91zz8.png)

## Space Invader
Space Invader is a shooting game and you should destroy all of the alien spaceships in order to win the game and for shooting you should press the up key in keyboard.

![space](http://i67.tinypic.com/23m7bc5.png)
