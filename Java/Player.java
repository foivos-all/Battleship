import java.util.*;

public class Player
{
    private final int row = 7;
    private final int col = 7;
    private String name;
    private int shots, shots_hit, shots_missed, tries;
    private Tile[][] B = new Tile[row][col];
    private Board P = new Board(B);
    Scanner input = new Scanner(System.in);
    private boolean hidden;
    
    public Player(String n, boolean h) //o dhmiourgos arxikopoia to onoma tou paikth me to orisma kai an einai kryfos o pinakas tou
    {
        this.name = n;
        this.shots = 0; //epishs arxikopoia tis ypoloipes metavlhtes tis klaseis se 0
        this.shots_hit = 0; 
        this.shots_missed = 0; 
        this.tries = 0;
        this.hidden = h;
    }
    
    public Board placeAllShips() //kalei thn placeAllShips tou board
    {
        P.placeAllShips(B);
        
        return P;
    }
    
    public void placeShip(Ship ship, int sp[]) //xrhsimopoia thn placeShip me orisma apo thn afyrhmenh klash Ship
    {
        char o;
        System.out.println("Give orientation for ship (press 'V' for vertical or 'H' for horizontal)");
        o = input.next().charAt(0); 
        
        ship.placeShip(sp, o, B);
    }
    
    public void fire(Tile B[][], int fp[]) //h methodos auth anaparista thn volh twn kathe paiktwn
    {
        shots++; //auksanei tis katallhles metavlhtes
        tries++;
        if (B[fp[0]][fp[1]].getType() == Type.Ship) //an sto shmeio pou dwthike yparxei ploio, allazei ton typo tou se Hit
        {
            B[fp[0]][fp[1]].setType(Type.Hit);
            System.out.println("Player: " + name + " hits."); //vgazei mhnyma an ktyphse
            shots_hit++; //auksanei ton arithmo twn eustoxwn volwn
        }
        else //alliws, an astoxise, allazei ton typo tou ploiou se Miss
        {
            B[fp[0]][fp[1]].setType(Type.Miss);
            System.out.println("Player: " + name + " misses."); //emfanizei katallhlo mhnyma
            shots_missed++; //auksanei ton arithmo astoxwn volwn
        }
    }
    
    public void getStats() //typwnei ta statistika tou kathe paikth
    {
        System.out.println("Name: " + name + ".");
        System.out.println("Shots fired: " + shots + " times.");
        System.out.println("Shots hit: " + shots_hit + " times.");
        System.out.println("Shots missed: " + shots_missed + " times.");
        System.out.println("Tries: " + tries + " times.");
    }
    
    public int getTries() //epistrefei tis prospatheies
    {
        return tries;
    }
    
    public boolean getHidden() //epistrefei an o pinakas tou paikth einai kryfos h oxi
    {
        return hidden;
    }
    
    public void setHidden(boolean h) //allazei thn katastash tou pinaka, apo kryfo se mh-kryfo
    {
        this.hidden = h;
    }
}