;---------------------------------------------------------------------
; ROZMYCIE OBRAZU I HISTOGRAM
; 06.11.2020 Mateusz Migot 
; Informatyka SSI semestr 5 rok akademicki 2020/2021
; v.0.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.0.2 - stworzony interfejs graficzny oraz wczytywanie i zapisywanie bitmapy (15.10.2020)
; v.0.1 - finalna wersja interfejsu graficznego oraz podstawowe funkcjonalnoœci programu g³ównego (20.10.2020)
; v.0.2.1 - dodanie CppDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ównym (21.10.2020)
; v.0.2.2 - dodanie ASMDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ówny (22.10.2020)
; v.0.2.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu (CppDLL) (22.10.2020)
; v.0.2.4 - zaimplementowany algorytm rozmycia obrazu(CppDLL) (24.10.2020)
; v.0.2.5 - dodanie równoleg³ego wykonywania siê funkcji (27.10.2020)
; v.0.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu(ASMDLL)(wersja 32-bitowa) (29.10.2020)
; v.0.3.1 - zaimplementowany algorytm rozmycia obrazu(ASMDLL)(wersja 32-bitowa) (02.11.2020)
; v.0.4 - zmiana projektu funkcji bibliotecznej(ASMDLL) na wersjê 64-bitow¹ (04.11.2020)
; v.0.5 - zmiana funkcji histogramu i funkcji rozmycia obrazu(ASM) na wersje 64-bitowe (04.11.2020)
; v.0.5 - dodanie operacji wektorowych do histogramu (04.11.2020)
; v.0.6 - finalna wersja funkcji rozmycia obrazu(wykorzystuj¹ca operacje wektorowe) (05.11.2020)
; v.1.0 - finalna i aktualna wersja programu z wszystkimi funkcjonalnoœciami i zabezpieczeniami, zgodna z za³o¿eniami (05.11.2020)
;---------------------------------------------------------------------


.data
;tablica wag zgodna z rozk³adem gaussa, przystosowana do operacji wektorowych
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
;Funkcja odczytuje wartoœæ skadowej danego pixela, a nastepnie inkrementuje element odpowiedniej tablicy(DWORD) o indeksie rownym wartosci skadowej tego pixela
;Wartoœæ pixela znajduje siê w przedziale <0;255>
;parametry wejœciowe procedury: tablica pixeli bitmapy(Byte), szerokoœæ obrazu(DWORD), numery wierszy od i Do których funkcja ma obliczyæ histogram(DWORD)
;wskaŸniki do tablic, które przetrzymuj¹ obliczony histogram 
;funkcja modyfikuje tablice, które przetrzymuj¹ obliczony histogram
;------------------------------
;odpowiednik w cpp: void histogram(Byte * pixels, int * r, int * g, int * b, int imageWidth, int startHeight, int endHeight)
;pixels -> rcx, r -> rbx, g -> r8, b -> r9, imageWidth -> stack, startHeight -> stack, endHeight -> stack
;Rejestry, które siê zmieniaj¹: rax, rbx, rcx, rdx, r8, r9, r10, r11, r12, r13, r14, r15, rip, efl
;Flagi, które ulegaj¹ zmianie: ZR, CY, PE, PL, AC
histogram proc

;wyzeruj rejestr r10
xor r10,r10
;wyzeruj rejestr r11
xor r11,r11
;wyzeruj rejestr r12
xor r12,r12

;skopiuj do rejestru r11, szerokosc bitmapy
mov r10d, dword ptr[rbp+48]
;skopiuj do rejestru r11, parametr startHeight, czyli numer wiersza od ktorego algorytm ma obliczyc histogram
mov r11d, dword ptr[rbp+56]
;skopiuj do rejestru r12, parametr endHeight, czyli numer wiersza do ktorego algorytm ma obliczyc histogram
mov r12d, dword ptr[rbp+64]

;przenies poczatek bitmapy do rejestru r15
mov r15, rcx
;przenies poczatek tablicy przechowujacej histogram dla skladowej niebieskiego do rejestru rsi
mov rsi, r9

;przenies szerokosc bitmapy do rejestru
mov rax, r10
;mnozenie akumulatora przez 3
imul rax, 3
;przechowaj w rejestrze r10 praktyczna szerokosc bitmapy
mov r10, rax 
;mnozenie akumulatora przez numer wiersza od ktorego algorytm ma obliczyc histogram
imul rax, r11
;przenies wartosc akumulatora do rejestru rcx
;rcx bedzie sluzyl jako podstawoway licznik petli
mov rcx, rax

