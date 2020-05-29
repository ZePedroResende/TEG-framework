import time
import subprocess
import datetime

def run_command(cmd):
    result = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE,stdin=subprocess.PIPE, shell=True)
    result.wait()
    try:
        return result.stdout.read().decode("ascii").strip()
    except Exception as e:
        print e
        return None

def run_program(program):
    while True:
        cmd = 'ps -eo user=|sort|uniq -c | grep -P "a[0-9]{5}" | wc -l'
        number = run_command(cmd)
        if number == '1':
            result = run_command(program)
            if result is not None:
                return result
            else :
                print "ERROR"
                return None
        else :
            time.sleep(1)

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

def run_func(table,nreps,k,func):
    tmp=[]
    for r in range(nreps):
        out = run_command(' '.join(["./scheduler", func ]))
        if out is not None:
            tmp.append(float(out))
        else:
            print "Error 1"

    try:
        table.write("," + str( k_best(k,tmp) ) )
    except:
        table.write(",")
        print "Error 2"

    table.write("\n")


def run_tests(funcs, nreps, k):
    total = len(funcs)*nreps
    fname = datetime.datetime.now().strftime("%Y-%m-%d_%H:%M") + ".csv"
    table = open( fname, "w" )
    table.write(",,Time\n")

    for func in funcs:
        print func
        table.write(func)
        run_func(table,nreps,k,func)
        table.write("\n")
    table.close()

if __name__ == '__main__':
    funcs = ["1", "2", "3"]
    nreps = 8
    k=3
    run_tests(funcs,nreps,k)
