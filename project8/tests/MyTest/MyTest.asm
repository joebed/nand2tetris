// SP initialization
@256
D=A
@SP
M=D
// LCL initialization
@300
D=A
@LCL
M=D
// ARG initialization
@400
D=A
@ARG
M=D
// THIS initialization
@3000
D=A
@THIS
M=D
// THAT initialization
@3010
D=A
@THAT
M=D
// push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
// push argument 2
@2
D=A
@ARG
A=D+M
D=A
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
A=M
M=D
// pop argument 1
@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
(END)
@END
0;JMP
