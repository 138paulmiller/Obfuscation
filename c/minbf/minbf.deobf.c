//Can only parse < > - + , . [ ], any other characters in the file will yield unexpected behaviors!

int *instr,*tape,i,j,k,c;//if +1 for [, -1 for ], stop at 0
int il(int a){a? --k:(tape[k]=getchar());}
int dc(int a){ a?  (tape[k]?go(-1):0) : --tape[k];}
int pr(int a){ a?  ++k : putchar(tape[k]); }
int ao(int a){ a?  (tape[k]?0:go(1)) : ++tape[k]; }
int(*action[])(int)={il,dc,pr,ao};
int go(int d)
{
	c=d;
	while((instr[i+=d]-91)? (instr[i]-93)? 1: (c-=1) : (c+=1)) ;
}

main(a)
{
	j=i,i=-1,k=0;
	a?(instr=sbrk(2<<16)):(tape=sbrk(2<<16));
	while( a? ~(instr[++i]=getchar())  ||  main(0):++i<j && 1+(action[(instr[i]&0xF)%4]((instr[i]>>4)-2)));		 				
}

