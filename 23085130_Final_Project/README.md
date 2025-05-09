
 Snake Game in C++ (Console-Based)

Welcome to the classic Snake Game built in **C++**, using Windows console features like cursor manipulation and color!

 Features

-   Classic snake movement
-   star collecting & tail growth
-   Enemies introduced with level progression
-  three  lives
-   Wall wrapping logic
-  interface using \windows.h\
-  Score saving to a file (\score.txt\)

---

 Requirements

This game is designed for **Windows OS** only.

- A C++ compiler (e.g., \g++\ from MinGW)
- Windows Command Prompt or compatible terminal
- Header files:
  - \<windows.h>\
  - \<conio.h>\

---

How to Compile and Run

### Using g++ (MinGW on Windows):
\\\ash
g++ SnakeGame.cpp -o SnakeGame
./SnakeGame
\\\

>  Make sure your terminal supports Windows-specific headers.

---

 Controls

| Key | Action       |
|-----|--------------|
| W   | Move Up      |
| A   | Move Left    |
| S   | Move Down    |
| D   | Move Right   |
| X   | Exit Game    |

---

 Files

- \SnakeGame.cpp\ — Main game code
- \score.txt\ — Stores past scores

---

 Future Improvements (Ideas)

- Enemy AI movement
- High score leaderboard
- Cross-platform compatibility (remove \<windows.h>\ and \<conio.h>\)
- Sound effects using \Beep()\

---
Author

Made  by: Crishtina KC   
