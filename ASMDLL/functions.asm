.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.code

MyProc1 proc x: DWORD, y: DWORD
xor eax,eax 
mov eax,x 
mov ecx,y 
ror ecx,1 
shld eax,ecx,2 
jnc ET1 
mul y 
ret 
ET1: 
Mul x 
Neg y 
ret
MyProc1 endp

Histogram proc BMP: PTR BYTE, imageSize: DWORD, red: PTR DWORD, green: PTR DWORD, blue: PTR DWORD 
xor eax,eax 
ret
Histogram endp

end MyProc1