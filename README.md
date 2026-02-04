# Space Dodger


//-------Space Dodger-------//

  Space Dodger is a simple 2D arcade-style game developed in C++ using the SFML (Simple and Fast Multimedia Library).
The player controls a spaceship and must dodge incoming enemies while earning points for survival.
This project was created as a learning experience to practice game loops, event handling, collision detection, and state management in SFML.

//-------Gameplay Overview-------//

The player controls a spaceship at the bottom of the screen.
Enemies fall from the top of the screen.
The goal is to avoid collisions and survive as long as possible.
Each enemy that successfully passes increases the score.
The game speed increases gradually over time.

//-------Game States-------//

The game consists of several states:

_Main Menu

Displays the game title “SPACE DODGER”
Press ENTER to start the game

_Countdown

Shows 3 → 2 → 1 → GO!
The player and background are visible during the countdown
The game starts immediately after GO!

_Gameplay

Player moves horizontally using the mouse
Enemies spawn at random positions from the top
Score is displayed at the top-left corner

_Game Over

Triggered when an enemy collides with the player
Displays:
GAME OVER
Final score
Instruction to return to menu
Press R to go back to the main menu

//-------Controls-------//

Action:                              Input:
1.Move spaceship                     1.Mouse (horizontal movement)
2.Start game                         2."ENTER" key on keyboard
3.Return to menu (Game Over)         3."R" key on keyboard
4.Close game                         4.Window close button

//-------Technical Features-------//

SFML RenderWindow for graphics rendering
Game loop with real-time input handling
Collision detection using "getGlobalBounds()"
Enemy spawning using "sf::Clock"
Dynamic difficulty (enemy speed increases over time)
Multiple game states:
1.Menu
2.Countdown
3.Gameplay
4.Game Over
5.Clean and organized code structure

//-------Visual Design-------//

Space-themed dark blue background
Scaled sprites for better proportions
Center-aligned text for menu and game over screen
Large countdown text for clarity

//-------Project Structure-------//

Space-Dodger/
│
├── main.cpp
├── player.png
├── enemy.png
├── bitwise.ttf
├── README.md
All resource files must be placed in the same directory as the executable!

//-------Requirements-------//

C++17 or higher
SFML 2.5+ (Graphics module)
Compiler: g++ / MinGW

//-------Authors-------//

Negin Soleimani

Parya Pirhajati

//-------Note-------//

This project was developed as a "first-semester university project" for the "Computer Engineering" program at "Allameh Tabataba'i University".


