# TYLEK8137

TYLEK8137 - tai maišos algoritmas gražinantis 256 bitų šešioliktainį skaičių (`string` pavidalu). Algoritmui galima paduoti bet kokio ilgio įvesties `string`'ą ir jis grąžins 64 simbolių ilgio `string`'ą. 

## Algoritmas

Algoritmo viduje duomenys saugomi 8 `unsigned long int` elementų masyve. Pradžioje sukuriamas masyvas, kurio kiekvieno elemento reikšmė lygi 0, tai bus masyvas saugantis galutinį rezultatą. Paskui vykdomas ciklas, kurio kievienos iteracijos metu apdorojami 8 įvesties `string`'o simboliai. Sukuriamas naujas masyvas, kurio reikšmės, tų simbolių ASCII reikšmės. Toliau vykdoma pati maišos funkcija 2 kartus. Iš kiekvienos reikšmės ištraukiama kvadratinė šaknis. Sudaroma reikšmė, kurios pirmi du simboliai yra šaknies sveikosios dalies du paskutiniai simboliai, sekantys šeši simboliai yra šaknies trupmeninės dalies pirmi šeši simboliai. Pavyzdžiui:

`a` => `97` => `9.8488578017` => `09848857`

Paskui sumaišomi masyvo elementų skaitmenys. Pavyzdžiui (pavyzdys bus rodomas su 4 elementais su 4 skaitmenimis):

`abcd` => `0097 0098 0099 0100` => `7890 9990 0001 0000`

Nauja masyvo elemento reikšmė apskaičiuojama atlikus XOR operaciją su šaknies reikšmėmis ir su jau sumaišytais skaitmenimis. Pavyzdžiui:

Pradiniai elementai `abcd`.
Masyvas iš ASCII reikšmių `0097 0098 0099 0100`.
Pirma iteracija.
Šaknų masyvas `0984 0989 0994 1000`
Sumaišytas masyvas `7890 9990 0001 0000`
Masyvas po XOR `7434 0003 0995 1000'
Antra iteracija
Šaknų masyvas `8622 0173 3154 3162`
Sumaišytas masyvas `7001 4090 3090 4350`
Masyvas po XOR `15095 3969 64 7332'

Antrasis masyvas XOR operacija pridedamas prie galutinio. Galutinis dar 1 kartą sumaišomas ankstesniu algoritmu. Nuskaitomi sekantys 8 įvesties simboliai ir veiksmai kartojami. Pabaigus nuskaityti įvestį, galutinis masyvas dar 2 kartus sumaišomas ir gražinama galutinis rezultatas.
