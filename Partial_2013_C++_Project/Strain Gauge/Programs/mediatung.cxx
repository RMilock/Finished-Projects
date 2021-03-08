#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double media( double *, double *, int );
double sommatoriadiff( double *, double *, int );
double erroreqmedio( double *, double *, int);
double erroremedia( double *, double *, int);
double sommatoria( double *, double *, int );

int main()
{
	using namespace std;
	
	ifstream fin, gin;
	
	fin.open( "etung.txt" );
	gin.open( "ktung.txt" );
	
	double e[2];
	double k[2];
	
	for( int i = 0; i < 2; i++ )
	{
		fin >> e[i];
		gin >> k[i];
	}
	
	fin.close();
	gin.close();
	
	
	fin.open( "sigmaetung.txt" );
	gin.open( "sigmaktung.txt" );
	
	double sigmae[2];
	double sigmak[2];
	
	for( int i = 0; i < 2; i++ )
	{
		fin >> sigmae[i];
		gin >> sigmak[i];
	}
	
	fin.close();
	gin.close();
	
	double meane = media( e, e + 2, 2 );
	double meank = media( k, k + 2, 2 );
	
	double errmeane = erroremedia( e, e + 2, 2 );
	double errmeank = erroremedia( k, k + 2, 2 );
	
	cout << "\n\n ** MEDIA di E - TUNGSTENO **" << endl << endl
		 << "E medio: " << meane << endl
		 << "errore: " << errmeane << endl
		 << "\nK medio: " << meank << endl
		 << "errore: " << errmeank << endl;
	
	cout << "\n\n*** COMPATIBILITA' E ***" << endl;
	for ( int i= 0; i < 2; i++ )
	{
		double compatibilita = 0;
		
		compatibilita = fabs( e[i] - meane )/ sqrt( pow( sigmae[i], 2 ) + pow( errmeane, 2 ) );
		
		if( i == 0 ) cout << "\n ALLUNGAMENTO" << endl;
		else if( i == 1 ) cout << "\n ACCORCIAMENTO" << endl;
		
		cout << "Valore di Compatibilita'	  Tipo di Compatibilita'" << endl << endl;
		
		
		cout << setw(12) << setprecision(1) << compatibilita << setw(37);
		
		if( compatibilita < 1 ) cout << "OTTIMA!" << endl;
		else if( 1 <= compatibilita && compatibilita < 2 ) cout << "BUONA" << endl;
		else if( 2 <= compatibilita && compatibilita < 3 ) cout << "pessima" << endl;
		else if( 3 < compatibilita ) cout << "Non c'e' compatibilita'" << endl;
		
	}
	
	cout << "\n\n*** COMPATIBILITA' K ***" << endl;
	for ( int i= 0; i < 2; i++ )
	{
		double compatibilita = 0;
		
		compatibilita = fabs( k[i] - meank )/ sqrt( pow( sigmak[i], 2 ) + pow( errmeank, 2 ) );
		
		if( i == 0 ) cout << "\n ALLUNGAMENTO" << endl;
		else if( i == 1 ) cout << "\n ACCORCIAMENTO" << endl;
		
		cout << "Valore di Compatibilita'	  Tipo di Compatibilita'" << endl << endl;
		
		
		cout << setw(12) << setprecision(1) << compatibilita << setw(37);
		
		if( compatibilita < 1 ) cout << "OTTIMA!" << endl;
		else if( 1 <= compatibilita && compatibilita < 2 ) cout << "BUONA" << endl;
		else if( 2 <= compatibilita && compatibilita < 3 ) cout << "pessima" << endl;
		else if( 3 < compatibilita ) cout << "Non c'e' compatibilita'" << endl;
		
	}
	
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

double media( double *inizio, double *fine, int totalemisure )
{
	double sum = 0;
	double *ptr;
	
		sum = sommatoria( inizio, fine, totalemisure );
		
	return ( sum / totalemisure );	
}

double sommatoriadiff( double *inizio, double *fine, int totalemisure )
{
	double *ptr;
	double sum = 0;
	double mean = media( inizio, fine, totalemisure );
	
	for( ptr = inizio; ptr != fine; ptr++ )
		sum = sum + pow( ( *ptr - mean ), 2 );
	
	return sum;
}
	
double erroreqmedio( double *inizio, double *fine, int totalemisure )
	{
		return sqrt( sommatoriadiff( inizio, fine, totalemisure ) / ( totalemisure - 1 ) );
	}
	
	
double erroremedia( double *inizio, double *fine, int totalemisure )
	{
		return erroreqmedio( inizio, fine, totalemisure ) / sqrt( totalemisure ); 
	}