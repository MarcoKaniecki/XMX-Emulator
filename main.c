#include "emulator.h"

unsigned short custom_breakpoint_loc;
unsigned long CPU_CLOCK = 0;

int main()
{
    unsigned short IR, action, first_run = TRUE;
    char UI[MAX_USER_INPUT_LEN];

    // TODO: add argc and argv checks to open file through drag and drop

    // TODO: set initial CPU states, see p.81 XMX Design Doc

    while (1)
    {
        printf("\n**** XMX Emulator - User Interface *****\n");
        printf("CPU clock cycles: %lu\n", CPU_CLOCK);
        printf("r   - run\n");
        printf("md  - Memory Dump\n");
        // printf("dc  - Display Contents at Memory Location\n");
        printf("drf - Display Register File\n");
        printf("mrf - Modify Register File\n");
        printf("sb  - Set Breakpoint\n");
        printf("cb  - Clear Breakpoint\n");
        printf("sp  - Set Custom PC\n");
        printf("rp  - Revert PC\n");
        printf("E   - Exit Emulator\n");

        printf("> ");
        scanf("%s", UI);
        getchar();


        if (strcmp(UI, "r") == 0)  // run
        {
            action = 1;  // reset if another run is performed

            // load data/instructions into main memory
            if (first_run)
            {
                loader();
                first_run = FALSE;
            }

            while (action != END)
            {
                IR = fetch();
                if (IR != 0)
                    printf("Sending to Decoder... %X\n", IR);

                action = decode(PC, IR);
            }
            // execute run from decode func
        }
        else if (strcmp(UI, "md") == 0)  // Memory dump
            memory_dump();
        else if (strcmp(UI, "drf") == 0)  // display register file
        {
            char modify_rf;

            display_regfile();

            printf("modify? y/n\n");
            printf("> ");
            scanf("%c", &modify_rf);
            if (modify_rf == 'y' || modify_rf == 'Y')
                modify_regfile();
        }
        else if (strcmp(UI, "mrf") == 0)  // modify register file
        {
            modify_regfile();
        }
        else if (strcmp(UI, "sb") == 0)  // set breakpoint
        {
            // TODO: currently not working because loader is overwriting breakpoint location when running program again
            int set_breakpoint;
            // value to be set will be 0x6000
            printf("Specify breakpoint location as word\n");
            printf("> ");
            scanf("%X", &set_breakpoint);
            getchar();
            set_custom_breakpoint(set_breakpoint);
        }
        else if (strcmp(UI, "cb") == 0)  // clear breakpoint
        {
            memory.word[custom_breakpoint_loc] = data_overwritten_at_breakpoint;
            printf("Cleared custom breakpoint location\n");
        }
        else if (strcmp(UI, "sp") == 0)  // set custom PC
        {
            int set_starting_adr;

            printf("Specify PC location as word\n");
            printf("> ");
            scanf("%X", &set_starting_adr);
            getchar();
            set_PC(set_starting_adr);

        }
        else if (strcmp(UI, "rp") == 0)  // revert PC to what was given in S-Record input file
        {
            printf("Removing custom PC location...\n");
            custom_PC = CLEAR;
        }
        else if (strcmp(UI, "E") == 0)  // exit program
        {
            printf("Exiting...\n");
            return 0;
        }
        else
        {
            printf("Invalid Command\n");
        }

    }

}
