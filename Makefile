CFLAGS := -std=c11 -g \
	-Wall -Wextra -pedantic \
	-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

uinput-inject: uinput-inject.o
uinput-inject.o: uinput-inject.c config.h
clean:
	$(RM) uinput-inject

.PHONY: clean
