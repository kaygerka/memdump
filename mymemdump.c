#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Hold the ASCII characters & Ensure null termination
    unsigned char buff[17];
    buff[16] = '\0';

    for (int i = 0; i < len; i++) {
        // Print address at the beginning of every 16 bytes
        if (i % 16 == 0) {
            if (i != 0) {
                // Print the ASCII buffer before moving to the next line
                fprintf(fd, " %s\n", buff);
            }
            fprintf(fd, "0x%016lX: ", (unsigned long)(p + i));
        }

        // Get value at [p]
        int c = p[i] & 0xFF;

        // Print byte as hexadecimal
        fprintf(fd, "%02X ", c);

        // Print byte if it's printable; else print '.'
        if (c < 32 || c > 126) {
            // Non-printable character
            buff[i % 16] = '.'; 
        } else {
            // Printable character
            buff[i % 16] = c; 
        }

        // Null-terminate the buff for safe printing
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters
    while (len % 16 != 0) {
        // Print padding in hex & Increment len to match the output
        fprintf(fd, "   "); 
        len++;
    }

    // Print the final ASCII representation
    fprintf(fd, " %s\n", buff);
}

