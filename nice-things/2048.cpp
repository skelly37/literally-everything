#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<fstream>

#ifdef _WIN32
	#include<conio.h>
#else
	#include<termios.h>
	#include<stdio.h>
#endif

using namespace std;

/* Klasa gry 2048 */
class Game2048
{
	private:
		/* Atrybuty klasy */

		// aktualna plansza do gry
		unsigned short board[4][4] =   {{0, 0, 0, 0}, 									
										{0, 0, 0, 0},
					 					{0, 0, 0, 0},
					 					{0, 0, 0, 0}},

		// plansza do sprawdzania, czy obecna tura byla ruchem oraz umozliwiajaca cofanie jednego ruchu
		previous_board[4][4];							        				

		// akumulatory ruchow oraz punktow
		unsigned int moves = 0, points = 0, 

		// zmienna pomocnicza do wykonywania cofania
		previous_points, 

		// najlepszy wynik
		highscore;

		// flaga sprawdzajaca czy nalezy wyswietlic komunikat o nowym rekordzie
		bool highscore_beaten = false;


		/* Koniec atrybutów klasy */


		/* Logika tablicy */

		// Glowna metoda, wykonujaca ruchy na tablicy
		// 	 1) aktualizacja tablicy pomocniczej po poprzednim ruchu
		// 	 2) wywolanie funkcji odpowiadajacej klawiszowi lub przerwanie
		// 	 3) ewentualna finalizacja ruchu -- inkrementacja akumulatora ruchow i dodanie 2 lub 4 w puste miejsce
		void move(char key)
		{
			switch(key)
			{
				case 'W':
					update_cache();
					move_up();
					break;
				case 'S':
					update_cache();
					move_down();
					break;
				case 'A':
					update_cache();
					move_left();
					break;
				case 'D':
					update_cache();
					move_right();
					break;
				case 'E':
					undo();
					return;
				default:
					return;
			};
			finish_move();
		}

			/* Metody pomocnicze sluzace do wykonywania ruchow */
				/*  Metody sluzace dodawaniu sasiednich liczb (dodaja w kierunku zgodnym z nazwa, tj. add_up() sluzy ruchowi w gore) */
			void add_up(unsigned short row, unsigned short column)
			{
				board[row][column] += board[row+1][column];
				points += board[row][column];
				board[row+1][column] = 0;
			}

			void add_down(unsigned short row, unsigned short column)
			{
				board[row+1][column] += board[row][column];
				points += board[row+1][column];
				board[row][column] = 0;
			}

			void add_left(unsigned short row, unsigned short column)
			{
				board[row][column] += board[row][column+1];
				points += board[row][column];
				board[row][column+1] = 0;
			}

			void add_right(unsigned short row, unsigned short column)
			{
				board[row][column+1] += board[row][column];
				points += board[row][column+1];
				board[row][column] = 0;
			}
				/* Koniec metod sluzacych dodawaniu sasiednich liczb */

				/* Metody przesuwajace zera mozliwie najdalej od pozadanej krawedzi, by umozliwic dodawanie liczb (dzialaja zgodnie z nazwa, tj. clear_zeros_up() 'czysci' gore z zer i przesuwa je mozliwie blisko dolnej krawedzi) */
			void clear_zeros_up(unsigned short column)
			{
				bool moved = false;

				for(unsigned short count=0; count<3; count++)
				{
					for(unsigned short row=0; row<3; row++)
					{
						if(board[row][column] == 0 and board[row+1][column] != 0)
						{
							board[row][column] = board[row+1][column];
							board[row+1][column] = 0;
							moved = true;
						}
					}
					if(not moved)
						return;	
				}			
			}

			void clear_zeros_down(unsigned short column)
			{
				bool moved = false;

				for(unsigned short count=0; count<3; count++)
				{
					for(unsigned short row=3; row>0; row--)
					{
						if(board[row][column] == 0 and board[row-1][column] != 0)
						{
							board[row][column] = board[row-1][column];
							board[row-1][column] = 0;
							moved = true;
						}
					}
					if(not moved)
						return;	
				}
			}

