;---------------------------------------------------------------------
; ROZMYCIE OBRAZU I HISTOGRAM
; 30.10.2020 Mateusz Migot 
; Informatyka SSI semestr 5
; v0.1 - pierwsza wersja: zaimplementowany algorytm obliczaj¹cy histogram obrazu (29.10.2020)
;---------------------------------------------------------------------

.data
gaussMatrix BYTE 1,2,1,2,4,2,1,2,1


.code
_TEXT SEGMENT

_DllMainCRTStartup PROC 

mov rax, 1 
ret

_DllMainCRTStartup ENDP
;------------------------------
;Funkcja o nazwie "Histogram" obliczaj¹ca histogram sk³adowych RGB bitmapy
;parametry wejœciowe procedury: BMP jest tablic¹ pixeli bitmapy, imageWidth - szerokoœæ obrazu, startHeight i endHeight - numery wierszy, dla których funkcja ma obliczyæ histogram
;red, green, blue - wskaŸniki do tablic, które przetrzymuj¹ obliczony histogram 
;------------------------------
;void histogram(BYTE* pixels, int* r, int* g, int* b, int imageWidth, int startHeight, int endHeight)
;pixels -> rcx, red -> rdx, green -> r8, blue -> r9
histogram proc

LOCAL startHeight: QWORD,
      endHeight: QWORD,
      imgWidth: QWORD,
      bmp: PTR BYTE,
      red: PTR DWORD,
      green: PTR DWORD,
      blue: PTR DWORD

xor r10,r10
xor r11,r11
xor r12,r12

mov r10d, dword ptr[rbp+48]
mov r11d, dword ptr[rbp+56]
mov r12d, dword ptr[rbp+64]

mov startHeight, r11
mov endHeight, r12


mov bmp, rcx
mov red, rdx
mov green, r8
mov blue, r9
mov r11, rcx
mov r12, rdx

mov rax, r10
imul rax, 3
mov imgWidth, rax
imul rax, startHeight
mov rcx, rax


mov rax, imgWidth
imul rax, endHeight
mov r12, rax

mainLoop:

mov r11, bmp
add r11, rcx ; BMP[i] address



movzx r9, byte ptr [r11] ; BMP[i]
imul r9, 4


mov r8, blue
add r8, r9 ;red[bmp[i]]
mov eax, dword ptr[r8]

inc rax
mov dword ptr [r8], eax

inc rcx

mov r11, bmp
add r11, rcx ; BMP[i] address
movzx r9, byte ptr [r11] ; BMP[i]
imul r9, 4
mov r8, green
add r8, r9 ;red[bmp[i]]
mov eax, dword ptr[r8]
inc rax
mov dword ptr [r8], eax


inc rcx

mov r11, bmp
add r11, rcx ; BMP[i] address
movzx r9, byte ptr [r11] ; BMP[i]
imul r9, 4
mov r8, red
add r8, r9 ;red[bmp[i]]
mov eax, dword ptr[r8]
inc rax
mov dword ptr [r8], eax

inc rcx

cmp rcx, r12
jae Koniec
jmp mainLoop

Koniec:
ret
histogram endp




gaussBlur proc BMP: PTR BYTE, bmpSize: DWORD, imageWidth: DWORD, startHeight: DWORD, endHeight: DWORD
Koniec:
ret
GaussBlur endp
_TEXT ENDS
end