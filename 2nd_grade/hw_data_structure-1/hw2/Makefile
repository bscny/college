CC = g++
CFLAGS = -Wall -I. -O2

TEST_OBJS = $(O_DIR)/test_code.o $(O_DIR)/sort_functions.o
EXPERIMENT_1_OBJS = $(O_DIR)/experiment_1.o $(O_DIR)/sort_functions.o
EXPERIMENT_2_OBJS = $(O_DIR)/experiment_2.o $(O_DIR)/sort_functions.o
EXPERIMENT_3_OBJS = $(O_DIR)/experiment_3.o $(O_DIR)/sort_functions.o
SUPPORT_OBJS = $(O_DIR)/supportEx.o $(O_DIR)/sort_functions.o

O_DIR = dir_temp

EXEC_SUPP = Support
EXEC_TEST = Testfuncs
EXEC_EX1 = Ex1
EXEC_EX2 = Ex2
EXEC_EX3 = Ex3

all: $(EXEC_SUPP) $(EXEC_TEST) $(EXEC_EX1) $(EXEC_EX2) $(EXEC_EX3)

$(EXEC_SUPP): $(O_DIR) $(SUPPORT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SUPPORT_OBJS)

$(EXEC_TEST): $(O_DIR) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

$(EXEC_EX1): $(O_DIR) $(EXPERIMENT_1_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXPERIMENT_1_OBJS)

$(EXEC_EX2): $(O_DIR) $(EXPERIMENT_2_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXPERIMENT_2_OBJS)

$(EXEC_EX3): $(O_DIR) $(EXPERIMENT_3_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXPERIMENT_3_OBJS)

$(O_DIR):
	mkdir $@

clean:
	rm -rf $(EXEC_SUPP) $(EXEC_TEST) $(EXEC_EX1) $(EXEC_EX2) $(EXEC_EX3) *.o $(O_DIR)

$(O_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
