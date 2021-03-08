
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

double sommatoria( double *, double *, int );

int main()
{
	using namespace std;
	string yesorno;
	
	cout << "\n\n     ****** Esperimento Viscosimetro ******" << endl << endl;

do
{
	char replydiametro;
		
	cout << "\nDi quale sfera vuoi calcolare i valori della retta interpolante s = s0 + vt?" << endl
		 << "\na) Diametro ( 1,5 +- 0,010 ) mm" << endl
		 << "b) Diametro ( 2,4 +- 0,010 ) mm" << endl
		 << "c) Diametro ( 4,0 +- 0,010 ) mm" << endl
		 << "d) Diametro ( 4,8 +- 0,010 ) mm" << endl
		 << "e) Diametro ( 5,6 +- 0,010 ) mm" << endl << endl;
	
	cin >> replydiametro;
	
	int totalemisure, mispercamp;
	double deltas, diametro;		
	ifstream write;
	
	if( replydiametro == 'a' )
	{
		write.open( "d1_5mm.txt" );
		totalemisure = 30;
		deltas = 0.05;
		mispercamp = 10;
		diametro = 0.0015;
	}
	else if( replydiametro == 'b' )
	{	
		write.open( "d3_32pol.txt" );
		totalemisure = 30;
		deltas = 0.05;
		mispercamp = 10;
		diametro = 0.0024;
	}
	else if( replydiametro == 'c' )
	{
		write.open( "d5_32pol.txt" );
		totalemisure = 25;
		deltas = 0.1;
		mispercamp = 5;
		diametro = 0.0040;
	}
	else if( replydiametro == 'd' )
	{	
		write.open( "d6_32pol.txt" );
		totalemisure = 30;
		deltas = 0.1;
		mispercamp = 5;
		diametro = 0.0048;
	}
	else if( replydiametro == 'e' )
	{	
		write.open( "d7_32pol.txt" );
		totalemisure = 12;
		deltas = 0.15;
		mispercamp = 3;
		diametro = 0.0056;
	}
 
	
	double tempi[totalemisure];
	
	for( int i = 0; i < totalemisure; i++ )
		write >> tempi[i];
	
	write.close;
	
	double tempimedi[mispercamp];
	int campioni = totalemisure / mispercamp;
	int counter = 0;
	
	cout << "\nTempi medi"	<< endl << endl;
	for( int i = 0; i < mispercamp; i++ )
	{
		for( int k = 0; k < campioni; k++ )
		{
			tempimedi[i] += tempi[i + k * mispercamp];
		
			if( tempi[i + k * mispercamp] == 0 )
				counter++;
			
		}

		tempimedi[i] = tempimedi[i] / ( campioni - counter );

		counter = 0;
		cout << tempimedi[i] << endl;	
	}
	
	
	double spazi[mispercamp];
	for( int i = 0; i < mispercamp; i++ )
		spazi[i] = deltas * ( i + 1 );
		
	cout << "\nVelocita' medie"	<< endl << endl;	
	double velocitamed[mispercamp];
	for( int i = 0; i < mispercamp; i++ )
	{
		velocitamed[i] = spazi[i] / tempimedi[i];	
		cout << setiosflags( ios::fixed | ios::showpoint ) << setprecision(5) << velocitamed[i] << endl;
	}
		
	double spazitempi[mispercamp];
	double tempiquadro[mispercamp];
	
	for( int i = 0; i < mispercamp; i++ )
	{	
		tempiquadro[i] = pow( tempimedi[i], 2 );
		spazitempi[i] = tempimedi[i] * spazi[i]; 
	}
	
	double delta, sommatempiquadro, sommatempi, sommaspazitempi, sommaspazi;
	
	sommatempiquadro = sommatoria( tempiquadro, tempiquadro + mispercamp, mispercamp );
	sommatempi = sommatoria( tempimedi, tempimedi + mispercamp, mispercamp );
	delta = mispercamp * sommatempiquadro - pow ( sommatempi, 2 );
	sommaspazi = sommatoria( spazi, spazi + mispercamp, mispercamp );
	sommaspazitempi = sommatoria( spazitempi, spazitempi + mispercamp, mispercamp );
	
	
	double a, addendo_1a, addendo_2a;
	addendo_1a = sommatempiquadro * sommaspazi;
	addendo_2a = sommatempi * sommaspazitempi;
	
	a = ( 1.0 / delta ) * ( addendo_1a - addendo_2a );
	
	double b, addendo_1b, addendo_2b; 
	
	addendo_1b = mispercamp * sommaspazitempi;
	addendo_2b = sommatempi * sommaspazi;
	b = ( 1.0 / delta ) * ( addendo_1b - addendo_2b );
	
	double scartiretta[mispercamp];
	for ( int i = 0; i < mispercamp; i++ )
		scartiretta[i] = pow ( ( a + b * tempimedi[i] - spazi[i] ), 2 );
		
	double sigma_y, sigma_a, sigma_b;
	
	sigma_y = sqrt( sommatoria ( scartiretta, scartiretta + mispercamp, mispercamp ) / ( mispercamp - 2 ) );
	sigma_a = sigma_y * sqrt ( sommatempiquadro / delta );
	sigma_b = sigma_y * sqrt ( mispercamp / delta ); 
	
	cout << "\n\na: " << a << endl
		 << "sigma a: " << sigma_a << endl
		 << "v: " << b << endl
		 << "sigma v: " << sigma_b << endl
		 << "sigma y: " << sigma_y << endl << endl;
	
	
	ofstream read, fout, gout;
	
	if( replydiametro == 'a' )
	{	
		read.open( "ri1_5mm.txt" );
		fout.open( "b1_5mm.txt");
		gout.open( "errb1_5mm.txt");
	}
	else if( replydiametro == 'b' )
	{	
		read.open( "ri3_32pol.txt" );
		fout.open( "b3_32pol.txt");
		gout.open( "errb3_32pol.txt");
	}
	else if( replydiametro == 'c' )
	{	
		read.open( "ri5_32pol.txt" );
		fout.open( "b5_32pol.txt");
		gout.open( "errb5_32pol.txt");
	}
	else if( replydiametro == 'd' )
	{	
		read.open( "ri6_32pol.txt" );
		fout.open( "b6_32pol.txt");
		gout.open( "errb6_32pol.txt");
	}
	else if( replydiametro == 'e' )
	{	
		read.open( "ri7_32pol.txt" );
		fout.open( "b7_32pol.txt");
		gout.open( "errb7_32pol.txt");
	}
	else if( replydiametro == 'f' )
	{	
		read.open( "ri8_32pol.txt" );
		fout.open( "b8_32pol.txt");
		gout.open( "errb8_32pol.txt");
	}
	else if( replydiametro == 'g' )
	{	
		read.open( "ri9_32pol.txt" );
		fout.open( "b9_32pol.txt");
		gout.open( "errb9_32pol.txt");
	}
	else if( replydiametro == 'h' )
	{	
		read.open( "ri9_32pol30min.txt" );
		fout.open( "b9_32pol30min.txt");
		gout.open( "errb9_32pol30min.txt");
	}
	
	for( int i = 0; i < mispercamp; i++ )
		read << tempimedi[i] << "   " << a + b * tempimedi[i] << endl;
	
	fout << b << endl;
	gout << sigma_b << endl;
	
	double erroretempi[mispercamp];
	double sommascartiq;
	
	for( int i = 0; i < mispercamp; i++ )
	{
		for( int k = 0; k < campioni; k++ )
			sommascartiq += pow( ( tempi[i + k * mispercamp] - tempimedi[i] ) , 2 );
		
		erroretempi[i] = sqrt( sommascartiq / mispercamp * ( mispercamp - 1 ) );		
	}
	
	
	double sigmavm[mispercamp];
	double errorespazi = 0.002 / sqrt(6);
	
	for( int i = 0; i < mispercamp; i++ )
		sigmavm[i] = sqrt( pow( ( errorespazi / tempimedi[i]), 2 ) + pow( spazi[i] * erroretempi[i], 2 ) / pow( tempimedi[i], 4 ) );
		
	//COMPATIBILITA'	
	
	cout << "Compatibilita' velocita'" << endl << endl;
	
	for ( int i = 0; i < mispercamp; i++ )
	{
		double compatibilita = 0;
		
		compatibilita = fabs( velocitamed[i] - b ) / sqrt( sigmavm[i] + pow( sigma_b, 2 ) );
		
		cout << compatibilita << setw(37);
		
		if( compatibilita < 1 ) cout << "OTTIMA!" << endl;
		else if( 1 <= compatibilita && compatibilita < 2 ) cout << "BUONA" << endl;
		else if( 2 <= compatibilita && compatibilita < 3 ) cout << "pessima" << endl;
		else if( 3 < compatibilita ) cout << "Non c'e' compatibilita'" << endl;
	}
	
	
	cout << "\n\nVuoi rieseguire il programma? ";
	cin >> yesorno;
	
	do
	{
		if( yesorno != "si" && yesorno != "no" )
		{
			cout << "\n*** Risposta non valida *** \nVuoi rieseguire il programma? ";
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
