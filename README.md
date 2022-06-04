# ECED3403 - Computer Architecture - XMX-Emulator
## Problem being solved

Before head-office can decide whether to proceed with the XMX project which is an extension
of the original XM processor with twice as many registers, an emulator has to be written in
software to examine how XMX will operate under certain test conditions. The following parts of
XMX’s ISA are to be emulated, including all CPU registers (R0-R7, A0-A3, A4/BP, A5/LR, A6/SP,
and A7/PC), all instructions, the program status word (PSW), addressing modes, encoded
constants, 64KiB of byte-addressable primary memory, and CPU execution time.
Since the new computer could have an entirely new architecture, support software would be
required. In our case a simple debugger as part of the emulator, which contains functions such
as a loader, register display, memory display, breakpoints, aborting programs and choosing
where to start running a program.
