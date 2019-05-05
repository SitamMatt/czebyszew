#define _USE_MATH_DEFINES

#include "iostream"
#include "windows.h"
#include  <cmath>
#include <cstdlib>
#include <array>
#include <fstream>

using namespace std;

class czebyszew
{
public:

	double *x = NULL;
	double dlugosc;
	double tablica(double n)
	{
		dlugosc = n;
		x = new double[n];
		return *x;
	}



	double *przedzialy(double  a, double b)
	{
		int j = 1;
		for (int i = 0; i < dlugosc ; i++)
		{
			x[i] = (a + b) / 2 + ((b - a) / 2)*cos((((2 * j) - 1) / (2 * dlugosc)) * M_PI);
			j++;
		}
		return x;
	}
	
};

class funkcje
{
public:
	int a;
	void komunikat()
	{
		cout << "wybierz jedna z funkcji 1 - 5";
		cout << "\n 1. wielomian : 2x^3 - 5x^2 - x + 3 ";
		cout << "\n 2. absolutna : |x| ";
		cout << "\n 3. trygonometryczna : cos(2x) ";
		cout << "\n 4. zlozenie : (x^2 + x - 5 ) * sin(x) ";
		cout << "\n 5. zlozenie : |x / 2| * cos(x) \n";

		cin >> a;
		cout << endl;
	}

	
	double wybor(double x)
	{
		switch (a)
		{
		case 1:
			{	
		    int wsp[4] = { 2,-5,-1,3 };
			int n = 3;
			double wynik = wsp[0];
			for (int i = 1; i <= n; i++)
					wynik = wynik * x + wsp[i];
				return wynik;
			}
		case 2:
			{
			double wynik = abs(x);
				return wynik;
			}
		case 3:
			{
			double wynik = cos(2*x);
				return wynik;
			}
		case 4:
			{
			double wynik = (pow(x, 2) + x - 5) * sin(x);
				return wynik;
			}
		case 5:
			{
			double wynik = abs(x / 2) * cos(x);
				return wynik;
			}
		default:
				return 0;
		}
	}


};

double interpolacja(double osx[], double osy[], int  n, double a)
{
	double mult;
	double sum = 0;
	int i, j;

	for (j = 0; j < n - 1; j++)
	{
		for (i = n - 1; i > j; i--)
			osy[i] = (osy[i] - osy[i - 1]) / (osx[i] - osx[i - j - 1]);
	}
	for (i = n - 1; i >= 0; i--)
	{
		mult = 1;
		for (j = 0; j < i; j++)
			mult *= (a - osx[j]);

		mult *= osy[j];
		sum += mult;
	}


	return sum;
}
class pliki {
public:
	void plik_interpolacja(double osx[], double osy[])
	{
		ofstream wykres;
		wykres.open("interpolacja.txt");
		for (int i = 0; i < 50; i++)
		{
			wykres << osx[i] << " " << osy[i] << endl;
		}
		wykres.close();
	}

	void plik_funkcja(double a, double b,funkcje obliczenia)
	{
		double y[50],x[50];
		double skok,start;
		if (a > b)
		{
			start = b;
			skok = (a - b) / 50;
		}
		else
		{
			start = a;
			skok = (b - a) / 50;
		}
		for (int i = 0; i < 50; i++)
		{
			y[i] = obliczenia.wybor(start);
			x[i] = start;
			start += skok;
		}
		ofstream wykres;
		wykres.open("funkcja.txt");
		for (int i = 0; i < 50; i++)
		{
			wykres << x[i] << " " << y[i] << endl;
		}
		wykres.close();
	}
	
	void plik_czebyszew(double **x, double n)
	{
		ofstream wykres;
		wykres.open("czebyszew.txt");
		for (int i = 0; i < n; i++)
		{
			wykres << x[i][0] << " " << x[i][1] << endl;
		}
		wykres.close();
	}
};




int main()
{
	char yes = 'y';
	while (yes == 'y')
	{
		funkcje obliczenia;
		czebyszew dane;
		pliki plik;
		double a, b, start, przeskok, pomoc;
		double osx[50];
		double osy[50];
		int n;
		double osox[50];
		double wykres[50];
		obliczenia.komunikat();
		cout << "podaj przedzialy wezlow  : ";
		cin >> b >> a;
		cout << endl << "ilosc punktow : ";
		cin >> n;
		dane.tablica(double(n));
		double *y = dane.przedzialy(a, b);
		double **punkty = new double*[n];
		for (int i = 0; i < n; i++)
		{
			punkty[i] = new double[2];
		}

		for (int j = 0; j < n; j++)
		{
			punkty[j][0] = y[j];
			punkty[j][1] = obliczenia.wybor(y[j]);
		}

		plik.plik_funkcja(a, b, obliczenia);
		plik.plik_czebyszew(punkty, n);

		cout << endl;
		if (a > b)
		{
			start = b;
			pomoc = b;
			przeskok = double((a - b)) / 49;
		}
		else
		{
			start = a;
			pomoc = a;
			przeskok = double((b - a)) / 49;
		}

		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < n; j++)
			{
				osx[j] = punkty[j][0];
				osy[j] = punkty[j][1];
			}
			wykres[i] = interpolacja(osx, osy, n, start);
			start = start + przeskok;
		}
		for (int i = 0; i < 50; i++)
		{
			osox[i] = pomoc;
			pomoc = pomoc + przeskok;
		}

		plik.plik_interpolacja(osox, wykres);

		delete[] y;
		delete[] punkty;
		cout << endl << "pliki zostaly utworzone";
		cout << endl;
		
		ShellExecute(NULL, "open", R"(D:\Dev\cpp\Interpolacja\Graph.NET\bin\Debug\Graph.NET.exe)", R"(-i D:\Dev\cpp\Interpolacja\Project11\interpolacja.txt -f D:\Dev\cpp\Interpolacja\Project11\funkcja.txt -n D:\Dev\cpp\Interpolacja\Project11\czebyszew.txt)", NULL, SW_SHOWDEFAULT);
		cout << "powtorzyc ? y/n : "; cin >> yes;
	}
	return 0;
}