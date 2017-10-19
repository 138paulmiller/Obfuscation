### Abusing C

##### Array indexing
	A[x] = x[A]
The index operator A[x] is compiled to an assembly instruction similar to *(A+x) in C.
The communative property of addition shows that *(A+x) = *(x+A).
Therefore, if C is given x[A] then this will compile into *(x+A), giving us the correct element address to dereference. 

##### Implicit typing
	f(a,b,c){return a+b+c;}  
	g,*p=&g;
	main()          
	{
		g = f(10, 20, 30);
		printf("%d\n", *p);
	}
All globally declared variables, function parameters and return types are implicitly declared as intger type.
Notice, the appending * before p, allows C to interpret p as an integer pointer.

##### Ignoring the return keyword on getchar
	f(){getchar();}  
	main(a)          
	{
		//echo back a character
		putchar('>');
		a=f();
		printf("%c\n", a);
	}
Main declared with implicit int return type and parameter types
f() implicitly returns an integer of data retrieved by getchar 
Notice, the return keyword can only be omitted for getchar(); and
declaring something such as f(a){a+32;} will not return a+32!

##### Array Initialization
	A[] = {
		#include "filename"
	}
	filename  = 
	 ________________
	|                |
	| 1,2,3,4,5,5,6, |
	| 7,8,9,10,11,...|
	|________________|

Since preprocessor directives perform text substitution before compiling, this feature can be taken advantage	
of to define blocks of data outside the C program. This does not neccessarily have to be done with arrays, but
is often useful for programs that read externally processed array data. The only downside is this program must be recompiled
if any of the data within the file is changed.

##### Hidden Source Macro Parameter
	HELLO("World")
This C source code is valid and will execute if compiled with very specific compiler flags and arguments. 
	gcc -D'HELLO(X)=int main(){printf("\nHello %s\n",X); }' foo.c -o foo 
GCC allows for macro definitions as arguments into the compiler. Compiling the source code with the above 
command is equivalent to the basic compilation command of the following:
	#define HELLO(X) int main(){printf("\nHello %s\n",X); }
	HELLO("World")
Which is essentially compiled to: 
	int main(){printf("\nHello %s\n","World"); 





