#!/usr/bin/env python3;
"""

"""
import os;
import sys;
import time;

pid = os.fork()
match pid : # Switch valido solo para python ver >= 3.1
   case -1:
           print("Error in fork.")
   case  0:
           print("Child  PID = %d, PPID = %d" % (os.getpid(), os.getppid()))
   case  _:
           print("Father PID = {}".format(os.getpid(), os.getppid()) )

#	time.sleep(0.030);
#	os.waitpid(childpid, 0);
