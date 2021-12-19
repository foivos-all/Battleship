import java.util.Random; //xrhsimopoioume thn klash random gia na dinoume tyxaies times

public class Board
{
    private final int row = 7; //arithmos grammwn pinaka
    private final int col = 7; //arithmos sthlwn pinaka
    Tile[][] B = new Tile[row][col]; //o pinakas einai ousiastika enas disdiastatos pinakas 7x7 typou Tile
    Tile c;
    private String message = " ";
    OversizeException oe = new OversizeException();
    OverlapTilesException ote = new OverlapTilesException();
    AdjacentTilesException ate = new AdjacentTilesException(); 
    
    public Board(Tile B[][]) //o dhmiourgos arxikopoia to kathe keli se Sea
    {
        for (int R = 0; R < row; R++)
            for (int C = 0; C < col; C++)
                B[R][C] = new Tile(R, C, Type.Sea);
    }
    
    public void drawboards(Tile P[][], Tile U[][], Player p, Player c) //emfanizei tous pinakes twn 2 paixtwn xrhsimopoiontas thn draw ths Tile
    {
        System.out.println("      - - Y O U - -        - O P P O N E N T -");
        System.out.println("   0  1  2  3  4  5  6     0  1  2  3  4  5  6");
        for (int R = 0; R < row; R++)
        {
            System.out.print(" " + R);
            for (int C = 0; C < col; C++)
                P[R][C].draw(p.getHidden());
                
            System.out.print("   ");
            
            for (int C = 0; C < col; C++)
                U[R][C].draw(c.getHidden());
                
            System.out.println();
        }
    }
    
    public Tile getAdjacentTiles(Tile c)
    {
        return c;
    }
   
