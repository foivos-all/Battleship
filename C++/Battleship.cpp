#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>

using namespace std;

const int row = 5;
const int col = 5;

class Tile //h klash tile anaparista kathe keli
{
	public:
		enum Type // typos o opoios mporei an parei tis akolouthes times
		{
			Sea, Ship, Hit, Miss	
		};
		Tile() {}
		Tile (int X, int Y, Type c) // o dhmiourgos o opoios arxikopoia tis metavlhtes ths klashs me ta orismata
		{
			this->X = X;
			this->Y = Y;
			this->cell = cell;
		}
		void setType(Type c) //pernei ton tipo tou poloiou kai ton anathetei sto cell
		{
			this->cell = c;
		}
		Type getType() //epistrefei ton tipo tou ploiou
		{
			return cell;
		}
		void draw(bool hidden) //analoga me ton tipo tou keliou tiponei analogo xaraktira
		{
			if (hidden == false)
				switch (this->getType())
				{
					case Tile::Sea:
						cout<<" ~ ";
						break;
					
					case Tile::Ship:
						cout<<" s ";
						break;
					
					case Tile::Hit:
						cout<<" X ";
						break;
					
					case Tile::Miss:
						cout<<" o ";
						break;
					default:
						cout<<" ~ ";
						break;	
				}
			else //allios tiponi ola extos ta ploia
				switch (this->getType())
				{
					case Tile::Hit:
						cout<<" X ";
						break;
						
					case Tile::Miss:
						cout<<" o ";
						break;
						
					default:
						cout<<" ~ ";
						break;
				}
		}
	private:
		Type cell;
		int X,Y;
};

class OversizeException : public exception //ekseresi an erthei extos orion epistrefei analogo minima
{
	private:	
		string message;
	
	public:
	    OversizeException()
	    {
	    	 message = " Cannot put ship there! Oversize Exception";
		}
		virtual ~OversizeException() throw() {}
		const string what()
		{
			return message;
		}
};

class OverlapTilesException : public exception //ekseresi opou epistrefei analogo minima an exei idi ploio ekei
{
	string message;
	
	public:
	    OverlapTilesException()
	    {
	    	 message = " Cannot put ship there! OverlapTiles Exception";
		}
		virtual ~OverlapTilesException() throw() {}
		const string what()
		{
			return message;
		}
};

class AdjacentTilesException : public exception//ekseresi opou epistrefei analogo minima an exei ploio dipla tou
{
   	string message;
    
    public:
		AdjacentTilesException ()
    	{
        	 message = "Cannot put ship there! AdjacentTiles Exception";
    	}
		virtual ~AdjacentTilesException() throw() {}
		const string what()
		{
			return message;
		}
};

class Ship //einai afrimeni klasi apo tin opoia tha klironomi ta ploia
{
	public:
		virtual void placeShip(int sp[], char o, Tile B[][col]) = 0; //abstract methodos h opoia topothetei ta ploia
		virtual void check_boundaries(int sp[], char o) = 0; //abstract methodos h opoia elegxei ta oria
    	virtual void check_placement(int sp[], char o, Tile B[][col]) = 0; //abstract methodos h opoia elegxei an yparxei hdh ploio ekei
   	 	virtual void check_orientation(int sp[], char o, Tile B[][col]) = 0; //abstract methodos h opoia elegxei an yparxei ploio dipla
    	virtual bool my_check_boundaries(int sp[], char o) = 0; //idia me check_boundaries, epistrefei bool
    	virtual bool my_check_placement(int sp[], char o, Tile B[][col]) = 0; //idia me check_placement, epistrefei bool
    	virtual bool my_check_orientation(int sp[], char o, Tile B[][col]) = 0; //idia me check_orientation, epistrefei bool
};

