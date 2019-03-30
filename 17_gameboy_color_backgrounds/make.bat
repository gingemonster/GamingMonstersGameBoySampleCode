c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o BackgroundData.o BackgroundData.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o BackgroundMap.o BackgroundMap.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j  -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o gbcbackground.gb BackgroundMap.o BackgroundData.o main.o

DEL *.lst
DEL *.o
DEL *.map
DEL *.sym