    public void placeAllShips(Tile B[][]) //topothetei ta ploia tyxaia
    {
        //prwta dhmiourga ena ploio apo kathe eidos
        Carrier carrier = new Carrier();
        Battleship battleship = new Battleship();
        Cruiser cruiser = new Cruiser();
        Submarine submarine = new Submarine();
        Destroyer destroyer = new Destroyer();
        int[] sp = new int[2]; //arxiko shmeio
        char o; //prosanatolismos
        Random r = new Random();
        String options = "VH"; //to xrhsimopoioume gia na dwsoume tyxaio prosanatolismo
        
        for (int R = 0; R < 5; R++) //me ena for kai ena switch topothetounte tyxaia ta ploia
            switch (R)
            {
                case 0: //an i = 0 topotheteite to carrier
                    o = options.charAt(r.nextInt(2)); //dinei tyxaia ton prosanatolismo
                    
                    sp[0] = r.nextInt(7); //tyxaia arxikh grammh, piernietai apo kapoious elegxous
                    if ((sp[0] == 3) || (sp[0] == 4) || (sp[0] == 5) || (sp[0] == 6))
                        o = 'H';
                        
                    sp[1] = r.nextInt(7); //tyxaia arxikh sthlh, piernietai apo kapoious elegxous
                    if ((sp[1] == 3) || (sp[1] == 4) || (sp[1] == 5) || sp[1] == 6)
                        o = 'V';
                    //mexri na ikanopoihthoun oi elegxoi ksanapernei tyxaies times
                    while ((carrier.my_check_boundaries(sp, o)) || (carrier.my_check_placement(sp, o, B)) || (carrier.my_check_orientation(sp, o, B)))
                    {
                        o = options.charAt(r.nextInt(2));
                    
                        sp[0] = r.nextInt(7);
                        if ((sp[0] == 3) || (sp[0] == 4) || (sp[0] == 5) || (sp[0] == 6))
                            o = 'H';
                        
                        sp[1] = r.nextInt(7);
                        if ((sp[1] == 3) || (sp[1] == 4) || (sp[1] == 5) || sp[1] == 6)
                            o = 'V';
                    }
                    try
                    {
                        carrier.check_boundaries(sp ,o);
                        carrier.check_placement(sp, o, B);
                        carrier.check_orientation(sp, o, B);
                        carrier.placeShip(sp, o, B); //an einai ola entaksei kalei thn placeShip tou ploiou
                    }
                    catch(OversizeException oe)
                    {System.out.println(oe.getMessage());}
                    catch(OverlapTilesException ote)
                    {System.out.println(ote.getMessage());}
                    catch (AdjacentTilesException ate)
                    {System.out.println(ate.getMessage());}
                        
                    break;
                case 1: //an i = 1 topotheteite to battleship, isxyoun ta idia me to parapanw me kapoies mikroparalages
                        o = options.charAt(r.nextInt(2));
                        
                        sp[0] = r.nextInt(7);
                        if ((sp[0] == 4) || (sp[0] == 5) || (sp[0] == 6))
                            o = 'H';
                            
                        sp[1] = r.nextInt(7);
                        if ((sp[1] == 4) || (sp[1] == 5) || (sp[1] == 6))
                            o = 'V';  
                        while ((battleship.my_check_boundaries(sp, o)) || (battleship.my_check_placement(sp, o, B)) || (battleship.my_check_orientation(sp, o, B)))
                        {
                            o = options.charAt(r.nextInt(2));
                        
                            sp[0] = r.nextInt(6);
                            if ((sp[0] == 4) || (sp[0] == 5) || (sp[0] == 6))
                                o = 'H';
                            
                            sp[1] = r.nextInt(7);
                            if ((sp[1] == 4) || (sp[1] == 5) || (sp[1] == 6))
                                o = 'V'; 
                        }
                        try
                        {
                            battleship.check_boundaries(sp ,o);
                            battleship.check_placement(sp, o, B);
                            battleship.check_orientation(sp, o, B);
                            battleship.placeShip(sp, o, B);
                        }
                        catch(OversizeException oe)
                        {System.out.println(oe.getMessage());}
                        catch(OverlapTilesException ote)
                        {System.out.println(ote.getMessage());}
                        catch (AdjacentTilesException ate)
                        {System.out.println(ate.getMessage());}
                                              
                    break;
                case 2: //an i = 2 topotheteite to cruiser, isxyoun ta idia me to parapanw me kapoies mikroparalages
                    o = options.charAt(r.nextInt(2));
                    
                    sp[0] = r.nextInt(7);
                    if ((sp[0] == 5) || (sp[0] == 6))
                        o = 'H';
                        
                    sp[1] = r.nextInt(7);
                    if ((sp[1] == 5) || (sp[1] == 6))
                        o = 'V';
                    while ((cruiser.my_check_boundaries(sp, o)) || (cruiser.my_check_placement(sp, o, B)) || (cruiser.my_check_orientation(sp, o, B)))
                    {
                        o = options.charAt(r.nextInt(2));
                    
                        sp[0] = r.nextInt(7);
                        if ((sp[0] == 5) || (sp[0] == 6))
                            o = 'H';
                        
                        sp[1] = r.nextInt(7);
                        if ((sp[1] == 5) || (sp[1] == 6))
                            o = 'V';
                    }
                    try
                    {
                        cruiser.check_boundaries(sp ,o);
                        cruiser.check_placement(sp, o, B);
                        cruiser.check_orientation(sp, o, B);
                        cruiser.placeShip(sp, o, B);
                    }
                    catch(OversizeException oe)
                    {System.out.println(oe.getMessage());}
                    catch(OverlapTilesException ote)
                    {System.out.println(ote.getMessage());}
                    catch (AdjacentTilesException ate)
                    {System.out.println(ate.getMessage());}
                        

                    break;
                case 3: //an i = 3 topotheteite to submarine, isxyoun ta idia me to parapanw me kapoies mikroparalages
                    o = options.charAt(r.nextInt(2));
                    
                    sp[0] = r.nextInt(7);
                    if ((sp[0] == 5) || (sp[0] == 6))
                        o = 'H';
                        
                    sp[1] = r.nextInt(7);
                    if ((sp[1] == 5) || (sp[1] == 6))
                        o = 'V';
                    while ((submarine.my_check_boundaries(sp, o)) || (submarine.my_check_placement(sp, o, B)) || (submarine.my_check_orientation(sp, o, B)))
                    {
                        o = options.charAt(r.nextInt(2));
                    
                        sp[0] = r.nextInt(7);
                        if ((sp[0] == 5) || (sp[0] == 6))
                            o = 'H';
                        
                        sp[1] = r.nextInt(7);
                        if ((sp[1] == 5) || (sp[1] == 6))
                            o = 'V';
                    }
                    try
                    {
                        submarine.check_boundaries(sp ,o);
                        submarine.check_placement(sp, o, B);
                        submarine.check_orientation(sp, o, B);
                        submarine.placeShip(sp, o, B);
                    }
                    catch(OversizeException oe)
                    {System.out.println(oe.getMessage());}
                    catch(OverlapTilesException ote)
                    {System.out.println(ote.getMessage());}
                    catch (AdjacentTilesException ate)
                    {System.out.println(ate.getMessage());}

                    break;
                case 4: //an i = 4 topotheteite to destroyer, isxyoun ta idia me to parapanw me kapoies mikroparalages
                    o = options.charAt(r.nextInt(2));
                    
                    sp[0] = r.nextInt(7);
                    if (sp[0] == 6)
                        o = 'H';
                        
                    sp[1] = r.nextInt(7);
                    if (sp[1] == 6)
                        o = 'V';
                    while ((destroyer.my_check_boundaries(sp, o)) || (destroyer.my_check_placement(sp, o, B)) || (destroyer.my_check_orientation(sp, o, B)))
                    {
                        o = options.charAt(r.nextInt(2));
                    
                        sp[0] = r.nextInt(7);
                        if (sp[0] == 6)
                            o = 'H';
                        
                        sp[1] = r.nextInt(7);
                        if (sp[1] == 6)
                            o = 'V';
                    }
                    try
                    {
                        destroyer.check_boundaries(sp ,o);
                        destroyer.check_placement(sp, o, B);
                        destroyer.check_orientation(sp, o, B);
                        destroyer.placeShip(sp, o, B);
                    }
                    catch(OversizeException oe)
                    {System.out.println(oe.getMessage());}
                    catch(OverlapTilesException ote)
                    {System.out.println(ote.getMessage());}
                    catch (AdjacentTilesException ate)
                    {System.out.println(ate.getMessage());}

                    break;
            }
    }
    
    public boolean allShipsSunk(Tile B[][]) //elegxei an yparxei akoma kapoio ploio ston pinaka, epistefei analogo boolean
    {
        boolean sunk = true;
        
        for (int R = 0; R < row; R++)
            for (int C = 0; C < col; C++)
                if (B[R][C].getType() == Type.Ship)
                {
                    sunk = false;
                    break;
                }
        
        return sunk;
    }
}