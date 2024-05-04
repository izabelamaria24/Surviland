# Surviland

## Surviland is a 2D game

##### You are in a world full of possibilities: Surviland!
##### In this world, you are a lost penguin and you need to survive as long as you can. 

## Controls:

### Movement:
- **W, A, S, D:** Use these keys to move your penguin character around the world.

### Combat:
- **B:** Click to attack enemies with your equipped weapon or tool.

### Upgrades:
- **L:** Upgrade normal attack.
- **O:** Upgrade spell attack.

### Exit Game:
- **Esc:** Save progress, or quit the game.


Mastering these controls is essential for navigating the challenging terrain and surviving encounters with the diverse wildlife of Surviland. Stay vigilant, adapt to your surroundings, and use your wits to overcome the obstacles that stand between you and survival!

## Entities:
- **YOU:** The only penguin left in this wild world!
- **DUMB ENEMIES:** Some kind of creatures riding a pig, they only follow a predefined trajectory
- **SMART ENEMIES:** Some wierd, but smart creatures, they are able to detect penguins, so they will follow you
- **HEAL POTION:** A mystic potion, you will gain +2HP if you consume it
- **STOPWATCH:** A special powerup, it will stop enemies for 4 seconds
- **ARMOR:** If you collect this powerup, it will protect you from enemies with damage < your total armor


### Cerințe modele de limbaj la nivel de semestru
- [x] minim o funcționalitate majoritar doar cu LLM
- [x] minim 2-3 funcționalități ~50% voi, ~50% LLM-ul
- [x] minim 2-3 funcționalități suficient de complicate pe care un LLM nu le poate implementa

### Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [x] constructori de inițializare
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [x] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [x] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [x] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri:
  - minim o clasă de bază și **3 clase derivate**
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] smart pointers (recomandat, opțional)
  - [x] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
- [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate**
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
- [x] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
- [x] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
