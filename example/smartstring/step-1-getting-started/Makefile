CC = gcc
CFLAGS = -I../../../include -I../../../lib -Wall -Wextra -lcjson

# Paths to the object files compiled in the root project
SMARTSTRING_OBJ = ../../../src/smartstring/smartstring.o
OBJS = $(SMARTSTRING_OBJ) $(CJSON_OBJ)

TARGET = getting-started

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET)
