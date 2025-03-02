import matplotlib.pyplot as plt

MAX_POWER_K = 20
POW_N = 20
LINE_NUM = 3
SKIP_LIST = 0
SKIP_LIST_P = 1
SKIP_LIST_C_V = 2

def main():
	x_mark = []
	y_mark = []
	x_data = []
	y_datas = [[],[],[]]

#set x data
	for i in range(0, MAX_POWER_K + 1):
		x_data.append(pow(2, i))

#set y data
	for j in range(0, MAX_POWER_K + 1):
		for i in range(0, LINE_NUM):
			temp = input()
			y_datas[i].append(float(temp))
	
#graphing
	fig_size = 100
	dot_size = 16
	line_size = 7.5
	font_size = 100
	file_name = f"FIG_experiment compare n=2^{POW_N}.png"

#set y interval
	max_data = 0
	min_data = 10000
	mark_num = 30
	for i in range(0, LINE_NUM):
		if(max_data < float( max(y_datas[i]) ) ):
			max_data = float( max(y_datas[i]) )
		if(min_data > float( min(y_datas[i]) ) ):
			min_data = float( min(y_datas[i]) )

	y_interval = (max_data - min_data) / mark_num
	for i in range(0, mark_num + 1):
		y_mark.append(i * y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.rcParams['axes.linewidth'] = line_size * 0.5

	plt.plot(x_data, y_datas[SKIP_LIST], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[SKIP_LIST_P], 'r-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[SKIP_LIST_C_V], 'y-o', lw = line_size, ms = dot_size)
	plt.xlabel(f"k\nfrom 2^0 to 2^{MAX_POWER_K}", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title(f"COMPARE of Different skip list (data size is 2^{POW_N} - 1)", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2, 0), pow(2, MAX_POWER_K) * 1.001])
	plt.ylim([0, max_data + y_interval])
	plt.legend(["Skip list with vector", "Skip list all pointer", "Skip list no repeation"], fontsize = font_size)

	plt.savefig(file_name)

main()
