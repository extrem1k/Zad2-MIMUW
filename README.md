# Zad2-MIMUW

Wprowadzenie
Rozwiązaniem problemu dokładnego pokrycia , dla rodziny P
 podzbiorów dziedziny S
, jest taki zbiór Q⊆P
, że każdy element dziedziny S
 należy do dokładnie jednego elementu Q
.

Problem dokładnego pokrycia jest NP-zupełny . Nie jest znany deterministyczny algorytm rozwiązujący go w czasie wielomianowym. Algorytm o koszcie wykładniczym, stosujący metodę prób i błędów, jest przez Donalda Knutha nazywany Algorytmem X .

Wiele problemów, np. łamigłówki, można sprowadzić do problemu dokładnego pokrycia. Pomimo wykładniczej złożoności, efektywność rozwiązania problemu za pomocą Algorytmu X może być dla użytkownika akceptowalna.

Polecenie
Napisz program czytający ciąg wierszy F,W1,…,Wn
, w którym F
 to filtr, a W1,…,Wn
 jest reprezentacją pojedynczej instancji problemu dokładnego pokrycia.

Wszystkie czytane wiersze są tej samej długości d
. Wiersz F
 składa się ze znaków minus - i plus +. Każdy wiersz W1,…,Wn
 jest ciągiem dowolnych znaków, z których co najmniej jeden jest różny od podkreślenia _.

W rozważanej instancji dziedziną jest S={1,…,d}
. Wiersze W1
 do Wn
 reprezentują rodzinę P
 podzbiorów S
 w ten sposób, że Wj
 reprezentuje j
-ty zbiór Pj
 w tej rodzinie. Element k∈S
 należy do zbioru Pj
 wtedy i tylko wtedy, gdy k
-ty znak wiersza Wj
 jest różny od znaku podkreślenia.

Wynikiem programu jest ciąg wierszy reprezentujących wszystkie możliwe rozwiązania instancji W1,…,Wn
, przekształconych następnie za pomocą filtru F
 przez usunięcie znaków z pozycji, na których w filtrze jest -.

Rozwiązaniem instancji W1,…,Wn
 jest zbiór T⊆{1,…,n}
. Zbiór ten jest reprezentowany przez tekst R
 długości d
, który nie zawiera znaku podkreślenia _ i spełnia warunek:

∀1≤i≤d∃j∈T((Wj)i=Ri∧∀k∈T∖{j}(Wk)i=_)
Rozwiązania budujemy ze znaków wierszy W1,…,Wn
, zgodnie z ich kolejnością. W danym rozwiązaniu, w kolejności od początku, wybieramy metodą prób i błędów znaki niekolidujące z wyborami dokonanymi wcześniej.

Kolejność rozważania wierszy danych oraz ich kolumn może mieć wpływ na kolejność wierszy wynikowych, ale nie będzie miała wpływu na to, jakie wiersze program wypisze.
