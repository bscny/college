CC = g++
CFLAGS = -Wall -g -I. -lm

S_DIR = ..
O_DIR = obj_dir

OBJS = $(O_DIR)/main.o

EXEC = out

all: $(EXEC)

$(EXEC): $(O_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(O_DIR):
	mkdir $@

clean:
	rm -rf $(EXEC) $(O_DIR) 

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
