import struct
import binascii

bmpcout = open("splash_screen.txt", 'r')
output = open("splash.pi", 'w')
for line in bmpcout:
    ints = line.split(',')[:-1]
    ints = [x[3:] for x in ints]
    for i in ints:
        if(len(i) == 4):
            output.write(struct.pack('B', int(i, base=16)/256))
            output.write(struct.pack('B', int(i, base=16)%256))
output.close()
