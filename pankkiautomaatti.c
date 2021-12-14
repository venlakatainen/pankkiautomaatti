#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void kirjautuminen();
void menu();
void otto();
void saldo();
void tapahtumat();
void puheajanLataus();

float tilinSaldo=1100;

int main(void){

    kirjautuminen();
    menu();
    
    return 0;
}

/*Funktio kirjautuminen kysyy käyttäjältä tilinumeron ja avaa tilinumeron nimisen tiedoston.
 Sen jälkeen, kayttaja syottaa tunnnusluvun ja luetaan tiedostosta oikea tunnusluku ja tarkistetaan onko 
 kayttajan syottama tunnusluku oikein. 
*/
void kirjautuminen(){

    char tilinumero[10], tunnusluku[5], rivi[5];
    int n;
    FILE *tiedosto1;
    
    while (1){
        printf("Syota tilinumero> ");
        scanf("%s", tilinumero);
        strcat(tilinumero, ".acc");

        if ((tiedosto1 = fopen(tilinumero, "r")) == NULL ){
            printf("Tiedostoa ei loydy.\n");
        }
        else {
            tiedosto1 = fopen(tilinumero, "r");
            fgets(rivi, 5, tiedosto1);
            break;
        }

    }

    while(1){
        printf("Syota tunnusluku > ");
        scanf("%s", tunnusluku);

        if (strcmp(tunnusluku, rivi) == 0){
            printf("Oikea tunnusluku.\n");
            break;
        }

        else {
            printf("Vaara tunnusluku.\n");
        }
    }
    fclose(tiedosto1);
}

