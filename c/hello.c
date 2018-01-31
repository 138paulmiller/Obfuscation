
/*
main()
{
// 64 bit block are stored little-endian order!
	//upper block
	unsigned int m = 10;
	unsigned int k = ('r') | ('l'<<8)| ('d'<<16) | ('!'<<24);
	//lower 	
	unsigned int j = ('o') | (' '<<8)| ('W'<<16) | ('o'<<24);
	unsigned int h = ('H') | ('e'<<8)| ('l'<<16) | ('l'<<24);
	printf("%s", &h);
}
*/
h=1819043144,j=1867980911,k=560229490,m=10;main(){printf("%s", &h);}
