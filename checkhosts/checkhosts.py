from os import system
import subprocess
from sys import argv, exit as leave

HOSTS_PATH = argv[1]

def main():
	arguments = argv[2:]

	if argv[2:] != []:
		apply_whitelist_blacklist(arguments)

	print('Looking for any changes...')

	are_different = compare_files()
			
	if not are_different:
		#leave and remove the temp file
		print('No changes found.')
		leave(2)

	#ask the user whether they want to update the file if there is any update
	elif are_different:
		print('Update found!')
		password = input('Do you want to update the hosts file? [y/n]')

		#if user does not want to update, remove the temp file and exit
		if password.lower() == 'n':
			leave(2)
		else:
			leave(0)

def parse_args(keyword, arguments):
	keyword_index = arguments.index(keyword)
	return arguments[1:keyword_index], arguments[keyword_index+1:]

def apply_whitelist_blacklist(arguments):
	print('Applying whitelist/blacklist...')

	whitelist, blacklist = parse_args(arguments)

	temp2_file = open('temp2_hostsfile', 'w')

	if whitelist != False:
		filer_new = open('temp_hostsfile', 'r')
		line = filer_new.readline()
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

	if blacklist != False:
		temp2_file.write('\n\n#USER DEFINED BLACKLIST:')
		for link in blacklist:
			temp2_file.write(link + '\n')

	temp2_file.close()
	system('cp temp2_hostsfile temp_hostsfile')
	print('Whitelist applied!')

def parse_args(arguments):
	if '--whitelist' in arguments:
		if '--blacklist' in arguments:
			if arguments[0] == '--whitelist':
				whitelist, blacklist = parse_args('--blacklist', arguments)
			else:
				blacklist, whitelist = parse_args('--whitelist', arguments) 
		else:
			whitelist, blacklist = arguments[1:], False
	elif '--blacklist' in arguments:
		whitelist, blacklist = False, arguments[1:]
	else:
		whitelist, blacklist = False, False

	return whitelist, blacklist

def compare_files(old_file_path=HOSTS_PATH, new_file_path='temp_hostsfile'):
	#initialize variables needed to compare the new file with the older one
	filer_old = open(old_file_path, 'r')
	filer_new = open(new_file_path, 'r')
	line_old = filer_old.readline()
	line_new = filer_new.readline()
	are_different = False
	record = 0

	#comparing the files
	for record in range(6):
		#print basic info about the both hosts files
		if record == 5:
			print('\n\nLocal hosts file: ')
			print('---------------------------------------')
			line_old = line_old[2:]
			print(line_old.strip())
			line_old = filer_old.readline()
			line_old = filer_old.readline()
			line_old = line_old[2:]
			print(line_old.strip())
			print('---------------------------------------')
			print('\nNew file:')
			print('---------------------------------------')
			line_new = line_new[2:]
			print(line_new.strip())
			line_new = filer_new.readline()
			line_new = filer_new.readline()
			line_new = line_new[2:]
			print(line_new.strip())
			print('---------------------------------------\n\n')

			if line_new != line_old:
				are_different = True
			else:
				are_different = False

		else:
			line_old = filer_old.readline()
			line_new = filer_new.readline()

main()