class Battleship : public Ship //klasi opou klironomi tin ship
{
	private:
		int size; //megethos ploiou
		char orientation;//prosanatolismos
		int starting_point[2];//arxio simio
		OversizeException oe;
		OverlapTilesException ote;
		AdjacentTilesException ate;
	public:
		Battleship() //o hdmiourgos arxkopoia to size me 4
		{
			this->size = 4; 
		}
		void placeShip(int sp[], char o, Tile B[][col]) //pairnei orimsa to starting point,prosanatolismos kai ton pinaka Tile
		{
			int R, C;
			//kanei tous elegxous
			this->my_check_boundaries(sp, o);
            this->my_check_placement(sp, o, B);
            this->my_check_orientation(sp, o, B);
            this->check_boundaries(sp, o);
            this->check_placement(sp, o, B);
            this->check_orientation(sp, o, B);
            
            if (o == 'V') //sthn synexeia topothetei ta ploia 
                for (R = sp[0]; R < size+sp[0]; R++)
                   	B[R][sp[1]].setType(Tile::Ship);
            else if (o == 'H')
                for (C = sp[1]; C < size+sp[1]; C++)
                    B[sp[0]][C].setType(Tile::Ship);
		}
		void check_boundaries(int sp[], char o) //elegxei ta oria
    	{
        	try
        	{
            	if (o == 'V')
                	if (sp[0]+size > 4)
                    	throw oe;
            	else if (o == 'H')
                	if (sp[1]+size > 4)
                    	throw oe;
        	}
        	catch(OversizeException oe)
        	{cout << oe.what() << endl;}
    	}
    	void check_placement(int sp[], char o, Tile B[][col]) //elegxei an yparxei hdh ploio ekei
    	{
        	try
        	{
            	if (o == 'V')
                	for (int R = sp[0]; R < size+sp[0]; R++)
                    	if (B[R][sp[1]].getType() == Tile::Ship)
                        	throw ote;
            	else if (o == 'H')
                	for (int C = sp[1]; C < size+sp[1]; C++)
                    	if (B[sp[0]][C].getType() == Tile::Ship)
                        	throw ote;
        	}
        	catch(OverlapTilesException ote)
        	{cout << ote.what() << endl;}
    	}
    	void check_orientation(int sp[], char o, Tile B[][col]) //elegxei an yparxei ploio dipla tou
    	{
        	try
        	{
            	if ((o == 'V') && (sp[1] == 0))
            		for (int R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'V') && (sp[1] == 4))
            		for (R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
            	else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        			for (int R = sp[0]; R < size+sp[0]; R++)
        			{
        				if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
					}	
        		else if ((o == 'H') && (sp[0] == 0))
            		for (int C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] == 4))
            		for (C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        			for (C = sp[1]; C < size+sp[1]; C++)
        			{
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
                	}
        	}
        	catch (AdjacentTilesException ate)
        	{cout << ate.what() << endl;}
    	}
    	bool my_check_boundaries(int sp[], char o) //idia me check_boundaries, epistrefei bool
    	{
        	bool result = false;
        
        	if (o == 'V')
            	if (sp[0]+size > 4)
                	result = true;
        	else if (o == 'H')
            	if (sp[1]+size > 4)
                	result = true;
        
        	return result;
    	} 
    	bool my_check_placement(int sp[], char o, Tile B[][col]) //idia me check_placement, epistrefei bool
   	 	{
        	bool result = false;
        
        	if (o == 'V')
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]].getType() == Tile::Ship)
                    	result = true;
        	else if (o == 'H')
             	for (int C = sp[1]; C < size+sp[1]; C++)
                 	if (B[sp[0]][C].getType() == Tile::Ship)
                    	result = true;
        
        	return result;
    	}
    	bool my_check_orientation(int sp[], char o, Tile B[][col]) //idia me check_orientation, epistrefei bool
    	{
        	bool result = false;
        
        	if ((o == 'V') && (sp[1] == 0))
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'V') && (sp[1] == 4))
            	for (R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
            else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        		for (int R = sp[0]; R < size+sp[0]; R++)
        		{
        			if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
                    if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
				}
        	else if ((o == 'H') && (sp[0] == 0))
            	for (int C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] == 4))
            	for (C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        		for (C = sp[1]; C < size+sp[1]; C++)
        		{
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
                    if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
                }
                    
        	return result;
    	}
};

