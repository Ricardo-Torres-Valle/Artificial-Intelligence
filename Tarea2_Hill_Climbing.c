#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
int sinCambio=50000000;//Este numero tan grande es para que el programa tarde un promedio de 30seg en ejecución 
int vecindario= 5;//Cambiese Segun el numero de vecindarios que quiera

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
	for(contador=1;contador<31;contador++)//Quitar si solo se quiere una corrida
	{
	//printf("Soy la corrida %d",contador);
	time_t inicio, fin;
	time(&inicio);//tiempo de inicio
	float solActual[2],solVecina[2],costoActual,costoVecina,parteDecimal0,parteDecimal1,vecino1, vecino2;	
	int i;
	srand(time(NULL));//Semmila del random
	
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
		solActual[0] =500;
	if(solActual[0] <-500)
		solActual[0] =-500;
	if(solActual[1] >500)
		solActual[1] =500;
	if(solActual[1] <-500)
		solActual[1] =-500;

	//se toma el primer costo como el mejor
	float mejorCosto=costo(solActual);
	//se inicalizan las variables de siclos y la de sin mejora
	int sinMejora=0, ciclos=0;
	//inicalización de proceso principal
	
	while(sinMejora<sinCambio&&ciclos<100000000)
	{
		ciclos++;	
		//SE GENERA UN FLOAT ALEATORIO ENTRE 1 Y -1 
		vecino1= (rand()%20001);
		vecino1=(vecino1*0.0001)-1;
		//GENERA VECINOS
		solVecina[0] = solActual[0]+(vecindario*(vecino1));
		if(solVecina[0] >500)
			solVecina[0] =500;
		if(solVecina[0] <-500)
			solVecina[0] =-500;
		vecino2= (rand()%20001)-1;
		vecino2=(vecino2*0.0001)-1;
		solVecina[1] = solActual[1]+(vecindario*(vecino2));
		if(solVecina[1] >500)
			solVecina[1] =500;
		if(solVecina[1] <-500)
			solVecina[1] =-500;
		//SE PRODUCE SU COSTO
		costoVecina=costo(solVecina);
		
		
		//PRUBAS PARA VER EL CORRECTO FUNCIONAMIENTO
		//printf("\nsoy la solucion actual [%f,%f] con costo: %f       [V1:%f    V2:%f]        soy la solución vecina[%f,%f] con costo: %f",solActual[0],solActual[1],mejorCosto,vecindario*vecino1,vecindario*vecino2,solVecina[0],solVecina[1],costoVecina);
		
		//si el costo del vecino es mas bajo o es igual entra al if
		if(costoVecina<=mejorCosto)
		{	
			//Dado que ya tenemos el costo del vecino y el actual y si el del vecino no es menor va a ser igual
			//cambiamos los valores de la solución actual a los del vecino
			solActual[0]=solVecina[0];
			solActual[1]=solVecina[1];
			//Si el costo del vecino es menor al de mejorCosto se toma el costo del vecino y se pone en 0 sinMejora
			if(costoVecina<mejorCosto){
				mejorCosto=costoVecina;
				sinMejora=0;
			}
			//Si no, quiere decir que no mejoró
			else
				sinMejora++;
		}
		else
			//En caso que el costo no es menor aumenta el numero sinMejora
			sinMejora++;
			if(sinMejora==sinCambio)
			{
				//printf("\n\nMe sali por no mejorar\n");
			}
	}
	//nos da los valores y el costo que genero
	printf("\n C:%d Mis valores son [%f, %f] mi costo es %f\n",contador, solActual[0],solActual[1],mejorCosto);

    
    time(&fin);//tiempo cuando se terminï¿½ de ejecutar 
    time_t elapsed = fin - inicio;//Resta entre tiempo final y tiempo inicial 
    printf("El tiempo de ejecución fue: %ld segundos.\n", elapsed);
	}
    return 0;
}
