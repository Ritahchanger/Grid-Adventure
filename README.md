# Grid Warrior — Game Summary

## Overview  
Grid Warriore is a minimalist, text-based rogue-like game implemented in C++. The player navigates a grid-based dungeon, avoiding walls and engaging in strategic combat with multiple enemies. The game runs entirely in the terminal, leveraging low-level input handling for smooth real-time movement using both WASD and arrow keys.

## Key Features  
- **Dynamic Map Display:** Centrally aligned dungeon map rendered with clear symbols for player (`@`), enemies (`E`), walkable tiles (`.`), and walls (`#`).  
- **Smooth Input Handling:** Real-time movement support using both WASD keys and arrow keys through terminal raw mode input.  
- **Enemy AI:** Enemies actively pursue the player, moving intelligently while avoiding obstacles and other enemies.  
- **Combat System:** The player can attack adjacent enemies to defeat them, scoring points and progressing toward victory.  
- **Health & Damage:** Player health is tracked with feedback after attacks, and the game ends upon player death.  
- **Scoring & Win Condition:** Score accumulates by defeating enemies, and the game congratulates the player upon clearing all foes.  
- **Cross-Platform Compatibility:** Uses conditional compilation to support clearing the screen on Windows and Unix-like terminals.

## Technical Highlights  
- Utilizes Unix terminal APIs (`termios`, `read()`) for capturing input without requiring Enter key presses, enabling real-time gameplay.  
- Clean separation of concerns with distinct classes for the game map, player, and enemies.  
- Robust boundary and collision checking ensures valid movement and interactions.  
- Friendly user prompts and pause states after significant actions enhance playability.

## Purpose & Learning Outcomes  
This project demonstrates mastery over terminal I/O, low-level input handling, real-time game loops, and object-oriented design in C++. It also emphasizes user experience in CLI applications by centering text output and providing clear, concise game feedback.