			void clear_zeros_left(unsigned short row)
			{
				bool moved = false;

				for(unsigned short count=0; count<3; count++)
				{
					for(unsigned short column=3; column>0; column--)
					{
						if(board[row][column-1] == 0 and board[row][column] != 0)
						{
							board[row][column-1] = board[row][column];
							board[row][column] = 0;
							moved = true;
						}
					}
					if(not moved)
						return;	
				}
			}

			void clear_zeros_right(unsigned short row)
			{
				bool moved = false;

				for(unsigned short count=0; count<3; count++)
				{
					for(unsigned short column=0; column<3; column++)
					{
						if(board[row][column+1] == 0 and board[row][column] != 0)
						{
							board[row][column+1] = board[row][column];
							board[row][column] = 0;
							moved = true;
						}
					}
					if(not moved)
						return;	
				}
			}
				/* Koniec metod przesuwajacych zera mozliwie najdalej od pozadanej krawedzi */

				/* Metody obslugujace ruch w konkretnym kierunku (np. move_up() wykonuje przesuniecie liczb w gore) */
				void move_up()
				{
					// Dla kazdej kolumny:
					//   1) Przerzuc zera na dol
					//   2) Dodaj sasiednie liczby (os pionowa)
					//   3) Przerzuc zera na dol
					for(unsigned short column=0; column<4; column++)
					{
						clear_zeros_up(column);
					

						if(board[0][column] == board[1][column])
						{
							add_up(0, column);

							if(board[2][column] == board[3][column])
								add_up(2, column);
						}

						else if(board[1][column] == board[2][column])
							add_up(1, column);

						else if(board[2][column] == board[3][column])
							add_up(2, column);

						clear_zeros_up(column);
					}
				}

				void move_down()
				{
					// Dla kazdej kolumny:
					//   1) Przerzuc zera do gory
					//   2) Dodaj sasiednie liczby (os pionowa)
					//   3) Przerzuc zera do gory 
					for(unsigned short column=0; column<4; column++)
					{
						clear_zeros_down(column);
					

						if(board[2][column] == board[3][column])
						{
							add_down(2, column);

							if(board[0][column] == board[1][column])
								add_down(0, column);
						}

						else if(board[1][column] == board[2][column])
							add_down(1, column);

						else if(board[0][column] == board[1][column])
								add_down(0, column);
						
						clear_zeros_down(column);
					}
				}

				void move_left()
				{
					// Dla kazdego wiersza:
					//   1) Przerzuc zera prawo
					//   2) Dodaj sasiednie liczby (os pozioma)
					//   3) Przerzuc zera na prawo 
					for(unsigned short row=0; row<4; row++)
					{
						clear_zeros_left(row);

						if(board[row][0] == board[row][1])
						{
							add_left(row, 0);

							if(board[row][2] == board[row][3])
								add_left(row, 2);
						}

						else if(board[row][1] == board[row][2])
							add_left(row, 1);

						else if(board[row][2] == board[row][3])
							add_left(row, 2);
					
						clear_zeros_left(row);
					}
				}

				void move_right()
				{
					// Dla kazdego wiersza:
					//   1) Przerzuc zera lewo
					//   2) Dodaj sasiednie liczby (os pozioma)
					//   3) Przerzuc zera na lewo 
					for(unsigned short row=0; row<4; row++)
					{
						clear_zeros_right(row);

						if(board[row][2] == board[row][3])
						{
							add_right(row, 2);

							if(board[row][0] == board[row][1])
								add_right(row, 0);
						}

						else if(board[row][1] == board[row][2])
							add_right(row, 1);

						else if(board[row][0] == board[row][1])
							add_right(row, 0);
					
						clear_zeros_right(row);
					}
				}
					/* Koniec metod obslugujacych ruch w konkretnym kierunku */
				/* Koniec metod pomocnicych sluzacych do wykonywania ruchow */

