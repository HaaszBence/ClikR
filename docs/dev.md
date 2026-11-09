# ClikR – Fejlesztői dokumentáció

## Projekt állapota és technológia

A ClikR egy C nyelven írt, raylibet használó, Windowsra beállított játékprototípus.
A főmenü, a beállításképernyő, a szünetmenü, az alapvető UI-elemek, az
erőforrás-betöltés és a konfiguráció betöltése már megvalósult. A játékjelenet
jelenleg csak egy helykitöltő feliratot és szünetmenüt tartalmaz; játékmenet,
játékállás-mentés és pontozás még nincs.

## Könyvtárszerkezet

```text
ClikR/
├── assets/
│   ├── downloaded/              Letöltött, külső grafikai csomag
│   ├── music/music.mp3           Háttérzene
│   ├── sfx/click.mp3             UI-kattintási hang
│   └── ui/cursor/                Normál és kattintó kurzorgrafika
├── data/
│   └── config.txt                Felhasználói beállítások
├── docs/
│   ├── dev.md                   Ez a fejlesztői leírás
│   └── user.md                  Játékos útmutató
├── include/                     Nyilvános fejlécfájlok
├── src/                         Alkalmazás- és jelenetkód
├── template/                    Egyszerű raylib C mintaprogram
└── ClikR.exe                    Helyi fordított futtatható fájl
```

### Forrásfájlok

| Fájl | Felelősség |
|---|---|
| `src/main.c` | Beállítások és raylib inicializálása, fő ciklus, jelenetváltás, erőforrások felszabadítása. |
| `src/menu.c` | Főmenü háttere, animált matematikai jelölések, menügombok. |
| `src/game.c` | Játékjelenet és szünetmenü. |
| `src/settings.c` | Beállítások betöltése, mentése, kezelőfelülete és alkalmazása. |
| `src/ui.c` | Közös gomb, hangerőcsúszka és saját kurzor kirajzolása. |
| `src/assets.c` | Textúrák és hangok betöltése, majd felszabadítása. |
| `include/menu.h` | A `Scene` felsorolás és a menü függvényének deklarációja. |
| `include/game.h` | Játékjelenet függvényének deklarációja. |
| `include/settings.h` | `GameSettings` adattípus és beállításfüggvények. |
| `include/ui.h` | Színpaletta és közös UI-függvények. |
| `include/assets.h` | A betöltött erőforrásokat összefogó `GameAssets` típus. |

## Programfolyam és jelenetek

Az indítási folyamat a `main` függvényben:

1. A program beolvassa a `data/config.txt` fájlt.
2. A konfigurációból beállítja az ablakméretet, teljes képernyős módot és
   cél-FPS-t, majd inicializálja a raylib ablakot és az audiót.
3. Betölti a kurzor-textúrákat, a háttérzenét és a kattintási hangot.
4. Elindítja a háttérzenét, elrejti a rendszerkurzort, és elindítja a fő
   rajzolási ciklust.
5. A `Scene` értéke határozza meg, hogy a főmenü, a játék vagy a beállítások
   frissülnek és rajzolódnak ki.
6. Minden képkockában kirajzolódik az egyedi kurzor. Kilépéskor az erőforrások
   felszabadulnak, a rendszerkurzor visszakapcsol, az audió és az ablak
   leáll.

A jeleneteket az `include/menu.h` fájlban deklarált `Scene` enum azonosítja:
`SCENE_MENU`, `SCENE_GAME`, `SCENE_SETTINGS`, `SCENE_EXIT`. A jelenetfüggvények
az új jelenetet adják vissza; így történik a menü- és képernyőváltás.
A beállításképernyő a `GameSettings.returnScene` mezőben kapja meg, hová kell
visszatérnie. A játék szünetállapotát a `src/game.c` fájl statikus
`isPaused` változója tárolja.

## Beállítások és mentés

A `GameSettings` mezői:

| Mező | Típus | Használat |
|---|---|---|
| `windowWidth` | `int` | Ablak induláskori szélessége. |
| `windowHeight` | `int` | Ablak induláskori magassága. |
| `targetFps` | `int` | A `SetTargetFPS` célértéke. |
| `musicVolume` | `float` | Háttérzene hangereje, 0 és 1 között. |
| `sfxVolume` | `float` | Kattintási hang hangereje, 0 és 1 között. |
| `isFullscreen` | `bool` | Teljes képernyős mód. |
| `returnScene` | `Scene` | Beállításokból való visszatérés célja; nem kerül a fájlba. |

