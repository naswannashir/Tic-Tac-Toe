#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ukuran;
char isi [7][7];
char pemain1 = 'X', pemain2 = 'O';

typedef struct {
	int x, y;
} langkah;

void menuAwal ();
void isiPapanAwal ();
void cetakPapan ();
void inputPemain (char pemain);
void pVp (); 
void pVb (int peran);
int cek (); 
int bot (int kedalaman, int alfa, int beta, bool cariMaksimal, char pemainBot, char pemainManusia);
int penilaian (char pemainBot);
langkah cariPosisi (char pemainBot, char pemainManusia, int kedalaman);
int maks (int a, int b);
int min (int a, int b);

int main (){
	menuAwal ();
	return 0;
}

void menuAwal (){
	int masukSatu, pilihPemain, pilihUkuran;
	
	printf ("TiC tAC ToE !\n\n");
	printf ("Ketik 1 biar dapet nilai 100 !: ");
	
	scanf ("%d", &masukSatu);
	
	system("cls");
	if (masukSatu == 1){
		printf ("Maunya gimana?\n");
		printf ("1. Maen bareng temen\n2. Maen bareng bot\n\n");
		scanf("%d", &pilihPemain);
		
		system("cls");
		printf ("Pengennya berapa kali berapa?\n");
		printf ("1. 3x3\n2. 4x4\n3. 5x5\n\n");
		scanf("%d", &pilihUkuran);
		
		if (pilihUkuran == 1){
			ukuran = 3;
		}
		else if (pilihUkuran == 2){
			ukuran = 4;
		}
		else if (pilihUkuran == 3){
			ukuran = 5;
		}
		
		if (pilihPemain == 1){
			isiPapanAwal(); 
			pVp ();
		}
		else {
			int peran;
			system ("cls");
			printf ("Kalo maen bareng bot pengen jadi orang pertama atau kedua? \n");
			printf ("1. Pertama\n2. Kedua\n\n");
			scanf("%d", &peran);
			isiPapanAwal();
			pVb (peran);
		}
		
	}
}

void isiPapanAwal (){
  for (int i = 0; i < ukuran; i++){
    for (int j = 0; j < ukuran; ++j){
      isi [i][j] = ' ';
    }
  }
}

void inputPemain (char pemain){
	int x, y;
	int posisi;
	while (true){
		if(pemain == pemain1){
			printf ("\nGiliran kamu, Si-X : ");
		}
		else{
			printf ("\nGiliran kamu, Si-O : ");
		}
		scanf ("%d", &posisi); 	
		x = posisi / ukuran;
		y = posisi % ukuran;
		if (isi[x][y] == ' '){
			isi[x][y] = pemain;
			break;
		}
		system("cls");
		cetakPapan();
		if (posisi >= 0 && posisi <= (ukuran * ukuran - 1)){
			printf ("\nNet-not, udah keisi !\n");
		}
		else{
			printf ("\n Yang buat pun nggak mampu soalnya udah di luar kemampuannya\n");
		}
	}
}

void cetakPapan (){
	for (int i = 0; i < ukuran; ++i){
		for (int j = 0; j < ukuran; ++j){
			if(isi[i][j] == ' '){
				int angkaTertulis = j + ukuran * i;
				if (j + ukuran * i < 10){
					printf("  %d  ", angkaTertulis);
				}
				else {
					printf("  %d ", angkaTertulis);
				}
			} 
			else{
				printf("  %c  ", isi[i][j]);
			}
			if (j < ukuran - 1){
				printf ("|");
			}
		}
		printf("\n");
		
		if (i < ukuran - 1){
			for (int j = 0; j < ukuran; ++j){
				printf ("-----");
				if (j < ukuran - 1){
					printf ("+");
				}
			}
			printf ("\n");
		}
	}
}

void pVp (){ 
	int posisi;
	int totalLangkah = ukuran * ukuran;
	for(int i = 1; i <= totalLangkah; ++i){
		int x, y;
		system("cls");
		cetakPapan ();	
		
		if(i % 2 != 0){                             
			inputPemain(pemain1);
			if(cek (isi) == 1){
				system("cls");
				cetakPapan ();
				printf("\nPemain 1 menang\n");
				return;
			}
		}
		else {
			inputPemain(pemain2);
			if(cek (isi) == 2){
				system("cls");
				cetakPapan();
				printf("\nPemain 2 menang\n");
				return;
			}
		}
	}
	system("cls");
	cetakPapan ();
	printf("\nHasilnya seri\n");
}

