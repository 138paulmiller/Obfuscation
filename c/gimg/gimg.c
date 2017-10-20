
#define W 500
#define H 400
#define CLAMP 255
unsigned int depth = 30;
main()
{
	unsigned int e, x ,y, steps;
	double min_r = -2.0;
	double max_r = 1.0;
	double min_i = -1.2;
	double max_i = 1.5;
	double r, i, z_r, z_i;
	double z_i2 , z_r2;
			
	printf("P6 %d %d %d\n", W, H, CLAMP+1);

	for(y=0;y<H;y++)
	{
		i = min_i+y*(max_i-min_i)/H;
		for(x=0;x<W;x++)
		{
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
				steps = 0;

			printf("%c%c%c%c%c%c", steps*depth%CLAMP, 0, steps*depth%CLAMP, 0, steps*depth%CLAMP, 0);		
		}
	}
}