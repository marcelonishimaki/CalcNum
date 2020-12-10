/* Marcelo Yuichi Matsuda Nishimaki 8127079 */

/*bibliotecas utilizadas */
#include <stdio.h>
#include <math.h>

/*definir Pi */
#define M_PI 3.14159265358979323846


/* calculo de d1 */
double x1(double St,double K, double r, double sigma, double T) {
    double d;
    d = (log(St/K)+(r+(pow(sigma,2))/2)*T) / (sigma*sqrt(T));
return d;
}

/*calculo de d2*/
double x2(double D1, double sigma,double T){
    double d;
    d = D1 - sigma*sqrt(T);
return d;
}

/*chute inicial da volatilidade*/
double sigma1(double T, double C, double S){
    double sig;
    sig = sqrt((2*M_PI)/T)*(C/S);
return sig;
}

/*calculo de N pelo metodo de Simpson*/
double Nx(double x, int n){
    double d,z,y,N;
    int i;
    y = 0;
    d = fabs(x)/n;
    z = 0;
    for (i = 1; i < n; i++){
        y = 0;
        z = i * d;
        y = exp(-(pow(z,2)/2)) * y;
    }
     y = d / 2 * (2 * y + 1 + exp (- (pow(x,2) /2)));
    if (x >= 0) {
        N = 1/2 + y / sqrt(2 * M_PI);
    }else
        N = 1/2 - y / sqrt(2 * M_PI);
return N;
}

int main(){
    double St, K, T, sigma, N1, N2, d1, d2, r, C, vol, f1;
    int n,i;
    /*entrada de dados */
    printf("Preco do ativo:  \n");
    scanf("%lf", &St);
    printf("Preco de exercicio: \n");
    scanf("%lf", &K);
    printf("Data vencimento (em dias): \n");
    scanf("%lf", &T);
    printf("Volatilidade no periodo: \n");
    scanf("%lf", &sigma);
    printf("Taxa livre de risco: \n");
    scanf("%lf", &r);    
    printf("Numero de iteracoes: \n");
    scanf("%d", &n);
    printf("Preco da opcao: \n");
    scanf("%lf", &C);
    
    /*conversao dos tempo */
    T = T/365;

    /*chamada das funcoes para calculos de d1,d2,N(d1) e N(d2)*/
    d1 = x1(St,K,r,sigma,T);
    d2 = x2(d1,sigma,T);
    N1 = Nx(d1, n);
    N2 = Nx(d2, n);
    printf("N(d1) vale %lf\n", N1);
    printf("N(d2) vale %lf\n", N2);

    /* calculo da volatilidade */
    vol = sigma1(T,C,St);
    f1 = St*N1-K*exp(-r*T)*N2;
    printf("Ct vale %lf\n", f1);
    //f2 = St*sqrt(T)*exp(-pow(d1,2)/2)/sqrt(2*M_PI);

    for(i=0;i<n;i++){
        vol = vol - (St*Nx(x1(St,K,r,vol,T), n)-K*exp(-r*T*(Nx(x2(x1(St,K,r,vol,T),vol,T),n))))/St*sqrt(T)*exp(-pow(x1(St,K,r,sigma,T),2)/2)/sqrt(2*M_PI);
    }
    printf("Volatilidade implicita vale %lf\n", vol);

return 0;
}

