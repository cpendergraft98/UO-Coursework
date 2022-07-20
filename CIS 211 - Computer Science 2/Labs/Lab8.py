'''
Lab 8

AUTHOR: Cole Pendergraft
'''

import re

result = re.search(r'[A-Z]*211', 'CIS210 CIS211 CIS212')
print(result.group(0))
print(result[0])

# Both above print statemetns out CIS211 twice. The pattern seems to be a capitalized
# string ending with 211

result = re.search(r'(xy){2}', 'xy xyxy xyxyxy')
print(result.group(0))
print(result[0])

# Above looks for the string 'xy' paired up twice, {2} dictates how many repetitions of 'xy'
# we are looking for in between blocks of whitespace, so it returns the string 'xyxy'
# for each print statement.

result = re.match(r'[A-Z|a-z]+211\.', 'Cis211.  CIS210 CIS211')
print(result.group(0))
print(result[0])

# Above prints out 'Cis211.' twice. I believe the pattern is a capitalized or a lowercase
# string ending with 211, and since the match function only looks at the beginning of
# the string, 'Cis211.' prints.

# Match finds an object matching the pattern at the beginning of the string and returns
# the matching object. Search scours the entire string looking for a match to the pattern
# and returns that matching object. The big difference is that match only looks at the
# beginning of the string.

result = re.match(r'(?P<course1>[A-Z|a-z]*210) (?P<course2>.*211)', 'Cis210 CIS211 CIS212')
print(result.groupdict())

# Above creates a dictionary that assigns 'course1' and 'course2' as keys related to
# their matching objects. Course1 looks for a pattern with either capital or lowercase
# letters ending in 210, so it returns the first instance at the beginning of the string
# which is Cis210. Course2 just looks for a matching object that ends with 211, so it
# selects CIS211.