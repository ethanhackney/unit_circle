CFLAGS  = -std=c++11 -Wall -Werror -pedantic
SRC     = main.cc
CC      = g++

all: $(SRC)
	$(CC) $(CFLAGS) $^
