# Space Dodger

//-------Space Dodger-------//

Space Dodger is a simple 2D arcade-style game developed in C++ using the SFML (Simple and Fast Multimedia Library).  
The player controls a spaceship and must dodge incoming enemies while earning points for survival.  
Each round's score is recorded in a leaderboard file (`leaderboard.txt`) and the highest score is displayed in real-time.  
This project was created as a learning experience to practice game loops, event handling, collision detection, state management, and file handling in SFML.

//-------Gameplay Overview-------//

- The player controls a spaceship at the bottom of the screen.  
- Enemies fall from the top of the screen.  
- The goal is to avoid collisions and survive as long as possible.  
- Each enemy that successfully passes increases the score.  
- Game speed increases gradually over time.  
- Scores are saved per round and the leaderboard tracks all past rounds, showing the highest score achieved.

//-------Game States-------//

The game consists of several states:

_Main Menu_  
- Displays the game title “SPACE DODGER”  
- Shows instruction: Press ENTER to start  

_Countdown_  
- Displays 3 → 2 → 1 → GO!  
- The player and background are visible during the countdown  
- Gameplay starts immediately after "GO!"  

_Gameplay_  
- Player moves horizontally using the mouse  
- Enemies spawn at random positions from the top  
- Current score and highest score are displayed  

_Game Over_
- Triggered when an enemy collides with the player  
- Displays:  
  - GAME OVER  
  - Final score of the current round  
  - Instruction to return to menu  
  - Press R to go back to the main menu  
- The round score is automatically saved to `leaderboard.txt`  
- Leaderboard is updated and highest score is refreshed

//-------Controls-------//

| Action                          | Input                        |
|---------------------------------|------------------------------|
| Move spaceship                  | Mouse (horizontal movement) |
| Start game                       | "ENTER" key                    |
| Return to menu (Game Over)       | "R" key                        |
| Close game                       | Window close button          |

//-------Technical Features-------//

- SFML RenderWindow for graphics rendering  
- Game loop with real-time input handling  
- Collision detection using `getGlobalBounds()`  
- Enemy spawning using `sf::Clock`
- Dynamic difficulty (enemy speed increases over time)  
- Round-based scoring system with file-based leaderboard  
- Multiple game states: Menu, Countdown, Gameplay, Game Over  
- Clean and organized code structure

//-------Visual Design-------//

- Space-themed dark blue background  
- Scaled sprites for better proportions  
- Center-aligned text for menu and game over screens  
- Large countdown text for clarity  
- Highlighted high score in yellow

//-------Project Structure-------//

Space-Dodger/  
│  
├── main.cpp  
├── player.png  
├── enemy.png  
├── bitwise.ttf  
├── leaderboard.txt (auto-generated if not present)  
├── README.md  

_All resource files must be placed in the same directory as the executable!_

//-------Requirements-------//

- C++17 or higher  
- SFML 2.5+ (Graphics module)  
- Compiler: g++ / MinGW

//-------Authors-------//

- Negin Soleimani  
- Parya Pirhajati

//-------Note-------//

**This project was developed as a "first-semester university project" for the "Computer Engineering" program at "Allameh Tabataba'i University".**