;skopiuj praktyczna szerokosc bitmapy do akumulatora
mov rax, r10
;pomnoz akumulator przez numer wiersza  do ktorego algorytm ma obliczyc histogram
imul rax, r12
;przenies wartosc akumulatora do rejestru r14
;wartosc trzymana w rejestrze r14 to wartosc przy ktorej petla ma sie zatrzymac
mov r14, rax

;poczatek petli
createPacket:
;przenies poczatek bitmapy do rejestru r13
mov r13, r15
;przenies do rejestru xmm0 8 skladowych pixeli poczawszy od adresu na ktory wskazuje poczatek bitmapy powiekszony przez wartosc licznika
;tzn. przenies 8 wartosci od danego indexu (od i  do i + 7)
movdqu xmm0, [r13 + rcx]

mainLoop:

;do rejestru rbx skopiuj pierwszy bajt z rejestru xmm0
pextrb rbx, xmm0, 0
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rsi
mov r9, rsi ;rsi przechowuje poczatek tablicy blue
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj drugi bajt z rejestru xmm0
pextrb rbx, xmm0, 1
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejestr r8
mov r9, r8 ;poczatek tablict green
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj trzeci bajt z rejestru xmm0
pextrb rbx, xmm0, 2
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rdx
mov r9, rdx ;rdx to poczatek tablicy red
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj czwarty bajt z rejestru xmm0
pextrb rbx, xmm0, 3
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rsi
mov r9, rsi
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj piaty bajt z rejestru xmm0
pextrb rbx, xmm0, 4
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest r8
mov r9, r8
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj szosty bajt z rejestru xmm0
pextrb rbx, xmm0, 5
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rdx
mov r9, rdx
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj siodmy bajt z rejestru xmm0
pextrb rbx, xmm0, 6
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rsi
mov r9, rsi
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj osmy bajt z rejestru xmm0
pextrb rbx, xmm0, 7
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest r8
mov r9, r8
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj dziewiaty bajt z rejestru xmm0
pextrb rbx, xmm0, 8
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rdx
mov r9, rdx
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj dziesiaty bajt z rejestru xmm0
pextrb rbx, xmm0, 9
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rsi
mov r9, rsi
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj jedenasty bajt z rejestru xmm0
pextrb rbx, xmm0, 10
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest r8
mov r9, r8
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj dwunasty bajt z rejestru xmm0
pextrb rbx, xmm0, 11
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rdx
mov r9, rdx
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj trzynasty bajt z rejestru xmm0
pextrb rbx, xmm0, 12
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rsi
mov r9, rsi
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy blue o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj czternasty bajt z rejestru xmm0
pextrb rbx, xmm0, 13
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest r8
mov r9, r8
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy green o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;do rejestru rbx skopiuj pietnasty bajt z rejestru xmm0
pextrb rbx, xmm0, 14
;przemnoz rejestr rbx przez 4
imul rbx, 4
;przenies do rejestru r9 rejest rdx
mov r9, rdx
;dodaj wartosc rejestru rbx do rejestru r9
add r9, rbx 
;skopiuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) do rejestru eax
mov eax, dword ptr [r9]
;inkrementuj rejestr rax
inc rax
;modyfikuj wartosc elementu tablicy red o indexie rownym wartosci rejestru rbx(wartosci skladowej pixela) wartoscia z rejestru eax
mov dword ptr [r9], eax

;zwieksz licznik o 15
add rcx, 15

;sprawdz czy licznik jest wiekszy lub rowny wartosci przy ktorej petla ma sie skonczyc
cmp rcx, r14
;jesli licznik jest wiekszy lub rowny przejdz do punktu powrotu z procedury
jae Koniec
;jesli licznik jest mniejszy przejdz na poczatek petli
jmp createPacket

;punkt powrotu z procedury
Koniec:
;powrot z procedury
ret
histogram endp

;Funckja gaussBlur ma za zadanie rozmycie obrazu za pomoc¹ algorytmu gaussa
;Do obliczania nowej wartoœci pixela brane s¹ pod uwage s¹siaduj¹ce pixele, które s¹ mno¿one przez odpowiednie wagi i dodawane do siebie,
;a ca³a suma jest dzielona przez sumê wag. Tak powstaje wartoœæ pixela wynikowego. 
;Funkcja posiada cztery parametry wejœciowe: wskaŸnik wskazuj¹cy na pocz¹tek tablicy przechowuj¹cej dane bitmapy, rozmiar bitmapy, oraz numery
; wierszy, które okreœlaj¹ zakres wykonania rozmycia
;Funkcja modyfikuje zawartoœæ tablicy z danymi bitmapy(wartoœci pixeli)
;bmp -> rcx, bmpSize -> rdx, imageWidth -> r8, startHeight -> r9, endHeight -> stack
;Rejestry, które ulegaj¹ zmianie: rax, rbx, rcx, rdx, rsi, rdi r8, r9, r10, r11, r12, r13, r14, r15, xmm0-14, rip, efl
;Flagi, które ulegaj¹ zmianie: ZR, CY, PE, PL, AC
;wykorzystanie rejestrow xmm pozwala w jednym kroku petli zmodyfikowac caly pixel(wszystkie 3 skladowe) za jednym razem, a nie jak to mialo miejsc
;przed wykorzystaniem operacji wektorowych gdzie dla kazdej skladowej pixela przypadalo jedno pelne przejscie calej petli
gaussBlur proc

