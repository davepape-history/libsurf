#include <gl.h>
#include <math.h>
#include "surf.h"

sl_surface_t *sl_create_sphere_struct(int x,int y,Boolean alloc_color,
				Boolean alloc_norms)
{
 sl_surface_t *sph;
 sph = PALLOC(sl_surface_t);
 sph->x = x;
 sph->y = y;
 sph->globe = TRUE;
 sph->geom_class = SURF_FULL;
 sph->geom.full_geom = ARRALLOC(sl_point_t,x*y);
 if (alloc_color) sph->color = ARRALLOC(ULONG,x*y);
 else sph->color = NULL;
 if (alloc_norms) sph->norm = ARRALLOC(sl_norm_t,x*y);
 else sph->norm = NULL;
 return(sph);
}

sl_surface_t *sl_create_surface_struct(int x,int y,int geom_class,
				Boolean alloc_geom,Boolean alloc_color,
				Boolean alloc_norms)
{
 sl_surface_t *s;
 s = PALLOC(sl_surface_t);
 s->x = x;
 s->y = y;
 s->globe = FALSE;
 s->geom_class = geom_class;
 if (alloc_geom) {
    if (geom_class == SURF_FULL)
	s->geom.full_geom = ARRALLOC(sl_point_t,x*y);
    else if (geom_class == SURF_COMPACT)
	s->geom.compact_geom = PALLOC(sl_compact_geom_t);
    else if (geom_class == SURF_FLAT)
	s->geom.flat_geom = PALLOC(sl_flat_geom_t);
    }
 else s->geom.full_geom = NULL;
 if (alloc_color) s->color = ARRALLOC(ULONG,x*y);
 else s->color = NULL;
 if (alloc_norms) s->norm = ARRALLOC(sl_norm_t,x*y);
 else s->norm = NULL;
 s->tex_basex = s->tex_basey = s->tex_dx = s->tex_dy = 0.0;
 return(s);
}

void sl_free_surface(sl_surface_t *surf)
{
 if ((surf->geom_class == SURF_FULL) && (surf->geom.full_geom)) {
	free(surf->geom.full_geom);
	if (surf->norm == (sl_norm_t *)surf->geom.full_geom) surf->norm = NULL;
	}
 else if ((surf->geom_class == SURF_COMPACT) && (surf->geom.compact_geom)) {
	if (surf->geom.compact_geom->zmap) free(surf->geom.compact_geom->zmap);
	free(surf->geom.compact_geom);
	}
 else if ((surf->geom_class == SURF_FLAT) && (surf->geom.flat_geom))
	free(surf->geom.flat_geom);
 if (surf->color) free(surf->color);
 if (surf->norm) free(surf->norm);
 free(surf);
}

void sl_sphere_surface(float radius,sl_surface_t *sph)
{
 float *sintheta,*costheta,theta,rsinj,rcosj;
 int i,j,x,y;
 sl_point_t *pos;
 x = sph->x; y = sph->y;
 sph->globe = TRUE;
 sph->geom_class = SURF_FULL;
 sintheta = (float *) malloc(x*sizeof(float));
 costheta = (float *) malloc(x*sizeof(float));
 for (i=0; i<x; i++) {
	theta = (float)i/(float)x*2.0*M_PI - M_PI_2;
	sintheta[i] = sin(theta);
	costheta[i] = cos(theta);
	}
 for (j=0, pos=sph->geom.full_geom; j<y; j++) {
	theta = (float)j/(float)(y-1)*M_PI - M_PI_2;
	rsinj = sin(theta) * radius;
	rcosj = cos(theta) * radius;
	for (i=0; i<x; i++, pos++) {
		pos->x = -rcosj*costheta[i];
		pos->y = rsinj;
		pos->z = rcosj*sintheta[i];
		}
	}
 free(sintheta); free(costheta);
}

void sl_sphere_surface_cyl(float radius,sl_surface_t *sph)
{
 float *sintheta,*costheta,theta,rsinj,rcosj,yval;
 int i,j,x,y;
 sl_point_t *pos;
 x = sph->x; y = sph->y;
 sph->globe = TRUE;
 sph->geom_class = SURF_FULL;
 sintheta = (float *) malloc(x*sizeof(float));
 costheta = (float *) malloc(x*sizeof(float));
 for (i=0; i<x; i++) {
	theta = (float)i/(float)x*2.0*M_PI - M_PI_2;
	sintheta[i] = sin(theta);
	costheta[i] = cos(theta);
	}
 for (j=0, pos=sph->geom.full_geom; j<y; j++) {
	yval = 2.0*radius*j/(y-1) - radius;
	theta = asin(yval);
	rcosj = cos(theta) * radius;
	for (i=0; i<x; i++, pos++) {
		pos->x = -rcosj*costheta[i];
		pos->y = yval;
		pos->z = rcosj*sintheta[i];
		}
	}
 free(sintheta); free(costheta);
}

