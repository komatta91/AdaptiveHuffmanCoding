#!/bin/python3

import sys
import math

prob = {}

with open(sys.argv[1], 'rb') as f:
    cntr = 1
    byte = f.read(1)
    while byte != b"":
        if byte not in prob.keys():
            prob[byte] = 0
        prob[byte] += 1
        byte = f.read(1)

probabilities = [float(v)/sum(prob.values()) for v in prob.values()]

print( -sum([p * math.log(p, 256) for p in probabilities]) )
