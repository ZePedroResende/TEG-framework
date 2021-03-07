import matplotlib
matplotlib.use('TKagg')
import matplotlib.pyplot as plt
import sys
import os
import pandas as pd

def k_best (k, values):
	error=(1,-1)
	values.sort()
	for i in range(len(values)-k):
		maximum = values[i+k-1]
		minimum = values[i]
		e = (maximum - minimum) / float(maximum)
		if e < 0.05:
			return sum(values[i:i+k]) / float(k)
		if e < error[0]:
			error=(e,i)
	if error[1] != -1:
		return sum(values[error[1]:error[1]+k]) / float(k)
	return -1

def main():
    #dirname = sys.argv[1]
    dirname = '/home/resende/2_async_benchmarks'
    folders = os.listdir(dirname)
    csv_files = list(map(lambda name: os.path.join(os.path.join(dirname, name),'new/raw.csv'), folders))

    df_from_each_file = (pd.read_csv(f, sep=',') for f in csv_files)
    df_from_each_file = (f.head() for f in df_from_each_file)
    #filtered_files =
    df_merged   = pd.concat(df_from_each_file, ignore_index=True)
    #a = df_merged.sort_values(by=["throughput_num"], ascending=False)
    print(df_merged)
    a = df_merged.sort_values(by=["throughput_num"], ascending=False)
    #b = df_merged.sort_values(by=["sample_measured_value"], ascending=True)
    a.to_csv( "merged.csv")
    #b.to_csv( "merged2.csv")

    a.plot(x='throughput_num', y='sample_measured_value', kind = 'scatter', loglog=True)
    #a.savefig("figura.png")
    plt.show()

if __name__ == "__main__":
  main()
