#include <gb/gb.h>
#include <stdio.h>

void main(){
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels


    while(1) {
        UBYTE joypad_state = joypad();
        
        if(joypad_state) {   
            // bit 5-0 Sound length
            // 0001 1111 is 0x1F the maximum length
            NR41_REG = 0x1F;

            // volume envelope
            // bit 7-4 - Initial Volume of envelope (0-0Fh) (0=No Sound)
            // bit 3 - Envelope Direction (0=Decrease, 1=Increase)
            // bit 2-0 - Number of envelope sweep (n: 0-7) (If zero, stop envelope operation.)
            // 1111 0001 is 0xF1, start at full volume, fade down, 1 envelope sweep  (decimal)
            NR42_REG = 0xF1;

            // bit 7-4 - Shift Clock Frequency (s)
            // bit 3   - Counter Step/Width (0=15 bits, 1=7 bits)
            // bit 2-0 - Dividing Ratio of Frequencies (r)
            // The amplitude is randomly switched between high and low at the given frequency. 
            // A higher frequency will make the noise to appear 'softer'. 
            // When Bit 3 is set, the output will become more regular, and some frequencies will sound more like Tone than Noise.
            // 0011 0000 is 0x30, shift clock frequency 3, step 0, dividing ratio 0
            NR43_REG = 0x30;

            // bit 7   - Initial (1=Restart Sound)
            // bit 6   - Controls if last forever or stops when NR41 ends
            // (1=Stop output when length in NR41 expires)
            // bit 5-0	Unused
            // 1100 0000, start sound, not continuous
            NR44_REG = 0xC0;  

            delay(1000);
        }
    }
}