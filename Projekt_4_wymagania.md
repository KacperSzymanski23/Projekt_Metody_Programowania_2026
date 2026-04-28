# Metody Programowania – Projekt

## Gra w Kółko i Krzyżyk dla Dowolnego Rozmiaru Planszy – Algorytm MinMax oraz Obcinanie Alfa-Beta

Pracujesz nad aplikacją, która ma analizować rozgrywki gry w kółko i krzyżyk. Kluczowe jest, aby rozwiązanie było elastyczne, pozwalało na łatwe dodawanie nowych strategii podejmowania decyzji oraz umożliwiało dynamiczną zmianę strategii dla gracza w trakcie działania programu.

Rozważamy planszę kwadratową rozmiaru **n x n**, gdzie **n >= 3**. W polu może znajdować się znak `X`, znak `O` albo pole puste. Wygrywa gracz, który jako pierwszy zapełni swoim symbolem cały wiersz, całą kolumnę albo jedną z dwóch głównych przekątnych.

---

### 1. Interfejs `Board`

```cpp
unsigned size() const;
char& operator()(unsigned x, unsigned y);
char operator()(unsigned x, unsigned y) const;
bool full() const;
void clear();
```

- `size()` — zwraca rozmiar planszy
- `operator()` — odczytuje i modyfikuje zawartość pól
- `full()` — sprawdza, czy plansza jest pełna
- `clear()` — czyści planszę

Przyjmujemy:

- `'X'` — ruch gracza X
- `'O'` — ruch gracza O
- `'.'` — pole puste

---

### 2. Przeciążenie `operator<<`

```cpp
std::ostream& operator<<(std::ostream& out, const Board& b);
```

Wypisuje planszę do podanego strumienia.

---

### 3. Klasa `BoardExt`

Klasa pochodna od `Board`.

```cpp
BoardExt(unsigned n);
```

Tworzy pustą planszę rozmiaru n x n.

---

### 4. Klasa `Move`

```cpp
Move(unsigned x, unsigned y);
unsigned x() const;
unsigned y() const;
```

Reprezentuje pojedynczy ruch.

---

### 5. Interfejs `Strategy`

```cpp
Move chooseMove(const Board& b, char symbol);
```

Zwraca najlepszy ruch dla gracza o symbolu `symbol` na podstawie aktualnego stanu planszy.

---

### 6. Strategie wyboru ruchu

#### `MinMaxStrategy`

Realizuje pełny algorytm min-max (przeszukuje pełne drzewo gry):

- stan wygrany → `1`
- stan przegrany → `-1`
- remis → `0`

#### `AlphaBetaStrategy`

Realizuje algorytm min-max z obcinaniem alfa-beta. Zwracany ruch ma taką samą wartość oceny jak w `MinMaxStrategy`, lecz przy wielu ruchach równoważnych może zostać zwrócony inny ruch optymalny.

---

### 7. Klasa `TicTacToeGame`

```cpp
TicTacToeGame(Board* b, Strategy* xStrategy, Strategy* oStrategy);
bool makeMove(Move m, char symbol);
void play();
bool finished() const;
char winner() const;
void changeStrategy(char symbol, Strategy* newStrategy);
```

- `makeMove()` — wykonuje pojedynczy ruch, o ile jest poprawny
- `play()` — prowadzi automatyczną rozgrywkę do końca (zaczyna X, jeśli plansza pusta)
- `finished()` — sprawdza, czy gra zakończona
- `winner()` — zwraca `'X'`, `'O'`, `'D'` (remis) lub `'.'` (gra trwa)
- `changeStrategy()` — podmienia strategię wybranemu graczowi

---

### 8. Klasa `MyExceptions`

Każda metoda sprawdza poprawność argumentów i rzuca wyjątek zdefiniowany w `MyExceptions` w przypadku błędu. Należy pamiętać o odpowiedniej obsłudze pamięci.

> W jednej z klas 3–7 przy implementacji należy wykorzystać **szablon klasy**.

---

### Przykład użycia

```cpp
Board* b = new BoardExt(3);
Strategy* s1 = new MinMaxStrategy();
Strategy* s2 = new AlphaBetaStrategy();
TicTacToeGame* g = new TicTacToeGame(b, s1, s2);

g->play();
std::cout << *b << std::endl;
std::cout << g->winner() << std::endl;

g->changeStrategy('X', s2);
b->clear();
g->play();
std::cout << *b << std::endl;
std::cout << g->winner() << std::endl;

delete g;
delete s2;
delete s1;
delete b;
```

---

### Struktura plików

Każda klasa w osobnych plikach `.h` i `.cpp`. Folder: `Nazwisko1_Nazwisko2_projekt`

```
board.h               board.cpp
boardExt.h            boardExt.cpp
move.h                move.cpp
strategy.h            strategy.cpp
minMaxStrategy.h      minMaxStrategy.cpp
alphaBetaStrategy.h   alphaBetaStrategy.cpp
ticTacToeGame.h       ticTacToeGame.cpp
myexceptions.h        myexceptions.cpp
main.cpp
```
