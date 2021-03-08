
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

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
	else if( replydiametro == 'f' )
	{	
		write.open( "d8_32pol.txt" );
		totalemisure = 12;
		deltas = 0.25;
		mispercamp = 2;
		diametro = 0.0064;
	} 
	else if( replydiametro == 'g' )
	{	
		write.open( "d9_32pol.txt" );
		totalemisure = 6;
		deltas = 0.5;
		mispercamp = 1;
		diametro = 0.0071;
	} 
	else if( replydiametro == 'h' )
	{	
		write.open( "d9_32pol30min.txt" );
		totalemisure = 5;
		deltas = 0.5;
		mispercamp = 1;
		diametro = 0.0071;
	} 
	
	double tempi[totalemisure];
	
	for( int i = 0; i < totalemisure; i++ )
		write >> tempi[i];
	
	write.close;
	
	
	double velocita[totalemisure];
	int j = 0;
	
	for( int i = 0; i < totalemisure; i++ )
	{
		if( tempi[i] == 0 )
			velocita[i] = 0;
		else if( tempi[i] != 0 )
			velocita[i] = ( j + 1 ) * deltas / tempi[i];
			
		j++;
		if( j >= mispercamp )
			j = 0;
	}
	
	cout << "\nNPR = Non e' stato possibile registrare questo dato" << endl << endl;
	
	int campioni = totalemisure / mispercamp;
	
	cout << "     Campione 1" << "           ";
	for( int l = 1; l < campioni; l++)
	{
		if( l < campioni - 1)
			cout << " Campione " << l+1 << "           ";
		else if( l == campioni - 1 ) 
			cout << " Campione " << l+1 << endl << endl << "    ";
	}
	
	// SERVE SOLO PER STAMPARE
	int k = 0;																						// k contatore definisce l'orizzontale
																									// i definisce la verticale 
	for( int i = 0; i < mispercamp; i++ )
	{
		for( int j = 0; j < campioni; j++ )
		{
			if( tempi[( i + k * mispercamp )] == 0 )										
			{
				if( 0 <= ( i + 1 + k * mispercamp ) && ( i + 1 + k * mispercamp ) <= 9 )			// serve per intabulare maniacalmente
					cout << "v" << i + 1 + k * mispercamp << ")     NPR           ";				// i dati
				else
					cout << "\bv" << i + 1 + k * mispercamp << ")     NPR           ";
			}	
			
			else if( tempi[( i + k * mispercamp )] != 0 )
			{
				if( 0 <= ( i + 1 + k * mispercamp ) && ( i + 1 + k * mispercamp ) <= 9 )
					cout << setiosflags( ios::fixed | ios:: showpoint ) << setprecision(5)
						 << "v" << i + 1 + k * mispercamp << ") = " << velocita[( i + k * mispercamp )] << "         ";
				else
					cout << "\bv" << i + 1 + k * mispercamp << ") = " << velocita[( i + k * mispercamp )] << "         ";
			}

			k++;
			if( k == campioni )
			{	
				cout << endl << "    ";
				k = 0;
			}
		}
	}
	
	double errorediametro = 0.000010; 
	
	double gravita = 9.806;
	double erroregravita = 0.001;
	
	double rhosf = 7870; 	// kg/m^3
	double errorerhosf = 5; // kg/m^3
	
	double rholiq = 1032;	// kg/m^3
	double errorerholiq = 1;// kg/m^3
	
	double diffrho = rhosf - rholiq;

	double eta[totalemisure];
	
	for( int i = 0; i < totalemisure; i++ )
	{
		if( velocita[i] == 0 )
			eta[i] = 0;
		else if( velocita[i] != 0 )
			eta[i] = pow( diametro, 2 ) * gravita * diffrho / ( 18 * velocita[i] ) ;
	}
	
	cout << endl << endl << "  ";
	
	for( int i = 0; i < mispercamp; i++ )
	{
		for( int j = 0; j < campioni; j++ )
		{
			if( tempi[( i + k * mispercamp )] == 0 )
			{
				if( 0 <= ( i + 1 + k * mispercamp ) && ( i + 1 + k * mispercamp ) <= 9 )
					cout << "eta" << i + 1 + k * mispercamp << ")     NPR         ";
				else
					cout << "\beta" << i + 1 + k * mispercamp << ")     NPR         ";
			}	
			
			else if( tempi[( i + k * mispercamp )] != 0 )
			{
				if( 0 <= ( i + 1 + k * mispercamp ) && ( i + 1 + k * mispercamp ) <= 9 )
					cout << setiosflags( ios::fixed | ios:: showpoint ) << setprecision(5)
						 << "eta" << i + 1 + k * mispercamp << ") = " << eta[( i + k * mispercamp )] << "       ";
				else
					cout << "\beta" << i + 1 + k * mispercamp << ") = " << eta[( i + k * mispercamp )] << "       ";
			}

			k++;
			if( k == campioni )
			{	
				cout << endl << "  ";
				k = 0;
			}
		}
	}	
	
	double erroredeltas = 0.002 / sqrt(6);
	double sigmav[totalemisure];
	double addendosv1[totalemisure]; 
	double addendosv2[totalemisure];
	double erroretempi = 0.0001;
	
	
	for( int i = 0; i < totalemisure; i++ )
	{
		if( tempi[i] == 0 )
			{
				addendosv1[i] = 0;
				addendosv2[i] = 0;
			}
		else if( tempi[i] != 0 )
		{
			addendosv1[i] = pow( erroredeltas, 2 ) / ( tempi[i] * tempi[i] );
			addendosv2[i] = pow( deltas, 2 ) * pow( erroretempi, 2 ) / ( tempi[i] * tempi[i] * tempi[i] * tempi[i] );
		}
	}
	
	for( int i = 0; i < totalemisure; i++ )
		sigmav[i] = sqrt( addendosv1[i] + addendosv2[i] );
	
		
	ofstream output, read, fout;
	if( replydiametro == 'a' )
	{
		read.open( "velocita1_5mm.txt" );
		fout.open( "sigmav1_5mm.txt" );
		output.open( "eta1_5mm.txt" );
	}
	else if( replydiametro == 'b' )
	{	
		read.open( "velocita3_32pol.txt" );
		fout.open( "sigmav3_32pol.txt" );
		output.open( "eta3_32pol.txt" );
	}	
	else if( replydiametro == 'c' )
	{	
		read.open( "velocita5_32pol.txt" );
		fout.open( "sigmav5_32pol.txt" );
		output.open( "eta5_32pol.txt" );
	}
	else if( replydiametro == 'd' )
	{	
		read.open( "velocita6_32pol.txt" );
		fout.open( "sigmav6_32pol.txt" );
		output.open( "eta6_32pol.txt" );
	}	
	else if( replydiametro == 'e' )
	{	
		read.open( "velocita7_32pol.txt" );
		fout.open( "sigmav7_32pol.txt" );
		output.open( "eta7_32pol.txt" );
	}
	else if( replydiametro == 'f' )
	{	
		read.open( "velocita8_32pol.txt" );
		fout.open( "sigmav8_32pol.txt" );
		output.open( "eta8_32pol.txt" );
	}
	else if( replydiametro == 'g' )
	{	
		read.open( "velocita9_32pol.txt" );
		fout.open( "sigmav9_32pol.txt" );
		output.open( "eta9_32pol.txt" );
	}
	else if( replydiametro == 'h' )
	{
		read.open( "velocita9_32pol30min.txt" );
		fout.open( "sigmav9_32pol30min.txt" );
		output.open( "eta9_32pol30min.txt" );
	}
	
	
	for( int i = 0; i < totalemisure; i++ )
	{
		read << velocita[i] << endl;
		fout << sigmav[i] << endl;
		output << eta[i] << endl;
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