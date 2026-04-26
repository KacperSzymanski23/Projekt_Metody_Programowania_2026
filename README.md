# Konfiguracja środowiska – Meson Build System

Wiem że jeszcze niewybraliśmy tematu ale jak już to zrobimy to musisz zainstalowac parę rzeczy. Na ostatnim projekcie z C++ ja i kolega mialiśmy problem z odpaleniem projektu, który miał dużo zależności do pobrania. Więc teraz masz taki mini tutorial jak to zrobić. **Jeszcze go nieskończyłem ale więc może jeszcze coś niedziałać.** Może jakiś skrypt zrobie co to odrazu ogarnie i zrobi to za nas ale narazie nie mam czasu.

---

## Instalacja zależności przez Winget

Otwórz **Terminal** lub **PowerShell** jako **Administrator**, a następnie wykonaj poniższe polecenia jedno po drugim.

### 1. Git

```powershell
winget install --id Git.Git -e --source winget
```

Git jest wymagany do klonowania repozytoriów z zależnościami oraz zarządzaniem wersjami kodu.

---

### 2. Meson

```powershell
winget install --id mesonbuild.meson -e --source winget
```

Meson to system budowania projektu. Żebyśmy mogli skompilować projekt, należy go zainstalować. CLion chyba ma go wbudowanego ale niejestem pewien.

---

### 3. Ninja

```powershell
winget install --id Ninja-build.Ninja -e --source winget
```

Ninja to szybki system budowania, który Meson używa jako domyślny backend.

---

### 4. pkg-config-lite

Bez tego Meson ma problem z znalezieniem zależności. Niewiem czy nam się to teraz przyda ale warto to mieć.
Winget nie oferuje bezpośrednio pakietu `pkg-config-lite`. Należy go zainstalować ręcznie:

1. Pobierz najnowszą wersję ze strony projektu:
   [pkg-config-lite na SourceForge](https://sourceforge.net/projects/pkgconfiglite/files/)

2. Wypakuj archiwum do wybranego katalogu, np.:

   ```
   C:\tools\pkg-config-lite\
   ```

3. Skopiuj plik `pkg-config.exe` z podkatalogu `bin\` – będzie potrzebny w kolejnym kroku podczas konfiguracji zmiennych środowiskowych.

Można też to pobrać z [MSYS2](https://www.msys2.org/) ale jest przy tym więcej roboty i pobierania.

---

## Konfiguracja zmiennych środowiskowych

Po instalacji należy upewnić się, że wszystkie narzędzia są widoczne w systemowej zmiennej `PATH`.

1. Naciśnij `Win + S`, wpisz **„Zmienne środowiskowe"** i wybierz:
   **„Edytuj zmienne środowiskowe systemu"**

2. W oknie **Właściwości systemu** kliknij przycisk **„Zmienne środowiskowe..."**

3. W sekcji **„Zmienne systemowe"** odszukaj zmienną **`Path`** i kliknij **„Edytuj..."**

4. Kliknij **„Nowy"** i dodaj kolejno ścieżki do folderów `bin\` każdego narzędzia (jeśli instalator nie zrobił tego automatycznie):

   | Narzędzie       | Przykładowa ścieżka do dodania |
   | --------------- | ------------------------------ |
   | Git             | `C:\Program Files\Git\cmd`     |
   | Meson           | `C:\Program Files\Meson`       |
   | Ninja           | `C:\Program Files\Ninja`       |
   | pkg-config-lite | `C:\tools\pkg-config-lite\bin` |

   Rzeczywiste ścieżki mogą i raczej napewno będą się różnić w zależności od miejsca instalacji. Więc musisz poprostu poszukać ich gdzieś na swoim komputerze.

5. Zatwierdź wszystkie okna przyciskiem **OK**.

## Weryfikacja instalacji

Po zakończeniu instalacji **uruchom nowy terminal** (aby odświeżyć zmienne środowiskowe) i sprawdź, czy każde narzędzie jest dostępne:

```powershell
git --version
meson --version
ninja --version
pkg-config --version
```

---

## Budowanie projektu

Po poprawnej konfiguracji środowiska możemy skompilować projekt:

Otwórz [CLion](https://www.jetbrains.com/clion/) i kliknij otwórz projekt i wybierz **Projekt_Metody_Programowania_2026**.
Potem kliknij ten zielony przycisk i wszystko powino się zacząć pobierać in kompilować.

## Rozwiązywanie problemów

| Problem                         | Możliwe rozwiązanie                                                        |
| ------------------------------- | -------------------------------------------------------------------------- |
| `meson: command not found`      | Sprawdź, czy ścieżka do Meson jest w zmiennej `PATH` i zrestartuj terminal |
| `ninja: command not found`      | Analogicznie jak wyżej dla Ninja                                           |
| `pkg-config: command not found` | Upewnij się, że ścieżka do `pkg-config-lite\bin` została dodana do `PATH`  |
| Winget nie jest rozpoznawany    | Zaktualizuj „Instalator aplikacji" w Microsoft Store                       |
| Błędy kompilacji po kompilacji  | Usuń katalog `builddir` z projektu i uruchom konfigurację ponownie         |

Jak pojawi się coś innego to pisz na Messengerze.

---

## Przydatne linki

- [Dokumentacja Meson](https://mesonbuild.com/documentation.html)
- [Dokumentacja Git](https://git-scm.com/doc)
- [Winget – dokumentacja Microsoft](https://learn.microsoft.com/pl-pl/windows/package-manager/winget/)
