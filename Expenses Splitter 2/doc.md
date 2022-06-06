# Skład zespołu:
1. Piotr Kluba
2. Julia Macuga
3. Miłosz Kowalewski

# Numer zespołu: Z02

# Tematyka i opis projektu:

## 1
 Zaprezentowant projekt ma formę aplikacji konsolowej pozwalającej na skoordynowane rozliczanie wydatków podczas danego wydarzenia (domyślnie: podróż). Fundamentalnym celem programu jest zmniejszenie ilości końcowych transakcji między uczestnikami poprzez optymalne przeliczanie balansów każdego z uczestników.

## 2
 Użytkownik począwszy od uruchomienia programu tworzy wydarzenie, po czym dodaje kolejnych użytkowników. Każdy z nich ma określone atrybuty (food, alcohol, nicotine, meat, gluten, dairy, other), które przyjmują wartości prawda/fałsz określające, czy dana osoba może spożywać/korzystać z produktu danego typu. Pozwala to na rozdzielenie konkretnych typów transkacji w taki sposób, aby tylko osoby z nich korzystające miały za nie płacić.

## 3
 Po dodadaniu osób użytkownik może przejść do sekwencyjnego dodawania transakcji. W nich zaś określa się płatnika, kategorię transakcji oraz opcjonalnie, jeśli jest to "transakcja specyficznie" w przeciwieństwie do "transakcji kolektywnej", konkretne osoby, które mają w niej uczestniczyć.

## 4
 W dowolnym momencie użytkownik może zdecydować się na uregulowanie długu między daną parą uczestników. Również można wyświetlić aktualny stan transakcji tj. balans kwot między uczestnikami lub bezpośrednio kwoty konkretnych transferów pieniężnych, które muszą wykonać określone osoby, tak aby wykonać ich minimalną ilość. Użytkownik może ponadto wyświetlić historię dokonanych transakcji.

## 5
 Program posiada również opcję zapisywania historii oraz wczytywania danych z zapisanych wyjazdów. Pozwala to na kontynnuację dłuższego wydarzenia, jak również i sprawdzanie tych zakończonych.

# Struktura plików

## Pliki nagłówkowe
Person.h (klasy: Person, enum class Category)
Transactions.h (klasy: Transaction; dziedzicząca po Transaction: CollectiveTransaction; dziedzicząca po CollectiveTransaction: Specific Transaction)
Trip.h (klasa: Trip)
ui_actions.h
ui_checks.h

## importowanie plików:
file_operations_tests.cpp: Trip.h
logic_tests.cpp: Trip.h
main.cpp: Person.h, Trip.h, ui_actions.h
Person.cpp: Person.h, Transactions.h
Transactions.cpp: Transactions.h, Trip.h
Trip.cpp: Trip.h, Transactions.h
ui_actions.cpp: Person.h, Transactions.h, ui_actions.h, ui_checks.h, Trip.h
ui_checks_tests.cpp: ui_checks.h, ui_actions.h
ui_checks.cpp: ui_checks.h


# Testy

file_operations_tests.cpp:

Testy dotyczą obsługi plików tj. zapisywania i odczytywania z nich w określonym formacie, który kolejno zawiera nazwę wyjazdu, uczestników oraz transkacje zapisywane według założonej składni. Wyjazd kończy się znakami "&&&".
W związku z takimi założeniami wśród testów znajdują się sprawdzenia określonej składni plików w tym między innymi weryfikacja wzajemnego położenia określonych części tekstu.
Testy początkowo sprawdzają poprawność zmiennych tekstowych z plików za pomocą funkcji z biblioteki std::stringstream.
Następnie weryfikowana jest składnia zawierająca informacje o kategorii, ID płatnika oraz kwocie transkacji, co również wykonywane jest za pomocą funkcji z biblioteki std::stringstream.
Odczytywanie z plików sprawdzane jest za pomocą funkcji z klasy Trip poprzez weryfikację konkretnych atrybutów tworzonych obiektów.

logic_tests.cpp:

Testy w tym pliku dotyczą logiki (importowany jest plik Trip.h).
Do testów używane są między innymi funkcje szablonowe zamieszczone w pliku, które służa do porówwnywania wartości liczbowych.
Na początku sprawdzanie jest działanie funkcji dodających uczestników do wektora ich przechowujących.
Następnie weryfikowane są takie funkcje jak zmiana balansu użytkownika a także funkcje inicjujące transakcje kolektywne poprzez sprawdzenie konkretnych wartości balansów poprzez przyrównanie ich do wartości oczekiwanych.
Później zaś analogiczne testy przeprowadzane są z dodawanie transkacji typu SpecificTransactions.
Kolejne testy dotyczą m.in. funkcji z klasy Person, które ustawiają atrybuty kategorii konkretnym użytkownikom oraz przeprowadzona jest weryfikacja inicjalizacji transkacji danej kategorii w grupie, w której występują uczestnicy nie spożywający/korzystający z danej kategorii.
Później zaś sprawdzane są funkcje wykonująće transfery pieniężne mięzy użytkownikami poprzez przyrównywanie konkretnych balansów do wartości oczekiwanych.
Kolejne testy dotyczą weryfikacji przydzielanych automatycznie ID użytkownikom poprzez przyrwnywanie ich do wartości oczekiwanych (deterministycznych).


# Instrukcja uruchomienia (skompilowania)

1. Znajdując się w folderze "Expenses Splitter 2" należy wykonać polecenie make (najpierw można wywołać polecenie make clean jeśli pozostały jakieś pliki wykonywalne).
2. Następnie należy wywołać plik "./main.out" i postępować zgodnie z opisem zamiesczonym na początku dokumentacji.

# Podsumowanie projektu

Program wykonuje zamierzone cele, począwszy od tego fundamentalnego tj. sprawnego analizowania transakcji i obliczania końcowych transferów pieniężnych między uczestnikami. Jednocześnie też pozwala zapisywać pliki, które stanowią historię wyjazdów a także odczytywanie ich i dalsze modyfikowanie.
Ponadto program jest odporny na błędne wpisywanie danych ze względu na zaimplementowaną walidację. Interfejs konsolowy jest maksymalnie uproszczony w taki sposób, aby użytkownik nie musiał wpisywać długich nazw, co wydatnie zwiększa komfort użytkowania.
W kolejnej wersji projektu planujemy dostosowanie aplikacji do interfejsu graficznego a także poszerzenie oferowanej gamy funckjonalności tak, aby aplikacja była jeszcze przyjaźniejsza.




