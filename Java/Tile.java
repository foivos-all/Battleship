enum Type //typos o opoios mporei na parei tis akolouthes times
{
    Sea, Ship, Hit, Miss
}

public class Tile //h klash tile anaparista to kathe keli
{   
    private Type cell; //o typos tou keliou
    private int X, Y; //oi syntetagmenes tou
    
    public Tile(int X, int Y, Type c) //o dhmiourgos arxikopoia tis times tou keliou me ta orismata pou pernei
    {
        this.X = X;
        this.Y = Y;
        this.cell = c;
    }
    
    public void setType(Type c) //setter h opoia thetei ton typo
    {
        this.cell = c;
    }
    
    public Type getType() //getter h opoia epistrefei ton typo
    {
        return cell;
    }
    
    public void draw(boolean hidden) //analoga me ton typo tou keliou emfanizei analogo xarakthra
    {
        if (hidden == false) //an den einai kryfos deixnei ta panta    
            switch (this.getType())
            {
                case Sea:
                    System.out.print(" ~ ");
                    break;
                
                case Ship:
                    System.out.print(" s ");
                    break;
                
                case Hit:
                    System.out.print(" X ");
                    break;
                
                case Miss:
                    System.out.print(" o ");
                    break;
            }
        else //alliws emfanizei ola ektos ta ploia
        {
            switch (this.getType())
            {
                case Hit:
                    System.out.print(" X ");
                    break;
                case Miss:
                    System.out.print(" o ");
                    break;
                default: 
                    System.out.print(" ~ ");
                    break;
            }
        }
    }
}