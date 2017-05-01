## NeHe's GLframe ported to SDL
## Fabio 'SnowDruid' Franchello
## snowdruid@tiscalinet.it

## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFlags = -Wall -g -DLINUX `sdl-config --cflags`
LFLAGS = `sdl-config --libs` -lGL -lGLU

HEADERFILES = main.h

OBJS = main.o app.o error.o

SRCS = main.cpp app.cpp error.cpp

all : GLframe
	chmod g+rw *.o

clean :
	rm -rf GLframe *.o

GLframe : ${OBJS}
	$(LD) -o $@ ${OBJS} ${LFLAGS}

depend :
	makedepend ${SRCS}

# DO NOT DELETE

main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/string.h /usr/include/xlocale.h
main.o: /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/inttypes.h
main.o: /usr/include/stdint.h /usr/include/bits/wchar.h /usr/include/GL/glu.h
main.o: main.h
app.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
app.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
app.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
app.o: /usr/include/bits/typesizes.h /usr/include/libio.h
app.o: /usr/include/_G_config.h /usr/include/wchar.h
app.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
app.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
app.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
app.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
app.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
app.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
app.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
app.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
app.o: /usr/include/math.h /usr/include/bits/huge_val.h
app.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
app.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
app.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
app.o: /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/inttypes.h
app.o: /usr/include/stdint.h /usr/include/bits/wchar.h /usr/include/GL/glu.h
app.o: /usr/include/assert.h main.h
error.o: /usr/include/stdio.h /usr/include/features.h
error.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
error.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
error.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
error.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
error.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
error.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
error.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
error.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
error.o: /usr/include/sys/types.h /usr/include/time.h
error.o: /usr/include/sys/select.h /usr/include/bits/select.h
error.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
error.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
error.o: /usr/include/alloca.h main.h
