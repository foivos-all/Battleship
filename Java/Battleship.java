public class Battleship extends Ship
{
    private int[] starting_point =  new int[2]; //pinakas 2 thesewn pou anaparista to arxiko shmeio
    private int size = 4; //megethos ploiou
    private char orientation; //prosanatolismos ploiou
    private String message = " ";
    OversizeException oe = new OversizeException();
    OverlapTilesException ote = new OverlapTilesException();
    AdjacentTilesException ate = new AdjacentTilesException(); 
        
    public void placeShip(int sp[], char o, Tile B[][]) //topothetish ploiou
    {
        int R, C;

        try
        {
            this.check_boundaries(sp ,o); //elegxei ta oria
            this.check_placement(sp, o, B); //elegxei an yparxei hdh topothethmeno ploio
            this.check_orientation(sp, o, B); //elegxei an yparxei dipla ploio
            
            if (o == 'V') //allazei ton typo twn keliwn autwn apo Sea se Ship
            {
                for (R = sp[0]; R < size+sp[0]; R++)
                    B[R][sp[1]].setType(Type.Ship);
                }
            else if (o == 'H')
            {
                for (C = sp[1]; C < size+sp[1]; C++)
                    B[sp[0]][C].setType(Type.Ship);
            }
        }
        catch(OversizeException oe)
        {System.out.println(oe.getMessage());}
        catch(OverlapTilesException ote)
        {System.out.println(ote.getMessage());}
        catch (AdjacentTilesException ate)
        {System.out.println(ate.getMessage());}
    }
    public void check_boundaries(int sp[], char o) throws OversizeException //elegxei ta oria
    {
        try
        {
            if (o == 'V')
                if (sp[0]+size > 6)
                    throw oe;
            else if (o == 'H')
                if (sp[1]+size > 6)
                    throw oe;
        }
        catch(OversizeException oe)
        {System.out.println(oe.getMessage());}
    }
    public void check_placement(int sp[], char o, Tile B[][]) throws OverlapTilesException //elegxei an yparxei ploio ekei
    {
        try
        {
            if (o == 'V')
                for (int R = sp[0]; R < size+sp[0]; R++)
                    if (B[R][sp[1]].getType() == Type.Ship)
                        throw ote;
            else if (o == 'H')
                for (int C = sp[1]; C < size+sp[1]; C++)
                    if (B[sp[0]][C].getType() == Type.Ship)
                        throw ote;
        }
        catch(OverlapTilesException ote)
        {System.out.println(ote.getMessage());}
    }
    public void check_orientation(int sp[], char o, Tile B[][]) throws AdjacentTilesException //elegxei an yparxei ploio dipla
    {
        try
        {
            if ((o == 'V') && (sp[1] != 6))
                for (int R = sp[0]; R < size+sp[0]; R++)
                    if (B[R][sp[1]+1].getType() == Type.Ship)
                        throw ate;
            else if ((o == 'V') && (sp[1] != 0))
                for (R = sp[0]; R < size+sp[0]; R++)
                    if (B[R][sp[1]-1].getType() == Type.Ship)
                        throw ate;
            else if ((o == 'H') && (sp[0] != 6))
                for (int C = sp[1]; C < size+sp[1]; C++)
                    if (B[sp[0]+1][C].getType() == Type.Ship)
                        throw ate;
            else if ((o == 'H') && (sp[0] != 0))
                for (C = sp[1]; C < size+sp[1]; C++)
                    if (B[sp[0]-1][C].getType() == Type.Ship)
                        throw ate;
        }
        catch (AdjacentTilesException ate)
        {System.out.println(ate.getMessage());}
    }
    
    public boolean my_check_boundaries(int sp[], char o) //elegxei ta oria, epistrefei boolean
    {
        boolean result = false;
        
        if (o == 'V')
            if (sp[0]+size > 6)
                result = true;
        else if (o == 'H')
            if (sp[1]+size > 6)
                result = true;
        
        return result;
    }
    
    public boolean my_check_placement(int sp[], char o, Tile B[][]) //elegxei an yparxei ploio ekei, epistrefei boolean
    {
        boolean result = false;
        
        if (o == 'V')
            for (int R = sp[0]; R < size+sp[0]; R++)
                if (B[R][sp[1]].getType() == Type.Ship)
                    result = true;
        else if (o == 'H')
             for (int C = sp[1]; C < size+sp[1]; C++)
                 if (B[sp[0]][C].getType() == Type.Ship)
                    result = true;
        
        return result;
    }
    
    public boolean my_check_orientation(int sp[], char o, Tile B[][]) //elegxei an yparxei ploio dipla, epistrefei boolean
    {
        boolean result = false;
        
        if ((o == 'V') && (sp[1] != 6))
            for (int R = sp[0]; R < size+sp[0]; R++)
                if (B[R][sp[1]+1].getType() == Type.Ship)
                    result = true;
        else if ((o == 'V') && (sp[1] != 0))
            for (R = sp[0]; R < size+sp[0]; R++)
                if (B[R][sp[1]-1].getType() == Type.Ship)
                    result = true;
        else if ((o == 'H') && (sp[0] != 6))
            for (int C = sp[1]; C < size+sp[1]; C++)
                if (B[sp[0]+1][C].getType() == Type.Ship)
                    result = true;
        else if ((o == 'H') && (sp[0] != 0))
            for (C = sp[1]; C < size+sp[1]; C++)
                if (B[sp[0]-1][C].getType() == Type.Ship)
                    result = true;
                    
        return result;
    }
}