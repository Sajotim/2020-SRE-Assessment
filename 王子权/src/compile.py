import sys
import struct

if len(sys.argv) != 2:
    print('[Usage]: compile.py [filename.txt]')
    exit()

filename = sys.argv[1].split('.')[0]
opfile = open(sys.argv[1], 'r')
out = open(filename + '.vm', 'wb')
table = {}
dic = ['PUSH',
       'POP',
       'ADD',
       'SUB',
       'MUL',
       'DIV',
       'OR',
       'XOR',
       'AND',
       'TOP',
       'OUT',
       'SET',
       'MOV',
       'JMP',
       'HLT']
ops = []
index = 0

print('[Status] Compiling...')
for txt in opfile.readlines():
    txt = txt.strip().upper()
    if txt == '':
        continue
    elif ':' in txt:
        table[txt.split(':')[0]] = index
    else:
        op = txt.split(' ')
        ops.append(dic.index(op[0]))
        if op[0] in ['JMP', 'PUSH']:
            if op[0] == 'PUSH':
                ops.append(int(op[1]))
            else:
                ops.append(op[1])
            index += 2
        else:
            index += 1

print('[Op]: ')
for index, i in enumerate(ops):
    if type(i) == str:
        ops[index] = table[i]
    print(f'\t{ops[index]}', end='' if (index+1) % 4 else '\n')

print('\n[Status]: Compiled.')

for i in ops:
    out.write(struct.pack('i', i))
out.close()

print('[Status]: Finished.')