class Cruiser : public Ship
{
	private:
		int size; //megethos ploiou
		char orientation; //prosanatolismos
		int starting_point[2]; //arxiko shmeio
		OversizeException oe;
		OverlapTilesException ote;
		AdjacentTilesException ate;
	public:
		Cruiser() //o dhmiourgos arxikopoia to megethos se 3
		{
			this->size = 3;
		}
		void placeShip(int sp[], char o, Tile B[][col]) //methodos h opoio topothetei to ploio
		{
			int R, C;
			//kanei tous elegxous
			this->my_check_boundaries(sp, o);
            this->my_check_placement(sp, o, B);
            this->my_check_orientation(sp, o, B);
            this->check_boundaries(sp ,o);
            this->check_placement(sp, o, B);
            this->check_orientation(sp, o, B);
            
            if (o == 'V') //topothetei to ploio, allazontas ton typo tou se Ship
                for (R = sp[0]; R < size+sp[0]; R++)
                   	B[R][sp[1]].setType(Tile::Ship);
            else if (o == 'H')
                for (C = sp[1]; C < size+sp[1]; C++)
                    B[sp[0]][C].setType(Tile::Ship);
		}
		void check_boundaries(int sp[], char o) //elegxei ta oria
    	{
        	try
        	{
            	if (o == 'V')
                	if (sp[0]+size > 4)
                    	throw oe;
            	else if (o == 'H')
                	if (sp[1]+size > 4)
                    	throw oe;
        	}
        	catch(OversizeException oe)
        	{cout << oe.what() << endl;}
    	}
    	void check_placement(int sp[], char o, Tile B[][col]) //elegxei an yparxei hdh ploio ekei
    	{
        	try
        	{
            	if (o == 'V')
                	for (int R = sp[0]; R < size+sp[0]; R++)
                    	if (B[R][sp[1]].getType() == Tile::Ship)
                        	throw ote;
            	else if (o == 'H')
                	for (int C = sp[1]; C < size+sp[1]; C++)
                    	if (B[sp[0]][C].getType() == Tile::Ship)
                        	throw ote;
        	}
        	catch(OverlapTilesException ote)
        	{cout << ote.what() << endl;}
    	}
    	void check_orientation(int sp[], char o, Tile B[][col]) //elegxei an yparxei dipla tou ploiou
    	{
        	try
        	{
            	if ((o == 'V') && (sp[1] == 0))
            		for (int R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'V') && (sp[1] == 4))
            		for (R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
            	else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        			for (int R = sp[0]; R < size+sp[0]; R++)
        			{
        				if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
					}	
        		else if ((o == 'H') && (sp[0] == 0))
            		for (int C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] == 4))
            		for (C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        			for (C = sp[1]; C < size+sp[1]; C++)
        			{
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
                	}
        	}
        	catch (AdjacentTilesException ate)
        	{cout << ate.what() << endl;}
    	}
    	bool my_check_boundaries(int sp[], char o) //idia me check_boundaries, epistrefei bool
    	{
        	bool result = false;
        
        	if (o == 'V')
            	if (sp[0]+size > 4)
                	result = true;
        	else if (o == 'H')
            	if (sp[1]+size > 4)
                	result = true;
        
        	return result;
    	}
    	bool my_check_placement(int sp[], char o, Tile B[][col]) //idia me thn check_placement, epistrefei bool
    	{
        	bool result = false;
        
        	if (o == 'V')
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]].getType() == Tile::Ship)
                    	result = true;
        	else if (o == 'H')
             	for (int C = sp[1]; C < size+sp[1]; C++)
                 	if (B[sp[0]][C].getType() == Tile::Ship)
                    	result = true;
        
        	return result;
    	}
    	bool my_check_orientation(int sp[], char o, Tile B[][col]) //idia me thn check_orientation, epistrefei bool
    	{
        	bool result = false;
        
        	if ((o == 'V') && (sp[1] == 0))
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'V') && (sp[1] == 4))
            	for (R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
            else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        		for (int R = sp[0]; R < size+sp[0]; R++)
        		{
        			if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
                    if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
				}
        	else if ((o == 'H') && (sp[0] == 0))
            	for (int C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] == 4))
            	for (C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        		for (C = sp[1]; C < size+sp[1]; C++)
        		{
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
                    if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
                }
                    
        	return result;
    	}	
};

