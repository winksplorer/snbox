CC := clang
CFLAGS = -O2 -Isrc -g -Wall -Wextra -pedantic -Wno-newline-eof
OUT = snbox
CFILES = $(shell find src -type f -name '*.c')
OBJECTS = $(CFILES:.c=.o)

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) -lcurl -larchive $(OBJECTS) -o $(OUT)
    
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUT)

install:
	sudo cp ./$(OUT) /usr/bin
	sudo chmod -w /usr/bin/$(OUT)