# FunGameWithC
This project is a simple Sokoban-inspired puzzle game written in C, where the player must push a box (B) onto a designated goal (x) to win. The game is played in the terminal and features:

  Classic Sokoban mechanics: Move the player (@) using W A S D controls to push the box to the target position.
  Interactive game board: Walls (#), player (@), box (B), and destination (x) are all part of the map.
  Background music: Enjoy the game with background music (using the Windows API and multithreading for asynchronous sound playback).
  Winning condition: The game is won when the box reaches the destination and is marked as O.

Features:
  Pure C implementation for the game logic.
  Terminal-based interface with simple instructions.
  Custom background music using the PlaySound function from the Windows API.
  Multi-threaded sound playing for a better experience.
  Simple game mechanics inspired by Sokoban puzzles.

How to Play:
  Use the following controls to move the player:
    w to move up
    s to move down
    a to move left
    d to move right
  Your goal is to push the box (B) onto the destination (x).
  Once the box is correctly placed, it becomes O, and you win!

Requirements:
  Windows (for sound playback).
  A C compiler (e.g., GCC or MSVC).
  The sound file (Luke-Bergs-Paradise-chosic.com_.wav) included in the project directory.

Feel free to try out the game and enjoy the music while solving this puzzle! 🎉
