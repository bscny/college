#include <vector>
using namespace std;

inline void swap(int &a, int &b);

void insertion_sort(vector<int> &arr, int start_index, int end_index);

void merge_sort_recursive(vector<int> &arr, int start_index, int end_index);

void merge_sort_iterative(vector<int> &arr, int start_index, int end_index);

void qsort_lomuto_recursive(vector<int> &arr, int start_index, int end_index);

void qsort_lomuto_iterative(vector<int> &arr, int start_index, int end_index);

void qsort_hoare_recursive(vector<int> &arr, int start_index, int end_index);

void qsort_3way_recursive(vector<int> &arr, int start_index, int end_index);

void qsort_hoare_iterative(vector<int> &arr, int start_index, int end_index);

void counting_sort(vector<int> &arr, int start_index, int end_index);
