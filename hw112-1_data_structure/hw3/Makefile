CC = g++
CFLAGS = -Wall -g -I. -O2

O_DIR = dir_temp

DATA_OBJS = $(O_DIR)/data_generator.o
TEST_OBJS = $(O_DIR)/test_range_query.o $(O_DIR)/sorted_arr.o $(O_DIR)/arr_of_sorted_arrs.o $(O_DIR)/skip_list.o $(O_DIR)/backtrace.o
EXPERIMENT_OBJS = $(O_DIR)/experiment.o $(O_DIR)/sorted_arr.o $(O_DIR)/arr_of_sorted_arrs.o $(O_DIR)/skip_list.o
COMPARE_SL_OBJS = $(O_DIR)/compare_skip_list.o $(O_DIR)/skip_list.o
COMPARE_LL_OBJS = $(O_DIR)/compare_linked_list.o $(O_DIR)/skip_list.o $(O_DIR)/arr_of_sorted_arrs.o

EXEC_DATA = Get_Data
EXEC_TEST = My_test
EXEC_EX = Experiment
EXEC_CMP_SL = Compare_skip_list
EXEC_CMP_LL = Compare_linked_list

all: $(EXEC_DATA) $(EXEC_TEST) $(EXEC_EX) $(EXEC_CMP_SL) $(EXEC_CMP_LL)

$(EXEC_DATA): $(O_DIR) $(DATA_OBJS)
	$(CC) $(CFLAGS) -o $@ $(DATA_OBJS)

$(EXEC_TEST): $(O_DIR) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

$(EXEC_EX): $(O_DIR) $(EXPERIMENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXPERIMENT_OBJS)

$(EXEC_CMP_SL): $(O_DIR) $(COMPARE_SL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(COMPARE_SL_OBJS)

$(EXEC_CMP_LL): $(O_DIR) $(COMPARE_LL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(COMPARE_LL_OBJS)

$(O_DIR):
	mkdir $@

clean:
	rm -rf $(EXEC_DATA) $(EXEC_TEST) $(EXEC_EX) $(EXEC_CMP_SL) $(EXEC_CMP_LL) $(O_DIR) 

$(O_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
