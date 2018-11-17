#include <stdio.h>
#include <mpfr.h>
#include <gmp.h>

int main(int argc, char* argv[])
{
    // NOTE:
    // Al seguito di alcune prove dichiarando le variabili della
    // sequenza e il rapporto come unsigned long long e double, 
    // i valori verso n=100 andavano in overflow
    // per cui sto usando le librerie gmp e mpfr 
    // per eseguire calcoli con cifre estremamente grandi.
    // Si può compilare il programma dopo aver installato
    // le 2 lib sul raspberry. 

    mpfr_rnd_t rnd = mpfr_get_default_rounding_mode(); // il valore default per l'approssimazione
    
    mpfr_t ratio;                       // dichiarazione della variabile floating point
    mpz_t n1, n2, n3;                   // dicharazione delle variabili per la sequenza 
    
    mpfr_init2(ratio, 256);             // inizializzazione di ratio a 128 bit
    mpz_init(n1);                       //
    mpz_init(n2);                       // inizializza n1, n2, n3
    mpz_init(n3);                       //
    
    mpz_set_ui(n2, 1);                  // set n1 e n2 a 1 (primi 2 termini della sequenza)
    mpz_set_ui(n1, 1);            
    
    // Fase Principale
    for(int i = 1;i<=100;i++) {
        
        if (i>1) {
            // applicazione di fibonacci
            mpz_add(n3, n2, n1);
        }
        
        gmp_printf("a(%d) = %Zd\n" ,i ,n3);     // stampare gli elementi della sequenza
        fflush(stdout);

        mpfr_set_z(ratio, n3, rnd);             // settare ratio per
        mpfr_div_z(ratio, ratio, n2, rnd);      // fare il rapporto tra a(n) a(n-1)       
        
        mpfr_printf ("ratio = %.32Rf\n", ratio); // stampare il rapporto
        fflush(stdout); 
        
        mpz_set(n1, n2);    // preparare le variabili
        mpz_set(n2, n3);    // per il ciclo successivo
    }

    // Liberare la memoria occupata
    mpfr_clear(ratio);
    mpfr_free_cache();
    mpz_clear(n3);
    mpz_clear(n2);
    mpz_clear(n1);

    // terminare il main con codice di uscita 0 (SUCCESS)
    return 0;
}