#include <X11/Xlib.h>
#define W 400
#define H 300
#define N 100

Display *dis;
int screen;
Window win;
GC gc;
typedef struct {float x,y,z;}vec;
vec vnew(float x, float y, float z) {return(vec){x,y,z};} 
vec normal(vec v) {float l = sqrt(v.x*v.x + v.y*v.y+v.z*v.z);return(vec){v.x/l, v.y/l, v.z/l};} 
vec cross(vec a, vec b) {return(vec){a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};}
vec divi(vec v, float a) {return(vec){v.x/a, v.y/a, v.z/a};}
vec div(vec a, vec b) {return(vec){a.x/b.x, a.y/b.y, a.z/b.z};}
vec mul(vec a, vec b) {return(vec){a.x*b.x, a.y*b.y, a.z*b.z};}
vec muli(vec v, float a) {return(vec){v.x*a, v.y*a, v.z*a};}
vec add(vec a, vec b) {return(vec){a.x+b.x, a.y+b.y, a.z+b.z};}
vec sub(vec a, vec b) {return(vec){a.x-b.x, a.y-b.y, a.z-b.z};}
float dist(vec a, vec b){return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)+(b.z-a.z)*(b.z-a.z));}
float dot(vec a, vec b) {return a.x*b.x + a.y*b.y+a.z*b.z;}

int intersects(vec origin, vec dir, vec center, float radius, float *t){
	vec l=sub(center,origin);*t = dot(l,dir);if(*t<0)return 0;
	float d= dot(l,l)-*t**t;if(d>radius*radius)return 0;
	float ta=sqrt(radius*radius-d);float t0=*t-ta;float t1=*t+ta; 
	if(t0 < 0) *t = t1;else *t = t0; return 1;}

float mix(float a, float b, float mix){return b*mix+a*(1-mix);}
vec look = {0,0,1}; //center of interest
vec eye = {0,0,0}; //eye pos
vec up = {0,1,0};  // up direction

vec w,u,v;			//eye coordinate space(normal, right and up of view plane)
float fov = 45,angle;
int i,j; //pixel coords
float aspect; //aspect ratio  
//ray

vec colors[W*H];
vec phit,nhit; //point of hit and normal of hit
float t, tmin;//tis dist, tmin is closest, 
int e,f,x,y, inside,si;//si is sphere index
#define S 2
#define D 5
float s_rad[S] = {3,4};
vec s_pos[S] = {{2,2,-20},{5,-1,-20}};
vec s_col[S] = {{255,255,0}, {0,120,120} };
vec s_emi[S] = {{255,0,0}, {0,255,255} };
float s_trans[S] = {0.9, 0.7};
float s_refl[S] = {0.0, 0.3}; 
void setup()
{
	angle = tan(3.1415926 * 0.5 * fov / 180);
	aspect =  W/H;
	w = div(sub(eye,look), normal(sub(eye,look)));
	u = div(cross(up, w), normal(cross(up, w)));
	v = cross(w,u);	
}

vec trace(vec origin, vec dir, int depth)
{

	vec col = {0,0,0};
	tmin = 1000000;	
	si=-1;	
	for(f=0; f < S; f++)
		if(intersects(origin, dir, s_pos[f], s_rad[f], &t) && t < tmin)
			{tmin = t;si = f;}
	if(si!= -1)
	{
		phit = add(origin, muli(dir, tmin));
		nhit = normal(sub(phit, s_pos[si]));
		inside =  0;
		if(dot(dir, nhit) > 0) nhit = muli(nhit,-1), inside=1;//inside the sphere 
		if((s_trans[si] || s_refl[si]) && depth<D)
		{
			float fresnel = mix(pow(1+1*dot(dir,nhit),3), 1, 0.1);
			vec refl = normal(sub(dir,muli(nhit, 2*dot(dir, nhit))));
			vec refl_col = trace(add(phit, muli(nhit, 1e-4)), refl, depth+1);
			vec refr_col ={0,0,0};
			if(s_trans[si])
			{
				float eta = inside ? 1.1 : 1 / 1.1;
				float cosi = -1*dot(nhit, dir);
				vec refr =normal(add(muli(dir,eta), muli(nhit,eta*cosi-sqrt(1-eta*eta*(1-cosi*cosi))))); 
				refr_col = trace(sub(phit, muli(nhit, 1e-4)), refr, depth+1);
			}
			col = add(muli(refl_col, fresnel), mul(muli(refr_col,(1-fresnel)*s_trans[si]), s_emi[si]));			
		}
		else
		{
//			col = s_col[si]* dot(eye, nhit)<0?0:dot(eye, nhit); //temp, light from eye
		}
		
		col = add(s_col[si],col);

	}
	return col;
}

main()
{
	dis=XOpenDisplay((char *)0);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,W, H, 5, 0,0);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
    gc=XCreateGC(dis, win, 0,0);
	XMapRaised(dis, win);
	XEvent event;
	setup();

	XNextEvent(dis, &event);
	long timer = 0;
	while(1){
		if( clock()-timer++ < 0){
			s_pos[0].x = 10*cos(timer);
			s_pos[0].y = 10*sin(timer);
			printf("P6 %d %d 255 ", W, H);
			for(e=0;e<W*H;e++)
			{
				x = e%W;
				y = (e-x)/W;		
				//get virtual screen coords
				vec dir = normal(vnew((2*((x+0.5)*1.0/W)-1)*angle*aspect,(1-2*((y+0.5)*1.0/H))*angle,-1));
				colors[W*y+x]= trace(eye, dir, 0); 	
			}
			XClearWindow(dis, win);		
			for(y=0;y<H;y++)for(x=0;x<W;x++) 
			{
				vec col =colors[W*y+x];
				XSetForeground(dis, gc, ((int)(col.x) | (int)(col.y)|(int)(col.z))%0xFFFFFF);
				printf("%c%c%c", (int)col.x, (int)col.y,(int)col.z);	
				XDrawPoint(dis, win, gc, x,y);
			}
			timer = clock();
		}
	}
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
    XCloseDisplay(dis);
}

