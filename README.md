# EE319K Final Project: Rock Band
Tianshu Huang and Quinn Buoy

![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/main.JPG)

## Game Overview
### Features
- 44.1kHz, 8 bit audio
- Audio and tracks via SD read
- inifinitely many songs supported, just by expanding the menu
- Full resolution (128x160) splash screens

### Dependencies
- tm4c123gh6p.h (tm4c hardware register definition file)
- PLL.h (TM4C PLL; used for 80mHz clock)
- FATFS; ST7735.h and diskio.h from Valvanoware (modified)

### Libraries and Modules
- Network: token network implementation, modified from Serial Token Ring
- Audio: SD read and DAC out; 8 bit x 44.1kHz (44.1kBps bitrate)
- Controller: Four digital and one analog, and derivative routines for the strummer
- Game: Core game control
- Display: SD drivers and display routines
- Menu: Generalized menu library using function pointers
- Graphics: Display routines for the guitar, splash screen, and misc utilities

### File Types
- Packed Image (.pi): packed 5-6-5 GBR 16-bit image, uncompressed, scanning starting from bottom left, across, then up
- Byte wave file (.bw): raw audio file, bit-depth of 8, 44.1kHz
- Rock Band Track (.rb): 16-bit array.
```
| R | Y | B | G | Reserved | Reserved | -- (10) Tick -- |
```
	- R, Y, B, G indicates whether each drum should be hit (1) at that note
or not (0).
	- Tick indicates the number of updates (441 updates/s or 100 audio ticks/update)
before the next note.

## Gameplay
Navigate the menus using the four buttons or by hitting the drums.
<img src="https://github.com/thetianshuhuang/rock-band/blob/master/images/instructions.JPG" width="100">
At first, the Menu screen will have a black background. Navigate to 'select instrument', and choose the desired instrument. Then, the background will change to match the chosen instrument. Then, select 'Enable Full Mode' to disable the 2:30 time limit on song duration if desired.

![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/menu.JPG){:height="400", width="300"}
![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/songs1.JPG){:height="400", width="300"}
![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/songs2.JPG){:height="400", width="300"}
All but one device should choose 'Join Lobby'. These devices will wait for the main ('Lobby Leader') device to choose a song, and join in.
![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/multiplayer.JPG)
All devices on the multiplayer "Waiting for Song Selection" screen will join the main device once a song is selected.
After a song is started, notes will scroll down the screen. Play notes by holding down the appropriate buttons and strumming (guitar/bass) or by hitting the drum pads. Hit notes will increase the score; missed notes will decrease the score. Once enough notes are hit, Star Power is enabled, turning the frets yellow and the notes white, and provides a score multiplier. Poor performance increases the difficulty of obtaining Star Power. The duration of Star Power increases on successful note hits, and decreases greatly on missed notes. 
![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/normal.JPG)
![Screenshot](https://github.com/thetianshuhuang/rock-band/blob/master/images/starpower.JPG)


## Materials
### Main Client Board
- Main PCB
- Micro USB to USB A cable
- ST7735R
- Micro SD Card
- Male-to-male cable, 8 pin
### Guitar Controller
- Button board
- Strummer base board
- 6 Pin female to female ribbon cable
### Drum Controller
- Op Amp drum controller board
- 4 Piezo sensors

## Setup instructions
1. Format the SD card as FAT32.
2. Copy the contents of 'resources' to the SD card.
3. Flash code to the TM4C.
4. Plug the TM4C and ST7735R into the main board and insert the SD card in the ST7735R's SD card slot
5. If playing with a guitar, use the 8 pin cable to connect one of the 8 pin connectors on the side of the main board to the 8 pin slot on the guitar. Ensure that the pin on the upper end of the main board (3.3v) is connected to the pin at the bottom of the guitar. Then, connect the male 6 pin connectors on the strummer board and button board. With both boards facing up, the 6 pin cable should be turned 180 degrees.
6. If playing with the drums, plug the 8 pin cable into the top 8 pin connector, with the 3.3v pin connected to the pin closest to the power LED. Then, plug each piezo sensor into the bottom 8 pin connector, with each piezo connected to two adjacent pins.
7. Connect the USB A port of each main board to the USB Micro B port of the next board. Note that the USB cable should not be plugged into either of the TM4C's USB ports. Connect the last board's USB A port to the USB Micro B port of the first board.
8. Connect a 5v source to one of the launchpads, either through the 5v pin or the TM4C's onboard USB port.

