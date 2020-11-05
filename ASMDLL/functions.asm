;---------------------------------------------------------------------
; ROZMYCIE OBRAZU I HISTOGRAM
; 30.10.2020 Mateusz Migot 
; Informatyka SSI semestr 5
; v0.1 - pierwsza wersja: zaimplementowany algorytm obliczaj¹cy histogram obrazu (29.10.2020)
;---------------------------------------------------------------------

.data
gaussMatrix:
word 1
word 1
word 1
word 2
word 2
word 2
word 1
word 1
word 1
word 2
word 2
word 2
word 4
word 4
word 4
word 2
word 2
word 2
word 1
word 1
word 1
word 2
word 2
word 2
word 1
word 1
word 1


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

createPacket:
mov r11, bmp
movdqu xmm0, [r11 + rcx]

mainLoop:

pextrb rbx, xmm0, 0
imul rbx, 4
mov r9, blue
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 1
imul rbx, 4
mov r9, green
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 2
imul rbx, 4
mov r9, red
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 3
imul rbx, 4
mov r9, blue
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 4
imul rbx, 4
mov r9, green
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 5
imul rbx, 4
mov r9, red
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 6
imul rbx, 4
mov r9, blue
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 7
imul rbx, 4
mov r9, green
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 8
imul rbx, 4
mov r9, red
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 9
imul rbx, 4
mov r9, blue
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 10
imul rbx, 4
mov r9, green
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 11
imul rbx, 4
mov r9, red
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 12
imul rbx, 4
mov r9, blue
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 13
imul rbx, 4
mov r9, green
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

pextrb rbx, xmm0, 14
imul rbx, 4
mov r9, red
add r9, rbx 
mov eax, dword ptr [r9]
inc rax
mov dword ptr [r9], eax

add rcx, 15

cmp rcx, r12
jae Koniec
jmp createPacket

Koniec:
ret
histogram endp


;bmp -> rcx, bmpSize -> rdx, imageWidth -> r8, startHeight -> r9, endHeight -> stack
gaussBlur proc
LOCAL   pixels: PTR BYTE,
        bmpSize: QWORD, 
        imageWidth: QWORD,
        startHeight: QWORD, 
        endHeight: QWORD,
        blurredPixel: QWORD

movdqu xmm0, oword ptr[gaussMatrix]
movdqu xmm1, oword ptr[gaussMatrix + 6]
movdqu xmm2, oword ptr[gaussMatrix + 12]

movdqu xmm3, oword ptr[gaussMatrix + 18]
movdqu xmm4, oword ptr[gaussMatrix + 24]
movdqu xmm5, oword ptr[gaussMatrix + 30]


xor r10, r10
mov r10d, dword ptr[rbp+48]
mov endHeight, r10

mov pixels, rcx
mov r15, rcx
mov bmpSize, rdx
mov startHeight, r9


mov rax, r8
imul rax, 3
mov imageWidth, rax
imul rax, startHeight
mov rcx, rax


mov rax, imageWidth
imul rax, endHeight
mov r12, rax

mainLoop:

inc rcx
; i-width-3>=0

mov rax, rcx
sub rax, imageWidth
sub rax, 3
cmp rax, 0
jl mainLoop

; i +width+3 <size
mov rax, rcx
add rax, imageWidth
add rax, 3
cmp rax, bmpSize
jae Koniec

;MAIN PART OF FUNCTION

;pierwszy index: i-width-3
mov rax, pixels
add rax, rcx 
sub rax, imageWidth
sub rax, 3

pmovzxbw xmm6, [rax]
add rax, 3
pmovzxbw xmm7, [rax]
add rax, 3
pmovzxbw xmm8, [rax]

add rax, imageWidth
pmovzxbw xmm9, [rax]
sub rax, 3
pmovzxbw xmm10, [rax]
sub rax, 3
pmovzxbw xmm11, [rax]

add rax, imageWidth
pmovzxbw xmm12, [rax]
add rax, 3
pmovzxbw xmm13, [rax]
add rax, 3
pmovzxbw xmm14, [rax]

pmullw xmm6, xmm0
pmullw xmm7, xmm1
pmullw xmm8, xmm2

pmullw xmm9, xmm3
pmullw xmm10, xmm4
pmullw xmm11, xmm5

pmullw xmm12, xmm0
pmullw xmm13, xmm1
pmullw xmm14, xmm2

paddw xmm6, xmm7
paddw xmm6, xmm8
paddw xmm6, xmm9
paddw xmm6, xmm10
paddw xmm6, xmm11
paddw xmm6, xmm12
paddw xmm6, xmm13
paddw xmm6, xmm14

psrlw xmm6, 4

; aktualny pixel
;mov ebx, ecx
;mov ecx, dword ptr [BMP]
;add ecx, ebx
;mov byte ptr [ecx], al

pextrw r9, xmm6, 0
pextrw r10, xmm6, 1
pextrw r14, xmm6, 2


mov r11, pixels
add r11, rcx 

mov byte ptr[r11], r9b
add r11, 1
mov byte ptr[r11], r10b
add r11, 1
mov byte ptr[r11], r14b

add rcx, 1

cmp rcx, r12
jae Koniec
jmp mainLoop

Koniec:
ret
GaussBlur endp
_TEXT ENDS
end