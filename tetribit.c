#include <stdio.h>
#include <math.h>

void citire_piesei(int a[10])
//citirea piesei intr-un vector cu miscarile ei

{

	int i = 0;

	for ( ; i < 9; i++)

	{

		scanf("%d", &a[i]);

	}

}

int ZeroNumber(__uint64_t harta)
//vreifica bitii nesetati

{

	  int i=64 , N1 = 0;


	__uint64_t mask;

	for( ; i > 0 ; i--)

	{

		mask = 1LLU << (i-1) ;

		if ( harta & mask ) { N1 ++;}


	}

	return 64 - N1;

	

}

__uint16_t shiftarileft(__uint16_t p ,__uint16_t loc , int nrs)
//shiftari la stanga
//p-piesa ; loc - linia pe care face mutari; nrs - nr de mutari
{

	int masck1 = 1 << 7 , masck2 = 1 << 15;

	if( (nrs == 0) || (loc  & p <<1 ) || (p & masck1) || (p & masck2) )
	
	{return p;}

	else{ return shiftarileft( p << 1, loc, nrs-1);}

}

__uint16_t shiftariright(__uint16_t p , __uint16_t loc , int nrs)
//shiftari dreapta
//p-piesa ; loc - linia pe care face mutari; nrs - nr de mutari
{

	int masck1 = 1 , masck2 = 1 << 8;

	if( (nrs == 0) || (loc  & p >>1 ) || (p & masck1) || (p & masck2) )
	 
	 {return p;}

	else{ return shiftariright( p >> 1, loc, nrs-1);}

}

void printH(__uint64_t harta)
//afisarea hartii

{


    int i = 63;

	__uint64_t mask;

	for( ; i >= 0 ; i--)

	{

		mask =  1LLU << i;

		if ( harta & mask ) { printf("%s" , " #");}

		else {printf("%s" , " .");}

		if( i % 8 == 0) {printf("\n");}

		
	}

	printf("\n");

}

void GameOver(int zn, int cL)
//calculeaza scorul
//zn- zero number; cl-linii complete
{

	float scor;

 	scor =  pow(zn   , 0.5)  + pow( 1.25 , cL)  ;

	printf("\n%s\n" , "GAME OVER!");

	printf("%s%.2f\n" ,"Score:",scor);

}

 __uint64_t dell_line_completa(__uint64_t harta )
//n1 ,n2 -cele 2 parti ale hartii fara linie completa
//t_h -harta dupa eliminare
//v-linia pentru verificare
{

	__uint64_t n1,n2 ,t_h = harta ;

	__uint8_t v , masck = ( (1 << 8) - 1);

	int i = 8 ;

	for ( ; i >= 0; i--)

	{

		v =( harta >> (8 * (i - 1) ));

		if( v == masck )

		{

			n1 = (t_h << (8 * ( 9 - i) ) );

			n2 = (t_h >> (8 * i) ) ;

			n1 >>= (8 * (9 - i ) );

			n2 <<= (8 * (i - 1) );
			
			if(i == 1){ t_h = n2 ;}
			
			else{t_h = n1 | n2;}

			harta = t_h;
		

		}

	}

	return t_h;
	
}

int nr_linii_complete(__uint64_t harta)
//in timpul verificarii
{ 

	__uint8_t v , masck = ( (1 << 8) - 1);

	int i = 0, n = 0  ;

	for ( ; i < 8; i++)

	{

		v =( harta >> (8 * i ));

		if( v == masck )
		
		{
		n++;
		}
	}
	
	return n;
}

void rezolvare(__uint64_t harta , int n )
//pm -piesa mutata in dreapta sau stanga
//a -piesa mutata pe harta=0;
//p_h -piesa pentru afisare la miscari

{
	int i, j, z, mutari;
	
	__uint16_t loc_pt_mutare , pm;
	
	int delline = 0;
	
	__uint64_t  a, p_h;
	
	int p[10];
	
	printH(harta);
	
	for(i = 0; i < n; i++)
	{
		citire_piesei(p);
	
		pm = p[0];
	
		for(j = 8; j > 0; j--)
		{
		
			mutari = p[9-j];
		
			loc_pt_mutare = (harta >> (8 *(j -1) ));
						
			if( loc_pt_mutare & pm)
			{	
				/*daca nu incape pe primul rand
				sau nu se afiseaza total ca are 16 biti*/
				
				if( ( j == 8) || 
				(( j == 7) && (pm > 255)) )
				
				{
					i = n;
					
					printH(p_h);
				}
				
				break;
			}			
			if( mutari > 0)
			{
			    pm = shiftariright(pm , loc_pt_mutare, mutari);
			}		
			if( mutari < 0)
			{
			     pm = shiftarileft(pm , loc_pt_mutare, 0 - mutari);
			}
			
			a = pm;
		
			a <<= (8 *(j - 1 ) );
		
			p_h = harta | a ;
		
			printH(p_h);
 		
		}
		if(nr_linii_complete(p_h))
		{
			delline += nr_linii_complete(p_h);
		
			harta = dell_line_completa(p_h);
		
			printH(harta);
		}
		else {harta = p_h;}
	
	}
	
	z = ZeroNumber(harta);
	
	GameOver(z, delline);

}

int main(void)

{

	__uint64_t harta;
	
	int M;

	scanf("%lu", &harta);

	scanf("%d", &M);

	rezolvare(harta , M);

	return  0;

}