		// Metoda zwracajaca wskaznik do dynamicznie alokowanej listy wspolrzednych zawierajacych 0 -- miejsca, gdzie mozna postawic nowa liczbe		
		unsigned short** get_empty_indexes()
		{
			// zainicjowanie tablicy 
			unsigned short** empty_indexes = new unsigned short*[16];
			
			// zamiana tablicy jednowymiarowej w dwuwymiarowa
			for(unsigned short index=0; index<16; index++)
				empty_indexes[index] = new unsigned short[2];

			// zapelnienie pustych miejsc liczbami 9 -- koniecznosc do iterowania po tych danych
			for(unsigned short row=0; row<16; row++)
			{
					empty_indexes[row][0] = 9;
					empty_indexes[row][1] = 9;
			}

			// pomocniczy licznik, sluzacy jako indeks dla petli zapisujacej wspolrzedne
			unsigned short array_helper = 0;

			// petla zapisujaca wspolrzedne pustych punktow
			for(unsigned short row=0; row<4; row++)
			{
				for(unsigned short column=0; column<4; column++)
				{
					if(board[row][column] == 0)
					{
						empty_indexes[array_helper][0] = row;
						empty_indexes[array_helper][1] = column;
						array_helper++;
					}
				}
			}
			return empty_indexes;
		}

		// Metoda pobierajaca wskaznik do listy wolnych miejsc i wstawiajaca liczbe 4 lub 2 (szanse 1:8)
		void add_2_or_4(unsigned short** empty_indexes)
		{
			// Jesli nie ma pustych miejsc, metoda moze zakonczyc dzialanie
			if(empty_indexes[0][0] == 9)
				return;

			// zmienna przechowujaca wartosc liczby wylosowanej do wpisania
			unsigned short two_or_four; 

			// wylosowanie 4 lub 2 z szansa 1:8
			if(get_random_number(1, 9) == 9)
				two_or_four = 4;
			else
				two_or_four = 2;

			// zliczenie ilosci pustych miejsc
			unsigned short num_of_indexes = 0;
			for(short count=0; count<16; count++)
			{
				if(empty_indexes[count][0] != 9)
					num_of_indexes++;
				else
					break;
			}

			// wylosowanie liczby, mieszczacej sie w zakresie wolnych miejsc,
			// nastepnie pobranie z tego indeksu wylosowanych wspolrzednych
			unsigned short 	random_index = get_random_number(0, num_of_indexes-1),
							row = empty_indexes[random_index][0],
						   	column = empty_indexes[random_index][1];

			// wpisanie wylosowanej liczby do wylosowanego pola
			board[row][column] = two_or_four;

			// usuniecie tablicy, na ktorej wskazniku operowala metoda
			delete[] empty_indexes;
		}

		// Metoda generujaca liczbe losowa z zadeklarowanego zakresu (wlacznie --- <min_value, max_value>)
		unsigned short get_random_number(unsigned short min_value, unsigned short max_value)
		{
			srand(time(0));
			return (rand() % (max_value - min_value + 1)) + min_value;
		}

		// Metoda sprawdzajaca czy cos sie zmienilo (czy tez nalezalo wykonac inny ruch)
		bool anything_changed()
		{
			for(unsigned short row=0; row<4; row++)
			{
				for(unsigned short column=0; column<4; column++)
				{
					if(board[row][column] != previous_board[row][column])
						return true;
				}
			}
			return false;
		}

		// TODO: metoda cofajaca ruch
		void undo()
		{
			bool move_undone = false;

			for(unsigned short row=0; row<4; row++)
			{
				for (unsigned short column=0; column<4; column++)
				{	
					if(board[row][column] != previous_board[row][column])
					{
						board[row][column] = previous_board[row][column];
						move_undone = true;
					}

				}
			}

			if(move_undone)
			{
				moves--;
				points = previous_points;
			}
		}


		// Metoda aktualizujaca tablice pomocnicza oraz akumulator punktow
		void update_cache()
		{
			//aktualizacja tablicy
			for(unsigned short row=0; row<4; row++)
			{
				for (unsigned short column=0; column<4; column++)
					previous_board[row][column] = board[row][column];
			}

			//aktualizacja akumulatora punktow
			previous_points = points;
		}

