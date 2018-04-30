from scipy.io import wavfile
import struct

song = wavfile.read("song-441khz.wav")
target = open("song-441khz.ebw", "wb")

for i in song[1]:
    target.write(
        struct.pack(
            'B',
            int((i[0] + i[1]) / 256 + 128))
    );

target.close();

