# Team C-- | Twixt With a Twist!

## General Information

C--'s modern C++ project - UniTBv - Informatică Aplicată - Anul II 2023-2024

Team members:

Ivana Florin-Andrei - @florin-irl - <b>Front-End</b><br>
Mițoi Alex-Gabriel - @m1toi - <b>Tests</b><br>
Ploșniță Gabriel Valentin - @gabi-plosnita - <b>Back-End</b><br>
Măndoiu Vlad-Ștefan - @Vlazzzz - <b>Front-End</b><br>

This project has been made for the Modern Elements of C++ course taken at UniTBv and has been completed in under 10 weeks.

![game_screenshot](https://github.com/florin-irl/C--/assets/147153949/3ee5565d-0bc9-44ca-a24f-977bd4c11d10)


---------------------------------------------------------
## About Twixt

"Twixt With a Twist!" is a 2 player game where the main objective is to connect your base ( the north most row if RED / the west most column if BLACK ) to 
your other base ( the south most row if RED / the east most column if BLACK ) using a series of pegs and bridges between those pegs that are color coded to 
your specific player color. 

Every turn, a player can do the following: he <i>MUST</i> place <i>a single peg</i> of his color on the board, but can create and delete as many of his own bridges between two pegs of his color as he wants ( he can even choose to not place or delete any bridges, and simply switch turns after he placed his peg ). 

RED goes first! After RED finished his first moves and presses the <b>SWITCH TURN</b> button, the BLACK player is then prompted by a pop-up window asking him if he would like to switch places with the RED player.
If so, player 1 become BLACK and player 2 becomes RED. <b>This happens only once, after the first SWITCH TURN!</b> If the BLACK player chooses <b>No</b> on the prompt, game goes on with player 1 remaining RED
and player 2 remaining as BLACK.

![switchTurnPrompt](https://github.com/florin-irl/C--/assets/147153949/7ea7ff5f-4e6c-4342-9600-1e12808cf0fb)

If both players have no pegs left and none of them managed to connect their respective bases, the game ends in a <b>DRAW!</b>

Each player must carefully plan their next move and out-think his opponent, cutting their bridges off and planning ahead in order to connect their base from one side of the board to the other and attain victory!

---------------------------------------------------------
## Game Controls

```LEFT CLICK``` - place a peg of your color on the board

![gif1leftmousebutton](https://github.com/florin-irl/C--/assets/147153949/ac9eece2-1f02-4f8a-892d-e743a88efe45)


```RIGHT CLICK``` - used to select pegs of the same color and:
create bridges between them if one doesn't already exist  

![gif2rightclickmakebridge](https://github.com/florin-irl/C--/assets/147153949/dc4623f7-b556-47d1-9cea-c2e7d3c2a9bd)

OR used to select pegs of the same color and delete the bridge between them if a bridge exists 

![gif3rightclickdeletebridge](https://github.com/florin-irl/C--/assets/147153949/a5746cc0-7f1e-4e69-ae42-f00c3fc61958)

---------------------------------------------------------
## About the Side Panel

### Game Status Panel

Displays semnificative information about the game
+ Current Game Status - PLAYING / WON BY RED! / WON BY BLACK! / DRAW!
+ Current player turn
+ Colors coresponding to each player

![gif3GameStatus](https://github.com/florin-irl/C--/assets/147153949/c32c371c-4c04-4e9c-9f3f-399f1350849c)

### Piece Counter Panel

Displays the number of pegs and bridges left for each player, auto-updates after every semnificative move ( placing of a peg, placing of a bridge)

![PiecesCounter](https://github.com/florin-irl/C--/assets/147153949/68f26552-daca-4650-a179-e3a3662b7595)

### Button Section

![buttonsPanel](https://github.com/florin-irl/C--/assets/147153949/011033c7-223e-41ba-a209-fd0f7c6b6099)

```SWITCH TURN``` - switches turn ( obviously )

```RESTART``` - cleans the board of pegs and bridges, resets the piece counter for each player

![gif4restart](https://github.com/florin-irl/C--/assets/147153949/1f9f9372-cee8-4361-936f-fd3f1c2bd5a5)

```SAVE GAME``` - save the current configuration of the game, number of pieces left for both players, status of the game, basically all the information required for loading the game back to the moment that the save has been commenced 

```LOAD GAME``` - loads up the game from the save file

![gif5load](https://github.com/florin-irl/C--/assets/147153949/e76f0c43-f780-4aad-bcae-a5f84d68647a)

### Game SetUp Panel

![game_setup_panel](https://github.com/florin-irl/C--/assets/147153949/1db8cd15-8b5a-4788-b038-b3ebae19d30d)

Allows the players to customize their game experience by configuring the board size and number of pegs and bridges given to each player, with some limitations:
+ Board Size must be between 5 and 24
+ Number of Pegs must be at least 3
+ Number of Bridges must be at least 2


![gif6set_up](https://github.com/florin-irl/C--/assets/147153949/d5d769f4-760e-4b92-825f-1c3c1fc7c22c)

### Message Panel

The Message Panel is located in the bottom right of the screen and displays different warnings and tips for the players

![message_displayer](https://github.com/florin-irl/C--/assets/147153949/840bb7a2-fd76-4337-897a-a520f365bf0d)






