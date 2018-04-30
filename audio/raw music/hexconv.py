import sys
import fileinput
import csv

with open("song.txt", "r") as filestream:
    with open("hexsong.txt", "w") as filestreamtwo:
        for line in filestream:
            currentline = line.split(",")
            for line1 in currentline:
                filestreamtwo.write(hex(int(line1)).split('x')[-1])
