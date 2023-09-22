# Programarea calculatoarelor si limbaje de programare 2 - Tema 1

Student: Andronache Madalina-Georgiana
Grupa: 312CC

Urmatorul fisier contine informatii despre rezolvarea problemei propusa in 
tema 1 de la PCLP2. Punctajul obtinut la testarea locala este de 100 de puncte.

Cea mai mare provocare intalnita a fost rezolvarea corecta si cat mai eficienta
a problemei propuse intr-un timp cat mai scurt. Aceasta tema a fost rezolvata
pe parcursul a 3 zile: in total am lucrat la aceasta tema 7 h, dintre care 1 h
fiind necesare pentru scrierea fisierului README, iar restul pentru codare si 
testarea problemei. In viitor, imi doresc rezolvarea mai rapida a cerintelor. 

Cuprins:
1. Operatia PRINT
2. Operatia ANALYZE
3. Operatia CLEAR
4. Citirea datelor

# 1. Operatia PRINT

Pentru operatia PRINT am creat 2 functii - care raspund la doua
necesitati diferite ale problemei:

* Functia void sensor_sort(sensor *v, int n), care primeste ca argumente
vectorul de senzori v si un numar intreg n reprezentand numarul de elemente
ale vectorului. Parcurg vectorul de la al doilea element si verific daca
este de tip "Power Management Unit". Ulterior, cat timp inaintea elementului de
tip "Power Managament Unit" se gaseste un element de tip "Tire Sensor" se 
realizeaza succesiv operatia de interschimbare intre acestea. Astfel, elementele
de tip "Power Management Unit" ajung sa se stiueze primele in vector, iar cele
"Tire Sensor" dupa acestea. Aceasta functie ajuta la implementarea operatiei 
de print (complex).

* Functia void display(sensor *v, int index, int n), care primeste ca argumente
vectorul de senzori v, un numar intreg n reprezentand numarul de elemente ale 
vectorului si un numar intreg index, reprezentand indexul/pozitia elementului
in vector. Astfel, se va afisa mesajul "Index not in range!" sau in functie
de tipul senzorului: PMU sau TIRE, detaliile despre fiecare componenta conform
enuntului.

# 2. Operatia ANALYZE

Pentru opeartia de ANALYZE am declarat un vector void *operations[8], in care, 
cu ajutorul functiei void get_operations(void **operations) din fisierul operations.c
am alcatuit vectorul de operatii. Atfel, pentru fiecare operatie ce trebuie efectuata,
am determinat indexul operatiei (codul ei) si am apelat functia specifica, folosindu-ma
de vectorul operations si am dat ca argument functiei datele senzorului respectiv.

# 3. Operatia CLEAR

Pentru operatia de CLEAR am implementat functia cu urmatorul antet:
void clear(sensor **v, int *n), care primeste ca argument vectorul de senzori
si numarul de elemente ale vectorului. Pornind de la primul element al 
vectorului, in functie de tipul acestuia se va verifica daca contine valori 
eronate. In caz afirmativ, se va elibera memoria elementului cu valori eronate
si se va actualiza ordinea in vector si numarul de elemente.

# 4. Citirea datelor

In functia main se realizeaza citirea datelor din fisierul binar dat ca 
argument in linia de comanda in urmatorul fel: In primul rand, se citeste 
numarul de senzori si se aloca memorie pentru vectorul sensor *v. Apoi se 
foloseste functia cu antetul void read(int n, sensor *v, FILE *fdata), in
care se citeste fiecare camp al fiecarui element din vectorul de senzori,
conform enuntului. Ulterior, vectorul este sortat conform enuntului. 

Folosind un sir auxiliar, citim de la standard input, comenzi. Pana cand
se intalneste comanda "exit", sirul primit de la tastatura este transformat
intr-un sir de carctere si un numar, folosindu-ma de functia 
char *transform(char *str, int *nr). Ulterior, in functie de comanda introdusa,
se apeleaza functiile corespunzatoare. 

Ultima parte a functiei main este reprezentata de dezalocarea memoriei si 
inchiderea fisierul binar.
