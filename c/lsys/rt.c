#include <stdio.h>
typedef struct {float x,y,z;}vec;
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


int intersects(vec origin, vec dir, vec center, float radius, float *t)
{
	vec l = sub(center,origin);
	*t = dot(l,dir);
	if (*t < 0) return 0;
	float d = dot(l,l) - *t * *t;
	if (d > radius*radius) return 0;
	float ta = sqrt(radius*radius - d);
	float t0 = *t - ta;
	float t1 = *t + ta; 
	if(t0 < 0) *t = t1;
	else *t = t0; 
	return 1;
}
vec coi = {0,0,-1}; //center of interest
vec eye = {0,0,1}; //eye pos
vec up = {0,1,0};  // up direction
vec w,u,v;			//eye coordinate space(normal, right and up of view plane)
float fov = 45;
int W= 300, H = 200; //img width and height 
int i,j; //pixel coords
float a,b; //alpha, beta (deltas in virtual screen coords from pixel coords)
float aspect; //aspect ratio  
//ray
vec dir;
float t;
vec q; //tmp
vec sc = {0,0,-2}; //spehere center
main()
{

	q =sub(eye,coi);
	w = div(q, normal(q));
	q = cross(up, w);
	u = div(q, normal(q));
	v = cross(w,u);	

	printf("P6\n%d\n%d\n255\n", W, H);
	

	for(j=0; j < H; j++)
		for(i=0; i < W; i++)
		{
			//get virtual screen coords
			a = tan(fov/2)*(j-W/2)/W/2;
			b = tan(fov/2)*(H/2-i)/H/2;
			q = sub(add(muli(u, a),muli(v, b)),w);			
			dir = div(q,normal(q));
			
			if(intersects(eye, dir, sc, 1, &t))
			{
				vec hit = sub(add(eye, muli(dir, t)), sc);
				if(dot(dir, hit) > 0) hit = muli(hit,-1);
				char s[3] = {255, 0, 0};
				fwrite(s,1,3,stdout);
			}
		
		}

}
