# ClikR – Játékos útmutató

## A játékról

A ClikR egy készülő, raylib-alapú játékprototípus. A menü és az alapvető
kezelőfelület már használható, de a játékmenet jelenleg még csak egy
„Game” feliratból és a szünetmenüből áll. Egyelőre nincs pontozás, cél,
pálya, fejlődési rendszer vagy menthető játékállás.

A főmenüben látható **v0.1 Alpha** verziójelzés is azt mutatja, hogy a program
korai fejlesztési állapotban van.

## Indítás

Indítsd el a `ClikR.exe` fájlt a projekt könyvtárából. A program a
`data/config.txt` beállításait és az `assets/` könyvtár hang- és képfájljait
relatív útvonalakon keresi, ezért az alkalmazást a projekt gyökérkönyvtárából
futtasd. Ha az erőforrások máshová kerülnek, vagy a munkakönyvtár eltér, a
program nem feltétlenül találja meg őket.

Az ablak bezárásával bármelyik képernyőről kiléphetsz. A főmenü **EXIT**
gombja ugyancsak bezárja a programot.

## Főmenü

A főmenü három gombot kínál:

| Gomb | Működés |
|---|---|
| **START** | Megnyitja a jelenlegi, még fejlesztés alatt álló játékjelenetet. |
| **SETTINGS** | Megnyitja a beállításokat. Visszalépés után a főmenübe tér vissza. |
| **EXIT** | Kilép a programból. |

A felület angol feliratokat használ. A gombok egérrel kezelhetők; föléjük
mozgatva az egérmutatót a gomb kiemelődik, kattintáskor pedig hangeffekt szólal
meg.

## Játék és szünetmenü

A **START** kiválasztása után megjelenik a játékjelenet. Ebben a prototípusban
még nincs aktív játékmenet. Egy egyszerű, textúra nélküli entitás jelenik meg
a középső területen, a HP-ját pedig sáv jelzi. A jobb felső sarokban látható
kreditszámláló jelenleg 0-ról indul; kreditet egyelőre nem lehet szerezni vagy
elkölteni.

Játék közben az **Esc** billentyű megnyitja a szünetmenüt. Az **Esc** ismételt
lenyomásával bezárható; ugyanez a **CONTINUE** gombbal is megtehető.

| Gomb | Működés |
|---|---|
| **CONTINUE** | Visszatér a játékjelenethez. |
| **SETTINGS** | Megnyitja a beállításokat. A **BACK** vagy az **Esc** visszatér a szünetmenühöz. |
| **MAIN MENU** | Visszatér a főmenübe. |
| **SAVE AND EXIT** | Kilép a programból. Játékállást nem ment: jelenleg nincs játékmentés. |

## Beállítások

A főmenüből vagy a szünetmenüből elérhető beállításképernyőn ezek módosíthatók:

### Music Volume

A háttérzene hangereje. A csúszka 0% és 100% között állítható. A háttérzene
automatikusan újraindul, amikor az aktuális lejátszás véget ér.

### SFX Volume

A kezelőfelület kattintási hangeffektjeinek hangereje. A csúszka 0% és 100%
között állítható.

### Fullscreen

A **Fullscreen: ON/OFF** gomb átváltja a teljes képernyős és az ablakos módot.

A **BACK** gomb vagy az **Esc** megnyomása elmenti a beállításokat, majd
visszatér az előző képernyőre. A mentés a `data/config.txt` fájlba történik.
Ha a fájl nem írható, a változtatások nem feltétlenül maradnak meg a program
bezárása után.

## Kezelőszervek röviden

- **Egérmozgatás:** kurzor mozgatása és a gombok kiemelése.
- **Bal egérgomb:** gomb aktiválása; a hangerőcsúszkák húzása.
- **Esc játék közben:** szünet menü megnyitása vagy bezárása.
- **Esc a beállításokban:** mentés és visszatérés az előző képernyőre.
- **Ablak bezárása:** kilépés.

Az alkalmazás elrejti a rendszerkurzort, és saját kurzorgrafikát rajzol. A
kattintás állapotában a kurzor megjelenése megváltozik.

## A beállításfájl jelenlegi értékei

A mellékelt `data/config.txt` jelenleg ezeket az értékeket tartalmazza:

| Beállítás | Érték | Jelentés |
|---|---:|---|
| `width` | `1000` | Ablak induláskori szélessége képpontban. |
| `height` | `600` | Ablak induláskori magassága képpontban. |
| `fps` | `240` | Cél képkockaszám másodpercenként. |
| `music` | `0.20` | Háttérzene hangereje (20%). |
| `sfx` | `0.80` | Hangeffektek hangereje (80%). |
| `fullscreen` | `1` | Teljes képernyős indítás bekapcsolva. |

Az ablakméret és az FPS a játékban nem állítható csúszkával vagy gombbal; ezek
közvetlenül a `data/config.txt` szerkesztésével módosíthatók. A `fullscreen`
értéke `1` esetén bekapcsolt, `0` esetén kikapcsolt állapotot jelent. A
hangerőértékek 0 és 1 közötti számok.