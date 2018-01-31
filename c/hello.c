
/*
main()
{
//Notice that the ints are pushed onto a stack so the order will be read in the reverse of the declaration 
//since in memory the next byte will be below tprevious.
	//upper block
	unsigned int m = 10;
	unsigned int k = ('r') | ('l'<<8)| ('d'<<16) | ('!'<<24);
	//lower 	
	unsigned int j = ('o') | (' '<<8)| ('W'<<16) | ('o'<<24);
	unsigned int h = ('H') | ('e'<<8)| ('l'<<16) | ('l'<<24);
	printf("%s", &h);
}
*/
//Declared as globals, the variables are declared in order, and the next value is just the next byte.
h=1819043144,j=1867980911,k=560229490,m=10;main(){printf("%s", &h);}
