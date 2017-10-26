#define G getchar()
#define _(x,y) x(a){y}

*I,*T,i,j,k,c;_(W,a?--k:(k[T]=G);)_(H,a?(k[T]?Q(-1):0):--k[T];)
_(E,a?++k:putchar(k[T]);)_(N,a?(k[T]?0:Q(1)):++k[T];)(*A[])()={W,H,E,N};_(Q,for(c=a;(I[i+=a]-91)?(I[i]-93)?1:(c-=1):(++c););)
_(main,a?(I=sbrk(2<<20)):0;for(j=i,i=-1,k=0;a?~(j++,I[++i]=G)|| (T=I+j) && main(0):++i<j&&1+(A[(I[i]&0xF)%4]((I[i]>>4)-2)););)
