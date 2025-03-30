This is the last assignment of the Programming Language Concepts course. We did it with Arda Menşur. The description of the assignment is in the .pdf file.

Strategy games typically focus on players' decision-making abilities, often requiring internal decision tree-like thinking and a good sense of situational awareness. On the other hand, board games revolve around pieces or counters moved or positioned on a designated surface, or "board," following a predefined set of rules. While strategic skills are essential for most board games, there is room to incorporate chance elements into their gameplay. Notable examples of strategy board games include Risk, Game of Thrones: The Board Game, Puerto Rico, and Diplomacy.

In this assignment, you will write a program to play a simplified, custom board game called "Gold Rush Alaska". In this game, we will assume that two players (the computer will not play the game) are positioned on opposite ends of a valley. The valley is a square-shaped platform made of n x n elements.

Each element on the board may or may not have one type of hidden resource. The hidden elements can be one of the following:
• Food
• Wood
• Medical supplies
• Gold
• Wild animals (the number of wolves should be twice the number of bears)
The players will specify the size of the board for the game. However, the board should always be square, and the size of the board should be at least 5 x 5. For this game, the program should randomly hide 2⌊𝑛225⌋ pieces of each resource (Food, Wood, Medical, Gold) across the grid (you need to consider an integer division in the given formula). The total number of wolves will be 2⌊𝑛2 25⌋ as well, while the total number of bears is half of this. Please note that ⌊⌋ stands for the floor function. The game begins by generating a random number between 20 and n2, which indicates the total number of turns (i.e., player 1 and player 2 combined) to take. At each turn, the current state of the game board should be displayed, as well as the total score for each player. Unless specific cell is chosen its contents are unknown to players.
• At the beginning of each turn, the players should choose the [x] and [y] coordinates on the board
where the top-left coordinate is (0, 0).
• The rules for placing an item on the game board are as follows:
▪ Each player will have a health and score (the amount of Gold found).
▪ In the beginning, the health of each player will be 2n, so if the value of n is 5, then the health
of each player is 2*5=10.
▪ If a player dies, the other player can continue playing, looking for more Gold.
▪ In case there is a wild animal at a specific coordinate, a menu will appear in front of the player to choose an even or odd number. Then, one random number will be generated for the animal (This will be our dice effect). If the player can guess if the random number is even or odd, s/he will manage to escape. Otherwise, the player will receive damage as follows, and the health of the player will be decreased. If the health becomes 0, then the player will die.
  ▪ Damage from wolf ⌊𝑛/4⌋.
  ▪ Damage from bear ⌊𝑛/2⌋.
▪ If the opened resource is food, wood (for heating and resting), or medical supplies, the health of the player will be increased as follows:
  ▪ Medical supplies ⌊𝑛 4⌋
  ▪ Food ⌊𝑛/6⌋
  ▪ Wood ⌊𝑛/8⌋
▪ If the opened resource is Gold, the player's score will be increased 100 points, and there will be no change in the player's health.

The objective of the game is to gather as much Gold as possible. The winner is the player with the most resources in terms of points, i.e., the highest score.

On each grid, the resources will be placed randomly and automatically. The effect of the resource is valid independently for each cell. For example, if the cell chosen has a bear which occupies 3 cells, the player can try to guess which other cells are bears to avoid damage, since the other 2 cells will still have the active bear effect. Similarly, if the cell chosen is wood, the player can try to guess the other cell for the effect of the wood. Please note that each element can only be activated once. The locations and points of each resource can be given as follows:
Element | Size (number of cells occupied) | Character to use for representing it on the board | Effect
Food                     1                                          F                           Increase health ⌊𝑛/6⌋
Wood                     2                                          I                           Increase health ⌊𝑛/8⌋
Medical Supplies         1                                          S                           Increase health ⌊𝑛/4⌋
Wild animal (Wolf)       1                                          W                           Dice throw, damage ⌊𝑛/4⌋.
Wild animal (Bear)       3                                          B                           Dice throw, damage ⌊𝑛,72⌋.
Gold                     1                                          G                           Increase the score 100 points
Please note that if an element occupies more than one cell, they should all be adjacent cells. Element placement will be discussed in more detail in a later section. After the resources have been positioned, the game proceeds in a series of rounds. In each round, each player takes a turn to announce a target cell in the grid. The computer then announces the actions to be followed. The grid is then updated accordingly.
