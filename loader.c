// Decoding S-records
// Marco Kaniecki
// B00783186

#include "emulator.h"

union mem memory = {0};

FILE *infile;
char srec[MAX_REC_LEN];

int loader()
{
    // program that reads and decodes s-records
    unsigned int rec_chksum;
    unsigned char type, type_num, checksum;
    unsigned int count, ahi, alo, byte;
    unsigned short address, final_addr;

    infile = fopen("Lab1.xme", "r");

    while(fgets(srec, MAX_REC_LEN, infile) > 0)
    {
        // parse first character
        sscanf(&srec[0], "%c", &type);

        // parse second char which determines the function of the record
        // 0 - header
        // 1 - data/instr
        // 9 - end record
        sscanf(&srec[1], "%c", &type_num);

        // check if first char is valid
        if (type != 'S' || (type_num > 2 && type_num < 9))
        {
            printf("bad type: %s", srec);
            continue;
        }

        sscanf(&srec[2], "%2x", &count);

        // check if count is correct
        // srec - 4 to remove type, count, LF and NUL and /2 to have number of bytes
        if (count != (strlen(srec) - 6) / 2)
        {
            printf("bad count: %s", srec);
            continue;
        }

        sscanf(&srec[4], "%2x%2x", &ahi, &alo);

        // convert from big-endian to little-endian
        address = ahi << 8 | alo;

        checksum = address + count;

        // determine data
        int pos = 8;
        count = count - 2;

        // header
        if (type_num == '0')
        {
            // stop when checksum byte is reached
            while (count != 1)
            {
                // read byte by byte
                sscanf(&srec[pos], "%2x", &byte);
                printf("%c", byte);
                count = count - 1;
                pos = pos + 2;
                checksum = checksum + byte;
            }
            sscanf(&srec[pos], "%2x", &rec_chksum);
            checksum = checksum + rec_chksum;

            if (checksum != 0xff)
            {
                // printf("bad checksum %s", srec);
                continue;
            }
            printf("\n");
        }
        else if (type_num == '1')  // data/instr
        {
            // assign bytes to memory
            while (count != 1)
            {
                sscanf(&srec[pos], "%2x", &byte);

                memory.byte[address] = byte;
                // printf("%X %X\n", address, byte);

                address++;
                count = count - 1;
                pos = pos + 2;
                checksum = checksum + byte;
            }
            sscanf(&srec[pos], "%2x", &rec_chksum);
            checksum = checksum + rec_chksum;

            if ((checksum & 0x0F) != 0x0F)
            {
                // printf("bad checksum: %s", srec);
                // continue;
            }
            // assign final addr at highest memory location
            if (final_addr < address)
                final_addr = address;
        }
        else if (type_num == '9')
        {
            pos = 2;
            sscanf(&srec[pos], "%2x", &count);
            pos+=2;

            while (count != 1)
            {
                sscanf(&srec[pos], "%2x", &byte);
                count = count - 1;
                pos = pos + 2;
                checksum = checksum + byte;
            }
            sscanf(&srec[pos], "%2x", &rec_chksum);
            checksum = checksum + rec_chksum;

            if (checksum != 0xFF)
            {
                // printf("bad checksum: %s", srec);
                // continue;
            }

            regfile[0][PC] = address;
            // printf("Starting address: %x", address);
        }
    }
    // add a terminator which ends program when last data/instr in
    // loader has been loaded into mem
    memory.word[(final_addr >> 1) + 1] = DONE;

    printf("\n********** LOADER DONE **********\n");
    fclose(infile);
    return 0;
}
