CC = gcc

CFLAGS = -std=c11 -Wall -Iinclude

SRCS = src/main.c src/inputChecker.c src/repertoire.c
OBJS = $(SRCS:.c=.o)

TARGET = projetRepertoire

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@