class Destroyer : public Ship 
{
	private:
		int size; //megethos ploiou
		char orientation; //prosanatolismos
		int starting_point[2]; //arxiko shmeio
		OversizeException oe;
		OverlapTilesException ote;
		AdjacentTilesException ate;
	public:
		Destroyer() //o dhmiourgos arxikopoia to megethos se 2
		{
			this->size = 2;
		}
		void placeShip(int sp[], char o, Tile B[][col]) //methodos h opoio topothetei to ploio
		{
			int R, C;
			//kanei tous elegxous
            this->my_check_boundaries(sp, o);
            this->my_check_placement(sp, o, B);
            this->my_check_orientation(sp, o, B);
			this->check_boundaries(sp ,o);
            this->check_placement(sp, o, B);
            this->check_orientation(sp, o, B);
            
            if (o == 'V') //topothetei to ploio allazontas ton typo tou se Ship
                for (R = sp[0]; R < size+sp[0]; R++)
                   	B[R][sp[1]].setType(Tile::Ship);
            else if (o == 'H')
                for (C = sp[1]; C < size+sp[1]; C++)
                    B[sp[0]][C].setType(Tile::Ship);
		}
		void check_boundaries(int sp[], char o) //elegxei ta oria
    	{
        	try
        	{
            	if (o == 'V')
                	if (sp[0]+size > 4)
                    	throw oe;
            	else if (o == 'H')
                	if (sp[1]+size > 4)
                    	throw oe;
        	}
        	catch(OversizeException oe)
        	{cout << oe.what() << endl;}
    	}
    	void check_placement(int sp[], char o, Tile B[][col]) //elegxei an yparxei hdh ploio ekei
    	{
        	try
        	{
            	if (o == 'V')
                	for (int R = sp[0]; R < size+sp[0]; R++)
                    	if (B[R][sp[1]].getType() == Tile::Ship)
                        	throw ote;
            	else if (o == 'H')
                	for (int C = sp[1]; C < size+sp[1]; C++)
                    	if (B[sp[0]][C].getType() == Tile::Ship)
                        	throw ote;
        	}
        	catch(OverlapTilesException ote)
        	{cout << ote.what() << endl;}
    	}
    	void check_orientation(int sp[], char o, Tile B[][col]) //elegxei an yparxei dipla ploio
    	{
        	try
        	{
            	if ((o == 'V') && (sp[1] == 0))
            		for (int R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'V') && (sp[1] == 4))
            		for (R = sp[0]; R < size+sp[0]; R++)
                		if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
            	else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        			for (int R = sp[0]; R < size+sp[0]; R++)
        			{
        				if (B[R][sp[1]+1].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    		throw ate;
					}	
        		else if ((o == 'H') && (sp[0] == 0))
            		for (int C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] == 4))
            		for (C = sp[1]; C < size+sp[1]; C++)
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
        		else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        			for (C = sp[1]; C < size+sp[1]; C++)
        			{
                		if (B[sp[0]-1][C].getType() == Tile::Ship)
                    		throw ate;
                    	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    		throw ate;
                	}
        	}
        	catch (AdjacentTilesException ate)
        	{cout << ate.what() << endl;}
    	}
    	bool my_check_boundaries(int sp[], char o) //idia me check_boundaries, epistrefei bool
    	{
        	bool result = false;
        
        	if (o == 'V')
            	if (sp[0]+size > 4)
                	result = true;
        	else if (o == 'H')
            	if (sp[1]+size > 4)
                	result = true;
        
        	return result;
    	}
    	bool my_check_placement(int sp[], char o, Tile B[][col]) //idia me check_placement, epistrefei bool
    	{
        	bool result = false;
        
        	if (o == 'V')
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]].getType() == Tile::Ship)
                    	result = true;
        	else if (o == 'H')
             	for (int C = sp[1]; C < size+sp[1]; C++)
                 	if (B[sp[0]][C].getType() == Tile::Ship)
                    	result = true;
        
        	return result;
    	}
    	bool my_check_orientation(int sp[], char o, Tile B[][col]) //idia me check_orientation, epistrefei bool
    	{
        	bool result = false;
        
        	if ((o == 'V') && (sp[1] == 0))
            	for (int R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'V') && (sp[1] == 4))
            	for (R = sp[0]; R < size+sp[0]; R++)
                	if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
            else if ((o == 'V') && (sp[1] != 4) && (sp[1] != 0))
        		for (int R = sp[0]; R < size+sp[0]; R++)
        		{
        			if (B[R][sp[1]+1].getType() == Tile::Ship)
                    	result = true;
                    if (B[R][sp[1]-1].getType() == Tile::Ship)
                    	result = true;
				}
        	else if ((o == 'H') && (sp[0] == 0))
            	for (int C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] == 4))
            	for (C = sp[1]; C < size+sp[1]; C++)
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
        	else if ((o == 'H') && (sp[0] != 4) && (sp[0] != 0))
        		for (C = sp[1]; C < size+sp[1]; C++)
        		{
                	if (B[sp[0]-1][C].getType() == Tile::Ship)
                    	result = true;
                    if (B[sp[0]+1][C].getType() == Tile::Ship)
                    	result = true;
                }
                    
        	return result;
    	}	
};

