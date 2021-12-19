import java.util.*;

public class Game
{   
    static Scanner input = new Scanner(System.in); //xrhsimopoioume thn klash Scanner gia na pernoume times apo ton xrhsth
    
    public static int[] getInput(int[] starting_point) //epistrefei pinaka 2 thesewn me tis times pou edwse o xrhsths
    {   
        starting_point[0] = input.nextInt();
        starting_point[1] = input.nextInt();
        
        while ((starting_point[0] > 6) || (starting_point[1] > 6))
        {
            System.out.println("Point out of bounds! Please give two numbers between 0 and 6");
            starting_point[0] = input.nextInt();
            starting_point[1] = input.nextInt();
        }
        
        return starting_point;
    }
    
    public static int[] getRandInput() //epistrefei pinaka me tyxaies times xrhsimopoiontas thn klash Random
    {
        Random random = new Random();
        int[] starting_point = new int[2];
        
        starting_point[0] = random.nextInt(7);
        starting_point[1] = random.nextInt(7);
        
        return starting_point;
    }
    
    public static char getOrientation(char o) //epistrefei ton prosanatolismo tou ploiou
    {
        System.out.print("Give orientation for the ship ('V for vertical or 'H' for horizontal): ");
        o = input.next().charAt(0);
        
        while ((o != 'V') && (o != 'H'))
        {
            System.out.print("Give proper orientation for the ship ('V for vertical or 'H' for horizontal): ");
            o = input.next().charAt(0);
        }
            
        return o;
    }
    
    public static boolean randomPlace(boolean answer) //epistrefei an o xrhsths thelei na topotheththoun tyxaia h oxi ta ploia tou
    {
        char a;
        
        a = input.next().charAt(0);
        
        while ((a != 'Y') && (a != 'N'))
        {
            System.out.print("Give proper answer ('Y' for yes or 'N' for no): ");
            a = input.next().charAt(0);
        }
        
        if (a == 'Y')
            answer = true;
        else if (a == 'N')
            answer = false;
            
        return answer;
    }
    
    public static void main(String[] args)
    {
        final int row = 7;
        final int col = 7;
        final int max_shots = 20; //megistos arithmos volwn
        //dhmiourgei ta antikeimena pou tha xreiastoun
        Tile[][] B_P = new Tile[row][col];
        Tile[][] B_C = new Tile[row][col];
        Board board_P = new Board(B_P);
        Board board_C = new Board(B_C);
        Carrier carrier = new Carrier();
        Battleship battleship = new Battleship();
        Cruiser cruiser = new Cruiser();
        Submarine submarine = new Submarine();
        Destroyer destroyer = new Destroyer();
        Player Player1 = new Player("Player1", false);
        Player CPU = new Player("CPU", true); 
        
        int[] starting_point = new int[2];
        int[] fire_point = new int[2];
        char orientation = ' ';
        boolean answer = false;
        //rwta an o xrhsths thelei na topotheththoun tyxaia h oxi ta ploia tou
        System.out.println("Do you want the ships to be placed randomly (press 'Y') or place them yourself (press 'N')?"); 
        
        if (randomPlace(answer) == true) //an h apanthsh einai thetikh tote kaleite h placeAllShips tou Board
            board_P.placeAllShips(B_P);
        else if (answer == false) //alliws me ena for kai ena switch topothetounte ta ploia me times tou xrhsth
        {   
            for (int i = 0; i < 5; i++)
            {
                switch (i)
                {
                    case 0: System.out.print("Give coordinates for the starting point of the carrier: "); //dinei arxiko shmeio kai prosanatolismo
                            starting_point = getInput(starting_point);
                            orientation = getOrientation(orientation);
                            carrier.placeShip(starting_point, orientation, B_P); //an i = 0 kaleite h placeShip tou carrier
                            break;
         
                    case 1: System.out.print("Give coordinates for the starting point of the battleship: "); //dinei arxiko shmeio kai prosanatolismo
                            starting_point = getInput(starting_point);
                            orientation = getOrientation(orientation);
                            battleship.placeShip(starting_point, orientation, B_P); //an i = 1 kaleite h placeShip tou battleship 
                            break;
                    
                    case 2: System.out.print("Give coordinates for the starting point of the cruiser: "); //dinei arxiko shmeio kai prosanatolismo
                            starting_point = getInput(starting_point);
                            orientation = getOrientation(orientation);
                            cruiser.placeShip(starting_point, orientation, B_P); //an i = 2 kaleite h placeShip tou cruiser
                            break;
                            
                    case 3: System.out.print("Give coordinates for the starting point of the submarine: "); //dinei arxiko shmeio kai prosanatolismo
                            starting_point = getInput(starting_point);
                            orientation = getOrientation(orientation);
                            submarine.placeShip(starting_point, orientation, B_P); //an i = 3 kaleite h placeShip tou submarine
                            break;
                            
                    case 4: System.out.print("Give coordinates for the starting point of the destroyer: "); //dinei arxiko shmeio kai prosanatolismo
                            starting_point = getInput(starting_point);
                            orientation = getOrientation(orientation);
                            destroyer.placeShip(starting_point, orientation, B_P); // an i = 4 kaleite h placeShip tou destroyer
                            break;
                }
            }
        }
         
        board_C.placeAllShips(B_C); //topothetei tyxaia ta ploia tou ypologisth
        
        do //oso den exei vythistoun ola ta ploia twn paiktwn h kapoios paikths den exei kseperasei to megisto orio volwn, ginonte voles
        {
            board_P.drawboards(B_P, B_C, Player1, CPU);
            System.out.println();
        
            System.out.print("Player 1 where do want to fire? "); //rwta ton paikth na dwsei syntetagmenes gia to pou tha pyrovolhsei
            fire_point = getInput(fire_point); //pairnei to shmeio pou dinei o paikths
            Player1.fire(B_C, fire_point); //pragmatopoiei thn volh
            fire_point = getRandInput(); //pernei tyxeio shmeio volhs gia ton ypologisth
            CPU.fire(B_P, fire_point); //pragmatopoiei thn volh tou ypologisth
        }
        while ((Player1.getTries() != max_shots) && (CPU.getTries() != max_shots) && (!board_P.allShipsSunk(B_P)) && (!board_C.allShipsSunk(B_C)));
        
        CPU.setHidden(false); //allazei ton pinaka tou ypologisth apo kryfo se emfanes

        if (board_P.allShipsSunk(B_P)) //an vythistikan ola ta ploio tou paikth emfanizei katallhlo mhnyma kai epishs ta statistika
        {
            System.out.println("Player1 you lost!");
            board_P.drawboards(B_P, B_C, Player1, CPU);
            System.out.println();
            Player1.getStats();
            CPU.getStats();
        }
        else if (board_C.allShipsSunk(B_C)) //an vythistikan ola ta ploio tou ypologisth emfanizei katallhlo mhnyma kai epishs ta statistika
        {
            System.out.println("Player1 you won!");
            board_P.drawboards(B_P, B_C, Player1, CPU);
            System.out.println();
            Player1.getStats();
            CPU.getStats();
        }
        else if (Player1.getTries() == max_shots) //an eftase sto orio volwn emfanizei katallhlo mhnyma kai epishs ta statistika
        {
            System.out.println("Player1 you run out of tries! You lost!");
            board_P.drawboards(B_P, B_C, Player1, CPU);
            System.out.println();
            Player1.getStats();
            CPU.getStats();
        }
    }
}