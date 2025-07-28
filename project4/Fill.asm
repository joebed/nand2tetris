// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(MAIN)
    // Set color depending on if there is keyboard input
    @KBD
    D=M
    @PICKWHITE
    D;JEQ

    // If any key is pressed, pick black
    @color
    M=-1
    @ENDPICKCOLOR
    0;JMP

    (PICKWHITE)
        @color
        M=0

    (ENDPICKCOLOR)

    // Draw the screen. Can optimize by only calling this when a new input is pressed/released
    @DRAWSCREEN
    0;JMP
    (ENDDRAWSCREEN)

    @MAIN
    0;JMP    // Jump back to the top of the main loop


// Function: Draws the screen to have the color in @color
(DRAWSCREEN)
    @SCREEN
    D=A
    @addr
    M=D
    @SCREENEND
    M=D
    @8192
    D=A
    @SCREENEND
    M=D+M
    (DRAWSCREENLOOP)
        @color
        D=M
        @addr
        A=M
        M=D
        @addr
        MD=M+1
        @SCREENEND
        D=M-D
        @DRAWSCREENLOOP
        D;JGT

    @ENDDRAWSCREEN
    0;JMP
