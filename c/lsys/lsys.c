/*
Takes input grammar for l-system production and number of iterations to run
Syntax:
Iterations\n
nonterm=rule_1\n 
... 
nonterm=rule_n\n
input_string

Uppercase Letters Denote Nonterminals
All other symbols besides '=' denote constants

+ means turn left 120
− means "turn right 120
*/
int x,y,a=0;
#define LEN 5
#define CLR puts("\e[1;1H\e[2J");
#define SET(X,Y) x=X,y=Y; 
char s[9999],* R[26],* res; 
int it = 0,i=-2,j;


void line(int c)
{
	for(i=LEN;i--;)
	{
		x+=cos(a);
		y-=sin(a);
	 	printf("\033[%d;%dH%c",y,x,c);
		
	}
}
main(c,r)char c,r;
{

	while((i==-2?i=-scanf("%d\n", &it):i<0?((c=getchar())!=-1)&&(1+(i=0)&&((r=getchar())=='=')):((r=getchar())!='\n')&&1+(s[i++]=r)||(1+(s[i]='\0')&&(c[R-65]= malloc(sizeof s))&&(strcpy(c[R-65],s))&&(i=-1)))||!((s[i++]=c) && (s[i++]=r)));
	while((((c=getchar())!=-1)&&c!='\n'
	&&(s[i++]=c)?1:(free(res),s[i]='\0')));
	while(it-->0 && (res=malloc(sizeof s))&& strcpy(res, s) &&((j=0) || (i=-1)))
	while(++i< strlen(res) && res[i]-65<=26 && 
	(res[i]-65>=0? strcpy(&s[j], R[res[i]-65]) && (j+=strlen(&s[j])):(s[j++]=res[i])));		

	CLR	

	
	SET(50,20)
	line('|');
	a=45;
	line('|'); 
	//for(;1;);
	a=0; 
	SET(50,20+LEN)
	line('\n');
}
