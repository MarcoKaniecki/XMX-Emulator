// Loader.c
// Decoding S-records
// Marco Kaniecki

#include "emulator.h"

union mem memory = {0};

int loader()
{
    // program that reads and decodes s-records
    unsigned int rec_chksum, count, ahi, alo, byte;
    unsigned char type, type_num, checksum;
    unsigned short address;

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
        if (type != 'S' || (type_num > S1_REC && type_num < S9_REC))
            printf("bad type: %s", srec);

        sscanf(&srec[2], "%2x", &count);

        // check if count is correct
        // srec - 5 to remove type, count, and LF, and /2 to have number of bytes
        if (count != (strlen(srec) - TYPE_COUNT_LF_LEN) / 2)
            printf("bad count: %s", srec);

        sscanf(&srec[4], "%2x%2x", &ahi, &alo);

        // convert from big-endian to little-endian
        address = ahi << 8 | alo;

        checksum = address + count;

        // determine data
        int pos = LOADER_DATA_INIT_POS;
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

            if ((checksum & 0x0F) != 0x0F)
                printf("bad checksum %s", srec);
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
                printf("bad checksum: %s", srec);
        }
        else if (type_num == '9')
        {
            pos = 2;
            sscanf(&srec[pos], "%2x", &count);
            pos += 2;

            while (count != 1)
            {
                sscanf(&srec[pos], "%2x", &byte);
                count = count - 1;
                pos = pos + 2;
                checksum = checksum + byte;
            }
            sscanf(&srec[pos], "%2x", &rec_chksum);
            checksum = checksum + rec_chksum;

            if (custom_PC == CLEAR)
                regfile[0][15].word = address;  // assign program counter to starting addr

            if ((checksum & 0x0F) != 0x0F)
                printf("bad checksum: %s", srec);
        }
    }

    printf("LOADER DONE\n");
    fclose(infile);
    return 0;
}