A `data/config.txt` egyszerű, soronként egy kulcs-érték párt tartalmazó fájl:

```text
width=1000
height=600
fps=240
music=0.20
sfx=0.80
fullscreen=1
```

Ha a fájl nem nyitható meg, a kód alapértékei: 1200×900 felbontás, 240 FPS,
0.5 zenehangerő, 0.8 hangeffekt-hangerő, ablakos mód. A beállításképernyő a
hangerőértékeket azonnal alkalmazza, a teljes képernyős gomb pedig azonnal
átváltja a módot. A beállításokat a **BACK** gomb vagy az **Esc** menti a
`data/config.txt` fájlba; az ablakméret és az FPS beállítását a felület nem
teszi lehetővé, azokat a konfigurációs fájlból olvassa.

## Erőforrások és futtatási könyvtár

A `src/assets.c` ezeket az útvonalakat tölti be:

- `assets/ui/cursor/base.png`
- `assets/ui/cursor/base_click.png`
- `assets/music/music.mp3`
- `assets/sfx/click.mp3`

Ezek relatív útvonalak. A program futtatási munkakönyvtárának ezért a
projekt gyökerének kell lennie. A kurzor textúráin bilineáris szűrés működik.
Az audió `Sound` erőforrásként töltődik be; a fő ciklus újraindítja a háttérzenét,
ha annak lejátszása befejeződött.

Az `assets/downloaded/kenney_cursor-pack/` könyvtárban található kurzorcsomag
és licencfájl letöltött forrásanyag. A futó program jelenleg nem ebből a
csomagból tölti be a kurzort, hanem a fenti két PNG-fájlból.

## Fordítás és futtatás

A VS Code projektbeállításai Windowsos MSYS2 UCRT64 GCC-t és raylibet
feltételeznek:

- GCC: `C:\msys64\ucrt64\bin\gcc.exe`
- GDB: `C:\msys64\ucrt64\bin\gdb.exe`
- raylib fejlécek és könyvtár: `C:\raylib\raylib\src`

Ezek a helyi útvonalak a `.vscode/tasks.json`, `.vscode/launch.json` és
`.vscode/c_cpp_properties.json` fájlokban szerepelnek. Más gépen szükség lehet
az útvonalak saját fejlesztői környezethez igazítására, valamint az MSYS2
UCRT64 GCC/GDB és raylib telepítésére.

VS Code-ban:

1. Nyisd meg a projekt gyökérkönyvtárát workspace-ként.
2. A **Terminal → Run Build Task** (vagy `Ctrl+Shift+B`) paranccsal futtasd a
   **Build raylib C** feladatot.
3. A fordító a `src/*.c` fájlokat a `ClikR.exe` programba fordítja, és a
   raylibet, valamint a szükséges Windows rendszerkönyvtárakat linkeli.
4. A **Run and Debug** nézetből vagy az `F5` billentyűvel indítsd a **Run
   raylib** konfigurációt. A konfiguráció fordítás előtt elindítja a build
   feladatot.

A beállítások és erőforrások relatív útvonalai miatt a programot a projekt
gyökérkönyvtárát munkakönyvtárként használva indítsd. A VS Code futtatási
konfigurációja ezt a workspace gyökerére állítja.

## UI-viselkedés

- A gombok egér fölé vitelekor és kattintásakor vizuális visszajelzést adnak.
- A gomb egy kattintást az egérgomb felengedésekor jelez, ha a mutató a gomb
  területén van.
- A csúszkák az egérgomb nyomva tartása közben állíthatók, és az értéket
  0–1 közé korlátozzák.
- A menü és a beállításképernyő elemei a képernyőmérethez viszonyított
  méretezéssel és elhelyezéssel készülnek.
- A gombok, képernyők, paletta és kurzor újrafelhasználható megvalósítása a
  `src/ui.c` és az `include/ui.h` fájlban található.

## Jelenlegi korlátok

- A játékjelenet még nem tartalmaz tényleges játékmechanikát.
- A **SAVE AND EXIT** csak kilép; játékállást nem ment.
- Az ablakméret és a cél-FPS csak a konfigurációs fájl szerkesztésével állítható.
- A projekt buildkonfigurációja konkrét, helyi Windows-útvonalakat használ.
- A VS Code buildfeladat automatikus tesztfuttatást nem tartalmaz.