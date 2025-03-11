import matplotlib
matplotlib.use('Agg')  # Non-interactive backend suitable for saving plots

import matplotlib.pyplot as plt

def main():
	x_mark = []
	y_mark = []
	x_data = []
	experiment1_array = [[], [], [], []]
	experiment1_list = [[], [], [], []]
	experiment2_array = [[], [], [], []]
	experiment2_list = [[], [], [], []]
	max_h = 20

#	set x data
	for i in range(10, max_h+1):
		x_data.append(pow(2, i))
		#x_mark.append(pow(2, i))

#	read y data
	for i in range(0, 4):
		for j in range(10, max_h+1):
			temp = input()
			experiment1_array[i].append(float(temp))
			temp = input()
			experiment1_list[i].append(float(temp))
			temp = input()
			experiment2_array[i].append(float(temp))
			temp = input()
			experiment2_list[i].append(float(temp))


	#graph 1
#	set y interval
	max_ex1 = 0
	min_ex1 = 100000

	fig_size = 100
	dot_size = 10
	line_size = 3
	font_size = 80
#	save_as = "experiment number 1-3.png"
	save_as = "none"

	for i in range(0, 4):
		if( max_ex1 < float(max(experiment1_array[i])) ):
			max_ex1 = float(max(experiment1_array[i]))
		if (min_ex1 > float(min(experiment1_array[i])) ):
			min_ex1 = float(min(experiment1_array[i]))

		if( max_ex1 < float(max(experiment1_list[i])) ):
			max_ex1 = float(max(experiment1_list[i]))
		if( min_ex1 > float(min(experiment1_list[i])) ):
			min_ex1 = float(min(experiment1_list[i]))

	y_interval = (max_ex1 - min_ex1) / 30
	for i in range(0, 31):
		y_mark.append(i*y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.plot(x_data, experiment1_array[0], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_array[1], 'r-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_array[2], 'y-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_array[3], 'k-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_list[0], 'b--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_list[1], 'r--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_list[2], 'y--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment1_list[3], 'k--s', lw = line_size, ms = dot_size)
	plt.xlabel("n", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title("experiment number 1", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2,10), pow(2, 20)+10000])
	plt.ylim([0, max_ex1 + y_interval])
	plt.legend(["array k=1", "array k=3", "array k=6", "array k=9", "list k=1", "list k=3", "list k=6", "list k=9"], fontsize = font_size)

	plt.savefig(save_as)
	
	#graph 2
#	set y interval
	max_ex2 = 0
	min_ex2 = 100000

	fig_size = 18
	dot_size = 5
	line_size = 1
	font_size = 15
	save_as = "experiment number 2-1.png"
#	save_as = "none"

	for i in range(0, 4):
		if( max_ex2 < float(max(experiment2_array[i])) ):
			max_ex2 = float(max(experiment2_array[i]))
		if (min_ex2 > float(min(experiment2_array[i])) ):
			min_ex2 = float(min(experiment2_array[i]))

		if( max_ex2 < float(max(experiment2_list[i])) ):
			max_ex2 = float(max(experiment2_list[i]))
		if( min_ex2 > float(min(experiment2_list[i])) ):
			min_ex2 = float(min(experiment2_list[i]))

	y_interval = (max_ex2 - min_ex2) / 30
	y_mark = []

	for i in range(0, 31):
		y_mark.append(i*y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.plot(x_data, experiment2_array[0], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_array[1], 'r-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_array[2], 'y-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_array[3], 'k-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_list[0], 'b--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_list[1], 'r--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_list[2], 'y--s', lw = line_size, ms = dot_size)
	plt.plot(x_data, experiment2_list[3], 'k--s', lw = line_size, ms = dot_size)
	plt.xlabel("n", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title("experiment number 1", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2,10), pow(2, 20)+10000])
	plt.ylim([0, max_ex2 + y_interval])
	plt.legend(["array k=1", "array k=3", "array k=6", "array k=9", "list k=1", "list k=3", "list k=6", "list k=9"], fontsize = font_size)

	plt.savefig(save_as)
	


main()