/*
Funktio menu kysyy käyttäjältä toiminnon, jonka käyttäjä haluaa tehdä.
Valittavia vaihtoehtoja rahan nosto, saldon tarkastelu, tapahtumat, puheajan lataus 
ja pankkiautomaatilta poistuminen.
*/
void menu(){
    int toiminto;

    printf("Syota toiminto:\notto - 1\nsaldo - 2\ntapahtumat - 3\npuheajan lataus - 4\nLopeta - 5\n");
    scanf("%d", &toiminto);

    if (toiminto == 1){
        otto();
    }

    else if (toiminto == 2){
        saldo();
    }

    else if (toiminto == 3){
        tapahtumat();
    }

    else if (toiminto == 4){
        puheajanLataus();
    }

    else if (toiminto == 5){
        printf("Kiitos kaynnista ja tervetuloa uudelleen!");
        exit(0);
    }
    else{
        printf("Valitsemasi toiminto ei ole kaytettavissa.");
    }
    
}
/* otto kysyy kayttajalta nostettavan summan. Summan on oltava 20, 40 tai enemmän 10 euron välein ja enintään
tilin saldon suuruinen. Funktio laskee montako 20 euron ja 50 euron seteliä käyttäjälle annetaan ja tulostaa 
seteleiden määrän, sekä tilin saldon käyttäjälle, jonka jälkeen ohjelma suljetaan.
Jos summa on vahemman kuin 20€ tai summa, jota ei voida nostaa tai enemman kuin tililla on rahaa, 
nosto ei ole mahdollinen ja ohjelma suljetaan.
*/
void otto(){
    int seteleidenMaara1=0, seteleidenMaara2=0, nostettavaSumma=0, n=0, m=0, s;

    printf("Alkuun - 1\n");
    printf("Syota nostettava summa >");
    scanf("%d", &nostettavaSumma);

    if (((nostettavaSumma==20) || (nostettavaSumma >= 40)) && (nostettavaSumma%10==0) && (nostettavaSumma <= tilinSaldo)){

        if (((nostettavaSumma == 20) || (nostettavaSumma == 40) || (nostettavaSumma == 60) || (nostettavaSumma == 80)) && (nostettavaSumma < tilinSaldo)){
            seteleidenMaara1 = nostettavaSumma / 20;
            tilinSaldo -= (float) nostettavaSumma;
            printf("Tilille jaa %.2lf euroa\n", tilinSaldo);
            printf("Annettu %d kpl 20 euron seteleita.\n", seteleidenMaara1);
            printf("Kiitos kaynnista ja tervetuloa uudelleen!\n");
            exit(0);
        }
        else if ((nostettavaSumma >= 50) && (nostettavaSumma <= 1000) && (nostettavaSumma <= tilinSaldo)){
            
            if ((nostettavaSumma % 50) == 0){
                seteleidenMaara2 = nostettavaSumma / 50;
                tilinSaldo -= nostettavaSumma;
                printf("Tilille jaa %.2lf euroa\n", tilinSaldo);
                printf("Annettu %d kpl 50 euron seteleita.\n", seteleidenMaara2);
                printf("Kiitos kaynnista ja tervetuloa uudelleen!\n");
                exit(0);
            }
            else {
                tilinSaldo -= nostettavaSumma;
                n = nostettavaSumma % 50;
                m = n % 20;
                if (m == 0){
                    seteleidenMaara2 = (nostettavaSumma - n) / 50;
                    seteleidenMaara1 =  (nostettavaSumma - (nostettavaSumma - n)) / 20;
                    printf("Tilille jaa %.2lf euroa\n", tilinSaldo);
                    printf("Annettu %d kpl 50 euron seteleita ja %d kpl 20 euron seteleita.\n", seteleidenMaara2, seteleidenMaara1);
                    printf("Kiitos kaynnista ja tervetuloa uudelleen!\n");
                    exit(0);
                }
                else {
                    for (s=nostettavaSumma; s>0; s-=20){
                        if ((s % 50) == 0){
                            seteleidenMaara2 = s / 50;
                            seteleidenMaara1 = (nostettavaSumma - s) / 20;
                            printf("Tilille jaa %.2lf euroa\n", tilinSaldo);
                            printf("Annettu %d kpl 50 euron seteleita ja %d kpl 20 euron seteleita.\n", seteleidenMaara2, seteleidenMaara1);
                            printf("Kiitos kaynnista ja tervetuloa uudelleen!\n");
                            exit(0);
                        }
                    }
                }
            }
        }
    }
    else if (nostettavaSumma == 1){
        menu();
    }
    else {
        printf("Vaaranlainen syote.\n");
        printf("Kiitos kaynnista ja tervetuloa uudelleen!\n");
        exit(0);
    }
    
}

//saldo tulostaa kayttajalle tilin saldon.
void saldo(){

    printf("Tilin saldo %.2lf+\n", tilinSaldo);

}

// tapahtumat tulostaa kayttajalle tilin viimeaikaiset tapahtumat.
void tapahtumat(){

    printf("Tililla ei ole viimeaikaisia tapahtumia.");
   
}

/* puheajanLataus kysyy kayttajalta operaattorin ja ladattavan summan. 
Tulostaa lopuksi tiedot latauksesta ja vahentaa tilin saldosta ladatun summan.
*/
void puheajanLataus(){

    int operaattori=0, 
        ladattavaSumma=0;

    printf("Palaa alkuun - 3\n");
    printf("Valitse operaattori 1 tai 2 >");
    scanf("%d", &operaattori);

    if ((operaattori == 1) || (operaattori == 2)){
        printf("Syota ladattava summa >");
        scanf("%d", &ladattavaSumma);
        
        if (ladattavaSumma < tilinSaldo){
            printf("Ladattu operaattorille %d, %d euroa.\n", operaattori, ladattavaSumma);
            tilinSaldo -= (float) ladattavaSumma;
        }
        else{
            printf("Vaaranlainen syote. Kiitos kaynnista ja tervetuloa uudelleen.");
            exit(1);
        }
    }
    else if (operaattori == 3){
        menu();
    }
    else {
        printf("Vaaranlainen syote. Kiitos kaynnista ja tervetuloa uudelleen.");
        exit(1);
    }
    
}