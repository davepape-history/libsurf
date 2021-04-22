
#define CHECK_POINTER(p,name) { if (!p) {\
	    fprintf(stderr,"draw_surface error: %s pointer is null\n",name);\
	    return; } }

static void draw_surf_lighted(sl_surface_t *surf)
{
 sl_point_t *p;
 sl_norm_t *n;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 for (j=0, p=surf->geom.full_geom, n=surf->norm; j < surf->y-1; j++) {
    bgntmesh();
    for (i=0; i < maxi; i++, p++, n++) {
	n3f((float *) n);
	v3f((float *) p);
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 maxi = surf->x;
 for (j=0, p=surf->geom.full_geom; j < surf->y-1; j++) {
    bgntmesh();
    for (i=0; i < maxi; i++, p++) {
	v3f((float *) p);
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_color_surf_lighted(sl_surface_t *surf)
{
 sl_point_t *p;
 sl_norm_t *n;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->norm,"norm");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 for (j=0, p=surf->geom.full_geom, n=surf->norm, c=surf->color;
	j < surf->y-1; j++) {
    bgntmesh();
    for (i=0; i < maxi; i++, p++, n++, c++) {
	cpack(*c);
	n3f((float *) n);
	v3f((float *) p);
	cpack(*(c+maxi));
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_color_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 for (j=0, p=surf->geom.full_geom, c=surf->color; j < surf->y-1; j++) {
    bgntmesh();
    for (i=0; i < maxi; i++, p++, c++) {
	cpack(*c);
	v3f((float *) p);
	cpack(*(c+maxi));
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_tex_surf_lighted(sl_surface_t *surf)
{
 sl_point_t *p;
 sl_norm_t *n;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->norm,"norm");
 maxi = surf->x;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, p=surf->geom.full_geom, n=surf->norm; j < surf->y-1; j++, t[1]+=tdy) {
    t[0] = surf->tex_basex;
    bgntmesh();
    for (i=0; i<maxi; i++, p++, n++, t[0]+=tdx) {
	t2f(t);
	n3f((float *) n);
	v3f((float *) p);
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_tex_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 maxi = surf->x;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, p=surf->geom.full_geom; j < surf->y-1; j++, t[1]+=tdy) {
    t[0] = surf->tex_basex;
    bgntmesh();
    for (i=0; i<maxi; i++, p++, t[0]+=tdx) {
	t2f(t);
	v3f((float *) p);
	t[1] += tdy; t2f(t); t[1] -= tdy;
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_color_tex_surf_lighted(sl_surface_t *surf)
{
 sl_point_t *p;
 sl_norm_t *n;
 ULONG *c;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_surf_lighted(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->norm,"norm");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, p=surf->geom.full_geom, n=surf->norm, c=surf->color;
	j < surf->y-1; j++, t[1]+=tdy) {
    t[0] = surf->tex_basex;
    bgntmesh();
    for (i=0; i<maxi; i++, p++, n++, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	n3f((float *) n);
	v3f((float *) p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_color_tex_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 ULONG *c;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 t[1] = surf->tex_basey;
 tdx = surf->tex_dx;
 tdy = surf->tex_dy;
 for (j=0, p=surf->geom.full_geom, c=surf->color;
	j < surf->y-1; j++, t[1]+=tdy) {
    t[0] = surf->tex_basex;
    bgntmesh();
    for (i=0; i<maxi; i++, p++, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	v3f((float *) p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	v3f((float *) (p+maxi));
	}
    endtmesh();
    }
}

static void draw_color_wire_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 ULONG *c;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_color_wire_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 CHECK_POINTER(surf->color,"color");
 maxi = surf->x;
 maxj = surf->y;
 for (j=0, p=surf->geom.full_geom, c = surf->color; j < maxj; j++) {
    bgnline();
    for (i=0; i < maxi; i++, p++, c++) {
	cpack(*c);
	v3f((float *) p);
	}
    endline();
    }
 for (i=0; i < maxi; i++) {
    p = surf->geom.full_geom + i;
    c = surf->color + i;
    bgnline();
    for (j=0; j < maxj; j++, p+=maxi, c+=maxi) {
	cpack(*c);
	v3f((float *) p);
	}
    endline();
    }
}

static void draw_wire_surf(sl_surface_t *surf)
{
 sl_point_t *p;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_wire_surf(%x)\n",surf);
#endif
 CHECK_POINTER(surf->geom.full_geom,"geom");
 maxi = surf->x;
 maxj = surf->y;
 for (j=0, p=surf->geom.full_geom; j < maxj; j++) {
    bgnline();
    for (i=0; i < maxi; i++, p++) {
	v3f((float *) p);
	}
    endline();
    }
 for (i=0; i < maxi; i++) {
    p = surf->geom.full_geom + i;
    bgnline();
    for (j=0; j < maxj; j++, p+=maxi) {
	v3f((float *) p);
	}
    endline();
    }
}

#undef CHECK_POINTER
