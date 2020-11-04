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


;bmp -> rcx, bmpSize -> rdx, imageWidth -> r8, startHeight -> r9, endHeight -> stack
gaussBlur proc
LOCAL   pixels: PTR BYTE,
        bmpSize: QWORD, 
        imageWidth: QWORD,
        startHeight: QWORD, 
        endHeight: QWORD,
        blurredPixel: QWORD

xor r10, r10
mov r10d, dword ptr[rbp+48]
mov endHeight, r10

mov pixels, rcx
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
mov blurredPixel, 0

;pierwszy index: i-width-3
mov rax, pixels
add rax, rcx 
sub rax, 3 ; BMP[i-3]
sub rax, imageWidth
movzx r15, byte ptr [rax]
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;drugi index: i - width
mov rax, pixels
add rax, rcx
sub rax, imageWidth
movzx r15, byte ptr [rax]
imul r15, 2
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;trzeci index: i - width + 3
mov rax, pixels
add rax, rcx
sub rax, imageWidth
add rax, 3
movzx r15, byte ptr [rax]
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;czwarty index: i-3
mov rax, pixels
add rax, rcx 
sub rax, 3 ; BMP[i-3]
movzx r15, byte ptr [rax]
imul r15, 2
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;piaty index: i
mov rax, pixels
add rax, rcx 
movzx r15, byte ptr [rax]
imul r15, 4
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;szosty index: i+3
mov rax, pixels
add rax, rcx 
add rax, 3 ; BMP[i-3]
movzx r15, byte ptr [rax]
imul r15, 2
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;siodmy index: i+width-3
mov rax, pixels
add rax, rcx 
sub rax, 3 ; BMP[i-3]
add rax, imageWidth
movzx r15, byte ptr [rax]
imul r15, 1
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;osmy index: i+width
mov rax, pixels
add rax, rcx 
add rax, imageWidth
movzx r15, byte ptr [rax]
imul r15, 2
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax

;siodmy index: i+width+3
mov rax, pixels
add rax, rcx 
add rax, 3 ; BMP[i-3]
add rax, imageWidth
movzx r15, byte ptr [rax]
imul r15, 1
mov rax, blurredPixel
add rax, r15
mov blurredPixel, rax


;Podzielenie wynikowego pixela przez 16
xor rax, rax
mov rax, blurredPixel
;mov r14, 16
sar rax, 4
mov blurredPixel, rax

; aktualny pixel
mov r14, pixels
add r14, rcx
mov byte ptr [r14], al

cmp rcx, r12
jae Koniec
jmp mainLoop

Koniec:
ret
GaussBlur endp
_TEXT ENDS
end