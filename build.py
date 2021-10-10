import subprocess
import sys

batDirectory = r'C:\Users\ryanw\Documents\GitHub\Wrath-Of-The-Dead\buildtools'

config = sys.argv[1]
platform = sys.argv[2]

if config == "Debug":
    if platform == "x64":
        batDirectory += r'\Debug-x64.bat'
        print(batDirectory)
        subprocess.call([batDirectory])
    if platform == "x86":
        batDirectory += r'\Debug-x86.bat'
        subprocess.call([batDirectory])

if config == "Release":
    if platform == "x64":
        batDirectory += r'\Release-x64.bat'
        print(batDirectory)
        subprocess.call([batDirectory])
    if platform == "x86":
        batDirectory += r'\Release-x86.bat'
        subprocess.call([batDirectory])

if config == "MinSizeRel":
    if platform == "x64":
        batDirectory += r'\MinSizeRel-x64.bat'
        print(batDirectory)
        subprocess.call([batDirectory])
    if platform == "x86":
        batDirectory += r'\MinSizeRel-x86.bat'
        subprocess.call([batDirectory])

if config == "RelWithDebInfo":
    if platform == "x64":
        batDirectory += r'\RelWithDebInfo-x64.bat'
        print(batDirectory)
        subprocess.call([batDirectory])
    if platform == "x86":
        batDirectory += r'\RelWithDebInfo-x86.bat'
        subprocess.call([batDirectory])

    
        
