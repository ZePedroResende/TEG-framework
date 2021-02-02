import datetime
import itertools
import subprocess


def run_command(cmd):
    result = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, shell=True)
    result.wait()
    try:
        return result.stdout.read().decode("ascii").strip()
    except Exception as e:
        print(e)
        return None


def k_best(k, values):
    error = (1, -1)
    values.sort()
    for i in range(len(values) - k):
        maximum = values[i + k - 1]
        minimum = values[i]
        e = (maximum - minimum) / float(maximum)
        if e < 0.05:
            return sum(values[i:i + k]) / float(k)
        if e < error[0]:
            error = (e, i)
            if error[1] != -1:
                return sum(values[error[1]:error[1] + k]) / float(k)
    return -1


def run_func(table, nreps, k, combination):
    tmp = []
    for r in range(nreps):
        out = run_command(' '.join(["./scheduler", ' '.join(combination)]))
        print(out)
        if out is not None and out != "":
            tmp.append(float(out))
        else:
            print("Error 1")

    try:
        table.write("," + str(k_best(k, tmp)))
    except:
        table.write(",Error2")
        print("Error 2")

    table.write("\n")


def run_tests(funcs, nreps, k):
    combinations = [p for p in itertools.product(*funcs)]
    fname = "../" + datetime.datetime.now().strftime("%Y-%m-%d_%H:%M") + ".csv"
    table = open(fname, "w")
    table.write("Scheduler,N_Threads,Time\n")

    for combination in combinations:
        print(combination)
        table.write(','.join(combination))
        run_func(table, nreps, k, combination)
        table.write("\n")
    table.close()


if __name__ == '__main__':
    funcs = [["1", "2", "3", "4","5"], ["2", "4", "8", "16", "32", "48"]]
    nreps = 8
    k = 3
    run_tests(funcs, nreps, k)
