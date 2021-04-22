#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <gl.h>
#include "surfd.h"

#include "draw_full_surf.c"
#include "draw_full_globe.c"
#include "draw_compact_surf.c"
#include "draw_flat_surf.c"

void sl_draw_surface(sl_surface_t *surf,Boolean solid,Boolean vcolor,
			Boolean lighted,Boolean texmap)
{
 switch (surf->geom_class) {
   case SURF_FULL:
	if (surf->globe) {
	   if (solid) {
		if (vcolor) {
		    if (lighted) {
			if (texmap) draw_color_tex_globe_lighted(surf);
			else draw_color_globe_lighted(surf);
			}
		    else {
			if (texmap) draw_color_tex_globe(surf);
			else draw_color_globe(surf);
			}
		    }
		else {
		    if (lighted) {
			if (texmap) draw_tex_globe_lighted(surf);
			else draw_globe_lighted(surf);
			}
		    else {
			if (texmap) draw_tex_globe(surf);
			else draw_globe(surf);
			}
		    }
		}
	   else {
		if (vcolor) draw_color_wire_globe(surf);
		else draw_wire_globe(surf);
		}
	   }

	else {
	   if (solid) {
		if (vcolor) {
		    if (lighted) {
			if (texmap) draw_color_tex_surf_lighted(surf);
			else draw_color_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_color_tex_surf(surf);
			else draw_color_surf(surf);
			}
		    }
		else {
		    if (lighted) {
			if (texmap) draw_tex_surf_lighted(surf);
			else draw_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_tex_surf(surf);
			else draw_surf(surf);
			}
		    }
		}
	   else {
		if (vcolor) draw_color_wire_surf(surf);
		else draw_wire_surf(surf);
		}
	   }
	break;

   case SURF_COMPACT:
	   if (solid) {
		if (vcolor) {
		    if (lighted) {
			if (texmap) draw_color_tex_comp_surf_lighted(surf);
			else draw_color_comp_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_color_tex_comp_surf(surf);
			else draw_color_comp_surf(surf);
			}
		    }
		else {
		    if (lighted) {
			if (texmap) draw_tex_comp_surf_lighted(surf);
			else draw_comp_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_tex_comp_surf(surf);
			else draw_comp_surf(surf);
			}
		    }
		}
	   else {
		if (vcolor) draw_color_wire_comp_surf(surf);
		else draw_wire_comp_surf(surf);
		}
	   break;

   case SURF_FLAT:
	   if (solid) {
		if (vcolor) {
		    if (lighted) {
			if (texmap) draw_color_tex_flat_surf_lighted(surf);
			else draw_color_flat_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_color_tex_flat_surf(surf);
			else draw_color_flat_surf(surf);
			}
		    }
		else {
		    if (lighted) {
			if (texmap) draw_tex_flat_surf_lighted(surf);
			else draw_flat_surf_lighted(surf);
			}
		    else {
			if (texmap) draw_tex_flat_surf(surf);
			else draw_flat_surf(surf);
			}
		    }
		}
	   else {
		if (vcolor) draw_color_wire_flat_surf(surf);
		else draw_wire_flat_surf(surf);
		}
	   break;
   default: fprintf(stderr,"WARNING: draw_surface: bad geom_class (%d)\n",surf->geom_class);
	    break;
   }
}
