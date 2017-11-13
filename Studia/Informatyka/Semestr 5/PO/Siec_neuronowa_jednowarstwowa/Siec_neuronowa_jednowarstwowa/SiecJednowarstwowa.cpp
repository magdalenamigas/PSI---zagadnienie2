#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
#include<list>
#include<math.h>
using namespace std;

class Perceptron {

public:
	int wymiar;
	int liczbaWejsc;
	int liczbaIteracji;
	double **wejscia;
	double **wyniki;
	double *wagi;
	double wspUczenia;
	double eta;
	double obliczWartosc(double suma);
	double obliczWartosc2(double suma);
	void losujWagi();
	void uczPerceptron();
	void  test(int *testTable,char znak);
	int indeksLitery;
	char litera;
	double wyjscie;
	int bias;
	Perceptron(int indeks, char znak);
};

Perceptron::Perceptron(int indeks, char znak): indeksLitery(indeks), litera(znak) {

	fstream plik;
	plik.open("zbior_uczacy1.txt");
	if (plik.good())
	{
		liczbaWejsc = 35;
		wymiar = 7;
		wejscia = new double*[wymiar];
		for (int i = 0;i < wymiar;i++)
			wejscia[i] = new double[liczbaWejsc];

		wyniki = new double*[wymiar];
		for (int i = 0; i<wymiar; i++)
			wyniki[i] = new double[20];

		wagi = new double[liczbaWejsc];

		for (int j = 0; j < wymiar; j++)
		{
			for (int i = 0; i < liczbaWejsc; i++)
			{
				plik >> wejscia[j][i];
			}

			for (int k= 0; k < 7; k++)
			{
				plik >> wyniki[j][k];
			}
		}
	}
	else
	{
		cout << "blad otwarcia pliku!";
	}
}

double Perceptron::obliczWartosc(double suma) {

	if (suma > eta)
		return 1;
	else
		return 0;
}

double Perceptron::obliczWartosc2(double suma) {

		return (1/(1+exp(-suma)));
}

void Perceptron::losujWagi() {

	for (int i = 0; i < liczbaWejsc; i++)
	{
		wagi[i] = -0.1 + (double)rand() / RAND_MAX* (0.2);
	}
	//eta = -20 + (double)rand() / RAND_MAX* (40);
	cout << endl;
}

void Perceptron::test(int *testTable, char znak)
{
	double wynik = 0;
	for (int i = 0; i < liczbaWejsc; i++)
		wynik +=(testTable[i] * wagi[i]);
	cout << "Czy otrzymana litera to "<< znak << " :"<< obliczWartosc(wynik);
}

void Perceptron::uczPerceptron() {

	losujWagi();
	double licznikBledow = 0;
	double y = 0;
	double blad = 0;
	liczbaIteracji = 10000;

	for (int i = 0; i < liczbaIteracji; i++)
	{
		licznikBledow = 0;
		for (int j = 0; j <wymiar; j++)
		{
			for(int k=0; k<liczbaWejsc; k++)
				y += (wejscia[j][k] * wagi[k]);
			if (wyniki[j][indeksLitery] != obliczWartosc(y))
			{
				blad = wyniki[j][indeksLitery] - obliczWartosc(y);
				double pochodna = obliczWartosc(y)*(1 - obliczWartosc(y));
				for (int l = 0; l<liczbaWejsc; l++)
					wagi[l] = wagi[l] + wspUczenia*blad*wejscia[j][l];
				//wagi[l] = wagi[l] + wspUczenia*blad*wejscia[j][l] * pochodna;
				//eta = eta - blad;
				licznikBledow++;
			}
		}
		if (licznikBledow == 0)
		{
			cout << "Liczba potrzebnych iteracji:" << i + 1 << endl;
			break;
		}
	}
	//cout << "Perceptron nauczony :-)" << endl;
    //cout  << "eta: " << eta << endl;
	int tab[35] = { 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 }; // A
	test(tab,litera);
}

int main()
{
	srand(time(NULL));
	Perceptron A(0, 'A'), B(1, 'B'), C(2, 'C'), D(3, 'D'), E(4, 'E'), F(5, 'F'), G(6, 'G'), H(7, 'H'), I(8, 'I'), J(9, 'J'), a(10, 'a'), b(11, 'b'), c(12, 'c'), d(13, 'd'), n(14, 'n'), f(15, 'f'), h(16, 'h'), i(17, 'i'), k(18, 'k'), o(19, 'o');
	//przykladowy.uczPerceptron();
	list<Perceptron> siecNeuronowa;
	siecNeuronowa.push_back(A);
	siecNeuronowa.push_back(B);
	siecNeuronowa.push_back(C);
	siecNeuronowa.push_back(D);
	siecNeuronowa.push_back(E);
	siecNeuronowa.push_back(F);
	siecNeuronowa.push_back(G);
	/*siecNeuronowa.push_back(H);
	siecNeuronowa.push_back(I);
	siecNeuronowa.push_back(J);
	siecNeuronowa.push_back(a);
	siecNeuronowa.push_back(b);
	siecNeuronowa.push_back(c);
	siecNeuronowa.push_back(d);
	siecNeuronowa.push_back(n);
	siecNeuronowa.push_back(f);
	siecNeuronowa.push_back(h);
	siecNeuronowa.push_back(i);
	siecNeuronowa.push_back(k);
	siecNeuronowa.push_back(o);*/

	for (Perceptron D : siecNeuronowa)
	{
		D.uczPerceptron();
	}

	return 0;
}
