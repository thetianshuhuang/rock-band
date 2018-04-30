from scipy.io import wavfile
import struct

song = wavfile.read("The Police - Message in a Bottle (44.1kHz).wav")
target = open("song_out.bw", "wb")

for i in song[1]:
    val = int((int(i[0]) + int(i[1])) / 512 + 128)
    if(val > 255):
        print(val)
        print("Integer overflow")
        val = 255
    if(val < 0):
        print(val)
        print("Integer underflow")
        val = 0
    
    target.write(
        struct.pack(
            'B', val))

target.close();