void pVb (int peran){
	int tingkatKesulitan;
	system("cls");
	printf("Pengen digampangin atau disusahin bot ?\n");
	printf("1. Gampang\n2. Rada-rada\n3. Susah\n");
	if (ukuran == 3){
		printf ("4. Emang bisa?\n");
	}
	printf("\n");
	scanf ("%d", &tingkatKesulitan);
	
	int posisi;
	int totalLangkah = ukuran * ukuran;
	langkah posisiBot;
	for(int i = 1; i <= totalLangkah; ++i){
		int x, y;
		system("cls");
		cetakPapan ();
		if (peran == 1 && (i % 2 != 0)){
			inputPemain(pemain1);
			if(cek () == 1){
				system("cls");
				cetakPapan ();
				printf("\nPemain 1 menang\n");
				return;
			}
		}
		else if (peran == 1 && (i % 2 == 0)){
			if(ukuran == 3){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain2, pemain1, 1);
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain2, pemain1, 2);
				}
				else if (tingkatKesulitan == 3){
					posisiBot = cariPosisi (pemain2, pemain1, 5);
				}
				else {
					posisiBot = cariPosisi (pemain2, pemain1, 8);
				}
			}
			else if(ukuran == 4){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain2, pemain1, 1); 
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain2, pemain1, 2); 
				}
				else {
					posisiBot = cariPosisi (pemain2, pemain1, 9); 
				}
			}
			else if(ukuran == 5){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain2, pemain1, 1);
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain2, pemain1, 2); 
				}
				else {
					posisiBot = cariPosisi (pemain2, pemain1, 7);
				}
			}
			x = posisiBot.x;
			y = posisiBot.y;
			isi[x][y] = pemain2;
			if (cek() == 2){
				system("cls");
				cetakPapan();
				printf("\nPemain 2 menang\n");
				return;
			}
		}
		else if (peran == 2 && (i % 2 == 0)){
			inputPemain(pemain2);
			if(cek() == 2){
				system("cls");
				cetakPapan ();
				printf("\nPemain 2 menang\n");
				return;
			}
		}
		else if (peran == 2 && (i % 2 != 0)){
			if(ukuran == 3){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain1, pemain2, 1);
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain1, pemain2, 2);
				}
				else if (tingkatKesulitan == 3){
					posisiBot = cariPosisi (pemain1, pemain2, 5);
				}
				else {
					posisiBot = cariPosisi (pemain1, pemain2, 8);
				}
			}
			else if(ukuran == 4){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain1, pemain2, 1); 
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain1, pemain2, 2); 
				}
				else {
					posisiBot = cariPosisi (pemain1, pemain2, 9);
				}
			}
			else if(ukuran == 5){
				if (tingkatKesulitan == 1){
					posisiBot = cariPosisi (pemain1, pemain2, 1); 
				}
				else if (tingkatKesulitan == 2){
					posisiBot = cariPosisi (pemain1, pemain2, 2); 
				}
				else {
					posisiBot = cariPosisi (pemain1, pemain2, 7); 
				}
			}
			x = posisiBot.x;
			y = posisiBot.y;
			isi[x][y] = pemain1;
			if (cek() == 1){
				system("cls");
				cetakPapan();
				printf("\nPemain 1 menang\n");
				return;
			}
		}
	}
	system("cls");
	cetakPapan ();
	printf("\nHasilnya seri\n");
}

