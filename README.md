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
- Cărțile de putere sunt amestecate.
- Cuburile de energie sunt puse la dispoziția jucătorilor pentru a fi folosite pe parcursul jocului.

---

## Desfășurarea unei runde
Jocul se desfășoară pe rând, fiecare rundă având următorii pași:

### Aruncarea zarurilor
- Jucătorul aruncă **6 zaruri**.
- Poate relansa zarurile de **maximum 2 ori**.
- Zarurile au următoarele simboluri și efecte:
    - **1, 2, 3** – oferă puncte de victorie dacă apar cel puțin 3 simboluri identice; fiecare simbol suplimentar oferă +1 punct
    - **⚡ Energie** – adaugă cuburi de energie
    - **❤️ Inimă** – vindecă puncte de viață (doar dacă monstrul nu se află în Tokyo)
    - **🐾 Gheară** – aplică daune monștrilor adversari

### Rezolvarea efectelor
După finalizarea aruncărilor:
- Se calculează punctele de victorie
- Se adaugă energia obținută
- Se aplică vindecarea
- Se aplică daunele către adversari

---

## Tokyo
- Dacă Tokyo este liber, jucătorul poate intra în Tokyo și primește **+1 punct de victorie**.
- Dacă un monstru rămâne în Tokyo la începutul rundei următoare, primește **+2 puncte de victorie**.
- Monștrii din Tokyo:
    - Nu pot folosi simbolurile de vindecare ❤️
    - Atacă toți monștrii aflați în afara Tokyo
- Dacă un monstru din Tokyo este atacat, acesta poate alege să părăsească Tokyo, iar atacatorul îi ia locul.

---

## Cărți de putere
La finalul turei, jucătorul poate cheltui cuburi de energie pentru a cumpăra cărți de putere. Există trei tipuri principale:

- **PutereAtac** – aplică 2 puncte de daune unui monstru adversar
- **PutereVindecare** – adaugă 3 puncte de viață propriului monstru (nu poate fi folosită în Tokyo)
- **PutereEnergie** – adaugă 2 cuburi de energie suplimentare

Fiecare carte are un cost diferit în energie, în funcție de efectul său.

---

## Structura jocului (implementare)
- Monștrii sunt reprezentați printr-o **clasă abstractă**, cu atribute precum:
    - nume
    - viață curentă
    - puncte de victorie
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
- Un jucător ajunge la **5 puncte de victorie**, sau
- Toți ceilalți monștri sunt eliminați

Câștigătorul este declarat **primul jucător care îndeplinește una dintre condițiile de mai sus**.
