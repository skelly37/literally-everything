from os import system
import subprocess
from sys import argv, exit as leave

HOSTS_PATH = argv[1]
whitelist=[]

if argv[2:] != []:
	whitelist = argv[1:]
	print('Usuwanie wyjątków...')

	filer_new = open('temp_hostsfile', 'r')
	line = filer_new.readline()
	temp2_file = open('temp2_hostsfile', 'w')
	while line != '':
		to_skip = False
		for count in range(len(whitelist)):
			if whitelist[count] in line:
				to_skip = True
				break

		if not to_skip:
			temp2_file.write(line)

		line = filer_new.readline()

	filer_new.close()

	system('cp temp2_hostsfile temp_hostsfile')
	print('Wyjątki usunięte!')

print('Sprawdzanie aktualizacji...')

#initialize variables needed to compare the new file with the older one
filer_old = open(HOSTS_PATH, 'r')
filer_new = open('temp_hostsfile', 'r')
line_old = filer_old.readline()
line_new = filer_new.readline()
are_different = False
record = 0

#comparing the files
while (line_new != '' or line_old != '') and not are_different:
	#print basic info about the both hosts files
	if record == 5:
		print('\n\nObecny plik hosts: ')
		print('---------------------------------------')
		line_old = line_old[2:]
		line_old = line_old.replace('Date','Data')
		print(line_old.strip())
		line_old = filer_old.readline()
		line_old = filer_old.readline()
		line_old = line_old[2:]
		line_old = line_old.replace('Number of unique domains','Liczba poszczególnych domen')
		print(line_old.strip())
		print('---------------------------------------')
		print('\nNowy plik:')
		print('---------------------------------------')
		line_new = line_new[2:]
		line_new = line_new.replace('Date','Data')
		print(line_new.strip())
		line_new = filer_new.readline()
		line_new = filer_new.readline()
		line_new = line_new[2:]
		line_new = line_new.replace('Number of unique domains','Liczba poszczególnych domen')
		print(line_new.strip())
		print('---------------------------------------\n\n')
	if line_new != line_old and record > 5:
		are_different = True
	else:
		line_old = filer_old.readline()
		line_new = filer_new.readline()
		record += 1

	#copy old blacklist to the new file
	if line_old == '# blacklist\n':
		for count in range(5):
			line_old = filer_old.readline()

		filer_new.close()
		filew_new = open('temp_hostsfile', 'a')
		while line_old != '':
			filew_new.write(line_old)
			line_old = filer_old.readline()

		break


if not are_different:
	#leave and remove the temp file
	print('Nie znaleziono aktualizacji.')
	leave(2)

#ask the user whether they want to update the file if there is any update
elif are_different:
	print('Znaleziono aktualizację!')
	password = input('Czy chcesz zaaktualizować plik hosts? [t/n]')

	#if user does not want to update, remove the temp file and exit
	if password.lower() == 'n':
		leave(2)
	else:
		leave(0)
