;---------------------------------------------------------------------
; ROZMYCIE OBRAZU I HISTOGRAM
; 30.10.2020 Mateusz Migot 
; Informatyka SSI semestr 5
; v0.1 - pierwsza wersja: zaimplementowany algorytm obliczaj¹cy histogram obrazu (29.10.2020)
;---------------------------------------------------------------------
.386
.model flat,stdcall

.data
endPoint dword ?

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

;------------------------------
;Funkcja o nazwie "Histogram" obliczaj¹ca histogram sk³adowych RGB bitmapy
;parametry wejœciowe procedury: BMP jest tablic¹ pixeli bitmapy, imageWidth - szerokoœæ obrazu, startHeight i endHeight - numery wierszy, dla których funkcja ma obliczyæ histogram
;red, green, blue - wskaŸniki do tablic, które przetrzymuj¹ obliczony histogram 
;------------------------------
Histogram proc BMP: PTR BYTE, imageWidth: DWORD, startHeight: DWORD, endHeight: DWORD, red: PTR DWORD, green: PTR DWORD, blue: PTR DWORD 

mov eax, imageWidth
mov ebx, 3
mul ebx ; width
mov ebx, endHeight
mul ebx 
sub eax, 3
mov ecx, eax
mov eax, imageWidth
mov ebx, 3
mul ebx ; width
mov ebx, startHeight
mul ebx
mov endPoint, eax

mainLoop:

dec ecx

mov         eax,dword ptr [BMP]  
add         eax, ecx  
mov         ebx, ecx
movzx       ecx,byte ptr [eax]
mov         edx,dword ptr [red]
mov         eax,dword ptr [edx+ecx*4]  
add         eax,1 
mov         ecx,dword ptr [BMP]  
add         ecx,dword ptr ebx  
movzx       edx,byte ptr [ecx]  
mov         ecx,dword ptr [red]  
mov         dword ptr [ecx+edx*4],eax
mov         ecx,ebx  

dec ecx


mov         eax,dword ptr [BMP]  
add         eax, ecx  
mov         ebx, ecx
movzx       ecx,byte ptr [eax]
mov         edx,dword ptr [green]
mov         eax,dword ptr [edx+ecx*4]  
add         eax,1 
mov         ecx,dword ptr [BMP]  
add         ecx,dword ptr ebx  
movzx       edx,byte ptr [ecx]  
mov         ecx,dword ptr [green]  
mov         dword ptr [ecx+edx*4],eax
mov         ecx,ebx  

dec ecx

jz Koniec

mov         eax,dword ptr [BMP]  
add         eax, ecx  
mov         ebx, ecx
movzx       ecx,byte ptr [eax]
mov         edx,dword ptr [blue]
mov         eax,dword ptr [edx+ecx*4]  
add         eax,1 
mov         ecx,dword ptr [BMP]  
add         ecx,dword ptr ebx  
movzx       edx,byte ptr [ecx]  
mov         ecx,dword ptr [blue]  
mov         dword ptr [ecx+edx*4],eax
mov         ecx,ebx

cmp ecx, endPoint
jb Koniec
jmp mainLoop ;jezeli licznik nie jest rowny 0, idz do poczatku petli
Koniec:
ret
Histogram endp

end MyProc1