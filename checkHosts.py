#This script checks whether there was an update of the
#StevenBlack's unified adware+malware hosts file
#If there was, the user may agree to replace the 
#older file from /etc/hosts with the newest one


from urllib.request import Request, urlopen
from bs4 import BeautifulSoup
from os import _exit, remove
import subprocess

HDR = {'User-Agent':'Mozilla/5.0'}
LINK = 'https://raw.githubusercontent.com/StevenBlack/hosts/master/hosts'

#get raw text file from GitHub
request = Request(LINK, headers=HDR)
print('Fetching data...')
plaintext = BeautifulSoup(urlopen(request), 'html.parser')
print('Fetching completed!')
print('Creating a temporary file...')

#dump the results into a temp file
filew = open('temp_hostsfile', 'w')
filew.write(plaintext.get_text())
filew.close()

print('File created!')
print('Checking for any changes...')

#initialize variables needed to compare the new file with the older one
filer_old = open('/etc/hosts', 'r')
filer_new = open('temp_hostsfile', 'r')
line_old = filer_old.readline()
line_new = filer_new.readline()
are_different = False
record = 0

#comparing the files
while (line_new != '' or line_old != '') and not are_different:
	#print basic info about the both hosts files
	if record == 5:
		print('\n\nLocal hosts file: ')
		print('---------------------------------------')
		print(line_old[2:].strip())
		line_old = filer_old.readline()
		print(line_old[2:].strip())
		print('---------------------------------------')
		print('---------------------------------------')
		print('\nNew file:')
		print('---------------------------------------')
		print(line_new[2:].strip())
		line_new = filer_new.readline()
		print(line_new[2:].strip())
		print('---------------------------------------\n\n')

	if line_new != line_old:
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
	print('No updates for the hosts file found.')

#ask the user whether they want to update the file if there is any update
elif are_different:
	print('hosts file update found!')
	password = input('Do you want to update the local hosts file? [y/n]')

	#if user does not want to update, remove the temp file and exit
	if password.lower() == 'n':
		remove('temp_hostsfile')
		_exit(0)

	#update the hosts file
	update = subprocess.Popen(['sudo', 'cp', 'temp_hostsfile', '/etc/hosts'], stderr=subprocess.STDOUT)
	stderr = update.communicate()[1]
	if stderr == None:
		print('\nFile updated!')
	else:
		print('\nSome error appeared, try again')


#remove the temp file
remove('temp_hostsfile')