int cek(){
	int hitungSama = 0;
	
	for (int i = 0; i < ukuran; ++i){
		if(isi[i][0] == ' '){
			continue;
		}
		for (int j = 0; j < ukuran; ++j){
			if(isi[i][0] == isi[i][j]){
				hitungSama++;
			}
			if(hitungSama == ukuran && isi[i][0] == pemain1){
				return 1;
			}
			else if (hitungSama == ukuran && isi[i][0] == pemain2){
				return 2;
			}
		}
		hitungSama = 0;
	}
	
	hitungSama = 0;
	
	for (int i = 0; i < ukuran; ++i){ 
		if(isi[0][i] == ' '){
			continue;
		}
		for (int j = 0; j < ukuran; ++j){
			if(isi[0][i] == isi[j][i]){
				hitungSama++;
			}
			if(hitungSama == ukuran && isi[0][i] == pemain1){
				return 1;
			}
			else if (hitungSama == ukuran && isi[0][i] == pemain2){
				return 2;
			}
		}
		hitungSama = 0;
	}
	
	hitungSama = 0;
	
	for (int i = 0; i < ukuran; ++i){ 
		if (isi[0][0] == ' '){
			break;
		}
		if (isi[0][0] == isi[i][i]){
			hitungSama++;
		}
		if (hitungSama == ukuran && isi[0][0] == pemain1){
			return 1;
		}
		else if (hitungSama == ukuran && isi[0][0] == pemain2){
			return 2;
		}	
	}
	
	hitungSama = 0;
	
	for (int i = 0; i < ukuran; ++i){
		if(isi[0][ukuran-1] == ' '){
			break;
		}
		if(isi[0][ukuran-1] == isi[i][ukuran-i-1]){
			hitungSama++;
		}
		if (hitungSama == ukuran && isi[0][ukuran-1] == pemain1){
			return 1;
		}
		else if (hitungSama == ukuran && isi[0][ukuran-1] == pemain2){
			return 2;
		}
	}
	
	for (int i = 0; i < ukuran; ++i){
		for (int j = 0; j < ukuran; ++j){
			if (isi[i][j] == ' '){
				return 0;
			}
		}
	}
	
	return 3;
}

int bot (int kedalaman, int alfa, int beta, bool cariMaksimal, char pemainBot, char pemainManusia){
	if ((kedalaman <= 0) || (cek(isi) != 0)){
		int nilai = penilaian (pemainBot);
		return nilai;
	}
	if (cariMaksimal){
		int nilaiMaks = -1000;
		for (int i = 0; i < ukuran;  ++i){
			for (int j = 0; j < ukuran;  ++j){
				if (isi[i][j] == ' '){
					isi[i][j] = pemainBot;
					int eval = bot (kedalaman - 1, alfa, beta, false, pemainBot, pemainManusia);
					isi[i][j] = ' ';
					
					nilaiMaks = maks (nilaiMaks, eval);
					alfa = maks (alfa, nilaiMaks);
					
					if(beta <= alfa){
						break;
					}
				}
			}
			if (beta <= alfa){
				break;	
			}
		}
		return nilaiMaks;
	}
	else{
		int nilaiMin = 1000;
		for (int i = 0; i < ukuran;  ++i){
			for (int j = 0; j < ukuran;  ++j){
				if (isi[i][j] == ' '){
					isi[i][j] = pemainManusia;
					int eval = bot (kedalaman - 1, alfa, beta, true, pemainBot, pemainManusia);
					isi[i][j] = ' ';
					
					nilaiMin = min (nilaiMin, eval);
					beta = min (beta, nilaiMin); 
					
					if(beta <= alfa){
						break;
					}
				}
			}
			if (beta <= alfa){
				break;	
			}
		}
		return nilaiMin;
	}
}

langkah cariPosisi (char pemainBot, char pemainManusia, int kedalaman){
	langkah posisiOptimal = {-1, -1};
	int nilaiOptimal = -1000;
	for (int i = 0; i < ukuran; i++){
		for (int j = 0; j < ukuran; j++){
			if (isi[i][j] == ' '){
				isi[i][j] = pemainBot;
				int eval = bot(kedalaman - 1, -1000, 1000, false, pemainBot, pemainManusia);
				isi[i][j] = ' ';
				if (nilaiOptimal <= eval){
					nilaiOptimal = eval;
					posisiOptimal.x = i;
					posisiOptimal.y = j;
				}
			}
		}
	}
	return posisiOptimal;
}

int penilaian (char pemainBot){
	if(pemainBot == pemain1){
		if(cek(isi) == 1){
			return 10;
		}
		else if (cek(isi) == 2){
			return -10;	
		}
	}
	else if (pemainBot == pemain2){
		if(cek(isi) == 1){
			return -10;
		}
		else if (cek(isi) == 2){
			return 10;	
		}
	}
	return 0;
}

int maks (int a, int b){
	if (a > b){
		return a;
	}
	else {
		return b;
	}
}

int min (int a, int b){
	if (a < b){
		return a;
	}
	else {
		return b;
	}
}
