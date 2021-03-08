
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
		
	cout << "\nDi quale sfera vuoi analizzare i dati?" << endl
		 << "\na) Diametro ( 1,5 +- 0,010 ) mm" << endl
		 << "b) Diametro ( 2,4 +- 0,010 ) mm" << endl
		 << "c) Diametro ( 4,0 +- 0,010 ) mm" << endl
		 << "d) Diametro ( 4,8 +- 0,010 ) mm" << endl
		 << "e) Diametro ( 5,6 +- 0,010 ) mm" << endl			 
		 << "f) Diametro ( 6,4 +- 0,010 ) mm" << endl 
		 << "g) Diametro ( 7,1 +- 0,010 ) mm" << endl
		 << "h) Diametro ( 7,1 +- 0,010 ) mm dopo 30 min" << endl << endl;
	
	cin >> replydiametro;

	ifstream write, input, fin, gin, hin, tit;
	int totalemisure;
	double diametro;
	
	if( replydiametro == 'a' )
	{
		fin.open( "d1_5mm.txt" );
		input.open( "velocita1_5mm.txt" );
		gin.open( "sigmav1_5mm.txt" );
		write.open( "eta1_5mm.txt" );
		hin.open( "b1_5mm.txt" );
		tit.open( "errb1_5mm.txt" );
		totalemisure = 30;
		diametro = 0.0015;
	}	
	else if( replydiametro == 'b' )
	{ 	
		fin.open( "d3_32pol.txt" );
		input.open( "velocita3_32pol.txt" );
		gin.open( "sigmav3_32pol.txt" );
		write.open( "eta3_32pol.txt" );
		hin.open( "b3_32pol.txt" );
		tit.open( "errb3_32pol.txt" );
		totalemisure = 30;
		diametro = 0.0024;
	}
	else if( replydiametro == 'c' )
	{
		fin.open( "d5_32pol.txt" );
		input.open( "velocita5_32pol.txt" );
		gin.open( "sigmav5_32pol.txt" );
		write.open( "eta5_32pol.txt" );
		hin.open( "b5_32pol.txt" );
		tit.open( "errb5_32pol.txt" );
		totalemisure = 25;
		diametro = 0.0040;
	}
	else if( replydiametro == 'd' )
	{
		fin.open( "d6_32pol.txt" );
		input.open( "velocita6_32pol.txt" );
		gin.open( "sigmav6_32pol.txt" );
		write.open( "eta6_32pol.txt" );
		hin.open( "b6_32pol.txt" );
		tit.open( "errb6_32pol.txt" );
		totalemisure = 30;
		diametro = 0.0048;
	}
	else if( replydiametro == 'e' )
	{
		fin.open( "d7_32pol.txt" );
		input.open( "velocita7_32pol.txt" );
		gin.open( "sigmav7_32pol.txt" );
		write.open( "eta7_32pol.txt" );
		hin.open( "b7_32pol.txt" );
		tit.open( "errb7_32pol.txt" );
		totalemisure = 12;
		diametro = 0.0056;
	}
	else if( replydiametro == 'f' )
	{
		fin.open( "d8_32pol.txt" );
		input.open( "velocita8_32pol.txt" );
		gin.open( "sigmav8_32pol.txt" );
		write.open( "eta8_32pol.txt" );
		totalemisure = 12;
		diametro = 0.0064;
	}
	else if( replydiametro == 'g' )
	{
		fin.open( "d9_32pol.txt" );
		input.open( "velocita9_32pol.txt" );
		gin.open( "sigmav9_32pol.txt" );
		write.open( "eta9_32pol.txt" );
		totalemisure = 6;
		diametro = 0.0071;
	}
	else if( replydiametro == 'h' )
	{
		fin.open( "d9_32pol30min.txt" );
		input.open( "velocita9_32pol30min.txt" );
		gin.open( "sigmav9_32pol30min.txt" );
		write.open( "eta9_32pol30min.txt" );
		totalemisure = 5;
		diametro = 0.0071;
	}
	
	double tempi[totalemisure];
	double velocita[totalemisure];
	double eta[totalemisure];
	double sigmav[totalemisure];
	double b, sigma_b;
	
	for( int i = 0; i < totalemisure; i++ )
	{
		fin >> tempi[i];
		input >> velocita[i];
		gin >> sigmav[i];
		write >> eta[i];
	}

	hin >> b;
	tit >> sigma_b;
	
	fin.close();
	input.close();
	gin.close();
	write.close();
	hin.close();
	
	double g = 9.806;
	double erroreg = 0.001;
	
	double rho = 7870.0;
	double errorerho = 5.0;
	
	double rholiq = 1032.0;
	double errorerholiq = 1;
	
	double errorediametro = 0.000010;
	
	double erroretaquad[totalemisure];
	
	double add1[totalemisure], add2[totalemisure], add3[totalemisure], add4[totalemisure];
	
	for( int i = 0; i < totalemisure; i++ )
	{
		if( velocita[i] != 0 )
		{
			add1[i] = 4 * pow( g, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( errorediametro, 2 );
			add2[i] = pow( diametro, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( erroreg, 2 );
			add3[i] = pow( diametro, 2 ) * pow( g, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( sigmav[i], 2 ) / pow( velocita[i], 2 );
			add4[i] = pow( diametro, 2 ) * pow( g, 2 ) * ( pow( errorerho, 2 ) + pow( errorerholiq, 2 ) );
		
			erroretaquad[i] = pow( diametro, 2 ) * sqrt( add1[i] + add2[i] + add3[i] + add4[i] ) / ( 324 * velocita[i]);
		}
		else if( velocita[i] == 0 )
			erroretaquad[i] = 0;
		cout << endl << erroretaquad[i] << endl;
	}
	
	
	double etasuerretaquad[totalemisure];
	double peso[totalemisure];
	
	for( int i = 0; i < totalemisure; i++ )
	{
		if( erroretaquad[i] == 0 )
		{	
			etasuerretaquad[i] = 0;
			peso[i] = 0;
		}
		else if( erroretaquad[i] != 0 )
		{
			etasuerretaquad[i] = eta[i] / erroretaquad[i];
			peso[i] = 1 / erroretaquad[i];
		}
	}

	double mediapesataeta;
	
	double somma1 = sommatoria( etasuerretaquad, etasuerretaquad + totalemisure, totalemisure );
	double somma2 = sommatoria( peso, peso + totalemisure, totalemisure );
	
	mediapesataeta = somma1 / somma2;
	
	double erroremediapesataeta;

	erroremediapesataeta = sqrt( 1 / somma2 );
	
	cout << "\n\nMedia pesata degli eta = " << mediapesataeta << endl
		 << "Errore della media pesata = " << erroremediapesataeta << endl;
	
	
	//COMPATIBILITA'
	double etadaretta = pow( diametro, 2 ) * 9.806 * ( rho - rholiq ) / ( 18 * b );
	
	double erroretadaretta = sqrt( pow( diametro, 2 ) * 
										sqrt( 4 * pow( g, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( errorediametro, 2 ) + 
							 pow( diametro, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( erroreg, 2 ) + 
							 pow( diametro, 2 ) * pow( g, 2 ) * pow( ( rho - rholiq ), 2 ) * pow( sigma_b, 2 ) / pow( b, 2 ) +
							 pow( diametro, 2 ) * pow( g, 2 ) * ( pow( errorerho, 2 ) + pow( errorerholiq, 2 ) ) ) 
								/ ( 324 * b) );
	
	
	cout << "eta da retta: " << etadaretta << endl
		 << "errore eta da retta: " << erroretadaretta << endl
		 << "\nCompatibilita' eta" << endl << endl;
	
	double compatibilita = 0;
		
	compatibilita = fabs( mediapesataeta - etadaretta ) / sqrt( pow( erroremediapesataeta, 2 ) + pow( erroretadaretta, 2 ) );
		
	cout << compatibilita << setw(37);
		
	if( compatibilita < 1 ) cout << "OTTIMA!" << endl;
	else if( 1 <= compatibilita && compatibilita < 2 ) cout << "BUONA" << endl;
	else if( 2 <= compatibilita && compatibilita < 3 ) cout << "pessima" << endl;
	else if( 3 < compatibilita ) cout << "Non c'e' compatibilita'" << endl;
	
		
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