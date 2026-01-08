CC = gcc
CFLAGS = -I./include -I./lib -Wall -Wextra -lcjson
LIBS = -lcjson

SRCS = src/smartstring/smartstring.c src/process/err/error.c src/http/http.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)

test: $(OBJS) tests/test_smartstring.c
	$(CC) $(CFLAGS) -o test_smartstring tests/test_smartstring.c $(OBJS) $(LIBS)
	./test_smartstring

test_http: $(OBJS) tests/test_http.c
	$(CC) $(CFLAGS) -o test_http tests/test_http.c $(OBJS) $(LIBS)
	./test_http

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) test_smartstring test_http
