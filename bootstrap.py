#!/usr/bin/python3

import os
import sys
import platform
import subprocess

Python = "python" if platform.system() == "Windows" else "python3"

def executeCommandSilent(command):
    out = open(os.devnull, 'w')
    err = subprocess.STDOUT
    return subprocess.call(command, shell = True, stdout=out, stderr=err);

def runPythonScript(Script, Params):
    if os.system( Python + " " + Script + " " + Params ) != 0:
        print( "Unable to run " + Script )
        exit(255)

def clear_terminal():
    os.system('cls' if os.name == 'nt' else 'clear')

if executeCommandSilent(Python + " --version") != 0:
    print( "Make sure Python can be started from the command line (add path to `python.exe` to PATH on Windows)" )
    exit(255)

if executeCommandSilent("cmake --version") != 0:
    print( "Install CMake first" )
    exit(255)

if executeCommandSilent("git --version") != 0:
    print( "Install Git first" )
    exit(255)

if executeCommandSilent("hg --version") != 0:
    print( "Install Mercurial first" )
    exit(255)

# run Tools/Bootstrap
clear_terminal()
runPythonScript( os.path.join("vendor", "bootstrap.py"), "-b vendor" )
print( "" )
print( "Bootstrapping done." )

__cwd = os.getcwd()
print("Build and install indirect dependencies?(Y/n):", end=" ")
build_and_install_deps = str(input())
print("")
if build_and_install_deps.lower() == "y":
    clear_terminal()
    build_script_path = os.path.join(__cwd, "build_and_install.py")
    project_dir = os.path.join(__cwd, "vendor", "src", "xtl")
    subprocess.run([Python, build_script_path, project_dir], check=True)
else:
    print("Script finished!")
