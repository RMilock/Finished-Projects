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

	char reply_numest;

	cout << "\nDi quale strumento vuoi calcolare K medio, relativo errore e compatibilità?" << endl
			 << "\na) Estensimetro n'  7 - L = 950 +- 2 mm | S = 0.330 mm +- 1%" << endl
			 << "b) Estensimetro n' 10 - L = 950 +- 2 mm | S = 0.406 mm +- 1%" << endl
			 << "c) Estensimetro n' 11 - L = 950 +- 2 mm | S = 0.432 mm +- 1%" << endl
			 << "d) Estensimetro n' 13 - L = 900 +- 2 mm | S = 0.279 mm +- 1%" << endl
			 << "e) Estensimetro n' 15 - L = 700 +- 2 mm | S = 0.279 mm +- 1%" << endl			 
			 << "f) Estensimetro n' 18 - L = 400 +- 2 mm | S = 0.279 mm +- 1%" << endl << endl;
		
	cin >> reply_numest;
	
	double ktutti[12];	
	
	ifstream gin( "kacc.txt" );
	
	for( int i = 0; i < 12; i++ )
			gin >> ktutti[i];
	
	gin.close();
	
	double sigmaktutti[12];
	
	gin.open( "sigmakacc.txt" );
	
	for( int i = 0; i < 12; i++ )
			gin >> sigmaktutti[i];
	
	gin.close();
	
	double kparziali[2];
	double sigmakparziali[2];
	
	if( reply_numest == 'a' )
	{
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[i];
			sigmakparziali[i] = sigmaktutti[i];
		}
	}
	else if( reply_numest == 'b' )
	{	
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[( i + 2 )];
			sigmakparziali[i] = sigmaktutti[( i + 2 )];
		}
	}
	else if( reply_numest == 'c' )
	{
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[( i + 4 )];	
			sigmakparziali[i] = sigmaktutti[( i + 4 )];
		}
	}
	else if( reply_numest == 'd' )
	{	
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[( i + 6 )];
			sigmakparziali[i] = sigmaktutti[( i + 6 )];
		}
	}
	else if( reply_numest == 'e' )
	{	
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[( i + 8 )];
			sigmakparziali[i] = sigmaktutti[( i + 8 )];
		}
	}
	else if( reply_numest == 'f' )
	{	
		for( int i = 0; i < 2; i++ )
		{
			kparziali[i] = ktutti[( i + 10 )];
			sigmakparziali[i] = sigmaktutti[( i + 10 )];
		}
	}
		
	
	for( int i = 0; i < 2; i++ )
		cout << kparziali[i] << "     " << sigmakparziali[i] << endl;
	
	
	double meank = media( kparziali, kparziali + 2, 2 );
	double errmeank = erroremedia( kparziali, kparziali + 2, 2 );
	
	cout << "\n\n ** MEDIA di K - ACCIAIO **" << endl << endl
		 << "K medio: " << meank << endl
		 << "errore: " << errmeank << endl;
	
	
	cout << "\n\n*** COMPATIBILITA' K ***" << endl;
	for ( int i = 0; i < 2; i++ )
	{
		double compatibilita = 0;
		
		compatibilita = fabs( kparziali[i] - meank )/ sqrt( pow( sigmakparziali[i], 2 ) + pow( errmeank, 2 ) );
		
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