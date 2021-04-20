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

#comparing the files
while (line_new != '' or line_old != '') and not are_different:
	if line_new != line_old:
		are_different = True
	else:
		line_old = filer_old.readline()
		line_new = filer_new.readline()

if are_different:
	#leave and remove the temp file
	print('No updates for the hosts file found.')

#ask the user whether they want to update the file if there is any update
elif not are_different:
	print('hosts file update found!')
	password = input('Do you want to update the local hosts file? [y/n]')

	if password.lower() == 'n':
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

