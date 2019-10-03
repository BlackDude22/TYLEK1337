# TYLEK8137

TYLEK8137 - tai maišos algoritmas gražinantis 256 bitų šešioliktainį skaičių (`string` pavidalu). Algoritmui galima paduoti bet kokio ilgio įvesties `string`'ą ir jis grąžins 64 simbolių ilgio `string`'ą. 

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

Pagal pasirinktą algoritmą nurodytą skaičių kartų generuojama pora unikalių `string`'ų, kurie skiriasi per vieną simbolį, ir sugeneruojami jų hash. Abu hash'ai palyginami bitų lygmenyje ir gaunamas jų panašumo koeficientas. Koeficientas apskaičiuojamas padalinus sutapusių bitų skaičių iš visų bitų skaičiaus. Iš visų koeficientų randama minimali, maksimali ir vidurkinė reikšmė. Šios reikšmės išvedamos į ekraną.

## Užduočių rezultatai

### Skaitymas iš failų

1. Failai iš vieno simbolio

| Įvestis | Hash |
|---------|------|
| test11.txt | ffda72429e525f874b8b244858d39e0cc06080b95b5f5924a0480d56a6cb4773 | 
| test12.txt | 792615e868977e6b2f590f68a8de2354732ca8edb515e8a217cddd5ed2635031 | 

Panašumo koeficientas: 0.539062

2. Failai su daug skirtingų simbolių

| Įvestis | Hash |
|---------|------|
| test21.txt | 4800c8eceb7e435db609a3b82f0550adc86f2b22bbcf93c8dcc1b93e3d745b0d | 
| test22.txt | ff309ecb83df6027311c4d0f6997d79ef931e70ce24f3fe510e9f3057df9ebf5 | 

Panašumo koeficientas: 0.535156

3. Failai su daug simbolių, skiriasi tik vienas

| Įvestis | Hash |
|---------|------|
| test31.txt | 80b4e47019da236f2364fe07b762eb37ab338bb8fbce3d639269407df55b3483 | 
| test32.txt | ff309ecb83df6027311c4d0f6997d79ef931e70ce24f3fe510e9f3057df9ebf5 | 

Panašumo koeficientas: 0.558594

4. Tuščias failas

| Įvestis | Hash |
|---------|------|
| test0.txt | 0000000000000000000000000000000000000000000000000000000000000000 | 

### Pirmas testas

Testas atliktas su failu `konstitucija.txt`. Testi gauti hash'ai pateikti faile `konstitucijarez.txt`.

Testo atlikimo laikas: 

### Antras testas

Testo rezultatai. Testas atliktas su 75 000 000 hash'ų.

| Algoritmas | Pasikortoję hash | Visas hash'avimo laikas, s | Vidutinis hash'avimo greitis, hash/s |
|------------|------------------|-------------------------|------------------------------|
| TYLEK8137 | 0 | 125.7 | 596 659 |
| SHA256    | 0 | 146.552 | 511 763 | 

### Trečias testas

Testo rezultatai. Testas atliktas su 1 000 000 porų hash'ų.

| Algoritmas | Minimali reikšmė | Maksimali reikšmė | Vidutinė reikšmė |
|------------|------------------|-------------------|------------------|
| TYLEK8137 | 0.34375 | 0.648438 | 0.500487 |
| SHA256    | 0.355469 | 0.644531 | 0.50001 |

## Išvada

Iš pateiktų testų rezultatų matome, kad tiek TYLEK8137 tiek SHA256 algoritmų panašumo koeficientai vienodi, bet TYLEK8137 ~16% greitesnis. Obejektyviai įvertinę šiuos rezultatus galime teigti, kad TYLEK8137 hash'avimo algoritmas geresnis nei SHA256. 
