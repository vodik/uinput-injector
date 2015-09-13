CFLAGS := -std=c11 -g \
	-Wall -Wextra -pedantic \
	-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

uinput-inject: uinput-inject.o uinput-key.o
clean:
	$(RM) uinput-inject

.PHONY: clean
