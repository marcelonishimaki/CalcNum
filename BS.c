/* Marcelo Yuichi Matsuda Nishimaki 8127079 */

/*bibliotecas utilizadas */
#include <stdio.h>
#include <math.h>

/*definir Pi */
#define M_PI 3.14159265358979323846

/* calculo de d1 */
double x1(double St,double K, double r, double sigma, double T, double t) {
    double d;
    d = (log(St/K)+(r+(pow(sigma,2))/2)*(T-t)) / (sigma*sqrt(T-t));
return d;
}

/*calculo de d2*/
double x2(double D1, double sigma,double T, double t){
    double d;
    d = D1 - sigma*sqrt(T-t);
return d;
}

/*chute inicial da volatilidade*/
double sigma1(double T, double C, double S){
    double sig;
    sig = sqrt(((2*M_PI)/T)*(C/S));
return sig;
}

/*calculo de N pelo metodo de Simpson*/
double Nx(double x, int n){
    double d,z,N;
    int i;
    d = fabs(x)/n;

    for (i = 0; i < n; i++){
        z = i * d;
        N = exp(-(pow(z,2)/2)) * N;
        N = d / 2 * (2 * N + 1 + exp (- (pow(x,2) /2)));
    }
	if (x >= 0) {
		N = 1/2 + N / sqrt(2 * M_PI);
	}else
		N = 1/2 - N / sqrt(2 * M_PI);
return N;
}
int main(){
    double St, K, T, t, sigma, N1, N2, d1, d2, r, C, vol, f1, f2;
    int n,i;
    /*entrada de dados */
    printf("Preco do ativo:  \n");
    scanf("%lf", &St);
    printf("Preco de exercicio: \n");
    scanf("%lf", &K);
    printf("Data vencimento: \n");
    scanf("%lf", &T);
    printf("Data inicial: \n");
    scanf("%lf", &t);
    printf("Volatilidade no periodo: \n");
    scanf("%lf", &sigma);
    printf("Taxa livre de risco: \n");
    scanf("%lf", &r);    
    printf("Numero de iteracoes: \n");
    scanf("%d", &n);
    printf("Preco da opcao: \n");
    scanf("%lf", &C);    

    /*chamada das funcoes para calculos de d1,d2,N(d1) e N(d2)*/
    d1 = x1(St,K,r,sigma,T,t);
    d2 = x2(d1,sigma,T,t);
    N1 = Nx(d1, n);
    N2 = Nx(d2, n);
    printf("N(d1) vale %lf\n", N1);
    printf("N(d2) vale %lf\n", N2);

    /* calculo da volatilidade implicita */
    vol = sigma1(T,C,St);
    f1 = St*N1-K*exp(-r*((T-t)/365))*N2;
    f2 = St*sqrt((T-t)/365)*exp(-pow(d1,2)/2)/sqrt(2*M_PI);

    for(i=0;i<n;i++){
        vol = vol - f1/f2;
    }
    printf("Volatilidade implicita vale %lf", vol);

return 0;
}