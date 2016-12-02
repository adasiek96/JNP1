// Autorzy: Adam Sobecki (as371793), Adrian Akerman (aa370708)

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <tuple>

using namespace std;

// WEKTOR KROTEK TYPU <1, 2, 3, 4, 5, 6>, GDZIE:
// 1=rok_wydania_int
// 2=nazwa_kraju_string
// 3=wartość_znaczka_double
// 4=nazwa_znaczka_string
// 5=wartość_znaczka_string
// 6=rok_wydania_string
typedef tuple <int, string, double, string, string, string> my_type;

void print_error(int line, const string & text) {
	cerr << "Error in line " << line << ":" << text << endl;
}

bool both_are_spaces(char lhs, char rhs) {
	return (lhs == rhs) && (lhs == ' ');
}

// funkcja iterująca po naszej bazie danych, udzielająca i wypisująca
// odpowiedzi na stdout
void answer_query(int year_from, int year_to, const vector<my_type> & my_data,
				  int line, string text) {
	
	vector<my_type>::const_iterator it;
	it = lower_bound(my_data.begin(), my_data.end(),
					 make_tuple(year_from, "", 0, "", "", ""));
	
	for (; it < my_data.end() && get<0>(*it) <= year_to; it++){
		cout << get<5>(*it) << " ";
		cout << get<1>(*it) << " ";
		cout << get<4>(*it) << " ";
		cout << get<3>(*it) << endl;
	}
}

// funkcja parsująca wiersz opisujący znaczek
my_type parse1(smatch result) {
	
	// name - nazwa znaczka, value - wartość, year - rok wydania,
	// country - kraj wydania / poczta
    string name = result[1].str().data();
	string value = result[2].str().data();
	string value_copy = result[2].str().data();
	string year = result[3].str().data();
	string country = result[4].str().data();
	
	// usuwanie możliwej spacji na końcu kraju wydania / poczty
	if (country[country.length() - 1] == ' ')
		country.pop_back();
	
	// zamiana ',' na '.', by móc ładnie zrobić konwersję ze stringa na double
	replace(value_copy.begin(), value_copy.end(), ',', '.');
	// konwersje wartości znaczka i roku wydania
	double value_double = stod(value_copy);
	int year_int = stoi(year);
	my_type m = make_tuple(year_int, country, value_double, name, value, year);
	
	return m;
}

// funkcja parsująca wiersz zawierający zapytanie oraz odpowiadająca na nie
void parse2_answer(smatch result, const vector<my_type> & my_data, int line,
				   string text) {
	
	// przedział lat: year_from_s - 'rok od', year_to_s - 'rok_do'
	string year_from_s = result[1].str().data();
	string year_to_s = result[2].str().data();
	int year_from = stoi(year_from_s);
	int year_to = stoi(year_to_s);
	
	// sprawdzenie poprawności roku i wypisanie odpowiedzi na zapytanie
	if (year_from > year_to)
		print_error(line, text);
	else
		answer_query(year_from, year_to, my_data, line, text);
}

int main() {
	vector<my_type> my_data; // baza danych
	string text, copy_of_text; // linia tekstu i jej kopia
	bool data_input_mode = true; // czy program przyjmuje jeszcze opisy znaczków
	int line = 0; // nr wczytywanej linii tekstu
	
	// regex szukający opisu znaczka:
	// początek_linii + odstęp + nazwa_znaczka + odstęp + wartość_znaczka +
	// + odstęp + rok_wydania + odstęp + nazwa_kraju_poczty + koniec linii
	regex pattern("^\\s*(.+)\\s(\\d+[.,]\\d+|\\d+)\\s(\\d{4})\\s(.+)$");
	// regex szukający opisu zapytania:
	// początek_linii + odstęp + rok_od + odstęp + rok_do + odstęp +
	// + koniec_linii
	regex pattern2("^\\s*(\\d{4})\\s(\\d{4})\\s*$");
	
	while (getline(cin, text)) {
		line++;
		copy_of_text = text;
		// zamiana spacji nierozdzielającej na zwykłą
		replace(text.begin(), text.end(), (char)(-1), ' ');
		// usuwanie zbędnych odstępów
		string::iterator new_end;
		new_end = unique(text.begin(), text.end(), both_are_spaces);
		text.erase(new_end, text.end());
		
		// wyszukiwanie za pomocą wyrażeń regularnych
		smatch result;
		if (data_input_mode && regex_search(text, result, pattern)) {
			try {
				my_type m = parse1(result);
				my_data.push_back(m);
			}
			catch (const out_of_range & e){
				print_error(line, copy_of_text);
			}
		}
		else {
			if (regex_search(text, result, pattern2)) {
				// przy pierwszym wierszu opisującym zapytanie o przedział lat
				// następuje sortowanie bazy danych
				if (data_input_mode) {
					data_input_mode = false;
					sort(my_data.begin(), my_data.end());
				}
				parse2_answer(result, my_data, line, copy_of_text);
			}
			else
				print_error(line, copy_of_text);
		}
	}
	return 0;
}
