#!/usr/bin/env python3
# this takes a ttl file that is complete but port indexes are not correct
# it will change the index so the ports appear in order
# its useful if you add a port in the middle of an existing file

import fileinput

i = 0
for line in fileinput.input(inplace=True):
    if line.find("lv2:index") > 0:
           print("                lv2:index "+str(i)+" ;"),
           i+=1
    else:
        print(line,end=""),
