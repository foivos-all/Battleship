<p align="center">
  <img src="images/battleship1.png" />
</p>

# Battleship
<p align="justify">
This repository holds the Java and C++ version of a Battleship game, created during the Object Oriented Programming course, completed during my first year of studies in the Computer Engineering and Informatics Department at the University of Patras. 
</p>

# Structure
<p align="justify">
In the Java folder, you can find the Java version of the game, which is as such:
<ul>
  <li><u>Tile:</u> This class represents each cell. It has an "enum" structure that determines the values that a cell can take ("Sea", "Ship", "Hit", "Miss"). The class also has the auxiliary methods:</li>
  <ul>
    <li><em>Tile (which is the constructor):</em> The constructor takes as arguments two integers that are the coordinates of the cell and its formula. It then assigns them to the variables of the class.</li>
    <li><em>setType:</em> It is a "setter" method that takes a formula as an argument and assigns it to the cell.</li>
    <li><em>getType:</em> It is a "getter" method that returns the cell type.</li>
    <li><em>draw:</em> This method takes as an argument a "boolean" variable which if it has the value "false" prints in the type of each cell (showing where the ships are) otherwise it simply prints the sea, the failures and the inaccuracies.</li>
  </ul>
  
  <li><u>Ship:</u> An abstract class from which the other types of ships will inherit. Represents the general type of each ship. From this class inherit the classes: "Carrier", "Battleship", "Cruiser", "Submarine" and "Destroyer" and has the following abstract methods:</li>
  <ul>
    <li><em>placeShip:</em> The method that is responsible for placing ships. It takes as arguments a two-position table which is the starting point of the ship, the orientation of the ship and the table on which it will place the ships.</li>
    <li><em>check_boundaries:</em> This method checks if the ship's placement goes out of bounds. It takes as arguments a two-position table which is the starting point of the ship and the orientation of the ship.</li>
    <li><em>check_placement:</em> Checks if there is already another ship where we are going to place a ship. As arguments he takes, a two-position table which is the starting point of the ship, the orientation of the ship and the table on which he will place the ships.</li>
    <li><em>check_orientation:</em> Checks if there is at least one empty cell between another ship. It takes as arguments a two-position table which is the starting point of the ship, the orientation of the ship and the table on which it will place the ships.</li>
    <li><em>my_check_boundaries:</em> It does the same job as check_boundaries, but returns "boolean" so that the ship details can be searched again.</li>
    <li><em>getType:</em> It is a "getter" method that returns the cell type.</li>
    <li><em>my_check_placement:</em> It does the same job as check_placement, but returns "boolean" so that the ship details can be searched again.</li>
    <li><em>my_check_orientation:</em> It does the same job as check_orientation, but returns "boolean" so that the ship details can be searched again.</li>
  </ul>
  
  <li><u>Carrier:</u> One of the classes that inherits from Ship. It has an integer variable "size = 5" which indicates the size of the ship. Finally, Ship implements the abstract methods.</li>
  
  <li><u>Battleship:</u> One of the classes that inherits from Ship. It has an integer variable "size = 4" which indicates the size of the ship. Finally, Ship implements the abstract methods.</li>
  
  <li><u>Cruiser:</u> One of the classes that inherits from Ship. It has an integer variable "size = 3" which indicates the size of the ship. Finally, Ship implements the abstract methods.</li>
  
  <li><u>Submarine:</u> One of the classes that inherits from Ship. It has an integer variable "size = 3" which indicates the size of the ship. Finally, Ship implements the abstract methods.</li>
  
  <li><u>Destroyer:</u> One of the classes that inherits from Ship. It has an integer variable "size = 2" which indicates the size of the ship. Finally, Ship implements the abstract methods.</li>

  <li><u>OversizeException:</u> A class that inherits from the Exception class and has the following methods:</li>
  <ul>
    <li><em>OversizeException (which is also the constructor):</em> Assigns a message to the variable of the "message" class.</li>
    <li><em>getMessage:</em> A getter method that returns the message of the class.</li>
  </ul>
  
  <li><u>OverlapTilesException:</u> A class that inherits from the Exception class and has the following methods:</li>
  <ul>
    <li><em>OverlapTilesException (which is also the constructor):</em> Assigns a message to the variable of the "message" class.</li>
    <li><em>getMessage:</em> A getter method that returns the message of the class.</li> 
  </ul>
  
  <li><u>AdjacentTilesException:</u> A class that inherits from the Exception class and has the following methods:</li>
  <ul>
    <li><em>AdjacentTilesException (which is also the constructor):</em> Assigns a message to the variable of the "message" class.</li>
    <li><em>getMessage:</em> A getter method that returns the message of the class.</li> 
  </ul>
  
  <li><u>Board:</u> The class that represents the 7x7 size table. There are two constants "row" and "col" which are the number of rows and columns. Finally, it has these methods:</li>
  <ul>
    <li><em>Board (which is also the constructor):</em> Takes as an argument a two-dimensional "Tile" table which it initializes using the creator of the "Tile" class.</li>
    <li><em>drawboards:</em> Takes as arguments two two-dimensional tables of type "Tile" and two objects of the class "Player". It then prints the two tables using the "Tile" method of the "Tile" class.</li>
    <li><em>getAdjacentTiles:</em> Takes as arguments a cell and the table and returns its neighbors.</li>
    <li><em>placeAllShips:</em> Argues a two-dimensional “Tile” type table and places the ships randomly by calling the “placeShip” method of each ship separately.</li> 
    <li><em>allShipsSunk:</em> Takes as an argument a two-dimensional "Tile" table and returns "boolean" and checks if all ships have sunk by returning "true" or "false".</li>
  </ul>
  
  <li><u>Player:</u> A class that represents each player. It has the following methods:</li>
  <ul>
    <li><em>Player (which is also the constructor):</em> Takes as arguments the alphanumeric which is the name of the player and a "boolean" which shows whether or not the table of the specific player is hidden.</li>
    <li><em>placeAllShips:</em> Gets no arguments and calls the "placeAllShips" of the "Board" class and then returns a "Board".</li>
    <li><em>placeShip:</em> A method that takes as an argument an object of the abstract class "Ship" and the starting point of the ship and calls the placeShip of the abstract class.</li>
    <li><em>fire:</em> This method implements the shot made by the players. Initially increases by one the variables of the class "shots" and "tries". Then, using the "getType" and "setType" methods of the "Tile" class, he performs the shot.</li> 
    <li><em>getStats:</em> Prints each player's statistics.</li>
    <li><em>getTries:</em> Returns the efforts of each player.</li>
    <li><em>getHidden:</em> Returns the boolean "hidden" variable of the class.</li>
    <li><em>setHidden:</em> Takes as an argument a Boolean variable and assigns it to the variable of class "hidden".</li>
  </ul>
  
  <li><u>Game:</u> Displays the main class which also contains the "main" method. It's essentially the class that starts the game. Contains the following methods:</li>
  <ul>
    <li><em>getInput:</em> A method that returns the starting point of ships or the position of the shot as an integer two-position table. Takes as an argument an integer two-position table and uses the "Scanner" class to get values from the user.</li>
    <li><em>getRandInput:</em> Returns an integer table of two positions and uses the "Random" class to give values from 0 to 6 as the starting point of the ship.</li>
    <li><em>getOrientation:</em> Returns a character that determines the orientation of the ship and takes a character as an argument. Uses the "Scanner" class to get values from the user.</li>
    <li><em>randomPlace:</em> A method that returns and takes as a variable a boolean variable. Asks the user if he wants the ships to be placed randomly or to place them himself. Uses the "Scanner" class to get a response from the user.</li> 
    <li><em>main:</em> The main method. Creates the objects of the game. Then it calls "randomPlace" and if it is "true" it calls the "placeAllShips" of the Board class. If the answer is "false", using the "switch" structure places the ships one by one, taking values from the user using the "getInput" and "getOrientation" methods and calling the "placeShip" of each ship. Then he randomly places the ships on the computer and the game begins, where using a "do-while" shots are fired at the points given by the player and randomly from the computer. The game ends when the shooting limit is exceeded (which is twenty) or if all of a player's ships have sunk. Finally, it displays an appropriate message, as the case may be, and prints the two tables.</li>
  </ul>
  </ul>

  and in the C++ folder you can find the corresponding version of the game, written in the C++ programming language.
</p>
