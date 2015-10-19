# 2-players-reactor-on-ARM
2 players reactor is a game written in C. 

It runs on Freescale FRDM-KL46Z board, which contains an ARM microcontroller with some peripherals.
In order to compile it and download into the board I used Keil uVision5.
Before running this code on the board be sure You have the latest firmware installed on the board.

Principles of the game:

This is the game for two players, though You probably could play it alone :)
The build in timer counts down from 6 to 0, but You can't see the numbers changing from number 3 (it displays 9s instead). Using two buttons on the board (SW1 and SW3) the players compete with each other about who will press the button first, right after the count reaches 0. The faster one wins, and the result is shown on the LCD screen. But, when one of the players hits the button too early (when the count still didn't reach 0) the opponent wins.
