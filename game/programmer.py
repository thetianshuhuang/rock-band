import pygame
import time
import struct

pygame.init()
screen = pygame.display.set_mode((400, 300))
done = False

# capture notes
notes = []
while not done:
    for event in pygame.event.get():
        keys = 0
        if event.type == pygame.KEYDOWN:
            if(event.key == pygame.K_a):
                keys += 1
            if(event.key == pygame.K_s):
                keys += 2
            if(event.key == pygame.K_d):
                keys += 4
            if(event.key == pygame.K_f):
                keys += 8
            if(keys !=0):
                notes.append([
                    keys,
                    int(time.time() * 441)])
            if(event.key == pygame.K_SPACE):
                done = True
pygame.quit()
print(notes)

# align notes
notesProcessed = []
for i in notes:
    if(len(notesProcessed) == 0):
        notesProcessed.append(i)
    elif(i[1] - notesProcessed[len(notesProcessed) - 1][1] < 20):
        notesProcessed[-1][0] |= i[0]
    else:
        notesProcessed.append(i)
print(notesProcessed)

# calculate offset
notesDiff = [[notesProcessed[0][0], 0]]
for i in range(len(notesProcessed) - 1):
    notesDiff.append([
        notesProcessed[i + 1][0],
        notesProcessed[i + 1][1] - notesProcessed[i][1]])
print(notesDiff)

# get pack
notesPacked = [(i[0] << 12) + i[1] for i in notesDiff]

outfile = open("rylah_b.rb", "w")
for i in notesPacked:
    outfile.write(struct.pack('H', i))
outfile.close()
