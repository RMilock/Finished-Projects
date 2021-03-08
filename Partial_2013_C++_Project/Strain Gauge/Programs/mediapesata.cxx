
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

double sommatoria( double *, double *, int );

int main()
{
	using namespace std;
	string yesorno;
do
{
	cout << "\n\nCalcoliamo il valore di E per l'acciaio tramite media pesata" << endl;
	
	//prendo i valori dal documento di testo che ho precedentemente creato con a, sigma di a, b e sigma di b di seguito.
	
	double e[12];
	double sigma_e[12];
	
	ifstream fin;
	fin.open("tutti_e.txt");
	
	for ( int i = 0; i < 12; i++ )
		fin >> e[i];
	
	fin.close();
	
	fin.open("tutti_sigma_e.txt");
	
	for ( int i = 0; i < 12; i++ )
		fin >> sigma_e[i];
	
	fin.close();
	
	double peso_e[12];
	for( int i = 0; i < 12; i++ )
		peso_e[i] = 1 / ( sigma_e[i] * sigma_e[i] );
		
	
	double media_pesata_e;
	double err_medpes_e;
	
	cout << endl;
	
	double e_i_peso_e[12];
	
	for ( int i = 0; i < 12; i++ )
		e_i_peso_e[i] = e[i] * peso_e[i];
		 
	media_pesata_e = sommatoria( e_i_peso_e, e_i_peso_e + 12, 12 ) / sommatoria( peso_e, peso_e + 12, 12 );
	
	err_medpes_e = sqrt( 1.0 / sommatoria( peso_e, peso_e + 12, 12 ) );
	
	cout << "\nMedia pesata di E: " << media_pesata_e << endl
		 << "Errore: " << err_medpes_e << endl;
		 
	cout << "\nLa compatibilita' tra i valori di E stimati la loro media pesata e':" << endl << endl
		 << " ALLUNGAMENTO" << endl
		 << " Estensimetro       Valore di Compatibilita'		Tipo di Compatibilita'" << endl << endl;
		
	int numest[] = { 7, 10, 11, 13, 15, 18};
	int k = 0;
	
	for ( int i= 0; i < 12; i++ )
	{
		double compatibilita = 0;
		
		compatibilita = fabs( e[i] - media_pesata_e )/ sqrt( pow( sigma_e[i], 2 ) + pow( err_medpes_e, 2 ) );
		
		if( k == 6 ) 
		{	
			cout << "\n ACCORCIAMENTO " << endl
				 << " Estensimetro       Valore di Compatibilita'		Tipo di Compatibilita'" << endl << endl;
			k = 0;
		}
		
		cout << setw(8) << numest[k] << setw(25) << setprecision(1) << compatibilita << setw(37);
		
		if( compatibilita < 1 ) cout << "OTTIMA!" << endl;
		else if( 1 <= compatibilita && compatibilita < 2 ) cout << "BUONA" << endl;
		else if( 2 <= compatibilita && compatibilita < 3 ) cout << "pessima" << endl;
		else if( 3 < compatibilita ) cout << "Non c'e' compatibilita'" << endl;
		
		k++;
	}
 
	cout << "\n\n\nVuoi rieseguire il programma? ";
	cin >> yesorno;
	
	do
	{
		if( yesorno != "si" && yesorno != "no" )
		{
			cout << "*** Risposta non valida *** \nVuoi rieseguire il programma? ";
			cin >> yesorno;
		}
	} while( yesorno != "si" && yesorno != "no" );
} 
while( yesorno == "si" );


	return 0;
}

double sommatoria( double *inizio, double *fine, int totalemisure )
{
	double sum = 0;
	double *ptr;
	
	for( ptr = inizio; ptr != fine; ptr++ )
		sum = sum + *ptr;
	
	return sum;
}
