# TYLEK8137

TYLEK8137 - tai maišos algoritmas gražinantis 256 bitų šešioliktainį skaičių (`string` pavidalu). Algoritmui galima paduoti bet kokio ilgio įvesties `string`'ą ir jis grąžins 64 simbolių ilgio `string`'ą. 

## Naudojimo pavyzdys

Sukompiliuojame programą.

`g++ -O3 main.cpp -o hash`

Vykdome programą.

***

`./hash <tekstas>`

Suhashuoja įvesties tekstą ir išveda jį į ekraną.

***

`./hash -f <kelias į failą>`

Suhashuoja nurodyto failo turinį ir išveda į ekraną.

***

`./hash -t1 <kelias į failą>`

Vykdomas pirmas testas.

***

`./hash -t2 <algoritmas> <testų skaičius>`

Vykdomas antras testas.

***

`./hash -t3 <algoritmas> <testų skaičius>`

Vykdomas trečias testas.

***

`./hash -cmp <pirmas hash> <antras hash>`

Palyginami hash'ai bitų lygmenyje. Panašumo koeficientas išvedamas į ekraną.

### Pirmas testas

Suhashuoja nurodyto failo turinį po vieną eilutę. Kiekvienas hash išvedamas į ekraną. Išvedamas realus hashavimo laikas.

### Antras testas

Pagal pasirinktą algoritmą nurodytą skaičių kartų sugeneruojamas unikalus įvesties `string` ir sugeneruojamas jo hash. Sugeneruotas hash palyginamas su visais anksčiau sugeneruotais hash. Kas 100 000 hash'ų į ekraną išvedama eilutė:

`<hash'ų skaičius>, <pasikartojusių hash'ų skaičius>, <visas hash'avimo laikas>, <hash'avimo greitis>, <vidutinis hash'avimo greitis`

Galimi algoritmai:

`-tylek8137`<br>
`-sha256`<br>
`-rytisgit` (šis algoritmas patalpintas su @Rytisgit sutikimu)

### Trečias testas

Pagal pasirinktą algoritmą nurodytą skaičių kartų generuojama pora unikalių `string`'ų, kurie skiriasi per vieną simbolį, ir sugeneruojami jų hash. Abu hash'ai palyginami bitų lygmenyje ir gaunamas jų panašumo koeficientas. Iš visų koeficientų randama minimali, maksimali ir vidurkinė reikšmė. Šios reikšmės išvedamos į ekraną.

## Užduočių rezultatai

### Skaitymas iš failų

1. Failai iš vieno simbolio

| Įvestis | Hash |
|---------|------|
| failas1       | hash1 | 
| failas2       | hash2 | 

2. Failai su daug skirtingų simbolių

| Įvestis | Hash |
|---------|------|
| failas1       | hash1 | 
| failas2       | hash2 | 

3. Failai su daug simbolių, skiriasi tik vienas

| Įvestis | Hash |
|---------|------|
| failas1       | hash1 | 
| failas2       | hash2 | 

4. Tuščias failas

| Įvestis | Hash |
|---------|------|
| failas1       | hash1 | 

### Pirmas testas

### Antras testas

Testo rezultatai. Testas atliktas su 75 000 000 hash'ų.

| Algoritmas | Pasikortoję hash | Visas hash'avimo laikas | Vidutinis hash'avimo greitis |
| TYLEK8137 | 0 |  |  |
| SHA256 | 0 |  |   | 

### Trečias testas

Testo rezultatai. Testas atliktas su 1 000 000 hash'ų.

| Algoritmas | Minimali reikšmė | Maksimali reikšmė | Vidutinė reikšmė |
| TYLEK8137 |   |   |   |
| SHA256 |   |   |   |

## Algoritmas

Algoritmo viduje duomenys saugomi 8 `unsigned long int` elementų masyve. Pradžioje sukuriamas masyvas, kurio kiekvieno elemento reikšmė lygi 0, tai bus masyvas saugantis galutinį rezultatą. Paskui vykdomas ciklas, kurio kievienos iteracijos metu apdorojami 8 įvesties `string`'o simboliai. Sukuriamas naujas masyvas, kurio reikšmės, tų simbolių ASCII reikšmės. Toliau vykdoma pati maišos funkcija 2 kartus. Iš kiekvienos reikšmės ištraukiama kvadratinė šaknis. Sudaroma reikšmė, kurios pirmi du simboliai yra šaknies sveikosios dalies du paskutiniai simboliai, sekantys šeši simboliai yra šaknies trupmeninės dalies pirmi šeši simboliai. Pavyzdžiui:

`a` => `97` => `9.8488578017` => `09848857`

Paskui sumaišomi masyvo elementų skaitmenys. Pavyzdžiui (pavyzdys bus rodomas su 4 elementais su 4 skaitmenimis):

`abcd` => `0097 0098 0099 0100` => `7890 9990 0001 0000`

Nauja masyvo elemento reikšmė apskaičiuojama atlikus XOR operaciją su šaknies reikšmėmis ir su jau sumaišytais skaitmenimis. Pavyzdžiui:

Pradiniai elementai `abcd`.<br>
Masyvas iš ASCII reikšmių `0097 0098 0099 0100`.<br>
Pirma iteracija.<br>
Šaknų masyvas `0984 0989 0994 1000`<br>
Sumaišytas masyvas `7890 9990 0001 0000`<br>
Masyvas po XOR `7434 0003 0995 1000`<br>
Antra iteracija<br>
Šaknų masyvas `8622 0173 3154 3162`<br>
Sumaišytas masyvas `7001 4090 3090 4350`<br>
Masyvas po XOR `15095 3969 64 7332`<br>


Antrasis masyvas XOR operacija pridedamas prie galutinio. Galutinis dar 1 kartą sumaišomas ankstesniu algoritmu. Nuskaitomi sekantys 8 įvesties simboliai ir veiksmai kartojami. Pabaigus nuskaityti įvestį, galutinis masyvas dar 2 kartus sumaišomas ir gražinama galutinis rezultatas.