class Board //h klash Board anaparista ton pinaka tou ypologisth
{
	private:
		Tile B[row][col];
		OversizeException oe;
    	OverlapTilesException ote;
    	AdjacentTilesException ate;
    	int R, C;
    	bool hidden;
    public: 
		Board (Tile B[][col]) //o dhmiourgos arxikopoia to kathe keli se Sea, epishs thetei ton pinaka kryfo
		{
			for (R = 0; R < row; R++)
            	for (C = 0; C < col; C++)
                	B[R][C] = Tile(R, C, Tile::Sea);
        	
        	this->hidden = true;
		}
		void drawboards(Tile B[][col]) //typwnei ton pinaka
    	{
        	cout << ("- O P P O N E N T -") << endl;
        	cout << ("   0  1  2  3  4") << endl;
        	
        	for (int R = 0; R < row; R++) //xrhsimopoiei thn draw ths Tile
        	{
            	cout << " " << R;
            	for (int C = 0; C < col; C++)
            	{
                	B[R][C].draw(this->hidden);
                }
                
            	cout << endl;
        	}
    	}
    	Tile getAdjacentTiles(Tile c)
    	{
        	return c;
    	}
    	void placeAllShips(Tile B[][col]) //topotehtei tyxaia ta ploia, xrhsimopoiontas ena for kai ena switch
    	{
    		//prwta dhmiourgounte ta ploio
    		Battleship battleship;
    		Cruiser cruiser;
    		Destroyer destroyer;
    		int sp[2]; //arxiko shmeio
    		char o; //prosanatolismos
    		char options[] = {'H', 'V'};
    		srand(time(0)); //xrhsimopoieite gia na dinontai synexeia diaforetikes tyxaies times
    		
    		for (int i = 0; i < 3; i++)
    			switch (i)
    			{
    				case 0: //an i = 0 topotheteite to battleship
    					o = options[rand() % 2]; //dinei tyxaia ton prosanatolismo
                    
                    	sp[0] = rand() % 5; //dinei tyxaia arxikh grammh, kai ginonte kapoioi elegxoi
                    	if ((sp[0] == 4) || (sp[0] == 3) || (sp[0] == 2))
                        	o = 'H';
                        
                    	sp[1] = rand() % 5; //dinei tyxaia arxikh sthlh, kai ginonte kapoioi elegxoi
                    	if ((sp[1] == 4) || (sp[1] == 3) || (sp[1] == 2))
                        	o = 'V';  
                    	while ((battleship.my_check_boundaries(sp, o)) || (battleship.my_check_placement(sp, o, B)) || (battleship.my_check_orientation(sp, o, B)))
                    	{
                    		//an isxyoun kapoio apo ta parapanw ksanadinontai times, gia na mhn egyrthoun oi ekseraiseis
                        	o = options[rand() % 2];
                    
                        	sp[0] = rand() % 5;
                        	if ((sp[0] == 4) || (sp[0] == 3) || (sp[0] == 2))
                            	o = 'H';
                        
                        	sp[1] = rand() % 5;
                        	if ((sp[1] == 4) || (sp[1] == 3) || (sp[1] == 2))
                            	o = 'V'; 
                    	}
                    	//ginonte elegxoi kai topotheteite to ploio
                        battleship.check_boundaries(sp ,o);
                        battleship.check_placement(sp, o, B);
                        battleship.check_orientation(sp, o, B);
                        battleship.placeShip(sp, o, B);
                        
                    	break;
                    case 1: //an i = 1 topotheteite to cruiser
                    	o = options[rand() % 2]; //dinetai tyxaios prosanatolismos
                    
                    	sp[0] = rand() % 5; //dinetai tyxaia arxikh grammh
                    	if ((sp[0] == 3) || (sp[0] == 4))
                        	o = 'H';
                        
                    	sp[1] = rand() % 5; //dinetai tyxaia arxikh sthlh
                    	if ((sp[1] == 3) || (sp[1] == 4))
                        	o = 'V';
                    	while ((cruiser.my_check_boundaries(sp, o)) || (cruiser.my_check_placement(sp, o, B)) || (cruiser.my_check_orientation(sp, o, B)))
                    	{
                    		//an isxyei kapoios apo tous parapanw elegxous, ksanadinontai times
                        	o = options[rand() % 2];
                    
                        	sp[0] = rand() % 5;
                        	if ((sp[0] == 3) || (sp[0] == 4))
                            	o = 'H';
                        
                        	sp[1] = rand() % 5;
                        	if ((sp[1] == 3) || (sp[1] == 4))
                            	o = 'V';
                    	}
                    	//ginontai elegxoi kai topotheteite to ploio
                        cruiser.check_boundaries(sp ,o);
                        cruiser.check_placement(sp, o, B);
                        cruiser.check_orientation(sp, o, B);
                        cruiser.placeShip(sp, o, B);
                        
                    	break;
                    case 2: //an i = 2, topotheteite to destroyer
                    	o = options[rand() % 2]; //dinei tyxaio prosanatolismo
                    
                    	sp[0] = rand() % 5; //dinei tyxaia arxikh grammh
                    	if (sp[0] == 4)
                        	o = 'H';
                        
                    	sp[1] = rand() % 5; //dinei tyxaia arxikh sthlh
                    	if (sp[1] == 4)
                        	o = 'V';
                    	while ((destroyer.my_check_boundaries(sp, o)) || (destroyer.my_check_placement(sp, o, B)) || (destroyer.my_check_orientation(sp, o, B)))
                    	{
                    		//an isxyei enas apo tous parapanw elegxous, ksanadinonte times
                        	o = options[rand() % 2];
                    
                        	sp[0] = rand() % 5;
                        	if (sp[0] == 4)
                            	o = 'H';
                        
                        	sp[1] = rand() % 5;
                        	if (sp[1] == 4)
                            	o = 'V';
                    	}
                    	//ginonte oi elegxoi kai topotheteite to ploio
                        destroyer.check_boundaries(sp ,o);
                        destroyer.check_placement(sp, o, B);
                        destroyer.check_orientation(sp, o, B);
                        destroyer.placeShip(sp, o, B);

                    	break;
				}
		}
		bool allShipsSunk(Tile B[][col]) //h methodos ayth elegxei an yparxei ploio akoma ston pinaka kai epistrefei bool
    	{
        	bool sunk = true;
        
        	for (int R = 0; R < row; R++)
            	for (int C = 0; C < col; C++)
                	if (B[R][C].getType() == Tile::Ship)
                	{
                    	sunk = false;
                    	break;
                	}
        
        	return sunk;
    	}
    	void setHidden(bool h) //thetei thn katastash tou pinaka, se kryfo h mh-kryfo
    	{
    		this->hidden = h;
		}
};