;rejestry od xmm0 do xmm5 zawieraja w sobie odpowiednie wagi pobrane z macierzy potrzebne do obliczenia sumy wazonej
movdqu xmm0, oword ptr[gaussMatrix]
movdqu xmm1, oword ptr[gaussMatrix + 6]
movdqu xmm2, oword ptr[gaussMatrix + 12]
movdqu xmm3, oword ptr[gaussMatrix + 18]
movdqu xmm4, oword ptr[gaussMatrix + 24]
movdqu xmm5, oword ptr[gaussMatrix + 30]

;wyczyszczenie rejestru r10
xor r10, r10
;pobranie ze stosu i zapisanie do rejestru r10 numeru wiersza, na którym algorytm ma poprzestaæ wykonywania siê(endHeight)
mov r10d, dword ptr[rbp+48]

;zapisanie do rejestru r15 adresu poczatku bitmapy
mov r15, rcx

;wczytanie do akumulatora szerokosci bitmapy
mov rax, r8
;pomnozenie bitmapy razy 3, aby dostac rzeczywisty rozmiar
;tzn. uwzgledniajac skladowe RGB(np. bitmapa jest szeroka na 50 pixeli, kazdy pixel sklada sie z 3 skladowych, czyli 50*3 = 150)
imul rax, 3

;zapisanie praktycznej szerokosci do rejestru rdi(zapisanie zawartosci rejestru rax do rejestru rdi)
mov rdi, rax

;pomnozenie praktycznej szerokosci przez numer wiersza, od którego algorytm ma wykonaæ algorytm
imul rax, r9  ;r9 przechowyuje numer wiersza, od którego algorytm ma wykonaæ algorytm

;przeniesie zawartosci rejestru rax do rejestru rcx
;rcx bedzie sluzyl jako licznik petli
mov rcx, rax

;wypelnienie akumulatora wartoscia praktycznej szerokosci(rejestru rdi)
mov rax, rdi
;pomnozenie akumulatora przez numer wiersza, na którym algorytm ma poprzestaæ wykonywania siê
imul rax, r10
;przeniesienie wartosci z akumulatora do rejestru r12
;rejestr r12 bedzie sluzyl do sprawdzania, czy petla ma sie dalej wykonywac(czy jest to koniec bitmapy/odcinka bitmapy)
mov r12, rax

mainLoop:

;inkrementacja licznika
add rcx, 3

;PIERWSZY WARUNEK
;wypelnienie akumulatora wartoscia licznika
mov rax, rcx
;odjecie praktycznej szerokosci od wartosci licznika
sub rax, rdi
;odjecie 3 od zawartosci akumulatora
sub rax, 3
;sprawdzenie czy zawartosc akumulatora nie jest mniejsza od zera
;jest to sprawdzenie, czy lewy gorny sasiad aktualnego pixela nie jest poza tablica
cmp rax, 0
;jesli zawartosc jest mniejsza to wroc na poczatek petli
jl mainLoop

;DRUGI WARUNEK
;wypelnienie akumulatora wartoscia licznika
mov rax, rcx
;dodanie praktycznej szerokosci od wartosci licznika
add rax, rdi
;dodanie 3 od zawartosci akumulatora
add rax, 3
;sprawdzenie czy zawartosc akumulatora jest wieksza od rozmiaru bitmapy
;jest to sprawdzenie, czy prawy dolny sasiad aktualnego pixela nie jest poza tablica
cmp rax, rdx ;rdx przechowuje rozmiar bitmapy
;jesli zawartosc jest wieksza lub rowna rozmiarowi bitmapy to idz do punktu zakonczenia wykonywanie procedury
jae Koniec

;GLOWNA CZESC FUNKCJI

;przeniesienie poczatku bitmapy do akumulatora
mov rax, r15
;dodanie licznika do akumulatora
add rax, rcx 
;odjecie praktycznej szerokosci od akumulatora
sub rax, rdi
;odjecie 3 od zawartosci akumulatora
sub rax, 3
;w akumulatorze znajduje sie adres pod ktorym znajduje sie wartosc lewego gornego sasiada aktualnego pixela
;aktualny pixel to pixel o indexie licznika(w c++ to bmp[i], a lewy gorny sasiad to w c++ bmp[i-width-3])

