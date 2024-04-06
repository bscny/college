CC = g++
CFLAGS = -Wall -g -I.

O_DIR = dir_temp

EXPERIMENT_OBJS = $(O_DIR)/experiments.o 
COMPARE_OBJS = $(O_DIR)/compare.o 

EXEC_EX = Experiment
EXEC_CMP = Compare

all: $(EXEC_EX) $(EXEC_CMP)

$(EXEC_EX): $(O_DIR) $(EXPERIMENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXPERIMENT_OBJS)

$(EXEC_CMP): $(O_DIR) $(COMPARE_OBJS)
	$(CC) $(CFLAGS) -o $@ $(COMPARE_OBJS)

$(O_DIR):
	mkdir $@

clean:
	rm -rf $(EXEC_EX) $(EXEC_CMP) $(O_DIR) 

$(O_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