class Player //anaparista ton paikth
{
	private:
		string name;
    	int shots, shots_hit, shots_missed, tries;
    	Tile B[row][col];
    public:
    	Player(string n) //arxikopoia to onoma tou paikth sto orisma pou dinetai, epishs arxikopoia tis ypoloipes metavlhtes klaseis se 0
    	{
    		this->name = n;
        	this->shots = 0;
        	this->shots_hit = 0; 
        	this->shots_missed = 0; 
        	this->tries = 0;
		}
    	void fire(Tile B[][col], int fp[]) //h methodos auth pragmatopoiei thn volh
    	{
        	shots++; //auksanei tis katallhles metavlhtes klaseis
        	tries++;
        	if (B[fp[0]][fp[1]].getType() == Tile::Ship) //an sto shmeio pou edwse o paikths yparxei ploio, tote allazei ton typo tou se Hit
        	{
            	B[fp[0]][fp[1]].setType(Tile::Hit);
            	cout << "Player: " << name << " hits." << endl; //emfanizei katallhlo mhynma
            	shots_hit++; //an o paikths htan eustoxos tote auksanei ton arithmo twn eustoxwn volwn
        	} 
        	else //alliws allazei ton typo tou keliou se Miss
        	{
            	B[fp[0]][fp[1]].setType(Tile::Miss);
            	cout << "Player: " << name << " misses." << endl; //emfanizei katallhlo mhnyma
            	shots_missed++; //kai auksanei ton arithmo ton astoxwn volwn
        	}
    	}
    	void getStats() //h methodos auth typwnei ta statistika tou paikth
    	{
        	cout << "Name: " << name << "." << endl;
        	cout << "Shots fired: " << shots << " times." << endl;
        	cout << "Shots hit: " << shots_hit << " times." << endl;
        	cout << "Shots missed: " << shots_missed << " times." << endl;
        	cout << "Tries: " << tries << " times." << endl;
    	}
    	int getTries() //epistrefei ton arithmo prospathiwn
    	{
        	return tries;
    	}
};

