#include <iostream>

using namespace std;

class Magazin{
	int peste = 0;
	int kalmar = 0;
	int chipsuri = 0;
	float apaMinerala = 0;
	float pivaBlonda = 0;
	float pivaBruna = 0;
	int paine = 0;
	int pastet = 0;
	float vodka = 0;
	float vin = 0;

	public:
		void citire();
		void preturi();
		float calculare();
		void afisare();
};

float Magazin::calculare(){
	return peste*20+kalmar*21+chipsuri*22+apaMinerala*23+pivaBlonda*24+pivaBruna*25+paine*26+pastet*27+vodka*28+vin*29;
}

void Magazin::afisare(){
	cout << "Suma totala:" << calculare() << endl;
}

void Magazin::preturi(){
	cout << "1.Peste - 20 lei" << endl;
	cout << "2.kalmar- 21 lei" << endl;
	cout << "3.chipsuri - 22 lei" << endl;
	cout << "4.apa minerala - 23 lei" << endl;
	cout << "5.piva blonda - 24 lei" << endl;
	cout << "6.piva bruna - 25 lei" << endl;
	cout << "7.paine - 26 lei" << endl;
	cout << "8.pastet - 27 lei" << endl;
	cout << "9.vodka - 28 lei" << endl;
	cout << "10.vin - 29 lei" << endl;
}

void Magazin::citire(){
	char option = 'a';
	int num;
	while(option != 'n'){
		preturi();
		cout << "Alegeti produsul:" << endl;
		cin >> num;
		cout << "Dati cantitatea dorita de procurat a produsului:" << endl;
		switch(num){
			case 1 :
					cin >> peste;
			break;

			case 2 :
					cin >> kalmar;
			break;

			case 3 :
					cin >> chipsuri;
			break;

			case 4 :
					cin >> apaMinerala;
			break;

			case 5 :
					cin >> pivaBlonda;
			break;

			case 6 :
					cin >> pivaBruna;
			break;

			case 7 :
					cin >> paine;
			break;

			case 8 :
					cin >> pastet;
			break;

			case 9 :
					cin >> vodka;
			break;

			case 10 :
					cin >> vin;
			break;
		}
		cout << "Doriti sa mai procurati ceva?: (y/n)" << endl;
		cin >> option;
	}
}

int main(){
	Magazin rubla;
	rubla.citire();
	rubla.afisare();
	return 0;
}
