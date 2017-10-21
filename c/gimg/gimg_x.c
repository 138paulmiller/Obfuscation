#include <X11/Xlib.h>
#define W 500
#define H 400
#define CLAMP 255

unsigned int depth = 30;
unsigned int e, x ,y, steps;
long double min_r = -2.0;
long double max_r = 1.0;
long double min_i = -1.2;
long double max_i = 1.5;
long double r, i, z_r, z_i;
long double z_i2 , z_r2;
Display *dis;
int screen;
Window win;
GC gc;
long colors[W*H];
unsigned long getColor(char* color_name )
{
	XColor near_color, true_color;
	XAllocNamedColor( dis, DefaultColormap( dis, 0 ), color_name, &near_color, &true_color );
	return( near_color.pixel );
}
void close(); void handle_event();void redraw(); void setup();
void setup()
{
	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		W, H, 5, WhitePixel(dis,0), BlackPixel(dis,0));
	//XSetStandardProperties(dis,win,"GIMG","IOCCC",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
    gc=XCreateGC(dis, win, 0,0);
	XSetForeground(dis,gc,WhitePixel(dis,0));
	XSetBackground(dis,gc,0);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
}
void close()
{
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
//	XCloseDisplay(dis);
	exit(1);	
}
void handle_event()
{
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[2];		/* a char buffer for KeyPress Events */
	int draw;
	int timer = 0; 
	while(1) {	
		XNextEvent(dis, &event);
		draw = 0;
		if (event.type==KeyPress) {
			timer = 100;
			if (text[0]=='q') {
				close();
			}
			printf("You pressed the %d key!\n",event.xkey.keycode);
			draw=1;
		}
		else if (event.type==ButtonPress) {
			printf("You pressed a button at (%i,%i)\n",
				event.xbutton.x,event.xbutton.y);
			draw = 1;
		}
		if (draw || event.type==Expose) {
			redraw();
		}
	}
}
void redraw()
{
	int threads=0;
	//printf("P6 %d %d %d\n", W, H, CLAMP+1);
	for(e=0;e<W*H;e++)
	{
		if(threads < 4)
		{
			pid_t child = fork();
			if(child == 0)	
			{
				threads++;
				x=e%W;
				y=(e-x)/W;
				i = min_i+y*(max_i-min_i)/H;
				r = min_r+x*(max_r-min_r)/W;
				z_i = 0, z_r = 0, steps = 0;
				z_i2 = 0, z_r2=0;
				while(++steps < depth && (z_r2+ z_i2) < 4)
				{
					z_i = (2*z_r*z_i) + i;
					z_r = z_r2 - z_i2 + r;
					z_r2 = (z_r*z_r);
					z_i2 = (z_i*z_i);
				}
				if(steps >= depth)
				{	steps = 0;
				}
			
				colors[W*y+x] =steps*depth;
				threads--;
			} 
		}
	}
	//draw
	XClearWindow(dis, win);
	for(e=0;e<W*H;e++)
	{
		x=e%W;
		y=(e-x)/W;
		XSetForeground(dis, gc, colors[W*y+x]);
		XDrawPoint(dis, win, gc, x,y);
	}
	XFlush(dis);
}
main()
{
		setup();
		redraw();
		handle_event();
}
