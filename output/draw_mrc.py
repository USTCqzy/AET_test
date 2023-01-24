import sys
import getopt
import matplotlib.pyplot as plt

tracefilename = ''
tracename = ''

def draw_mrc():
    with open(tracefilename, 'r') as f:
        lines = f.readlines()
        i = 0
        while i < len(lines):
            # match pattern
            if lines[i].find('calculate MRC finished in') != -1:
                break
            i = i + 1
        if i == len(lines) or i == len(lines) - 1:
            print('no MRC found')
            return
        i = i + 1
        x = []
        y = []
        # y_save = 2
        while i < len(lines):
            x_, y_ = lines[i].split(',')
            x.append(float(x_) * 4 / 1024 / 1024)
            y.append(float(y_))
            # if(y_save <= float(y_) and y_save < 1):
            #     break
            # y_save = float(y_)
            i = i + 1
        # only keep one minimum point
        i = len(y) - 1
        while i > 0 and y[i] == y[i - 1]:
            i = i - 1
        # if i < len(y) - 2:
        #     i = i + 2
        # elif i < len(y) - 1:
        #     i = i + 1
        if i < len(y) - 1:
            i = i + 1
        x = x[:i]
        y = y[:i]
        print("x:", x)
        print("y:", y)
        plt.plot(x, y)
        plt.xlabel('cache size (GiB)')
        plt.xlim(xmin=0)
        # plt.xticks([2 ** i for i in range(5, 11, 1)], [str(2 ** i) for i in range(5, 11, 1)])
        # plt.xticks([2 ** i for i in range(5, 8, 1)], [str(2 ** i) for i in range(5, 8, 1)])
        plt.ylabel('miss ratio')
        plt.ylim(0, 1)
        plt.yticks([i / 10 for i in range(0, 11, 1)], [str(i / 10) for i in range(0, 11, 1)])
        plt.grid()
        plt.title('MRC')
        plt.savefig(tracename + '_mrc.png')


def get_MSR_trace_name():
    # parse path to get trace name
    global tracename
    trace_name = tracefilename.split('/')[-1]
    trace_name = trace_name.split('.')[0]
    tracename = trace_name

def main(argv):
    options = "h:f:"
    long_options = ["help", "filename"]

    try:
        opts, args = getopt.getopt(argv, options, long_options)
    except getopt.GetoptError:
        print('draw_mrc.py -f <tracefilename>')
        sys.exit(2)
    
    for opt, arg in opts:
        if opt in ("-h", "help"):
            print('aet.py -f <tracefilename>')
            sys.exit()
        elif opt in ("-f", "-filename"):
            global tracefilename
            tracefilename = arg
            get_MSR_trace_name()

    print(tracename)
    draw_mrc()



if __name__ == "__main__":
   main(sys.argv[1:]) 