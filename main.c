#include "emulator.h"

unsigned long CPU_CLOCK = 0;
unsigned short breakpoint = 0xFFFF;
unsigned short custom_PC = CLEAR;

int main()
{
    unsigned short IR, instr;
    char UI[MAX_USER_INPUT_LEN];

    // TODO: add argc and argv checks to open file through drag and drop

    // TODO: set initial CPU states, see p.81 XMX Design Doc
    PC = PC_default;
    SP = SP_default;
    PSW.C = CLEAR;
    PSW.N = CLEAR;
    PSW.V = CLEAR;
    PSW.Z = CLEAR;

    while (1)
    {
        printf("\n**** XMX Emulator - User Interface *****\n");
        printf("CPU clock cycles: %lu\n", CPU_CLOCK);
        printf("r   - run\n");
        printf("md  - Memory Dump\n");
        printf("drf - Display Register File\n");
        printf("mrf - Modify Register File\n");
        printf("sb  - Set Breakpoint\n");
        printf("sp  - Set PC\n");
        printf("E   - Exit Emulator\n");

        printf("> ");
        scanf("%s", UI);
        getchar();


        if (strcmp(UI, "r") == 0)  // run
        {
            // load data/instructions into main memory
            loader();

            while (PC < breakpoint && IR != BREAK_INSTRUCTION)
            {
                printf("\n");
                IR = fetch();
                instr = decode(IR);
                if (instr == END_i) break;
                printf("passing instr number: %d\n", instr);
                execute(instr, IR);
                display_regfile();
            }
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
            printf("Specify breakpoint location\n");
            printf("> ");
            scanf("%hX", &breakpoint);
            getchar();

        }
        else if (strcmp(UI, "sp") == 0)  // set custom PC
        {
            printf("> ");
            scanf("%hX", &PC);
            getchar();
            custom_PC = SET;
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
