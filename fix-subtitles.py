#/usr/bin/python3
from sys import argv

chars = {'³': 'ł', '¹': 'ą', 'ê': 'ę', 'Ÿ': 'ź', '¿': 'ż', 'æ': 'ć', 'ñ': 'ń', 'œ': 'ś', '¯': 'Ż', 'Œ': 'Ś'}

filename = argv[1]

filer = open(filename, 'r')
filew = open(filename+'fixed', 'r')

line = filer.readline()

while line.strip != '':
	for char in chars:
		line = line.replace(char, chars[char])
	filew.write(line)	
	line = filer.readline()

filew.close()
filer.close()


