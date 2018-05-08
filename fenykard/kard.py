import os
import sys
import fnmatch
import re
import time

walk_dir = sys.argv[1]

walk_dir = os.path.abspath(walk_dir)
sum_point = 0

filename = time.strftime('%Y-%m-%d') + 'FUTURE_points_log'
sys.stdout = open(filename, 'w')

for root, subdirs, files in os.walk(walk_dir):
    list_file_path = os.path.join(root)
    part_point = 0

    for filename in fnmatch.filter(files, '*.props'):
        print(os.path.join(root, filename))
        with open(os.path.join(root, filename), 'r') as props_file:
            tmp = props_file.readlines()
            for line in tmp: 
                line = line.strip()           
                part_point += int(re.sub('.*?([0-9]*)$', r'\1', line))
            print('Részpontszám: ', part_point, '\n')
        sum_point += part_point

for i in range(80):
    print('*', end="")        

print('\nÖsszpont: ', sum_point, '\n')

os.close(1)



