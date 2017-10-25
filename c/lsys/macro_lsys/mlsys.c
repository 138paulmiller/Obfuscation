int x, y,i,a;
#define P printf("\033[%d;%dH\u2588",y=m*x+1,x)
#define clear printf("\033[H\033[J")
main()
{
	clear;
	x=y=10,a=0;
	for(i=L;i;i--)
		P,usleep(100);
	y=100;
	P;
}

