import re
import subprocess



def runCProgram():
	subprocess.call(["gcc", "sorter.c", "-o", "sorter"])
	subprocess.call(["./sorter"])




def chordSearch(match):
	count = 0
	with open("sorted.txt") as fp:
		for line in fp:
			count += 1
			if re.search(r'\({}.*\)'.format(match), line, re.IGNORECASE):
        			print("\t{}".format(line.strip()))




def nameSearch(match):
	count = 0
	with open("sorted.txt") as fp:
		for line in fp:
			count += 1
			if re.search(r'{}'.format(match), line, re.IGNORECASE):
				print("\t{}".format(line.strip()))




def main():
	runCProgram();
	print('======WELCOME TO SONG FINDER!======')
	print('--ENTER 1 FOR NAME SEARCH')
	print('--ENTER 2 FOR CHORD SEARCH')
	mode = str(input())
	if mode == '1':
		print('-ENTER A SONG NAME')
		name = str(input())
		print('SONGS FOUND:\n')
		nameSearch(name)
	if mode == '2':
		print('-ENTER A CHORD')
		chord = str(input())
		print('SONGS FOUND:\n')
		chordSearch(chord)
	print('')
	print('--Would you like to search again? (y/n)')
	if str(input()) == 'y':
		main()


if __name__ == '__main__':
	main()