class Game
{
	public:
		int* getInput(int starting_point[]) //h methodos h opoia pairnei tis times pou dinei o xrhsths kai ta epistrefei san deikth
    	{   
        	cin >> starting_point[0];
        	cin >> starting_point[1];
        
        	while ((starting_point[0] > 4) || (starting_point[1] > 4)) //an o arithmos pou edwse einai ektos oriwn ksanazhta times
        	{
            	cout << "Point out of bounds! Please give two numbers between 0 and 4" << endl;
        		cin >> starting_point[0];
        		cin >> starting_point[1];
        	}
        
        	return starting_point; 
    	}
    	
};

int main()
{
	const int max_shots = 10; //megistos arithmos volwn
	//dhmiourgei ta antikeimena pou tha xreiastoun
	Game g;
	Tile B_C[row][col];
    Board board_C = Board(B_C);
    Player Player1 = Player ("Player1");
    int* fire_point;
	fire_point = (int *)malloc(2 * sizeof(int));
    
    board_C.placeAllShips(B_C);//topothetei ta ploia, tou ypologisth
    board_C.drawboards(B_C);//emfanizei ton pinaka tou
    do //oso o paikths den exei ftasei sto megisto orio volwn h den exoun vythistei ola ta ploio tou ypologisth, pragmatopoiounte voles
    {
        cout << endl;
        
        cout << "Player 1 where do want to fire? " << endl; //zhtaei apo ton xrhsth na dwsei to shmeio volhs tou
        fire_point = g.getInput(fire_point); //pairnei tis times xrhsimopoiontas thn getInput ths klashs Game
        Player1.fire(B_C, fire_point); //ektelei thn volh
        board_C.drawboards(B_C); //emfanizei ton pinaka
    }
    while ((Player1.getTries() != max_shots) && (!board_C.allShipsSunk(B_C)));
        
    board_C.setHidden(false); //kanei ton pinaka tou ypologisth se mh-kryfo
    	
    if (board_C.allShipsSunk(B_C)) //an o paikths exei vythisei ola ta ploio tou ypologisth emfanizei katallhlo mhnynma
    {
        cout << "Player1 you won!" << endl;
        board_C.drawboards(B_C); //emfanizei ton pinaka tou ypologisth
        cout << endl;
        Player1.getStats(); //emfanizei ta statistika tou paikth
    }
    else if ((Player1.getTries() == max_shots) && (!board_C.allShipsSunk(B_C))) //an exei ftasei sto megisto orio volwn kai den exoun vythistei ta ploio tou yplogisth, emfanizei katallhlo mynhma
    {
        cout << "Player1 you run out of tries! You lost!" << endl;
        board_C.drawboards(B_C); //emfanizei ton pinaka tou ypologisth
        cout << endl;
        Player1.getStats(); //emfanizei ta stastistika tou paikth
    }
        
	return 0; //symvolizei oti to programma termatisthke kanonika
}
