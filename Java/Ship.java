public abstract class Ship
{   
    abstract public void placeShip(int sp[], char o, Tile B[][]); //h methodos pou einai ypefthini gia thn topothethsh twn ploiwn
    abstract public void check_boundaries(int sp[], char o) throws OversizeException; //elegxei ta oria
    abstract public void check_placement(int sp[], char o, Tile B[][]) throws OverlapTilesException; //elegxei an yparxei ploio ekei
    abstract public void check_orientation(int sp[], char o, Tile B[][]) throws AdjacentTilesException; //elegxei an yparxei ploio dipla
    abstract public boolean my_check_boundaries(int sp[], char o); //elegxei ta oria, epistrefei boolean
    abstract public boolean my_check_placement(int sp[], char o, Tile B[][]); //elegxei an yparxei ploio ekei, epistrefei boolean
    abstract public boolean my_check_orientation(int sp[], char o, Tile B[][]); //elegxei an yparxei ploio dipla, epistrefei boolean
}   