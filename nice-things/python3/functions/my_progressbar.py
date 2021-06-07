"""Call in a loop to create terminal progress bar

        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        print_end   - Optional  : end character (e.g. "\r", "\r\n") (Str)
    

    Exemplary usage
    
        from time import sleep
        max = 153
        show_progressbar(0, max)
        for count in range(max):
            sleep(0.05) 
            
            #some code instead of time.sleep()
            
            show_progressbar(count+1, max)"""

def show_progressbar(iteration, total, prefix = 'Progress:', suffix = '', decimals = 2, length = 25, fill = '#', print_end = "\r"):

    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))  #percent of the progress in format 0:.[decimals]f. eg. 0:.2f
    filled = int(length * iteration // total)                                           #how much of the bar is already filled
    bar = fill * filled + '-' * (length - filled)                                       #inside of the bar
    print(f'\r{prefix} [{bar}] {percent}% {suffix}', end = print_end)                   #format and print the prepared bar
    
    if iteration == total:                                                              #print a new line when the progressbar reaches 100%
        print()
