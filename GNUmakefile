# Program output file
OUT := snbox

# Compiler & options. Prefer clang if available, otherwise GCC
CC := $(shell command -v clang >/dev/null 2>&1 && echo clang || echo gcc)
CFLAGS := -O2 -Isrc -Wall -Wextra -pedantic -Wno-newline-eof -I/opt/homebrew/Cellar/libarchive/3.7.7/include
EXT_CFLAGS :=

# Linker & options.
LD := $(CC)
LDFLAGS := -lcurl -larchive
EXT_LDFLAGS :=

CFILES = $(shell find src -type f -name '*.c')
OBJECTS = $(CFILES:.c=.o)

all: $(OUT)

$(OUT): $(OBJECTS)
	$(LD) $(LDFLAGS) $(EXT_LDFLAGS) $(OBJECTS) -o $(OUT)
    
%.o: %.c
	$(CC) $(CFLAGS) $(EXT_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUT)

install:
	install -m 755 $(OUT) /usr/bin

install2:
	install -m 755 $(OUT) /usr/local/bin
