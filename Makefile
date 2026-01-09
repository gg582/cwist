CC = gcc
CFLAGS = -I./include -I./lib -I./lib/cjson -Wall -Wextra -pthread
LIBS = -pthread -lcjson

SRCS = src/sstring/sstring.c src/process/err/error.c src/http/http.c src/session/session_manager.c
OBJS = $(SRCS:.c=.o)
LIB_NAME = libcwist.a

PREFIX ?= /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

test: $(LIB_NAME) tests/test_sstring.c
	$(CC) $(CFLAGS) -o test_sstring tests/test_sstring.c $(LIB_NAME) $(LIBS)
	./test_sstring

test_http: $(LIB_NAME) tests/test_http.c
	$(CC) $(CFLAGS) -o test_http tests/test_http.c $(LIB_NAME) $(LIBS)
	./test_http

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(LIB_NAME)
	install -d $(LIBDIR)
	install -d $(INCLUDEDIR)/cwist
	install -d $(INCLUDEDIR)/cwist/err
	install -m 644 $(LIB_NAME) $(LIBDIR)
	install -m 644 include/cwist/*.h $(INCLUDEDIR)/cwist
	install -m 644 include/cwist/err/*.h $(INCLUDEDIR)/cwist/err

uninstall:
	rm -f $(LIBDIR)/$(LIB_NAME)
	rm -rf $(INCLUDEDIR)/cwist

clean:
	rm -f $(OBJS) $(LIB_NAME) test_sstring test_http
