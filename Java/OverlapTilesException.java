public class OverlapTilesException extends Exception //dixnei to mhnyma oti to ploio den mporei na topotheththei ekei dioti exei allo ploio
{
    String message = " ";
    
    public OverlapTilesException() //o dhmiourgos arxikopoia thn metavlhth klashs message
    {
        this.message = "Cannot put ship there! OverlapTiles Exception";
    }
    
    public String getMessage() //getter methodos h opoia epistrefei to mhnyma
    {
        return message;
    }
}