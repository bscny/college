import matplotlib.pyplot as plt

MAX_POWER_N = 26
QSRT_RECUR = 0
QSRT_ITER = 1
MSRT_RECUR = 2
MSRT_ITER = 3

def main():
	x_mark = []
	y_mark = []
	x_data = []
	y_datas = [[],[],[],[]]

#set x data
	for i in range(10, MAX_POWER_N + 1):
		x_data.append(pow(2, i))

#set y data
	for j in range(10, MAX_POWER_N+ 1):
		for i in range(0, 4):
			temp = input()
			y_datas[i].append(float(temp))
	
#graphing
	fig_size = 15
	dot_size = 3
	line_size = 1.5
	font_size = 15
	file_name = "FIG_support.png"

#set y interval
	max_data = 0
	min_data = 1000
	mark_num = 30
	for i in range(0, 4):
		if(max_data < float( max(y_datas[i]) ) ):
			max_data = float( max(y_datas[i]) )
		if(min_data > float( min(y_datas[i]) ) ):
			min_data = float( min(y_datas[i]) )

	y_interval = (max_data - min_data) / mark_num
	for i in range(0, mark_num + 1):
		y_mark.append(i * y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.plot(x_data, y_datas[QSRT_RECUR], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[QSRT_ITER], 'r-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[MSRT_RECUR], 'b--o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_datas[MSRT_ITER], 'r--o', lw = line_size, ms = dot_size)
	plt.xlabel("n \nfrom 2^10 to 2^26", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title("SUPPORT CHART compare iterative & recursive", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2, 10), pow(2, MAX_POWER_N) + 10000])
	plt.ylim([0, max_data + y_interval])
	plt.legend(["Hoare qsort recursive", "Hoare qsort iterative", "msort recursive", "msort iterative"], fontsize = font_size)

	plt.savefig(file_name)

main()
