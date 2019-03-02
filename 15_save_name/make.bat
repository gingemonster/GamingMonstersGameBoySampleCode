REM added savestate see http://www.devrs.com/gb/files/sram.txt
c:\gbdk\bin\lcc -Wa-l -Wf-ba0 -c -o savestate.o savestate.c
c:\gbdk\bin\lcc -Wa-l -c -o main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo4 -Wl-ya4 -o main.gb main.o savestate.o
