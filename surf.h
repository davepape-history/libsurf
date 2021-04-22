#ifndef _surf_
#define _surf_

#include <gl.h>

#define UCHAR unsigned char
#define ULONG unsigned long

#define SURF_FULL	1
#define SURF_COMPACT	2
#define SURF_FLAT	3

typedef struct { float x,y,z; } sl_point_t;

typedef struct { float nx,ny,nz; } sl_norm_t;

typedef struct {
		float basex,basey,basez;
		float dx,dy,dz;
		UCHAR *zmap;
		} sl_compact_geom_t;

typedef struct {
		float basex,basey,basez;
		float dx,dy;
		} sl_flat_geom_t;

typedef struct {
		int x,y;
		Boolean globe;
		int geom_class;
		ULONG *color;
		sl_norm_t *norm;
		float tex_basex,tex_basey;
		float tex_dx,tex_dy;
		union {
			sl_point_t *full_geom;
			sl_compact_geom_t *compact_geom;
			sl_flat_geom_t *flat_geom;
			} geom;
		} sl_surface_t;

#define PALLOC(x) (x *) malloc(sizeof(x))
#define ARRALLOC(x,n) (x *) malloc((n)*sizeof(x))

void sl_draw_surface(sl_surface_t *surf,Boolean solid,Boolean vcolor,
			Boolean lighted, Boolean texmap);
sl_surface_t *sl_create_surface_struct(int x,int y,int geom_class,
		Boolean alloc_geom,Boolean alloc_color,Boolean alloc_norms);
sl_surface_t *sl_create_sphere_struct(int x,int y,Boolean alloc_color,
				Boolean alloc_norms);
void sl_sphere_surface(float radius,sl_surface_t *sph);
void sl_sphere_surface_cyl(float radius,sl_surface_t *sph);
void sl_bumpy_sphere(UCHAR *data,float radius,float bump_scale,
			sl_surface_t *sph);
void sl_bumpy_plane(UCHAR *data,float basex,float basey,float basez,
		float dx,float dy,float bump_scale,sl_surface_t *plane);
void sl_bumpy_plane_16s(short *data,float basex,float basey,float basez,
		float dx,float dy,float bump_scale,sl_surface_t *plane);
void sl_bumpy_plane_float(float *data,float basex,float basey,float basez,
		float dx,float dy,float bump_scale,sl_surface_t *plane);
void sl_flat_plane(float basex,float basey,float basez,float dx,float dy,
		sl_surface_t *plane);
void sl_bumpy_plane_compact(UCHAR *data,float basex,float basey,float basez,
		float dx,float dy,float bump_scale,sl_surface_t *plane);
void sl_flat_plane_compact(float basex,float basey,float basez,float dx,
			float dy,sl_surface_t *plane);
int sl_init_texmapping(void);
int sl_create_texture_from_file(char *fname);
int sl_create_texture(unsigned long *img,long xres,long yres);
sl_surface_t *sl_create_texture_square_from_file(char *rgbfile,char *alphafile,
						int *texid);
void sl_bumpy_sphere_float(float *data,float radius,float bump_scale,
				sl_surface_t *sph);

#endif
