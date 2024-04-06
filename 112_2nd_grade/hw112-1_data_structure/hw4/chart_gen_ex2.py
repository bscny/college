import matplotlib.pyplot as plt

MIN_POWER_N = 10
MAX_POWER_N = 15
LINE_NUM = 2
HASH_TABLE = 0
BSTREE = 1

def main():
	x_mark = []
	y_mark = []
	x_data = []
	y_datas = [[],[]]

#set x data
	for i in range(MIN_POWER_N, MAX_POWER_N + 1):
		x_data.append(pow(2, i))

#set y data
	for j in range(MIN_POWER_N, MAX_POWER_N + 1):
		for i in range(0, LINE_NUM):
			temp = input()
			y_datas[i].append(float(temp))
	
#graphing
	fig_size = 100
	dot_size = 16
	line_size = 7.5
	font_size = 100
	file_name = f"FIG_experiment 2-3 decrease search data.png"
	title_modifier = f""

#set y interval
	max_data = 0
	min_data = 100000
	mark_num = 30
	for i in range(0, LINE_NUM):
		if(max_data < float( max(y_datas[i]) ) ):
			max_data = float( max(y_datas[i]) )
		if(min_data > float( min(y_datas[i]) ) ):
			min_data = float( min(y_datas[i]) )

	y_interval = (max_data - 0) / mark_num
	for i in range(0, mark_num + 1):
		y_mark.append(i * y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.rcParams['axes.linewidth'] = line_size * 0.5

	plt.plot(x_data, y_datas[HASH_TABLE], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[BSTREE], 'r-o', lw = line_size, ms = dot_size)
	plt.xlabel(f"n\nfrom 2^{MIN_POWER_N} to 2^{MAX_POWER_N}", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title(f"EXPERIMENT 2 search 10000 datas {title_modifier}", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2, MIN_POWER_N), pow(2, MAX_POWER_N) * 1.001])
	plt.ylim([0, max_data + y_interval])
	plt.legend(["hash table", "binary search tree"], fontsize = font_size)

	plt.savefig(file_name)

main()
