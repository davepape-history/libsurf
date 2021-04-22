
#define CHECK_POINTER(p,name) { if (!p) {\
	    fprintf(stderr,"draw_surface error: %s pointer is null\n",name);\
	    return; } }

static void draw_globe_lighted(sl_surface_t *globe)
{
 sl_point_t *p;
 sl_norm_t *n;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_globe_lighted(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->norm,"norm");
 maxi = globe->x;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, n=globe->norm; j < globe->y-1; j++)
    for (i=0; i < maxi; i++, p++, n++) {
	n3f((float *) n);
	v3f((float *) p);
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
 endtmesh();
}

static void draw_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 maxi = globe->x;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom; j < globe->y-1; j++)
    for (i=0; i < maxi; i++, p++) {
	v3f((float *) p);
	v3f((float *) (p+maxi));
	}
 endtmesh();
}

static void draw_color_globe_lighted(sl_surface_t *globe)
{
 sl_point_t *p;
 sl_norm_t *n;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_globe_lighted(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->norm,"norm");
 CHECK_POINTER(globe->color,"color");
 maxi = globe->x;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, n=globe->norm, c=globe->color;
	j < globe->y-1; j++)
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

static void draw_color_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 ULONG *c;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->color,"color");
 maxi = globe->x;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, c=globe->color; j < globe->y-1; j++)
    for (i=0; i < maxi; i++, p++, c++) {
	cpack(*c);
	v3f((float *) p);
	cpack(*(c+maxi));
	v3f((float *) (p+maxi));
	}
 endtmesh();
}

static void draw_tex_globe_lighted(sl_surface_t *globe)
{
 sl_point_t *p;
 sl_norm_t *n;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_globe_lighted(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->norm,"norm");
 maxi = globe->x;
 t[0] = globe->tex_basex;
 t[1] = globe->tex_basey;
 tdx = globe->tex_dx;
 tdy = globe->tex_dy;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, n=globe->norm; j < globe->y-1; j++) {
    for (i=0, t[0]=globe->tex_basex; i<maxi; i++, p++, n++, t[0] += tdx) {
	t2f(t);
	n3f((float *) n);
	v3f((float *) p);
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    t2f(t);
    n3f((float *) (n-maxi));
    v3f((float *) (p-maxi));
    t[1] += tdy; t2f(t);
    n3f((float *) n);
    v3f((float *) p);
    }
 endtmesh();
}

static void draw_tex_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_tex_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 maxi = globe->x;
 t[0] = globe->tex_basex;
 t[1] = globe->tex_basey;
 tdx = globe->tex_dx;
 tdy = globe->tex_dy;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom; j < globe->y-1; j++) {
    for (i=0, t[0]=globe->tex_basex; i<maxi; i++, p++, t[0]+=tdx) {
	t2f(t);
	v3f((float *) p);
	t[1] += tdy; t2f(t); t[1] -= tdy;
	v3f((float *) (p+maxi));
	}
    t2f(t);
    v3f((float *) (p-maxi));
    t[1] += tdy; t2f(t);
    v3f((float *) p);
    }
 endtmesh();
}

static void draw_color_tex_globe_lighted(sl_surface_t *globe)
{
 sl_point_t *p;
 sl_norm_t *n;
 ULONG *c;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_globe_lighted(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->norm,"norm");
 CHECK_POINTER(globe->color,"color");
 maxi = globe->x;
 t[0] = globe->tex_basex;
 t[1] = globe->tex_basey;
 tdx = globe->tex_dx;
 tdy = globe->tex_dy;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, n=globe->norm, c=globe->color;
	j < globe->y-1; j++) {
    for (i=0, t[0]=globe->tex_basex; i<maxi; i++, p++, n++, c++, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	n3f((float *) n);
	v3f((float *) p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	n3f((float *) (n+maxi));
	v3f((float *) (p+maxi));
	}
    cpack(*(c-maxi));
    t2f(t);
    n3f((float *) (n-maxi));
    v3f((float *) (p-maxi));
    cpack(*c);
    t[1] += tdy; t2f(t);
    n3f((float *) n);
    v3f((float *) p);
    }
 endtmesh();
}

static void draw_color_tex_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 ULONG *c;
 float t[2],tdx,tdy;
 int i,j,maxi;
#ifdef DEBUG
printf("draw_color_tex_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->color,"color");
 maxi = globe->x;
 t[0] = globe->tex_basex;
 t[1] = globe->tex_basey;
 tdx = globe->tex_dx;
 tdy = globe->tex_dy;
 bgntmesh();
 for (j=0, p=globe->geom.full_geom, c=globe->color; j < globe->y-1; j++) {
    for (i=0, t[0]=globe->tex_basex; i<maxi; i++, p++, c++, t[0]+=tdx) {
	cpack(*c);
	t2f(t);
	v3f((float *) p);
	cpack(*(c+maxi));
	t[1] += tdy; t2f(t); t[1] -= tdy;
	v3f((float *) (p+maxi));
	}
    cpack(*(c-maxi));
    t2f(t);
    v3f((float *) (p-maxi));
    cpack(*c);
    t[1] += tdy; t2f(t);
    v3f((float *) p);
    }
 endtmesh();
}

static void draw_color_wire_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 ULONG *c;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_color_wire_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 CHECK_POINTER(globe->color,"color");
 maxi = globe->x;
 maxj = globe->y;
 for (j=0, p=globe->geom.full_geom, c = globe->color; j < maxj; j++) {
    bgnline();
    for (i=0; i < maxi; i++, p++, c++) {
	cpack(*c);
	v3f((float *) p);
	}
    cpack(*(c-maxi));
    v3f((float *) (p-maxi));
    endline();
    }
 for (i=0; i < maxi; i++) {
    p = globe->geom.full_geom + i;
    c = globe->color + i;
    bgnline();
    for (j=0; j < maxj; j++, p+=maxi, c+=maxi) {
	cpack(*c);
	v3f((float *) p);
	}
    endline();
    }
}

static void draw_wire_globe(sl_surface_t *globe)
{
 sl_point_t *p;
 int i,j,maxi,maxj;
#ifdef DEBUG
printf("draw_wire_globe(%x)\n",globe);
#endif
 CHECK_POINTER(globe->geom.full_geom,"geom");
 maxi = globe->x;
 maxj = globe->y;
 for (j=0, p=globe->geom.full_geom; j < maxj; j++) {
    bgnline();
    for (i=0; i < maxi; i++, p++) {
	v3f((float *) p);
	}
    v3f((float *) (p-maxi));
    endline();
    }
 for (i=0; i < maxi; i++) {
    p = globe->geom.full_geom + i;
    bgnline();
    for (j=0; j < maxj; j++, p+=maxi) {
	v3f((float *) p);
	}
    endline();
    }
}

#undef CHECK_POINTER
