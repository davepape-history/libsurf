CFLAGS = -O2 -I$(HOME)/lib
LINKFLAGS = -O4

LIBOBJS = draw.o geom.o transform.o norms.o texmaps.o

libsurf.a: $(LIBOBJS)
	ar srv libsurf.a $?

draw.o: draw.c draw_flat_surf.c draw_full_surf.c draw_compact_surf.c draw_full_globe.c

