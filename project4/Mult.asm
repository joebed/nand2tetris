// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.


// It is also given in project spec that R0>=0 and R1>=0

    // Zero out the output register
    @0
    D=A
    @R2
    M=D

    // R1 is going to be our counter, so this does change the data in R1 but allows us to do this without another register
    @R1
    D=M
    @LOOP
    D;JGT
    @END
    0;JMP
(LOOP)
    // Add R0 to output
    @R0
    D=M
    @R2
    M=D+M
    // Update counter
    @R1
    M=M-1
    D=M
    @LOOP
    D;JGT
(END)
