#!/usr/bin/env python

import sys

with open(sys.argv[1], 'r') as f:
    nums = []
    for l in f:
        try:
            nums.append(float(l.strip()))
        except ValueError:
            continue

print('\n'.join(['{:4.4g}'.format(n) for n in sorted(nums)[:5]]))
