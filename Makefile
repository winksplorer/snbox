CC := clang
CFLAGS = -O2 -Isrc -Wall -Wextra -pedantic -Wno-newline-eof -I/opt/homebrew/Cellar/libarchive/3.7.7/include
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

install2:
	sudo cp ./$(OUT) /usr/local/bin
	sudo chmod -w /usr/local/bin/$(OUT)