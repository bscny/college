import matplotlib
matplotlib.use('Agg')  # Non-interactive backend suitable for saving plots

import matplotlib.pyplot as plt

MAX_POWER_N = 21
LINE_NUM = 6
INSSORT = 0
MSORT = 1
LOMUTO = 2
HOARE = 3
THREE_WAY = 4
COUNTSORT = 5

def main():
	x_mark = []
	y_mark = []
	x_data = []
	y_datas = [[],[],[],[],[],[]]

#set x data
	for i in range(10, MAX_POWER_N + 1):
		x_data.append(pow(2, i))

#set y data
	for j in range(10, MAX_POWER_N+ 1):
		for i in range(0, LINE_NUM):
			temp = input()
			y_datas[i].append(float(temp))
	
#graphing
	fig_size = 100
	dot_size = 16
	line_size = 7.5
	font_size = 100
	file_name = "FIG_experiment 1-extra.png"

#set y interval
	max_data = 0
	min_data = 10000
	mark_num = 30
	for i in range(0, LINE_NUM):
		if(i == INSSORT):
			continue
		if(max_data < float( max(y_datas[i]) ) ):
			max_data = float( max(y_datas[i]) )
		if(min_data > float( min(y_datas[i]) ) ):
			min_data = float( min(y_datas[i]) )

	y_interval = (max_data - min_data) / mark_num
	for i in range(0, mark_num + 1):
		y_mark.append(i * y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.rcParams['axes.linewidth'] = line_size * 0.5
#plt.plot(x_data, y_datas[INSSORT], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[MSORT], 'r-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[LOMUTO], 'k-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[HOARE], 'y-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[THREE_WAY], 'c-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[COUNTSORT], 'm-o', lw = line_size, ms = dot_size)
	plt.xlabel(f"n \nfrom 2^10 to 2^{MAX_POWER_N}", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title("EXPERIMENT 1", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2, 10), pow(2, MAX_POWER_N) * 1.001])
	plt.ylim([0, max_data + y_interval])
#plt.legend(["Insertion", "Merge", "Lomuto qsort", "Hoare qsort", "3-way qsort", "counting"], fontsize = font_size)
	plt.legend(["Merge", "Lomuto qsort", "Hoare qsort", "3-way qsort", "counting"], fontsize = font_size)

	plt.savefig(file_name)

main()