		// Metoda inkrementujaca akumulator ilosci ruchow i wywolujaca metode losujaca nowa liczbe to tablicy z wskaznikiem do wolnych miejsc jako argumentem, jesli cos sie zmienilo w tym ruchu
		// oraz przypisujaca highscore wartosc aktualnych punktow, jesli sa wieksze
		void finish_move()
		{
			if(anything_changed())
			{
				moves++;
				add_2_or_4(get_empty_indexes());
				update_highscore();
			}			
		}

		/* Koniec logiki tablicy */

		/* Logika pozostalych elementow gry */

		// sprawdzenie czy mozna wykonac jakis ruch (w tablicy wystepuje 0 lub 2 takie same liczby granicza ze soba)
		bool may_be_continued()										
		{
			for(unsigned short row=0; row<4; row++)
			{
				for(unsigned short column=0; column<4; column++)
				{
					if(board[row][column] == 0)
						return true;
					else if(board[row][column] == board[row-1][column] and row>0)
						return true;
					else if(board[row][column] == board[row+1][column] and row<3)
						return true;
					else if(board[row][column] == board[row][column-1] and column>0)
						return true;
					else if(board[row][column] == board[row][column+1] and column<3)
						return true;
				}
			}
			return false;
		}

		// aktualizacja najlepszego wyniku jesli ta gra wyznacza nowy h-score oraz ustawienie flagi, pozwalajacej pozniej na wyswietlenie w game_over(), ze mial miejsce nowy ruch
		void update_highscore()
		{
			if(points>highscore)
			{
				highscore = points;
				if(not highscore_beaten)
					highscore_beaten = true;
			}
		}

		/* Koniec pozostalej logiki */
		

		/* Kosmetyka */

		// prywatny 'akcesor', zwracajacy plansze gry jako ladnie sformatowany string i przekazuje do funkcji print_ui()
		// robi ladne granice i wyznacza pola o 5 znakach szerokosci
		string get_board()												
		{
			string theboard = "===========================\n";
			for(unsigned short row=0; row<4; row++)
			{
				theboard += "|";
				for(unsigned short column=0; column<4; column++)
				{
					string current_num = to_string(board[row][column]);
					theboard += "|";

					switch(current_num.length())
					{
						case 5:
							theboard += current_num;
							break;
						case 4:
							theboard += " " + current_num;
							break;
						case 3:
							theboard += "  " + current_num;
							break;
						case 2:
							theboard += "   " + current_num;
							break;
						case 1:
							theboard += "    " + current_num;
							break;
					}
				}
				theboard += "||\n";
				if(row<3)
					theboard += "||_____|_____|_____|_____||\n";
				else
					theboard += "||     |     |     |     ||\n";
			}
			return theboard + "===========================\n";
		}

		// wyswietlanie UI gracza -- ruchy, tabela i punkty
		void print_ui()												
		{
			print_moves();
			cout << get_board();
			print_points();
			print_highscore();
		}																					

		// wyswietlanie ruchow
		void print_moves()
		{
			cout << "Ruchy: " << setw(20) << moves << endl;
		}

		// wyswietlanie punktow
		void print_points()
		{
			cout << "Punkty: " << setw(19) << points << endl;
		}

		// wyswietlanie najlepszego wyniku
		void print_highscore()
		{
			cout << "Najlepszy wynik: " << setw(10) << highscore << endl;
		}

		/* Koniec kosmetyki */

	public:
		/* konstruktor domyslny, sprawdzajacy najlepszy wynik, dodajacy 4 lub 2 (szansa 1:8) do poczatkowej tablicy oraz tworzacy tablice pomocnicza */

		Game2048()
		{
			fstream highscore_file;
			highscore_file.open("highscore.dat", ios::in | ios::binary);

			if(highscore_file)
				highscore_file >> highscore;
			else
			{
				highscore_file.open("highscore.dat", ios::out | ios::binary);
				highscore_file << 0;
				highscore = 0;
			}

			highscore_file.close();

			add_2_or_4(get_empty_indexes());
			update_cache();
		}

		/* destruktor, aktualizujacy highscore.dat po zakonczeniu rozgrywki (obiektu) */

