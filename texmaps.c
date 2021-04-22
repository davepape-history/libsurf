#include <stdio.h>
#include <gl.h>
#include "dave.h"
#include "surf.h"

int sl_init_texmapping(void)
{
 float tevprops[] = { TV_NULL };
 if (!getgdesc(GD_TEXTURE)) return(0);
 tevdef(1,0,tevprops);
 tevbind(TV_ENV0,1);
 return(1);
}

int sl_create_texture_from_file(char *fname)
{
 float texprops[] = { TX_NULL };
 unsigned long *img;
 int xres,yres,id;
 id = dpNewID();
 if (!dpReadSgiImageLong(fname,&img,&xres,&yres)) return(0);
 texdef2d(id,4,xres,yres,img,0,texprops);
 free(img);
 return id;
}

int sl_create_texture(unsigned long *img,long xres,long yres)
{
 float texprops[] = { TX_NULL };
 int id = dpNewID();
 texdef2d(id,4,xres,yres,img,0,texprops);
 return id;
}

sl_surface_t *sl_create_texture_square_from_file(char *rgbfile,char *alphafile,
						int *texid)
{
 float texprops[] = { TX_NULL };
 sl_surface_t *s;
 int xres,yres,xres2,yres2,i;
 unsigned long *image,*ip;
 if (!dpReadSgiImageLong(rgbfile,&image,&xres,&yres)) return(NULL);
 if (alphafile) {
    unsigned char *alpha,*ap;
    if (!dpReadSgiImageByte(alphafile,&alpha,&xres2,&yres2)) {
	free(image);
	return(NULL);
	}
    if ((xres!=xres2) || (yres!=yres2)) {
	fprintf(stderr,"error: create_texture_square_from_file: "
		"\"%s\" & \"%s\" are not the same size\n",
		rgbfile,alphafile);
	free(image);
	free(alpha);
	return(NULL);
	}
    for (i=xres*yres, ip=image, ap=alpha; i; i--, ip++, ap++)
		*ip = (*ip & 0x00ffffff) | (*ap << 24);
    free(alpha);
    }
 s = sl_create_surface_struct(2,2,SURF_FLAT,TRUE,FALSE,FALSE);
 s->geom.flat_geom->basex = 0.0;
 s->geom.flat_geom->basey = 0.0;
 s->geom.flat_geom->basez = 0.0;
 s->geom.flat_geom->dx = 1.0;
 s->geom.flat_geom->dy = 1.0;
 s->tex_basex = 0.0;
 s->tex_basey = 0.0;
 s->tex_dx = 1.0;
 s->tex_dy = 1.0;
 *texid = dpNewID();
 texdef2d(*texid,4,xres,yres,image,0,texprops);
 free(image);
 return s;
}
