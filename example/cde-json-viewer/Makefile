CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lcjson -lcwist

SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = cde-viewer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
