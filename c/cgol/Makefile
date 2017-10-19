SOURCE="universe"
all: CC
	@echo gcc cgol.c -o cgol
CC: 	
	@gcc -w -DN="(E=(R*(P+1)+S-1)[*W]+(R*(P+1)+S)[*W]+(R*(P+1)+S+1)[*W]+(R*(P)+S-1)[*W]+(R*(P)+S+1)[*W]+(R*(P-1)+S-1)[*W]+(R*(P-1)+S)[*W]+(R*(P-1)+S+1)[*W])" -D"FOR(X)={for(A=0,W[C=0]=U,W[printf(\"\033c\")-1]=malloc(sizeof(U));!usleep(10) && A < R*R ||(A=0)||~(C=(C+1)%2);A++)X}" -D"EVER=((1+(S=A%R,P=(A-S)/R)) && C)?(R*(P)+S)[*W]=(R*(P)+S)[C[W]],(R*(P)+S)[1[W]]=0:(printf(\"\033[%d;%dH%c\",S,P,((R*(P)+S)[C[W]]?'#':' '),(S==0? putchar('\n'):0)),(R*(P)+S)[1[W]]=(1+N,(R*(P)+S)[*W]?(E>>1)==1:E==3));" -D"BIGBANG=U[]={" -D"COOL=},*W[2]={U,},R=sqrt(sizeof(U)/sizeof(*U));" -DUNIVERSE='$(SOURCE)' cgol.c -o cgol -lm

clean:
	rm cgol