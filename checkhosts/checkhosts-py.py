from os import system
import subprocess
from sys import argv, exit as leave

HOSTS_PATH = argv[1]

def main():
	if argv[2] == '--force':
		arguments = argv[3:]
		force = True
	else:
		arguments = argv[2:]
		force = False

	if arguments != []:
		apply_whitelist_blacklist(arguments)

	print('Looking for any changes...')

	are_different = compare_files()
		
	#ask the user whether they want to update the file if there is any update		
	if are_different or force:
		print('Update found!')
		choice = input('Do you want to update the hosts file? [y/n]')

		#if user does not want to update, remove the temp file and exit
		if choice.lower() == 'n':
			leave(2)
		else:
			leave(0)

	else:
		#leave and remove the temp file
		print('No changes found.')
		leave(2)

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
		temp2_file.write('\n\n#USER DEFINED BLACKLIST:\n')
		for link in blacklist:
			temp2_file.write("0.0.0.0 " + link + '\n')

	temp2_file.close()
	system('cp temp2_hostsfile temp_hostsfile')
	print('Whitelist applied!')

def parse_args(arguments):
	if '--whitelist' in arguments:
		if '--blacklist' in arguments:
			if arguments[0] == '--whitelist':
				blacklist_flag_index = get_flag_index('--blacklist', arguments)
				whitelist = arguments[1:blacklist_flag_index]
				blacklist = arguments[blacklist_flag_index+1:]
			else:
				whitelist_flag_index = get_flag_index('--whitelist', arguments) 
				blacklist = arguments[1:whitelist_flag_index]
				whitelist = arguments[whitelist_flag_index+1:]
		else:
			whitelist, blacklist = arguments[1:], False
	elif '--blacklist' in arguments:
		whitelist, blacklist = False, arguments[1:]
	else:
		whitelist, blacklist = False, False

	return whitelist, blacklist

def get_flag_index(flag, arguments):
	return arguments.index(flag)

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

	return are_different

main()