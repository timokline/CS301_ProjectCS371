CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Using the Game
 * Design Decisions


INTRODUCTION
------------
Timothy Kline and Andrew Kozak

We created a game using c++ and implimented assembly to calculate type advantages, the game
is a dungeon delving/turnbased style game where you pick up weapons and fight enemies as you
proceed deeper down the dungeon.

USING THE GAME
-------------
Once you download and run the Game.exe file you are met with 3 adjacent rooms, simply enter a 
number to move to one of the rooms. You will then be presented with a chest which you can open 
with "yes" or "no". Or an enemy which is when combat starts, simply enter the number which 
corrisponds with a choice to make a decision for you action, the enemy will then attack, this
will go back and forth untill  one of you reaches 0 hp.  Then the game will prompt you to use 
a potion which you can use to heal you.

DESIGN DECISIONS
----------------

 During combat there is a type advantage and disadvantage, the three elements are fire, water,
 and moss/wood. Fire deals 2x damage to moss and 0.5x damage to water. Water deals 2x damage 
 to fire and 0.5x to moss. And moss deals 2x to water but 0.5x to fire. This is calculated in
 assembly by assigning each type with a bit signature, fire = 0b0001, water = 0b0010,
 moss = 0b0100 for mosters and fire = 0b0100, water = 0b0001, moss = 0b0010 for weapons , 
 and then are compared with an & funtion to register effectiveness.  