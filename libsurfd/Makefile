CFLAGS = -O2 -I$(HOME)/lib
LINKFLAGS = -O4

LIBOBJS = draw.o geom.o transform.o norms.o texmaps.o

libsurfd.a: $(LIBOBJS)
	ar srv libsurfd.a $?

draw.o: draw.c draw_flat_surf.c draw_full_surf.c draw_compact_surf.c draw_full_globe.c

