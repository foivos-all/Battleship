public class AdjacentTilesException extends Exception //dixnei to mhnyma oti to ploio den mporei na topotheththei ekei dioti exei allo ploio dipla tou
{
    String message = " ";
    
    public AdjacentTilesException() //o dhmiourgos arxikopoia thn metavlhth klashs message
    {
        this.message = "Cannot put ship there! AdjacentTiles Exception";
    }
    
    public String getMessage() //getter methodos h opoia epistrefei to mhnyma
    {
        return message;
    }
}