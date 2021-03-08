
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
	
	cout << "\n\n     ****** Esperimento Estensimetro ******" << endl << endl;

do
{
	char reply_mat, reply_numest;
	
	cout << "Quale materiale ti interessa analizzare?" << endl
		 << "\na) Acciaio" << endl
		 << "b) Tungsteno" << endl;
	
	cin >> reply_mat;

	double l0, diametro, err_lung, errdiametro, e_teorico;
	
	ifstream write;
	if( reply_mat == 'a' )
	{
		cout << "\nDi quale strumento vuoi analizzare i dati?" << endl
			 << "\na) Estensimetro n'  7 - L = 950 +- 2 mm | S = 0.330 mm +- 1%" << endl
			 << "b) Estensimetro n' 10 - L = 950 +- 2 mm | S = 0.406 mm +- 1%" << endl
			 << "c) Estensimetro n' 11 - L = 950 +- 2 mm | S = 0.432 mm +- 1%" << endl
			 << "d) Estensimetro n' 13 - L = 900 +- 2 mm | S = 0.279 mm +- 1%" << endl
			 << "e) Estensimetro n' 15 - L = 700 +- 2 mm | S = 0.279 mm +- 1%" << endl			 
			 << "f) Estensimetro n' 18 - L = 400 +- 2 mm | S = 0.279 mm +- 1%" << endl << endl;
		
		cin >> reply_numest;
		
		if( reply_numest == 'a' )
		{
			write.open("estensimetro7acc.txt");
			l0 = 0.950;
			diametro = 0.000330;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		else if( reply_numest == 'b' )
		{	
			write.open("estensimetro10acc.txt");
			l0 = 0.950;
			diametro = 0.000406;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		else if( reply_numest == 'c' )
		{
			write.open("estensimetro11acc.txt");
			l0 = 0.950;
			diametro = 0.000432;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		else if( reply_numest == 'd' )
		{	
			write.open("estensimetro13acc.txt");
			l0 = 0.900;
			diametro = 0.000279;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		else if( reply_numest == 'e' )
		{	
			write.open("estensimetro15acc.txt");
			l0 = 0.700;
			diametro = 0.000279;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		else if( reply_numest == 'f' )
		{	
			write.open("estensimetro18acc.txt");
			l0 = 0.400;
			diametro = 0.000279;
			err_lung = 0.002;
			errdiametro = diametro / 100;
		}
		
	}
	else if( reply_mat == 'b' )	 
	{	
		cout << "\n  *** Estensimetro n' 2 - Tungsteno - 1000 +- 2 mm | 0,250 +- 0,005 mm ***" << endl;
		write.open("estensimetro2tung.txt");
		l0 = 1.0;
		diametro = 0.000250;
		err_lung = 0.002;
		errdiametro = 0.000005;
	}
	
	
	const int totaledati = 18;
	double allungamenti[totaledati];
		
	for( int i = 0; i < totaledati; i++ )
		write >> allungamenti[i];
	
	write.close();
	
	double forze[9];
	int k = 9;
	cout << "\n Forze        Allungamenti        Accorciamenti" << endl << endl;
	
	for ( int i = 0; i < 9; i++ )
	{	
		forze[i] = 0.1 * 4 * i * 9.806;
		allungamenti[i] = allungamenti[i] * pow( 10, -5 );
		allungamenti[k] = allungamenti[k] * pow( 10, -5 );
		cout << setiosflags( ios::fixed | ios::showpoint ) << setprecision(1) << setw(5) << forze[i] 
			 << setprecision(6) << setw(20) << allungamenti[i] << setw(20) << setprecision(6) << allungamenti[k] << endl;
		k++;
	}
	
	
	double quad_forze[9];
	for ( int i = 0; i < 9; i++ )
		quad_forze[i] = forze[i] * forze[i];
	
	
	double sommaquadforze = sommatoria( quad_forze, quad_forze + 9, 9 );

	double sommaforze = sommatoria( forze, forze + 9, 9 );
	
	double sommallungamenti, sommallungperforza, delta, addendo_1a, addendo_2a, a, addendo_1b, addendo_2b, b;
	
	double allungperforza[9];
		
	delta = 9 * sommaquadforze - pow ( sommaforze, 2 );

	string prosric;
	
	do{
	
	string allacc;
	
	cout << "\n\nVuoi calcolare la retta interpolante dell'allungamento o dell'accorciamento?" << endl;
	cin >> allacc;
	
	double errore_y, sigma_a, sigma_b, E, sigma_E;
	
	double quad_diff_ret_y[9];
	
	if( allacc == "allungamento" )
	{
		sommallungamenti = sommatoria( allungamenti, allungamenti + 9, 9 );
		
		for( int i = 0; i < 9; i++ )
			allungperforza[i] = allungamenti[i] * forze[i];
	}
	else if( allacc == "accorciamento" )
	{
		sommallungamenti = sommatoria( allungamenti + 9, allungamenti + 18, 9 );
		
		for( int i = 0; i < 9; i++ )
			allungperforza[i] = allungamenti[( i + 9 )] * forze[i];
	}
		
	sommallungperforza = sommatoria( allungperforza, allungperforza + 9, 9 );
		
	addendo_1a = sommaquadforze * sommallungamenti;
	addendo_2a = sommaforze * sommallungperforza;
	
	a = ( 1.0 / delta ) * ( addendo_1a - addendo_2a );
	
	addendo_1b = 9 * sommallungperforza;
	addendo_2b = sommaforze * sommallungamenti;
	
	b = ( 1.0 / delta ) * ( addendo_1b - addendo_2b );
	
	int p;
	if( allacc == "allungamento" )
		p = 0;
	else if( allacc == "accorciamento" )
		p = 9;
	
	for ( int i = 0; i < 9; i++ )
		quad_diff_ret_y[i] = pow ( ( a + b * forze[i] - allungamenti[( i + p )] ), 2 );
		
	errore_y = sqrt ( sommatoria ( quad_diff_ret_y, quad_diff_ret_y + 9, 9 ) / (9 - 2) );
	
	sigma_a = errore_y * sqrt ( sommatoria ( quad_forze, quad_forze + 9, 9 ) / delta );
	
	sigma_b = errore_y * sqrt ( 9.0 / delta ); 
	
	double sezione = M_PI * pow( diametro, 2 ) / 4;
	
	E = l0 / ( sezione * b );
	
	double add_1_sE = pow( sezione, 2 ) * pow( b, 2 ) * err_lung;
	
	double sigmasezione = M_PI * diametro * errdiametro / 2;
	
	double add_2_sE = pow( b, 2 ) * pow( l0, 2 ) * pow( sigmasezione, 2 );
	
	double add_3_sE = pow( sezione, 2 ) * pow( l0, 2 ) * pow( sigma_b, 2 );

	sigma_E = sqrt( add_1_sE + add_2_sE + add_3_sE ) / ( pow( b, 2 ) * pow( sezione, 2 ) );
	
	cout << setprecision(0) << "\n\ndelta: " << delta << endl << setprecision(7) << "a: " << a << endl
		 << "b: " << b << endl << "\nSigma di a e': " << sigma_a << endl << "Sigma di b e': " << sigma_b << endl  
		 << "L'errore della y: " << errore_y << endl
		 << setprecision(10) << "Sezione: " << sezione << endl
		 << "L'errore della sezione: "<< sigmasezione << endl
		 << setprecision(0) << "\n\nE: " << E << " +- " << sigma_E << endl
		 << setprecision(7) << "K: " << b << " +- " << sigma_b << endl;
	
	ofstream fout, gout, hout;	
	if( reply_mat == 'a' )
	{	
		if( reply_numest == 'a' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_7acc.txt" );
				gout.open( "retta_allungamento_7acc.txt" );
				hout.open( "e_allungamento_7acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_7acc.txt" );
				gout.open( "retta_accorciamento_7acc.txt" );
				hout.open( "e_accorciamento_7acc.txt" );
			}
		}
		else if( reply_numest == 'b' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_10acc.txt" );
				gout.open( "retta_allungamento_10acc.txt" );
				hout.open( "e_allungamento_10acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_10acc.txt" );
				gout.open( "retta_accorciamento_10acc.txt" );
				hout.open( "e_accorciamento_10acc.txt" );
			}
		}
		else if( reply_numest == 'c' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_11acc.txt" );
				gout.open( "retta_allungamento_11acc.txt" );
				hout.open( "e_allungamento_11acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_11acc.txt" );
				gout.open( "retta_accorciamento_11acc.txt" );
				hout.open( "e_accorciamento_11acc.txt" );
			}
		}
		else if( reply_numest == 'd' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_13acc.txt" );
				gout.open( "retta_allungamento_13acc.txt" );
				hout.open( "e_allungamento_13acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_13acc.txt" );	
				gout.open( "retta_accorciamento_13acc.txt" );
				hout.open( "e_accorciamento_13acc.txt" );
			}
		}
		else if( reply_numest == 'e' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_15acc.txt" );
				gout.open( "retta_allungamento_15acc.txt" );
				hout.open( "e_allungamento_15acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_15acc.txt" );
				gout.open( "retta_accorciamento_15acc.txt" );
				hout.open( "e_accorciamento_15acc.txt" );
			}
		}
		else if( reply_numest == 'f' )
		{
			if( allacc == "allungamento" )
			{
				fout.open( "dati_allungamento_18acc.txt" );
				gout.open( "retta_allungamento_18acc.txt" );
				hout.open( "e_allungamento_18acc.txt" );
			}
			else if( allacc == "accorciamento" )
			{
				fout.open( "dati_accorciamento_18acc.txt" );	
				gout.open( "retta_accorciamento_18acc.txt" );
				hout.open( "e_accorciamento_18acc.txt" );
			}
		}
	}
	
	else if( reply_mat == 'b' )
	{
		if( allacc == "allungamento" )
		{
			fout.open( "dati_allungamento_2tung.txt" );
			gout.open( "retta_allungamento_2tung.txt" );
			hout.open( "etungall.txt" );
		}
		else if( allacc == "accorciamento" )
		{
			fout.open( "dati_accorciamento_2tung.txt" );	
			gout.open( "retta_accorciamento_2tung.txt" ); 
			hout.open( "etungacc.txt" );
		}
	}
	
	int j;
	
	if( allacc == "allungamento" ) j = 0;
	else if( allacc == "accorciamento" ) j = 9;
		
	for ( int i = 0; i < 9; i++ )
		fout << setiosflags( ios::fixed | ios::showpoint ) << setprecision(2) << forze[i] << "    " 
			 << setprecision(4) << allungamenti[( i + j )] << endl;
		
	fout.close();

	double retta_interpolante[9];
	
	for ( int i = 0; i < 9; i++ )
	{
		retta_interpolante[i] = a + b * forze[i];
		gout << setiosflags( ios::fixed | ios::showpoint ) << setprecision(3) << forze[i] << "    " << retta_interpolante[i] << endl;
	}

	gout.close();

	hout << E << "   " << sigma_E << endl;

	hout.close();
	
	cout << "\n\nSe vuoi ricalcolare allungamento e/o accorciamento inserisci 'ricomincia'" << endl << "Altrimenti inserisci una qualsiasi stringa" << endl;
	cin >> prosric;
	
	}	while( prosric == "ricomincia" );
		
		
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
