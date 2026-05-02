# Konfiguracja środowiska – Meson Build System

Wiem, że jeszcze nie wybraliśmy tematu, ale jak już to zrobimy, to musisz zainstalować parę rzeczy. Na ostatnim projekcie z C++ ja i kolega mieliśmy problem z odpaleniem projektu, który miał dużo zależności do pobrania. Więc teraz masz taki mini tutorial jak to zrobić. **Jeszcze go nie skończyłem, więc może jeszcze coś nie działać.** Może jakiś skrypt zrobię, co to od razu ogarnie i zrobi to za nas, ale na razie nie mam czasu.

> **Uwaga:** Plikiem `native.ini` się nie przejmój nie jest ci do niczeho potrzebny.

---

## Instalacja zależności przez Winget

Otwórz **Terminal** lub **PowerShell** jako **Administrator**, a następnie wykonaj poniższe polecenia jedno po drugim.

### 1. Git

```powershell
winget install --id Git.Git -e --source winget
```

Git jest wymagany do klonowania repozytoriów z zależnościami oraz do zarządzania wersjami kodu.

---

### 2. Meson

```powershell
winget install --id mesonbuild.meson -e --source winget
```

Meson to system budowania projektu. Żebyśmy mogli skompilować projekt, należy go zainstalować. CLion wymaga Mesona zainstalowanego w systemie bo sam go nie zainstaluje.

---

### 3. Ninja

```powershell
winget install --id Ninja-build.Ninja -e --source winget
```

Ninja to backend dla Mesona. Jest to narzędzie do budowania projektów.

---

### 4. pkg-config-lite

Bez tego Meson ma problem ze znalezieniem zależności. Narazie się to nam nie przyda, ale wkrótce będziemy dodawać biblioteki do projektu, więc warto to mieć od razu.

Można zainstalować przez Winget:

```powershell
winget install --id bloodrock.pkg-config-lite -e --source winget
```

Jeśli winget będzie nie działa, to jest też opcja instalacji [pkg-config-lite z SourceForge](https://sourceforge.net/projects/pkgconfiglite/files/), albo z przy pomocy [MSYS2](https://www.msys2.org/), ale jest przy tym więcej roboty i pobierania.

---

### 5. CLang

Opcjonalnie możesz zainstalować ten kompilator, ale nie jest to wymagane. Ja go używam do skompilowania projektów, ale zamiast tego możesz skompilować je z wykorzystaniem domyslego kompilatora z CLion'a.

```powershell
winget install --id LLVM.LLVM -e --source winget
```

Potem będziesz musiał go dodać w CLion w **Settings → Build, Execution, Deployment → C/C++ → Toolchains → Add Toolchain...** i wybierz **MinGW** z listy, następnie w polu **C Compiler** wpisujesz `C:\Program Files\LLVM\bin\clang.exe`, a w **C++ Compiler** `C:\Program Files\LLVM\bin\clang++.exe`.

---

## Konfiguracja zmiennych środowiskowych

Po instalacji należy upewnić się, że wszystkie narzędzia są widoczne w systemowej zmiennej `PATH`.

1. Naciśnij `Win + S`, wpisz **„Zmienne środowiskowe"** i wybierz:
   **„Edytuj zmienne środowiskowe systemu"**

2. W oknie **Właściwości systemu** kliknij przycisk **„Zmienne środowiskowe..."**

3. W sekcji **„Zmienne systemowe"** odszukaj zmienną **`Path`** i kliknij **„Edytuj..."**

4. Kliknij **„Nowy"** i dodaj kolejno ścieżki do folderów `bin\` (albo poprostu ścieżkę do `.exe` każdego narzędzia) każdego narzędzia (jeśli instalator nie zrobił tego automatycznie):

   | Narzędzie       | Domyślna ścieżka Winget (USER = twoja nazwa użytkownika)                                                                                           |
   | --------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
   | Git             | `C:\Program Files\Git\cmd`                                                                                                                         |
   | Meson           | `C:\Program Files\Meson`                                                                                                                           |
   | Ninja           | `C:\Users\USER\AppData\Local\Microsoft\WinGet\Packages\Ninja-build.Ninja_Microsoft.Winget.Source_8wekyb3d8bbwe`                                    |
   | pkg-config-lite | `C:\Users\USER\AppData\Local\Microsoft\WinGet\Packages\bloodrock.pkg-config-lite_Microsoft.Winget.Source_8wekyb3d8bbwe\pkg-config-lite-0.28-1\bin` |

   Jeśli instalowałeś narzędzia w innych miejscach, ścieżki będą się różnić — po prostu wyszukaj `ninja.exe` i `pkg-config.exe` w Eksploratorze plików i dodaj ich katalogi.

> Zastąp `USER` swoją rzeczywistą nazwą użytkownika Windows.

5. Zatwierdź wszystkie okna przyciskiem **OK**.

---

## Weryfikacja instalacji

Po zakończeniu instalacji **uruchom nowy terminal** (aby odświeżyć zmienne środowiskowe) i sprawdź, czy każde narzędzie jest dostępne:

```powershell
git --version
meson --version
ninja --version
pkg-config --version
```

---

## Budowanie projektu w CLion

Po poprawnej konfiguracji środowiska możemy skompilować projekt:

1. Otwórz [CLion](https://www.jetbrains.com/clion/).
2. Wybierz **File → Open** i wybież folder wcześniej sklonowanego repozytorium **Projekt_Metody_Programowania_2026**.
3. CLion automatycznie wykryje plik `meson.build` i zaproponuje konfigurację projektu — kliknij **OK** / **Load Project**.
4. Jeśli CLion pyta o ścieżkę do Mesona: przejdź do **Settings → Build, Execution, Deployment → Meson** i podaj ścieżkę do `meson.exe`.
5. Kliknij zielony przycisk **▶ Run**, żeby zbudować i uruchomić projekt.

---

## Rozwiązywanie problemów

| Problem                                   | Możliwe rozwiązanie                                                                         |
| ----------------------------------------- | ------------------------------------------------------------------------------------------- |
| `meson: command not found`                | Sprawdź, czy ścieżka do Meson jest w zmiennej `PATH` i zrestartuj terminal                  |
| `ninja: command not found`                | Analogicznie jak wyżej dla Ninja                                                            |
| `pkg-config: command not found`           | Upewnij się, że ścieżka do `pkg-config-lite\bin` została dodana do `PATH`                   |
| Winget nie jest rozpoznawany              | Zaktualizuj „Instalator aplikacji" w Microsoft Store                                        |
| Błędy kompilacji / projekt się nie ładuje | Usuń katalog `builddir` z projektu, a następnie w CLion wybierz **Build → Run Meson Setup** |
| CLion nie widzi Mesona                    | Przejdź do **Settings → Build → Meson** i ustaw ścieżkę do `meson.exe` ręcznie              |

Jak pojawi się coś innego, to pisz na Messengerze.

---

## Przydatne linki

- [Dokumentacja Meson](https://mesonbuild.com)
- [Dokumentacja Git](https://git-scm.com/doc)
