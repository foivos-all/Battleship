public class OversizeException extends Exception //dixnei to mhnyma oti to ploio den mporei na topotheththei ekei dioti vgainei ektos oriwn
{
    String message = " ";
    
    public OversizeException() //o dhmiourgos arxikopoia thn metavlhth klashs message
    {
        this.message = "Cannot put ship there! Oversize Exception";
    }
    
    public String getMessage() //getter methodos h opoia epistrefei to mhnyma
    {
        return message;
    }
}