void sl_bumpy_sphere(UCHAR *data,float radius,float bump_scale,sl_surface_t *sph)
{
 float r,*sintheta,*costheta,theta,sinj,cosj;
 int i,j,x,y;
 UCHAR *dz;
 sl_point_t *p;
 x = sph->x; y = sph->y;
 sph->globe = TRUE;
 sph->geom_class = SURF_FULL;
 sintheta = (float *) malloc(x*sizeof(float));
 costheta = (float *) malloc(x*sizeof(float));
 for (i=0; i<x; i++) {
	theta = (float)i/(float)x*2.0*M_PI - M_PI_2;
	sintheta[i] = sin(theta);
	costheta[i] = cos(theta);
	}
 for (j=0, dz=data, p=sph->geom.full_geom; j<y; j++) {
	theta = (float)j/(float)(y-1)*M_PI - M_PI_2;
	sinj = sin(theta);
	cosj = cos(theta);
	for (i=0; i<x; i++, p++, dz++) {
		r = radius + (*dz)*bump_scale;
		p->x = -r*cosj*costheta[i];
		p->y = r*sinj;
		p->z = r*cosj*sintheta[i];
		}
	}
 free(sintheta); free(costheta);
}

void sl_bumpy_sphere_float(float *data,float radius,float bump_scale,
				sl_surface_t *sph)
{
 float r,*sintheta,*costheta,theta,sinj,cosj;
 int i,j,x,y;
 float *dz;
 sl_point_t *p;
 x = sph->x; y = sph->y;
 sph->globe = TRUE;
 sph->geom_class = SURF_FULL;
 sintheta = (float *) malloc(x*sizeof(float));
 costheta = (float *) malloc(x*sizeof(float));
 for (i=0; i<x; i++) {
	theta = (float)i/(float)x*2.0*M_PI - M_PI_2;
	sintheta[i] = sin(theta);
	costheta[i] = cos(theta);
	}
 for (j=0, dz=data, p=sph->geom.full_geom; j<y; j++) {
	theta = (float)j/(float)(y-1)*M_PI - M_PI_2;
	sinj = sin(theta);
	cosj = cos(theta);
	for (i=0; i<x; i++, p++, dz++) {
		r = radius + (*dz)*bump_scale;
		p->x = -r*cosj*costheta[i];
		p->y = r*sinj;
		p->z = r*cosj*sintheta[i];
		}
	}
 free(sintheta); free(costheta);
}

void sl_bumpy_plane(UCHAR *data,float basex,float basey,float basez,
			float dx,float dy,float bump_scale,sl_surface_t *plane)
{
 int i,j;
 UCHAR *dz;
 sl_point_t *p;
 plane->geom_class = SURF_FULL;
 plane->globe = FALSE;
 for (j=0, dz=data, p=plane->geom.full_geom; j<plane->y; j++)
	for (i=0; i<plane->x; i++, p++, dz++) {
		p->x = basex + i*dx;
		p->y = basey + j*dy;
		p->z = basez + (*dz)*bump_scale;
		}
}

void sl_bumpy_plane_16s(short *data,float basex,float basey,float basez,
			float dx,float dy,float bump_scale,sl_surface_t *plane)
{
 int i,j;
 short *dz;
 sl_point_t *p;
 plane->geom_class = SURF_FULL;
 plane->globe = FALSE;
 for (j=0, dz=data, p=plane->geom.full_geom; j<plane->y; j++)
	for (i=0; i<plane->x; i++, p++, dz++) {
		p->x = basex + i*dx;
		p->y = basey + j*dy;
		p->z = basez + (*dz)*bump_scale;
		}
}

void sl_bumpy_plane_float(float *data,float basex,float basey,float basez,
			float dx,float dy,float bump_scale,sl_surface_t *plane)
{
 int i,j;
 float *dz;
 sl_point_t *p;
 plane->geom_class = SURF_FULL;
 plane->globe = FALSE;
 for (j=0, dz=data, p=plane->geom.full_geom; j<plane->y; j++)
	for (i=0; i<plane->x; i++, p++, dz++) {
		p->x = basex + i*dx;
		p->y = basey + j*dy;
		p->z = basez + (*dz)*bump_scale;
		}
}

void sl_flat_plane(float basex,float basey,float basez,float dx,float dy,
			sl_surface_t *plane)
{
 int i,j;
 sl_point_t *pos;
 plane->globe = FALSE;
 plane->geom_class = SURF_FULL;
 for (j=0, pos=plane->geom.full_geom; j<plane->y; j++)
	for (i=0; i<plane->x; i++, pos++) {
		pos->x = basex + i*dx;
		pos->y = basey + j*dy;
		pos->z = basez;
		}
}

void sl_bumpy_plane_compact(UCHAR *data,float basex,float basey,float basez,
			float dx,float dy,float bump_scale,sl_surface_t *plane)
{
 plane->globe = FALSE;
 plane->geom_class = SURF_COMPACT;
 plane->geom.compact_geom->basex = basex;
 plane->geom.compact_geom->basey = basey;
 plane->geom.compact_geom->basez = basez;
 plane->geom.compact_geom->dx = dx;
 plane->geom.compact_geom->dy = dy;
 plane->geom.compact_geom->dz = bump_scale;
 plane->geom.compact_geom->zmap = data;
}

void sl_flat_plane_compact(float basex,float basey,float basez,
			float dx,float dy,sl_surface_t *plane)
{
 plane->globe = FALSE;
 plane->geom_class = SURF_FLAT;
 plane->geom.flat_geom->basex = basex;
 plane->geom.flat_geom->basey = basey;
 plane->geom.flat_geom->basez = basez;
 plane->geom.flat_geom->dx = dx;
 plane->geom.flat_geom->dy = dy;
}
