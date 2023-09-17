
GREEN = '\033[32m'
YELLOW = '\033[33m'
BLUE = '\033[34m'

def main():
	answer = int(input(GREEN + "Номер задания: "))
	
	if answer == 1:
		task_1()
	elif answer == 2:
		task_2()
	elif answer == 3:
		task_3()

if __name__ == "__main__":
	main()