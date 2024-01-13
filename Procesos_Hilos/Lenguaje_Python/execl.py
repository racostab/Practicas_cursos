 #!/usr/bin/env python3;
"""
   Programa equivalente a Execl
   $ python3 execl.py
"""
import subprocess

arg1 = "-l"
pathname = "/bin/ls"

# result = subprocess.run([pathname, pathname, arg1], capture_output=True)
result = subprocess.run(["ls", "-l"], capture_output=True)
#result = subprocess.run(["pwd"], capture_output=True)

if result.returncode == 0:
    print(result.stdout.decode())
else:
    print(f"Error: {result.stderr.decode()}")
