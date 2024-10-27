CC = clang
CFLAGS = -O2 -Isrc
OUT = snbox
CFILES = $(shell find src -type f -name '*.c')
OBJECTS = $(CFILES:.c=.o)

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) -lcurl $(OBJECTS) -o $(OUT)
    
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUT)

install:
	sudo cp ./$(OUT) /usr/bin
	sudo chmod -w /usr/bin/$(OUT)