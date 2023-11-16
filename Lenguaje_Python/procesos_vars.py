#!/usr/bin/env python3;
"""
    Use of timer and waitpid
"""
import os;
import time;

pid = os.fork()
match pid : # Switch valido solo para python ver >= 3.1
   case -1:
           print("Error in fork.")
   case  0:
           print("Child  PID = {} PPID = {}".format(os.getpid(), os.getppid()) )
           time.sleep(5.0);
           print("Child end wakeup.")
   case  _:
           print("Father PID = {} PPID = {}".format(os.getpid(), os.getppid()) )
           os.waitpid(pid, 0);
           print("Father end waitpid.")
