#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

int vecindario= 17;//Cambiese Segun el numero de vecindarios que quiera

float costo(float solucion[2]){
	//sqrt(numeroFloat-double); RAIZ CUADRADA

	//sin(numeroFloat-double) SENO
	float a=solucion[0];
	float b=solucion[1];
	float valorAbsolutoA,valorAbsolutoB;
	
	//Para sacar el valor absoluto
	if(solucion[0]<0)
		valorAbsolutoA=-1*solucion[0];
	else
		valorAbsolutoA=solucion[0];
	
	if(solucion[1]<0)
		valorAbsolutoB=-1*solucion[1];
	else
		valorAbsolutoB=solucion[1];

	float funcion= (418.9829*2) -(a*sin(sqrt(valorAbsolutoA))+b*sin(sqrt(valorAbsolutoB)));//Función de Schwefel
	return (funcion);
}


int main () {
	
	int contador=0;
	srand(time(NULL));//Semmila del random
	
	for(contador=1;contador<31;contador++)//Quitar si solo se quiere una corrida
	{
	//printf("Soy la corrida %d",contador);
	time_t inicio, fin;
	time(&inicio);//tiempo de inicio
	float solActual[2],solVecina[2],mejorSol[2],costoActual,costoVecina,mejorCosto,parteDecimal0,parteDecimal1,vecino1, vecino2,tInicial=1000,tFinal=0.00001,alfa=0.95,u,b,aux;	
	int i, iter=300;
	
	
	solActual[0] = (rand()%1001)-500;//GENERA UN ALEATORIO ENTERO ENTRE [500,-500]
	parteDecimal0= (rand()%10000);//ESTA PARTE Y LA DE ABAJO SE ENCARGA DE GENERAR LA PARTE DECIMAL DEL ALEATORIO
	parteDecimal0=parteDecimal0*0.0001;
	solActual[1] = (rand()%1001)-500;//GENERA UN ALEATORIO ENTERO ENTRE [500,-500]
	parteDecimal1= (rand()%10000);//ESTA PARTE Y LA DE ABAJO SE ENCARGA DE GENERAR LA PARTE DECIMAL DEL ALEATORIO
	parteDecimal1=parteDecimal1*0.0001;
	//Se suma la parte decimal y la parte entera
	solActual[0]=solActual[0]+parteDecimal0;
	solActual[1]=solActual[1]+parteDecimal1;
	//Para que los datos no se desborden de los permitidos
	if(solActual[0] >500)
		solActual[0] =500-(solActual[0]-500);
	if(solActual[0] <-500)
		solActual[0] =-500-(solActual[0]-500);
	if(solActual[1] >500)
		solActual[1] =500-(solActual[1]-500);
	if(solActual[1] <-500)
		solActual[1] =-500-(solActual[1]-500);

	//se toma el primer costo como el mejor
	costoActual=costo(solActual);
	
	mejorSol[0]=solActual[0];
	mejorSol[1]=solActual[1];
	mejorCosto=costoActual;
	//printf("\nPrimeros Valores A1:%f,   A2:%f     Costo:%f",solActual[0],solActual[1],costoActual);
	float temp=tInicial;
	//inicalización de proceso principal
	//printf("\nTi: %f,     Tf:%f",temp,tFinal);
	while(temp>tFinal)
	{	
		for(i=0;i<iter;i++)
		{
			///+++++++++++++++++++++++Genera SolVecino+++++++++++++++++++++++++++
			//SE GENERA UN FLOAT ALEATORIO ENTRE 1 Y -1 
			vecino1= (rand()%20001);
			vecino1=(vecino1*0.0001)-1;
			//GENERA VECINOS
			solVecina[0] = solActual[0]+(vecindario*(vecino1));
			if(solVecina[0] >500)
			solVecina[0] =500-(solVecina[0]-500);;
			if(solVecina[0] <-500)
				solVecina[0] =-500-(solVecina[0]-500);
			vecino2= (rand()%20001)-1;
			vecino2=(vecino2*0.0001)-1;
			solVecina[1] = solActual[1]+(vecindario*(vecino2));
			if(solVecina[1] >500)
				solVecina[1] =500-(solVecina[1]-500);
			if(solVecina[1] <-500)
				solVecina[1] =-500-(solVecina[1]-500);
			///+++++++++++++++++++++++Fin Genera SolVecino+++++++++++++++++++++++++++
			//SE PRODUCE SU COSTO
			costoVecina=costo(solVecina);
			//printf("\nV1:%f,   V2:%f     CostoV:%f",solVecina[0],solVecina[1],costoVecina);
			if(costoVecina<mejorCosto)
			{
				mejorCosto=costoVecina;
				mejorSol[0]=solVecina[0];
				mejorSol[1]=solVecina[1];
			}
			else
			{
				u=(rand()%10001);
				u=u*0.0001;
				aux=(-costoVecina+costoActual)/temp;
				b=exp(aux);
				
				if(u<b)
				{
					costoActual=costoVecina;
					solActual[0]=solVecina[0];
					solActual[1]=solVecina[1];
				}
			}
		//printf("\nMejores valores son [%f, %f] mi costo es %f\n", mejorSol[0],mejorSol[1],mejorCosto);
		}
		temp=temp*alfa;
	
	
	}
	printf("\n C:%d Mis valores son [%f, %f] mi costo es %f\n",contador, mejorSol[0],mejorSol[1],mejorCosto);
	time(&fin);//tiempo cuando se terminï¿½ de ejecutar 
    time_t elapsed = fin - inicio;//Resta entre tiempo final y tiempo inicial 
    printf("El tiempo de ejecución fue: %ld segundos.\n", elapsed);
    }
	return 0;
}
