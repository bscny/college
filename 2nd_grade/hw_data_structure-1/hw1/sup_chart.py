import matplotlib.pyplot as plt

def main():
	x_mark = []
	y_mark = []
	x_data = []
	y_data = [[],[]]

#	set x data
	for i in range(10, 28+1):
		x_data.append(pow(2, i))
		#x_mark.append(pow(2, i))

#	read y data
	for i in range(10, 28+1):
		temp = input()
		y_data[0].append(float(temp))

	for i in range(10, 28+1):
		temp = input()
		y_data[1].append(float(temp))

	#graph 1
#	set y interval
	max_ex1 = 0
	min_ex1 = 100000

	fig_size = 15
	dot_size = 5
	line_size = 1
	font_size = 20
#	save_as = "experiment number 1-3.png"
	save_as = "proof.png"

	max_ex1 = float(max(y_data[0]))
	min_ex1 = float(min(y_data[1]))
	
	y_interval = (max_ex1 - min_ex1) / 30
	for i in range(0, 31):
		y_mark.append(i*y_interval)

	plt.figure(figsize=(fig_size, fig_size))
	plt.plot(x_data, y_data[1], 'b-o', lw = line_size, ms = dot_size)
	plt.plot(x_data, y_data[0], 'b--o', lw = line_size, ms = dot_size)
	plt.xlabel("n", fontsize = font_size)
	plt.ylabel("time(sec)", fontsize = font_size)
	plt.title("support chart", fontsize = font_size)
	plt.xticks(x_mark, fontsize = font_size)
	plt.yticks(y_mark, fontsize = font_size)
	plt.xlim([pow(2,10), pow(2, 28)+1000000])
	plt.ylim([0, max_ex1 + y_interval])
	plt.legend(["array k=1", "list k=1"], fontsize = font_size)

	plt.savefig(save_as)


main()
