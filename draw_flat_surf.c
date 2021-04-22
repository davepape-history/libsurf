
#define CHECK_POINTER(p,name) { if (!p) {\
	    fprintf(stderr,"draw_surface error: %s pointer is null\n",name);\
	    return; } }

static void draw_flat_surf_lighted(sl_surface_t *surf)
{
 float p[3],basex,dx,dy;
 sl_norm_t *n;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_flat_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0, n=surf->norm; j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, n++, p[0]+=dx) {
	n3f((float *) n);
	v3f(p);
	n3f((float *) (n+maxi));
	p[1] += dy;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_flat_surf(sl_surface_t *surf)
{
 float p[4],basex,dx,dy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0; j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, p[0]+=dx) {
	v3f(p);
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_flat_surf_lighted(sl_surface_t *surf)
{
 float p[3],basex,dx,dy;
 sl_norm_t *n;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_flat_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->color,"color");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0, n=surf->norm, c=surf->color; j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, n++, c++, p[0]+=dx) {
	cpack(*c);
	n3f((float *) n);
	v3f(p);
	cpack(*(c+maxi));
	n3f((float *) (n+maxi));
	p[1] += dy;
	v3f(p);
	p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_flat_surf(sl_surface_t *surf)
{
 float p[4],basex,dx,dy;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0, c=surf->color; j < surf->y-1; j++, p[1]+=dy) {
    bgntmesh();
    for (i=0, p[0]=basex; i < maxi; i++, c++, p[0]+=dx) {
	cpack(*c);
	v3f(p);
	cpack(*(c+maxi));
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_tex_flat_surf_lighted(sl_surface_t *surf)
{
 float p[3],t[2],basex,dx,dy,tdx,tdy;
 sl_norm_t *n;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_flat_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, n=surf->norm; j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, n++, p[0]+=dx, t[0]+=tdx) {
	t2f(t);
	n3f((float *) n);
	v3f(p);
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_tex_flat_surf(sl_surface_t *surf)
{
 float p[3],t[2],basex,dx,dy,tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0; j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, p[0]+=dx, t[0]+=tdx) {
	t2f(t);
	v3f(p);
	t[1] += tdy;
	t2f(t); t[1] -= tdy;
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_tex_flat_surf_lighted(sl_surface_t *surf)
{
 float p[3],t[2],basex,dx,dy,tdx,tdy;
 sl_norm_t *n;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_flat_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->color,"color");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, n=surf->norm, c=surf->color;
	j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, n++, p[0]+=dx, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	n3f((float *) n);
	v3f(p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_tex_flat_surf(sl_surface_t *surf)
{
 float p[3],t[2],basex,dx,dy,tdx,tdy;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 basex = surf->geom.flat_geom->basex;
 p[1] = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 t[0] = surf->tex_basex;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, c=surf->color; j < surf->y-1; j++, p[1]+=dy, t[1]+=tdy) {
    bgntmesh();
    for (i=0, p[0]=basex; i<maxi; i++, p[0]+=dx, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	v3f(p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	p[1] += dy; v3f(p); p[1] -= dy;
	}
    endtmesh();
    }
}

static void draw_color_wire_flat_surf(sl_surface_t *surf)
{
 float p[3],basex,basey,dx,dy;
 ULONG *c;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_color_wire_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 maxj = surf->y;
 basex = surf->geom.flat_geom->basex;
 p[1] = basey = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0, c = surf->color; j < maxj; j++, p[1]+=dy) {
    bgnline();
    for (i=0, p[0] = basex; i < maxi; i++, c++, p[0]+=dx) {
	cpack(*c);
	v3f(p);
	}
    endline();
    }
 for (i=0, p[0]=basex; i < maxi; i++, p[0]+=dx) {
    c = surf->color + i;
    bgnline();
    for (j=0, p[1]=basey; j < maxj; j++, c+=maxi, p[1]+=dy) {
	cpack(*c);
	v3f(p);
	}
    endline();
    }
}

static void draw_wire_flat_surf(sl_surface_t *surf)
{
 float p[3],basex,basey,dx,dy;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_wire_flat_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.flat_geom,"flat_geom");
 maxi = surf->x;
 maxj = surf->y;
 basex = surf->geom.flat_geom->basex;
 p[1] = basey = surf->geom.flat_geom->basey;
 p[2] = surf->geom.flat_geom->basez;
 dx = surf->geom.flat_geom->dx;
 dy = surf->geom.flat_geom->dy;
 for (j=0; j < maxj; j++, p[1]+=dy) {
    bgnline();
    for (i=0, p[0] = basex; i < maxi; i++, p[0]+=dx) {
	v3f(p);
	}
    endline();
    }
 for (i=0, p[0]=basex; i < maxi; i++, p[0]+=dx) {
    bgnline();
    for (j=0, p[1]=basey; j < maxj; j++, p[1]+=dy) {
	v3f(p);
	}
    endline();
    }
}

#undef CHECK_POINTER
