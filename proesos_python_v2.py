#!/usr/bin/env python3;
"""

"""
import os;
import sys;
import time;

# Main
print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));

# Create child process
childpid = os.fork();  # 1
if(childpid == 0):
	print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
	for i in range(0, 2):
		# Create child process
		childpid = os.fork();  # 2, 3
		if(childpid == 0):
			print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
			if(i == 0):
				childpid = os.fork();  # 4
				if(childpid == 0):
					print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
					time.sleep(0.030);
					exit(0);
				else:
					os.waitpid(childpid, 0);
			if(i == 1):
				childpid = os.fork();  # 5
				if(childpid == 0):
					print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
					for j in range(0, 2):
						childpid = os.fork();  # 6, 7
						if(childpid == 0):
							print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
							if(j == 0):
								time.sleep(0.030);
								exit(0);
							if(j == 1):
								for k in range(0, 3):
									childpid = os.fork();  # 8, 9, 10
									if(childpid == 0):
										print("CHILD PID = %d, PPID = %d" % (os.getpid(), os.getppid()));
										time.sleep(0.030);
										exit(0);
									else:
										os.waitpid(childpid, 0);
							time.sleep(0.030);
							exit(0);
						else:
							os.waitpid(childpid, 0);
					time.sleep(0.030);
					exit(0);
				else:
					os.waitpid(childpid, 0);
			time.sleep(0.030);
			exit(0);
		else:
			os.waitpid(childpid, 0);
	time.sleep(0.030);
	exit(0);
else:
	os.waitpid(childpid, 0);
