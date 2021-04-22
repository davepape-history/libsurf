
#define CHECK_POINTER(p,name) { if (!p) {\
	     fprintf(stderr,"draw_surface error: %s pointer is null\n",name);\
	     return; } }

static void draw_comp_surf_lighted(sl_surface_t *surf)
{
 float p[3],basex,basez,dx,dy,dz;
 sl_norm_t *n;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_comp_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap, n=surf->norm;
	j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, z++, n++, p[0]+=dx) {
	n3f((float *) n);
	p[2] = basez + (*z)*dz;
	v3f(p);
	n3f((float *) (n+maxi));
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_comp_surf(sl_surface_t *surf)
{
 float p[3],basex,basez,dx,dy,dz;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap; j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, z++, p[0]+=dx) {
	p[2] = basez + (*z)*dz;
	v3f(p);
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_comp_surf_lighted(sl_surface_t *surf)
{
 float p[3],basex,basez,dx,dy,dz;
 sl_norm_t *n;
 ULONG *c;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_comp_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->color,"color");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap, n=surf->norm, c=surf->color;
	j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, z++, n++, c++, p[0]+=dx) {
	cpack(*c);
	n3f((float *) n);
	p[2] = basez + (*z)*dz;
	v3f(p);
	cpack(*(c+maxi));
	n3f((float *) (n+maxi));
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_comp_surf(sl_surface_t *surf)
{
 float p[3],basex,basez,dx,dy,dz;
 ULONG *c;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap, c=surf->color;
	j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, z++, c++, p[0]+=dx) {
	cpack(*c);
	p[2] = basez + (*z)*dz;
	v3f(p);
	cpack(*(c+maxi));
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_tex_comp_surf_lighted(sl_surface_t *surf)
{
 float p[3],t[2],basex,basez,dx,dy,dz,tdx,tdy;
 sl_norm_t *n;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_comp_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, z=surf->geom.compact_geom->zmap, n=surf->norm;
	j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, z++, n++, p[0]+=dx, t[0]+=tdx) {
	t2f(t);
	n3f((float *) n);
	p[2] = basez + (*z)*dz;
	v3f(p);
	t[1] += tdy;
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	t2f(t);
	n3f((float *) (n+maxi));
	v3f(p);
	t[1] -= tdy;
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_tex_comp_surf(sl_surface_t *surf)
{
 float p[3],t[2],basex,basez,dx,dy,dz,tdx,tdy;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, z=surf->geom.compact_geom->zmap; j < surf->y-1;
		j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, z++, p[0]+=dx, t[0] += tdx) {
	t2f(t);
	p[2] = basez + (*z)*dz;
	v3f(p);
	t[1] += tdy;
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	t2f(t);
	v3f(p);
	t[1] -= tdy;
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_tex_comp_surf_lighted(sl_surface_t *surf)
{
 float p[3],t[2],basex,basez,dx,dy,dz,tdx,tdy;
 sl_norm_t *n;
 ULONG *c;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_comp_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->color,"color");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, z=surf->geom.compact_geom->zmap, n=surf->norm, c=surf->color;
	j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, z++, n++, p[0]+=dx, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	n3f((float *) n);
	p[2] = basez + (*z)*dz;
	v3f(p);
	t[1] += tdy;
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	cpack(*(c+maxi));
	t2f(t);
	n3f((float *) (n+maxi));
	v3f(p);
	t[1] -= tdy;
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_tex_comp_surf(sl_surface_t *surf)
{
 float p[3],t[2],basex,basez,dx,dy,dz,tdx,tdy;
 ULONG *c;
 UCHAR *z;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 basex = surf->geom.compact_geom->basex;
 p[1] = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, z=surf->geom.compact_geom->zmap, c=surf->color;
	j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, z++, p[0]+=dx, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	p[2] = basez + (*z)*dz;
	v3f(p);
	t[1] += tdy;
	p[1] += dy;
	p[2] = basez + (*(z+maxi))*dz;
	cpack(*(c+maxi));
	t2f(t);
	v3f(p);
	t[1] -= tdy;
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_wire_comp_surf(sl_surface_t *surf)
{
 float p[3],basex,basey,basez,dx,dy,dz;
 ULONG *c;
 UCHAR *z;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_color_wire_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 maxj = surf->y;
 basex = surf->geom.compact_geom->basex;
 p[1] = basey = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap, c = surf->color; j < maxj;
	j++, p[1]+=dy) {
    bgnline();
    for (i=0, p[0] = basex; i < maxi; i++, z++, c++, p[0]+=dx) {
	cpack(*c);
	p[2] = basez + (*z)*dz;
	v3f(p);
	}
    endline();
    }
 for (i=0, p[0]=basex; i < maxi; i++, p[0]+=dx) {
    z = surf->geom.compact_geom->zmap + i;
    c = surf->color + i;
    bgnline();
    for (j=0, p[1]=basey; j < maxj; j++, z+=maxi, c+=maxi, p[1]+=dy) {
	cpack(*c);
	p[2] = basez + (*z)*dz;
	v3f(p);
	}
    endline();
    }
}

static void draw_wire_comp_surf(sl_surface_t *surf)
{
 float p[3],basex,basey,basez,dx,dy,dz;
 UCHAR *z;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_wire_comp_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.compact_geom,"compact_geom");
 maxi = surf->x;
 maxj = surf->y;
 basex = surf->geom.compact_geom->basex;
 p[1] = basey = surf->geom.compact_geom->basey;
 basez = surf->geom.compact_geom->basez;
 dx = surf->geom.compact_geom->dx;
 dy = surf->geom.compact_geom->dy;
 dz = surf->geom.compact_geom->dz;
 for (j=0, z=surf->geom.compact_geom->zmap; j < maxj; j++, p[1]+=dy) {
    bgnline();
    for (i=0, p[0] = basex; i < maxi; i++, z++, p[0]+=dx) {
	p[2] = basez + (*z)*dz;
	v3f(p);
	}
    endline();
    }
 for (i=0, p[0]=basex; i < maxi; i++, p[0]+=dx) {
    z = surf->geom.compact_geom->zmap + i;
    bgnline();
    for (j=0, p[1]=basey; j < maxj; j++, z+=maxi, p[1]+=dy) {
	p[2] = basez + (*z)*dz;
	v3f(p);
	}
    endline();
    }
}

#undef CHECK_POINTER
