all: sfs
sfsmaster: sfsmaster.o
	gcc sfsmaster.o -o sfsmaster -Wall -D_FILE_OFFSET_BITS=64 -g -pthread -lfuse -lrt -ldl
sfschunkserver: sfschunkserver.o
	gcc sfschunkserver.o -o sfschunkserver -Wall -D_FILE_OFFSET_BITS=64 -g -pthread -lfuse -lrt -ldl
sfsmetalogger.o: sfsmetalogger.o
	gcc sfsmetalogger.o -o sfsmetalogger -Wall -D_FILE_OFFSET_BITS=64 -g   -c -o simple_fuse.o simple_fuse.c
.PHONY : all
clean :
	rm  -f sfsmetalogger.o sfsmetalogger sfschunkserver.o sfschunkserver sfsmaster sfsmaster.o