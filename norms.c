#include <stdio.h>
#include <math.h>
#include "surf.h"

static void get_norm(float x1,float y1,float z1,float x2,float y2,float z2,
	float x3,float y3,float z3,float *n)
{
 float dx2,dy2,dz2,dx3,dy3,dz3;
 dx2 = x2 - x1; dy2 = y2 - y1; dz2 = z2 - z1;
 dx3 = x3 - x1; dy3 = y3 - y1; dz3 = z3 - z1;
 n[0] = dy2*dz3 - dy3*dz2;
 n[1] = dz2*dx3 - dz3*dx2;
 n[2] = dx2*dy3 - dx3*dy2;
}

static void compute_normals_full(sl_surface_t *surf)
{
 int i,j;
 sl_norm_t *n1,*n2,*n3,*n4,*norm;
 sl_point_t *p1,*p2,*p3,*p4;
 float n[3],len;
#ifdef DEBUG
printf("compute_normals_full\n");
#endif
 for (j=0, norm=surf->norm; j < surf->y; j++)
    for (i=0; i < surf->x; i++, norm++)
	norm->nx = norm->ny = norm->nz = 0.0;
 norm = surf->norm;
 p1 = surf->geom.full_geom;	n1 = surf->norm;
 p2 = p1+1;			n2 = surf->norm+1;
 p3 = p1+surf->x;		n3 = surf->norm+surf->x;
 p4 = p1+surf->x+1;		n4 = surf->norm+surf->x+1;
 for (j=0; j < surf->y-1; j++) {
    for (i=0; i < surf->x-1; i++, p1++,p2++,p3++,p4++, n1++,n2++,n3++,n4++) {
	get_norm(p1->x,p1->y,p1->z, p2->x,p2->y,p2->z, p3->x,p3->y,p3->z, n);
	n1->nx += n[0];   n1->ny += n[1];   n1->nz += n[2];
	n2->nx += n[0];   n2->ny += n[1];   n2->nz += n[2];
	n3->nx += n[0];   n3->ny += n[1];   n3->nz += n[2];
	get_norm(p4->x,p4->y,p4->z, p3->x,p3->y,p3->z, p2->x,p2->y,p2->z, n);
	n4->nx += n[0];   n4->ny += n[1];   n4->nz += n[2];
	n2->nx += n[0];   n2->ny += n[1];   n2->nz += n[2];
	n3->nx += n[0];   n3->ny += n[1];   n3->nz += n[2];
	}
    p1++, p2++, p3++, p4++;
    n1++, n2++, n3++, n4++;
    }
 for (j=0, norm=surf->norm; j < surf->y; j++)
    for (i=0; i < surf->x; i++, norm++) {
	len = fsqrt(norm->nx*norm->nx + norm->ny*norm->ny + norm->nz*norm->nz);
	norm->nx /= len;
	norm->ny /= len;
	norm->nz /= len;
	}
}

static void compute_normals_compact(sl_surface_t *surf)
{
 int i,j;
 sl_norm_t *n1,*n2,*n3,*n4,*norm;
 UCHAR *p1,*p2,*p3,*p4;
 float n[3],len,dx,dy,dz,x1,y1,z1,x2,y2,z2,x3,y3,z3,x,y;
#ifdef DEBUG
printf("compute_normals_compact\n");
#endif
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, norm=surf->norm; j < surf->y; j++)
    for (i=0; i < surf->x; i++, norm++)
	norm->nx = norm->ny = norm->nz = 0.0;
 norm = surf->norm;
 p1 = surf->geom.compact_geom->zmap;	n1 = surf->norm;
 p2 = p1+1;			n2 = surf->norm+1;
 p3 = p1+surf->x;		n3 = surf->norm+surf->x;
 p4 = p1+surf->x+1;		n4 = surf->norm+surf->x+1;
 for (j=0, y=0.0; j < surf->y-1; j++, y+=dy) {
    for (i=0, x=0.0; i < surf->x-1;
		i++, p1++,p2++,p3++,p4++, n1++,n2++,n3++,n4++, x+=dx) {
	x1 = x;     y1 = y;     z1 = *p1 * dz;
	x2 = x+dx;  y2 = y;     z2 = *p2 * dz;
	x3 = x;     y3 = y+dy;  z3 = *p3 * dz;
	get_norm(x1,y1,z1, x2,y2,z2, x3,y3,z3, n);
	n1->nx += n[0];   n1->ny += n[1];   n1->nz += n[2];
	n2->nx += n[0];   n2->ny += n[1];   n2->nz += n[2];
	n3->nx += n[0];   n3->ny += n[1];   n3->nz += n[2];
	x1 = x+dx;  y1 = y+dy;  z1 = *p4 * dz;
	x2 = x;     y2 = y+dy;  z2 = *p3 * dz;
	x3 = x+dx;  y3 = y;     z3 = *p2 * dz;
	get_norm(x1,y1,z1, x2,y2,z2, x3,y3,z3, n);
	n4->nx += n[0];   n4->ny += n[1];   n4->nz += n[2];
	n2->nx += n[0];   n2->ny += n[1];   n2->nz += n[2];
	n3->nx += n[0];   n3->ny += n[1];   n3->nz += n[2];
	}
    p1++, p2++, p3++, p4++;
    n1++, n2++, n3++, n4++;
    }
 for (j=0, norm=surf->norm; j < surf->y; j++)
    for (i=0; i < surf->x; i++, norm++) {
	len = fsqrt(norm->nx*norm->nx + norm->ny*norm->ny + norm->nz*norm->nz);
	norm->nx /= len;
	norm->ny /= len;
	norm->nz /= len;
	}
}

sl_compute_normals(sl_surface_t *surf)
{
 if (surf->geom_class == SURF_FULL) compute_normals_full(surf);
 else if (surf->geom_class = SURF_COMPACT) compute_normals_compact(surf);
}
