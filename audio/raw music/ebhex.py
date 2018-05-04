from scipy.io import wavfile
import struct

song = wavfile.read("Band Of Horses - The Funeral (Y2K x Honest Remix) (BassBoosted).wav")
target = open("song_out.bw", "wb")

val_previous = 128
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
    if(abs(val - val_previous) > 128):
        print("Warning: large change")
        print(val)
        print(val_previous)
    target.write(struct.pack('B', val))
    val_previous = val
target.close();
