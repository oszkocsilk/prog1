
#include <iostream>
#include <string>	//a csapat neveknek
#include <math.h>	//gyök függvény

const int NoT = 16;		//Number of Teams

const int cross[NoT][NoT] = {		//lejátszott meccsek "kódtáblája"
		{0, 3, 2, 1, 2, 3, 2, 3, 3, 2, 3, 2, 2, 2, 2, 3},
		{3, 0, 2, 1, 3, 2, 1, 3, 3, 3, 1, 2, 1, 3, 2, 1},
		{1, 1, 0, 3, 3, 1, 3, 2, 2, 2, 3, 1, 1, 1, 2, 1},
		{3, 2, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 3, 2, 1, 1},
		{3, 3, 3, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2},
		{1, 1, 3, 1, 1, 0, 1, 1, 3, 2, 2, 1, 2, 1, 2, 3},
		{1, 2, 3, 2, 1, 1, 0, 1, 1, 1, 3, 3, 1, 3, 3, 1},
		{3, 1, 1, 1, 3, 2, 1, 0, 3, 1, 3, 1, 1, 1, 3, 1},
		{3, 3, 1, 2, 3, 1, 2, 1, 0, 3, 3, 2, 1, 1, 3, 1},
		{3, 1, 1, 2, 3, 2, 3, 1, 1, 0, 3, 1, 3, 1, 3, 3},
		{2, 3, 1, 2, 1, 1, 3, 1, 1, 2, 0, 1, 1, 1, 1, 2},
		{3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 1, 0, 2, 1, 2, 3},
		{1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 3, 1, 0, 3, 1, 2},
		{2, 1, 2, 2, 1, 2, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1},
		{1, 3, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 2, 1, 2, 3, 1, 1, 1, 1, 1, 2, 1, 3, 0}
	};

const std::string teams[NoT] = {	//csapat nevek
		"BFC Siófok",
		"Budapest Honvéd",
		"Vasas",
		"Debreceni VSC",
		"Ferencváros",
		"Győri ETO",
		"Kaposvári Rákóczi",
		"Kecskeméti TE",
		"Lombard Pápa",
		"MTK Budapest",
		"Paksi FC",
		"Szolnoki MÁV FC",
		"Szombathelyi Haladás",
		"Újpest",
		"Videoton",
		"Zalaegerszegi TE"
	};

void	// pagerank kiir függvénye, módosítva a csapat nevek miatt
kiir (double tomb[], const std::string names[], int db){

	int i;

	for (i=0; i<db; ++i){
		std::cout<<names[i]<<": "<<tomb[i]<<std::endl;
	}
}

double	// pagerank tavolsag függvénye
tavolsag (double PR[], double PRv[], int n){

	int i;
	double osszeg=0;

	for (i = 0; i < n; ++i)
		osszeg += (PRv[i] - PR[i]) * (PRv[i] - PR[i]);

	return sqrt(osszeg);
}

void // eredetihez képesti módosítás: ciklus változókban 4-es helyett NoT
pagerank(double T[NoT][NoT]){

	double PR[NoT]; //ebbe megy az eredmény
	double PRv[NoT]; //ezzel szorzok

	for(int i=0;i<NoT;i++) {
		PR[i] = 0.0;
		PRv[i] = 1.0 / (NoT * 1.0);
	}

	for(;;){

		// ide jön a mátrix művelet

		for (int i=0; i<NoT; i++){
			PR[i]=0.0;
			for (int j=0; j<NoT; j++){
				PR[i] = PR[i] + T[i][j]*PRv[j];
			}
		}

			if (tavolsag(PR,PRv,NoT) < 0.0000000001)
				break;

		// ide meg az átpakolás PR-ből PRv-be

			for (int i=0;i<NoT; i++){
				PRv[i]=PR[i];
			}
	}

	kiir (PR, teams, NoT);
}


void null_matrix(int matrix[NoT][NoT]) {

	for (int i = 0; i < NoT; ++i) {
		for (int j = 0; j < NoT; ++j) {
		matrix[i][j] = 0;
		}
	}
}

void load_data(int matrix[NoT][NoT]) {

	for (int i = 0; i < NoT; ++i) {
		for (int j = 0; j < NoT; ++j) {
		matrix[i][j] = cross[i][j];
		}
	}

}

void load_points(const int matrix[NoT][NoT], int points[NoT][NoT]) {

	null_matrix(points);

	for (int i = 0; i < NoT; ++i) {
		for (int j = 0; j < NoT; ++j) {

		if (matrix[i][j] == 1) { // hazai nyert - zöld

		  ++points[i][j];

		} else if (matrix[i][j] == 2) { // döntetlen - sárga

		  ++points[i][j];
		  ++points[j][i];

		} else if (matrix[i][j] == 3) { // vendégként nyert - piros

		  ++points[j][i];

		} else if (matrix[i][j] == 0) { // nem játszott - üres

		  ;

		} else {
		  std::cout<<"I feel a disturbance in the force..";
		}
	}}
}

void col_summing(const int points[NoT][NoT],int col_sum[NoT]) {

	for (int i = 0; i < NoT; ++i) {
		int c = 0;
		for (int j = 0; j < NoT; ++j) {
			c += points[j][i];
      }
      col_sum[i] = c;
    }
}

void init_pr(const int points[NoT][NoT],const int col_sum[NoT],double alt_pr[NoT][NoT]) {


	for (int i = 0; i < NoT; ++i) {
		for (int j = 0; j < NoT; ++j) {
	        if (col_sum[j] != 0.0) {
		alt_pr[i][j]=points[i][j] * (1.0 / col_sum[j]);
        } else {
          alt_pr[i][j]=0.0;
        }

      }


  }
}

int main()
{

	int matrix[NoT][NoT];	//eredeti eredmények betöltése
	load_data(matrix);


	int points[NoT][NoT]; //pontok átkonvertálása
	load_points(matrix,points);


	int col_sum[NoT]; //oszlop összeg számolás
	col_summing(points,col_sum);


	double alt_pr[NoT][NoT]; //pontok eloszlatása - "vízvezeték szerűen"
	init_pr(points, col_sum, alt_pr);


	std::cout<<std::endl<<"Rank: "<<std::endl<<"-----"<<std::endl;

	pagerank(alt_pr); //pagerank alkalmazása

	std::cout<<std::endl;


return 0;

}