;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm6
pmovzxbw xmm6, [rax]
; dodanie do akumulatora wartosci 3
; skutkuje to przesunieciem sie o jeden pixel w prawo
; tzn. jesli w rzedzie mamy pixele: p1, p2, p3, p4, p5 (kazdy pixel sklada sie z 3 skladowych, czyli pixel p1 to tak naprawde 3 skladowe r1, g1, b1)
; to w xmm6 znajduja sie: r1, g1, b1, r2, g2, b2, r3, g3
; a w xmm7 beda to:       r2, g2, b2, r3, g3, b3, r4, g4
; analogicznie w xmm8:    r3, g3, b3, r4, g4, b4, r5, g5
add rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm7
pmovzxbw xmm7, [rax]
; dodanie do akumulatora wartosci 3
add rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm8 (wyjasnienie opisano wyzej)
pmovzxbw xmm8, [rax]

;dodanie do akumulatora praktycznej szerokosci
;z punktu widzenia algorytmu jest to przejscie o rzad nizej w bitmapie
add rax, rdi
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm9
pmovzxbw xmm9, [rax]
;odjecie od akumulatora wartosci 3
sub rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm10
pmovzxbw xmm10, [rax]
;odjecie od akumulatora wartosci 3
sub rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm11
pmovzxbw xmm11, [rax]


;dodanie do akumulatora praktycznej szerokosci
;z punktu widzenia algorytmu jest to przejscie o rzad nizej w bitmapie
add rax, rdi
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm12
pmovzxbw xmm12, [rax]
;dodanie do akumulatora wartosci 3
add rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm13
pmovzxbw xmm13, [rax]
;dodanie do akumulatora wartosci 3
add rax, 3
;przeniesienie 8 kolejnych skladowych pixeli do rejestru xmm14
pmovzxbw xmm14, [rax]

;wszystkie operacje pmullw maja za zadanie przemnozenie wszystkich wartosci pixeli przez odpowiednie wagi
pmullw xmm6, xmm0
pmullw xmm7, xmm1
pmullw xmm8, xmm2

pmullw xmm9, xmm3
pmullw xmm10, xmm4
pmullw xmm11, xmm5

pmullw xmm12, xmm0
pmullw xmm13, xmm1
pmullw xmm14, xmm2


;zsumowanie wszystkich pixeli przemnozonych wczesniej przez odpowiednie wagi
;wynikiem beda sumy wazone znajdujaca sie w xmm6
paddw xmm6, xmm7
paddw xmm6, xmm8
paddw xmm6, xmm9
paddw xmm6, xmm10
paddw xmm6, xmm11
paddw xmm6, xmm12
paddw xmm6, xmm13
paddw xmm6, xmm14

;podzielenie sum wazonych przez 16
psrlw xmm6, 4

;skopiowanie do rejestru r9 pierwszego 2-bajtowego slowa z rejestry xmm6
pextrw r9, xmm6, 0
;rejestr r9 przechowuje teraz wartosc skladowa wynikowego pixela
;skopiowanie do rejestru r13 drugiego 2-bajtowego slowa z rejestry xmm6
pextrw r13, xmm6, 1
;rejestr r13 przechowuje teraz wartosc skladowa wynikowego pixela
;skopiowanie do rejestru r14 trzeciego 2-bajtowego slowa z rejestry xmm6
pextrw r14, xmm6, 2
;rejestr r14 przechowuje teraz wartosc skladowa wynikowego pixela

;skopiuj do rejestru r11, poczatek bitmapy
mov r11, r15
;dodaj wartosc licznika do poczatku bitmapy
add r11, rcx 

;zmodyfikuj wartosc pierwszej skladowej pixela
mov byte ptr[r11], r9b
;inkrementuj rejestr r11
add r11, 1
;zmodyfikuj wartosc drugiej skladowej pixela
mov byte ptr[r11], r13b
;inkrementuj rejestr r11
add r11, 1
;zmodyfikuj wartosc trzeciej skladowej pixela
mov byte ptr[r11], r14b

;sprawdz czy licznik jest wiekszy lub rowny wartosci zakonczenia petli
cmp rcx, r12
;jesli tak to przejdz do punktu zakonczenia procedury
jae Koniec
;jesli nie to przejdz do poczatku petli(wykonuj petle dalej)
jmp mainLoop

;punkt zakoñczenia procedury
Koniec:
;powrót z procedury
ret

;Koniec procedury rozmycia obrazu
GaussBlur endp

_TEXT ENDS

end