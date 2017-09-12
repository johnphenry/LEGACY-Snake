# This makefile demonstrates a static link to SDl2.
# use sdl2-config —-static-libs to get the extra libraries.
# however, do not use -lSDL2 as the link, because that becomes dynamic, and makes it a nightmare to distribute.
# Instead, simply place libSDl2.a into the directory, or setup a directory path.
all:
	gcc snake.c LIB.c -o snake libSDL2.a -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit
