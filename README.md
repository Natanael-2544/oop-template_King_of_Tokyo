# Joc de tip „King of Tokyo” – Descriere generală

## Obiectivul jocului
Obiectivul jocului este să fii **primul jucător care atinge 5 puncte de victorie** sau să **rămâi ultimul monstru în viață** după eliminarea tuturor celorlalți jucători.

---

## Pregătirea jocului
La începutul jocului:
- Fiecare jucător își alege un monstru și își plasează figura și tabla de monstru în față.
- Fiecare monstru începe cu **viață inițială** și **0 puncte de victorie**, conform caracteristicilor sale:
    - **Mutant**: 12 puncte de viață și un bonus mic de atac
    - **Dragon**: 10 puncte de viață și un bonus de energie
    - **Robot**: 14 puncte de viață și reducere de daune
    - **MegaMutant**: moștenește trăsături din Mutant, Dragon și Robot, dar începe cu doar 8 puncte de viață pentru echilibru
- Tabla **Tokyo** este plasată în centru.
- Cărțile de putere sunt puse pe cate un teanc de carti specifice.
- Cuburile de energie sunt puse la dispoziția jucătorilor pentru a fi folosite pe parcursul jocului.

---

## Desfășurarea unei runde
Jocul se desfășoară pe rând, fiecare rundă având următorii pași:

### Aruncarea zarurilor
- Fiecare jucator arunca un zar numerotat de la 1 la 6. Incepe cel care, in cele din urma, obtine zarul cu cel mai mare numar.
In caz de egalitate, se rejoaca pana va castiga unul dintre ei.
- Jucătorul aruncă **6 zaruri**.
- Zarurile au următoarele simboluri și efecte:
    - **1, 2, 3** - Dacă apar doar 2 zaruri identice (dublete), acestea se transformă în fulgere:
                    - Zar 1 → 1 fulger
                    - Zar 2 → 2 fulgere
                    - Zar 3 → 3 fulgere
                  - Dacă apar 3 sau mai multe zaruri identice (triplete sau mai multe), se acordă puncte de victorie:
                    - Zar 1 → 1 PV
                    - Zar 2 → 2 PV
                    - Zar 3 → 3 PV
                  - Dacă apar mai mult de 3 zaruri identice, tripletul oferă PV, iar restul zarurilor rămase se transformă în fulgere.

    - **⚡(*) Energie** – adaugă cuburi de energie
    - **❤️(H) Inimă** – vindecă puncte de viață (doar dacă monstrul nu se află în Tokyo)
    - **🐾(G) Gheară** – aplică daune monștrilor adversari

### Rezolvarea efectelor
După finalizarea aruncărilor:
- Se calculează punctele de victorie
- Se adaugă energia obținută
- Se aplică vindecarea
- Se aplică daunele către adversari
- Este intrebat jucatorul curent daca vrea sa cumpere vreo carte si in caz afirmativ e intrebat si daca vrea sa o foloseasca.
Apoi e obligat sa ii dea discard.

---

## Tokyo
- Primul Jucator care da cu jarul G, intra automat in Tokyo, si alege sa ofere daunele unui singur adversar
- Dacă un monstru rămâne în Tokyo la începutul rundei următoare, primește **+2 puncte de victorie**.
- Monștrii din Tokyo:
    - Nu pot folosi simbolurile de vindecare ❤️ (H)
    - Atacă toți monștrii aflați în afara Tokyo
- Dacă un monstru din Tokyo este atacat, acesta poate alege să părăsească Tokyo, iar atacatorul îi ia locul.

---

## Cărți de putere
La finalul turei, jucătorul poate cheltui cuburi de energie pentru a cumpăra cărți de putere. Există trei tipuri principale:

- **PutereAtac** – aplică 2 puncte de daune unui monstru adversar. Costa 3 fulgere
- **PutereVindecare** – adaugă 3 puncte de viață propriului monstru (nu poate fi folosită în Tokyo). Costa 5 fulgere
- **PutereEnergie** – adaugă 1 punct de victorie la finalul rundei. Costa 4 fulgere.

Fiecare carte are un cost diferit în energie, în funcție de efectul său, și poate fi folosită o singura dată.
(Nu se poate cumpăra o carte de mai multe ori, ci se poate recumpăra dupa ce jucatorul curent alege să o foloseasca și astfel îi dă discard. 
Mai mulți jucători pot avea copii ale aceleiași cărți.)

---

## Structura jocului (implementare)
- Monștrii sunt reprezentați printr-o **clasă abstractă**, cu atribute precum:
    - nume
    - viață curentă
    - puncte de victorie
    - număr de fulgere
    - indicator de poziție în Tokyo
    - ID unic
- Fiecare monstru are metode virtuale pentru:
    - atac
    - vindecare
    - folosirea puterilor speciale
- Clasele derivate implementează comportamentele specifice fiecărui tip de monstru.
- Zarurile sunt gestionate printr-un **container generic**, capabil să stocheze rezultatele într-un vector sau listă și să ofere metode pentru:
    - aruncare
    - afișare
    - sortare și numărare simboluri folosind funcții generice și expresii lambda

---

## Pattern-uri utilizate
- **Singleton** – gestionează:
    - lista de jucători activi
    - cărțile disponibile
    - numărul maxim de monștri
    - viața maximă
    - numărul de jucători
- **Factory** – utilizat pentru crearea monștrilor și a cărților de putere, în funcție de tipul ales
- Evenimentele importante sunt logate prin funcții statice.

---

## Finalul jocului
Jocul se încheie imediat atunci când:
- Un jucător ajunge la **8 puncte de victorie**, sau
- Toți ceilalți monștri sunt eliminați

Câștigătorul este declarat **primul jucător care îndeplinește una dintre condițiile de mai sus**.
