#define I "universe"

/*get universe data, must be square(Width=height)*/
U[]=
{	
	#include I
},
V[]={
	#include I
},
//Pointer to each world (2 copies of world to perform buffer swapping)
*GEN[2]={U,V},
//R = number of rows which is equivalent to columns
//size of U, divided by size of elements = number of elements
R=sqrt(sizeof(U)/sizeof(*U));
//access element from universe array GEN[w][R*y+x] as (R*y+x)[w[GEN]] 
get(x,y,w){return (R*y+x)[w[GEN]];} //mask by one two return 0 or 1
//get number of neightbors of x,y in world w
set(x,y,w,v) {(R*y+x)[w[GEN]]=v;}
//visually shows neighbors of x,y omitting x,y
n(x,y,w){return get(x-1,y+1,w)+ get(x,y+1,w)+ get(x+1,y+1,w)+
				get(x-1,y,w)+ /*get(x,y,w)*/  get(x+1,y,w)+
                get(x-1,y-1,w)+ get(x,y-1,w)+ get(x+1,y-1,w);}

//x - row iteratferor, y = col iterator, e = element iterator 
//w is the current world generation, next generation is (w++)%2
main(x,y,e,w)
{
	printf("\033c"); //clear, returns 2 since \033 and c are two chars being output
	//only after e < R*R is false will e=0 and (w=(w+1)%2) will be evaluated
	//e=0 is always false so (w=(w+1)%2) is bit flipped to always be true(w=0 or w=1)
	for(e=0; e < R*R || (e=0) || ~(w=(w+1)%2); e++) //each element in array
	{
		usleep(10);
		/*
		1D array in row-major so A[x][y] = A[R*y+x]
		To iterate element e in a single array, x modulates between R, so x = e%R
		And y can be found by solving A[R*y+x] = A[e] -> e = R*y+x -> (e-x)/R = y
		*/
		x=e%R;
		y = (e-x)/R;
		if(w)
		{
			printf("\033[%d;%dH%c",x,y, (get(x,y,w)?'#':' '), (x==0? putchar('\n'):0));
			//apply rules in next gen add expr ^ to avoid to get requests
			//get statement can be used as ternary cond in set argument
			if(get(x,y,w)) //alive stays alive if 2 or 3 neighbors
				//if 2 or 3 (0010 or 0011) neighbors, x,y survives. 
				//if n shifted right once = 001. Then it survives!
				//So (n>>1) will be 1 if 2 or 3
				set(x,y,0,(n(x,y,1)>>1)==1);
			else
				//rule, if dead then 3 neighbors is now alive
				set(x,y,0,(n(x,y,1))==3);			
		}
		else
		{
			//if at second array, copy x,y into first array and clear out first
			set(x,y,1,get(x,y,w));
			set(x,y,w,0);
		}
	}
}