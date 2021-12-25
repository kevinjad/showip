all: showip

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

showip: Makefile showip.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) showip.c

clean:
	rm -f showip

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	./showip

