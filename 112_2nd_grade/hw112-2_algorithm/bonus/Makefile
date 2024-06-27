CC = gcc
CFLAGS = -Wall -g -I.

O_DIR = dir_temp

OBJS = $(O_DIR)/bonus.o $(O_DIR)/backtrace.o

EXEC = out

all: $(EXEC)

$(EXEC): $(O_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(O_DIR):
	mkdir $@

clean:
	rm -rf $(EXEC) $(O_DIR) 

$(O_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
