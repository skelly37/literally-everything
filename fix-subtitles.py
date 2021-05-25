#/usr/bin/python3
from sys import argv
import subprocess as s

def main():
	#know problematic characters and the correct ones
	chars = {'³': 'ł', '¹': 'ą', 'ê': 'ę', 'Ÿ': 'ź', '¿': 'ż', 'æ': 'ć', 'ñ': 'ń', 'œ': 'ś', '¯': 'Ż', 'Œ': 'Ś'}

	#initializing a flag whether user wants to overwrite the old file or not
	overwrite = False
	
	#check whether the -o or --overwrite flag was entered
	try:	
		filename = argv[2]
		if argv[1].lower() == '-o' or argv[1].lower() == '--overwrite':
			overwrite = True
	except IndexError:
		filename = argv[1]

	#get the number of lines for the progressbar
	lines = calc_num_of_lines(filename)

	#open the files and replace the characters
	filer = open(filename, 'r')
	filew = open(filename+'fixed', 'w')

	line = filer.readline()
	count = 0

	while line != '':
		#display progress
		show_progressbar(count+1, lines)
		
		for char in chars:
			line = line.replace(char, chars[char])
		filew.write(line)	
		line = filer.readline()
		count += 1


	filew.close()
	filer.close()
	
	#overwrite the file if user wants to
	if overwrite:
		system('mv ' + filename+'fixed ' + filename)

#get the output of $wc -l filename and parse it to get only the number of lines that is returned
def calc_num_of_lines(filename):
	wc = s.Popen(['wc', '-l',  filename], stdout=s.PIPE, stderr=s.PIPE)

	out, err = wc.communicate()
	lines = ''

	out = str(out)
	unwanted = ' ' + filename + '\\n\''
	out = out.replace(unwanted, '')
	out = [char for char in out][2:]

	for char in out:
		lines += char

	return int(lines)

def show_progressbar(iteration, total, prefix = 'Progress:', suffix = '', decimals = 2, length = 25, fill = '#', print_end = "\r"):

    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))  #percent of the progress in format 0:.[decimals]f. eg. 0:.2f
    filled = int(length * iteration // total)                                           #how much of the bar is already filled
    bar = fill * filled + '-' * (length - filled)                                       #inside of the bar
    print(f'\r{prefix} [{bar}] {percent}% {suffix}', end = print_end)                   #format and print the prepared bar
    
    if iteration == total:                                                              #print a new line when the progressbar reaches 100%
        print()

main()
