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