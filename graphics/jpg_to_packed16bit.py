import struct
import binascii

bmpcout = open("splash_screen.txt", 'r')
output = open("splash.pi", 'w')
for line in bmpcout:
    ints = line.split(',')[:-1]
    ints = [x[3:] for x in ints]
    for i in ints:
        output.write(binascii.a2b_hex(i))
output.close()