		~Game2048()
		{
			fstream highscore_file;
			highscore_file.open("highscore.dat", ios::out | ios::binary);
			highscore_file << highscore;
		}


		/* rdzen gry */

		void game(const char CLEAR[])
		{
			char choice;

			do
			{
				clear_screen(CLEAR);
				print_ui();
				choice = get_choice();
				move(choice);
			}while(choice != 'Q' and may_be_continued());
		}


		/* Metody komunikacyjne */

		// metoda wyswietlajaca startowe informacje o grze
		static void print_start_menu()
		{
			cout << "------------------------" << endl;
			cout << "|Prosta wersja gry 2048|" << endl; 
			cout << "------------------------" << endl << endl;

			cout << "Sterowanie:" << endl;
			cout << "-------------" << endl;
			cout << "W -- w gore" << endl;
			cout << "S -- w dol" << endl;
			cout << "A -- w lewo" << endl;
			cout << "D -- w prawo" << endl;
			cout << "E -- cofnij (UWAGA! Mozesz cofnac tylko raz!)" << endl;
			cout << "Q -- wyjdz" << endl << endl;

			cout << "Nacisnij dowolna litere aby rozpoczac" << endl;
			cout << "-------------------------------------\n";
		}

		// metoda komunikujaca zakonczenie gry i wyswietlajaca jej wyniki
		void game_over(const char CLEAR[])
		{	
			clear_screen(CLEAR);
			cout << get_board() << endl;
			cout << endl << "---------------------------" << endl; 
			cout << "Koniec gry.";
			if(highscore_beaten)
				cout << setw(16) << "Nowy rekord!";
			cout << endl; 
			print_points();
			print_moves();
			cout << "---------------------------" << endl;
			cout << endl << "Aby zagrac jeszcze raz nacisnij dowolna litere" << endl;
			cout << "Aby wyjsc z gry nacisnij Q" << endl;
		}

		/* Koniec metod komunikacyjnych*/


		/* Statyczne metody pomocnicze */

		// metoda czyszczaca terminal odpowiednia dla OS komenda
		static void clear_screen(const char CLEAR[])
		{
			system(CLEAR);
		}


		// odpowiednie dla OS metody pobierajace znak z buforu
#ifdef _WIN32
	static char get_choice()
	{
		return toupper(getch());
	}

#else

	static char get_choice()
	{
		struct termios old, current;

		// pobranie starych ustawien i/o
		tcgetattr(0, &old);

		// ustawienie tymczasowych ustawien na identyczne ze starymi
		current = old;

		// wylaczenie wyswietlania wpisywanego klawisza oraz buforu
		current.c_lflag &= ~ICANON;
		current.c_lflag &= ~ECHO;

		// uzycie nowych ustawien i/o, pobranie znaku, przywrocenie starych ustawien i zwrocenie duzej litery
		tcsetattr(0, TCSANOW, &current);
		char ch;
		cin >> ch;
		tcsetattr(0, TCSANOW, &old);
		return toupper(ch);
	}
#endif
		/* Koniec statycznych metod pomocniczych */
/* Koniec klasy */		
};



int main()
{
	// okreslenie odpowiedniej dla aktualnego OS komendy shellowej czyszczacej terminal
	#ifdef _WIN32
		const char CLEAR[4] = {'c', 'l', 's', '\0'};
	#else
		const char CLEAR[6] = {'c', 'l', 'e', 'a', 'r', '\0'};
	#endif

	// wyczyszczenie terminala odpowiednia komenda i wyswietlenie informacji startowych
	Game2048::clear_screen(CLEAR);
	Game2048::print_start_menu();

	// Pobranie wyboru dot. kontynuacji od gracza
	char choice = Game2048::get_choice();

	// Petla tworzaca nowe gry po przegraniu/przerwaniu poprzednich, dopoki gracz jej nie przerwie
	while(choice != 'Q')
	{
		Game2048 gra;
		gra.game(CLEAR);
		gra.game_over(CLEAR);
		choice = Game2048::get_choice();
	}
}