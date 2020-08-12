#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "tester.h"

/*
	Cada una de estas funciones prueba unica e individualmente las funciones que corresponden
	a cada tipo de comportamiento.
	En cada funcion se actualiza el tester y nos muestra cada una de las afirmaciones que va
	haciendo y su resultado.
*/
void probar_lista(tester_t* tester);
void pruebas_iterador_externo(tester_t* tester);
void probar_pila(tester_t* tester);
void probar_cola(tester_t* tester);
void prueba_iterador_interno(tester_t* tester);

/*
	Se usa el conjunto total de funciones en la lista, sea  comportandose como pila, cola o lista.
	Tambien se actualiza correspondientemente el tester y se muestra cada afirmacion hecha y 
	su resultado
*/
void pruebas_integrales(tester_t* tester);

typedef struct test_busqueda
{
	int clave;
	void* valor;
}test_busqueda_t;


int main()
{
	tester_t* tester = crear_test();

	probar_lista(tester);
	pruebas_iterador_externo(tester);
	probar_pila(tester);
	probar_cola(tester);
	prueba_iterador_interno(tester);
	pruebas_integrales(tester);


	mostrar_resultados(tester);
	destruir_tester(tester);

	return 0;
}

bool buscar_en_lista(void* elemento, void* buscado)
{
	if(((int*)elemento) == ((int*)buscado)) return true;

	return false;
}

void lista_buscar_en_listas_con_varios_elementos_y_elemento_a_buscar_esta(tester_t* tester)
{

	int varios[7] = {1,5,6,2,5,6,11};
	int no_esta = 22;

	lista_t* lista = lista_crear();
	for(size_t i=0; i<7; i++)
	{
		lista_insertar(lista,(void*)&varios[i]);
	}

	afirmar(tester,"Busco en lista con {1,5,6,2,5,6,11} el 5 y esta ",*(int*)lista_buscar(lista,&buscar_en_lista,(void*)&varios[1]) == 5);
	afirmar(tester," -> En la misma listta busco el 22 y no esta",lista_buscar(lista,&buscar_en_lista,(void*)&no_esta) == NULL);
	afirmar(tester,"Busco el 11",*(int*)lista_buscar(lista,&buscar_en_lista,(void*)&varios[6]) == 11);
	lista_destruir(lista);	
}


void lista_insertar_en_lista_vacia(tester_t* tester)
{
		
	int a = 120;
	lista_t* lista = lista_crear();
	afirmar(tester,"insertar al final de la lista vacia", lista_insertar(lista,&a) == 0 && lista_elementos(lista) == 1 && ((int*)lista_ultimo(lista)) == (int*)lista_primero(lista));
	lista_destruir(lista);
	
}

void lista_insertar_en_lista_con_varios_elementos_lista_vacia(tester_t* tester)
{

	int varios[] = {1,5,20};
	lista_t* lista = lista_crear();

	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	afirmar(tester,"lista_insertar para varios elementos en lista vacia", lista_elementos(lista) == 3 && *(int*)lista_primero(lista) == 1 && *(int*)lista_ultimo(lista) == 20);
	
	lista_destruir(lista);
	
}

void lista_borrar_del_final_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();

	afirmar(tester,"borrar del final de una lista vacia devuelve error",lista_borrar(lista) == -1);
	
	lista_destruir(lista);
}

void lista_borrar_del_final_lista_con_un_elemento(tester_t* tester)
{
	int a=5;
	lista_t* lista = lista_crear();
	lista_insertar(lista,&a);
	
	lista_borrar(lista);
	afirmar(tester,"lista_borrar en lista con un elemento", lista_vacia(lista));
	
	lista_destruir(lista);
}

void lista_borrar_del_final_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);
	
	lista_borrar(lista);
	afirmar(tester,"lista_borrar en lista con varios elementos", lista_elementos(lista) == 2 && *(int*)lista_ultimo(lista) == 5);
	
	lista_destruir(lista);
}

void lista_insertar_en_posicion_en_lista_vacia(tester_t* tester)
{
	int a=10;
	lista_t* lista = lista_crear();
	
	lista_insertar_en_posicion(lista,&a,10);
	afirmar(tester,"lista_insertar_en_posicion se comporta como insertar al final en lista vacia",lista_elementos(lista) == 1 && ((int*)lista_ultimo(lista)) == (int*)lista_primero(lista));

	lista_destruir(lista);
}

void lista_insertar_en_posicion_en_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	int a_insertar = 15;
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_insertar_en_posicion(lista,&a_insertar,1);
	afirmar(tester,"insertar en posicion en lista con varios elementos",lista_elementos(lista) == 4 && *(int*)lista_elemento_en_posicion(lista,1) == 15);
	lista_destruir(lista);
}

void lista_insertar_en_posicion_al_final_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	int a_insertar = 15;
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_insertar_en_posicion(lista,&a_insertar,3);
	afirmar(tester,"insertar al final en lista con varios elementos",lista_elementos(lista) == 4 && *(int*)lista_ultimo(lista) == 15);
	
	lista_destruir(lista);
}

void lista_borrar_de_posicion_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();

	afirmar(tester,"borrar en posicion en una lista vacia devuelve error",lista_borrar_de_posicion(lista,0) == -1);

	lista_destruir(lista);
}

void lista_borrar_de_posicion_en_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_borrar_de_posicion(lista,1);
	afirmar(tester,"borrar en posicion en una lista con varios elementos",lista_elementos(lista) == 2 && *(int*)lista_ultimo(lista) == 7);

	lista_destruir(lista);
}

void listar_borrar_de_posicion_final_en_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_borrar_de_posicion(lista,2);
	afirmar(tester,"lista_borrar_de_posicion se comporta como lista_borrar si la posicion es la final",lista_elementos(lista) == 2 &&*(int*)lista_ultimo(lista) == 5);

	lista_destruir(lista);

}

void lista_borrar_de_posicion_primer_elemento(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_borrar_de_posicion(lista,0);
	afirmar(tester,"lista_borrar_de_posicion sobre el primer elemento",lista_elementos(lista) == 2 && *(int*)lista_primero(lista) == 5);

	lista_destruir(lista);


}

void lista_iterador_crear_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();
	lista_iterador_t* it = lista_iterador_crear(lista);
	afirmar(tester,"crear iterador en lista vacia devuelve null",it == NULL);

	lista_destruir(lista);
}

void lista_iterador_crear_en_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_iterador_t* it = lista_iterador_crear(lista);
	afirmar(tester,"crear iterador en lista con varios elementos se inicia correctamente",*(int*)lista_iterador_siguiente(it) == 1);

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void lista_iterador_tiene_siguiente_en_lista_con_1_elemento(tester_t* tester)
{
	int a=10;
	lista_t* lista = lista_crear();	
	lista_insertar(lista,&a);

	lista_iterador_t* it = lista_iterador_crear(lista);
	afirmar(tester,"lista_iterador_tiene_siguiente en lista con un elemento",lista_iterador_tiene_siguiente(it));

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void lista_iterador_siguiente_en_lista_con_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,7};
	lista_t* lista = lista_crear();
	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);

	lista_iterador_t* it = lista_iterador_crear(lista);
	lista_iterador_siguiente(it);
	afirmar(tester,"lista_iterador_siguiente en lista con varios elementos avanza correctamente",lista_iterador_tiene_siguiente(it) && *(int*)lista_iterador_siguiente(it) == 5);

	lista_destruir(lista);
	lista_iterador_destruir(it);
}	

void lista_apilar_en_lista_null(tester_t* tester)
{
	lista_t* lista = NULL;
	int a = 10;

	afirmar(tester,"intentar apilar en lista nula devuelve error",lista_apilar(lista,&a) == -1);
}


void lista_apilar_1_elemento_en_lista_vacia(tester_t* tester)
{
	int a = 10;
	lista_t* lista = lista_crear();

	lista_apilar(lista,&a);
	afirmar(tester,"apilar un elemento en lista vacia",*(int*)lista_tope(lista) == a && lista_elementos(lista) == 1);

	lista_destruir(lista);
}

void lista_apilar_varios_elementos(tester_t* tester)
{
	int varios[] = {1,5,-7};
	lista_t* lista = lista_crear();

	lista_apilar(lista,&varios[0]);
	lista_apilar(lista,&varios[1]);
	lista_apilar(lista,&varios[2]);
	
	afirmar(tester,"lista_apilar para varios elementos en lista vacia",*(int*)lista_tope(lista) == -7);

	lista_destruir(lista);
}

void lista_desapilar_en_lista_null(tester_t* tester)
{
	lista_t* lista = NULL;
	afirmar(tester,"intentar desapilar de lista vacia devuelve error",lista_desapilar(lista) == -1);
}

void lista_desapilar_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();

	afirmar(tester,"intentar desapilar en lista vacia devuelve error",lista_desapilar(lista) == -1);

	lista_destruir(lista);	
}

void lista_desapilar_en_lista_1_elemento(tester_t* tester)
{
	lista_t* lista = lista_crear();
	int a = 10;
	lista_apilar(lista,&a);

	afirmar(tester,"desapilar de pila con 1 elemento",lista_desapilar(lista) == 0 && lista_tope(lista) == NULL && lista_tope(lista) == lista_ultimo(lista));

	lista_destruir(lista);	
}

void lista_desapilar_en_lista_de_varios_elementos(tester_t* tester)
{
	int varios[] = {1,0,-7};
	lista_t* lista = lista_crear();

	lista_apilar(lista,&varios[0]);
	lista_apilar(lista,&varios[1]);
	lista_apilar(lista,&varios[2]);
	
	lista_desapilar(lista);
	afirmar(tester,"lista_apilar para varios elementos en lista vacia",*(int*)lista_tope(lista) == 0 && lista_tope(lista) == lista_ultimo(lista));

	lista_destruir(lista);
}

void lista_encolar_en_lista_null(tester_t* tester)
{
	lista_t* lista = NULL;
	int a = 10;

	afirmar(tester,"intentar encolar en lista nula devuelve error",lista_encolar(lista,&a) == -1);
}

void lista_encolar_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();
	int a = 10;

	afirmar(tester,"lista_encolar en lista vacia",lista_encolar(lista,&a) == 0 && *(int*)lista_primero(lista) == a);

	lista_destruir(lista);
}

void lista_encolar_varios_elementos(tester_t* tester)
{
	int varios[] = {1,0,-7};
	lista_t* lista = lista_crear();

	lista_encolar(lista,&varios[0]);
	lista_encolar(lista,&varios[1]);
	lista_encolar(lista,&varios[2]);
	
	afirmar(tester,"lista_encolar para varios elementos",*(int*)lista_primero(lista) == 1 && *(int*)lista_ultimo(lista) == -7);

	lista_destruir(lista);
}

void lista_desencolar_en_lista_null(tester_t* tester)
{
	lista_t* lista = NULL;
	afirmar(tester,"lista_desencolar en lista nula devuelve error",lista_desencolar(lista) == -1);
}

void lista_desencolar_en_lista_vacia(tester_t* tester)
{
	lista_t* lista = lista_crear();
	afirmar(tester,"lista_desencolar en lista vacia devuelve error",lista_desencolar(lista) == -1);
	lista_destruir(lista);
}

void lista_desencolar_en_lista_con_1_elemento(tester_t* tester)
{
	lista_t* lista = lista_crear();
	int a = 10;
	lista_encolar(lista,&a);

	afirmar(tester,"desencolar en lista con 1 elemento",lista_desencolar(lista) == 0 && lista_primero(lista) == NULL);

	lista_destruir(lista);	
}

void lista_desencolar_en_lista_de_varios_elementos(tester_t* tester)
{
	int varios[] = {1,0,-7};
	lista_t* lista = lista_crear();

	lista_encolar(lista,&varios[0]);
	lista_encolar(lista,&varios[1]);
	lista_encolar(lista,&varios[2]);

	afirmar(tester,"desencolar en lista con varios elementos",lista_desencolar(lista) == 0 && *(int*)lista_primero(lista) == 0);

	lista_destruir(lista);
}

void pruebas_iterador_externo(tester_t* tester)
{
	evento("Pruebas sobre iterador externo");
	lista_iterador_crear_en_lista_vacia(tester);
	lista_iterador_crear_en_lista_con_varios_elementos(tester);
	lista_iterador_tiene_siguiente_en_lista_con_1_elemento(tester);
	lista_iterador_siguiente_en_lista_con_varios_elementos(tester);
	printf("\n");
	printf("------------------------------------------------- \n");
	printf("\n");
}

void probar_lista(tester_t* tester)
{
	evento("Probar lista_insertar");
	lista_insertar_en_lista_vacia(tester);
	lista_insertar_en_lista_con_varios_elementos_lista_vacia(tester);
	evento("Probar lista_borrar");
	lista_borrar_del_final_en_lista_vacia(tester);
	lista_borrar_del_final_lista_con_un_elemento(tester);
	lista_borrar_del_final_lista_con_varios_elementos(tester);
	evento("Probar lista_insertar_en_posicion");
	lista_insertar_en_posicion_en_lista_vacia(tester);
	lista_insertar_en_posicion_en_lista_con_varios_elementos(tester);
	lista_insertar_en_posicion_al_final_lista_con_varios_elementos(tester);
	evento("Probar lista_borrar_de_posicion");
	lista_borrar_de_posicion_en_lista_vacia(tester);
	lista_borrar_de_posicion_en_lista_con_varios_elementos(tester);
	listar_borrar_de_posicion_final_en_lista_con_varios_elementos(tester);
	lista_borrar_de_posicion_primer_elemento(tester);
	evento("Probar lista_buscar");
	lista_buscar_en_listas_con_varios_elementos_y_elemento_a_buscar_esta(tester);

	printf("\n");
	printf("------------------------------------------------- \n");
	printf("\n");

}

void probar_pila(tester_t* tester)
{
	evento("Probar lista comportandose como pila");
	lista_apilar_en_lista_null(tester);
	lista_apilar_1_elemento_en_lista_vacia(tester);
	lista_apilar_varios_elementos(tester);
	lista_desapilar_en_lista_null(tester);
	lista_desapilar_en_lista_vacia(tester);
	lista_desapilar_en_lista_1_elemento(tester);
	lista_desapilar_en_lista_de_varios_elementos(tester);
	printf("\n");
	printf("------------------------------------------------- \n");
	printf("\n");
}

void probar_cola(tester_t* tester)
{
	evento("Probar lista comportandose como cola");
	lista_encolar_en_lista_null(tester);
	lista_encolar_en_lista_vacia(tester);
	lista_encolar_varios_elementos(tester);
	lista_desencolar_en_lista_null(tester);
	lista_desencolar_en_lista_vacia(tester);
	lista_desencolar_en_lista_con_1_elemento(tester);
	lista_desencolar_en_lista_de_varios_elementos(tester);
	printf("\n");
	printf("------------------------------------------------- \n");
	printf("\n");
}

void cambiar_signo(void* elemento, void* suma_opuestos)
{

	(*(int*)elemento) *= -1;	
	(*(int*)suma_opuestos) += (*(int*)elemento);
	
}

void prueba_iterador_interno(tester_t* tester)
{ 

	lista_t* lista = lista_crear();
	int varios[] = {-2,0,4,-7,5}; 
	int suma_opuestos = 0;
	void (*ptr_cambiar_signo)(void*, void*) = cambiar_signo;

	lista_insertar(lista,&varios[0]);
	lista_insertar(lista,&varios[1]);
	lista_insertar(lista,&varios[2]);
	lista_insertar(lista,&varios[3]);
	lista_insertar(lista,&varios[4]);

	lista_con_cada_elemento(lista,ptr_cambiar_signo,(void*)&suma_opuestos);
	evento("Iterador interno con funcion de prueba");
	afirmar(tester,"prueba sobre iterador interno",suma_opuestos == 0);

	lista_destruir(lista);
}

void pruebas_integrales(tester_t* tester)
{
	printf(" \n");
	evento("Pruebas integrales sobre la lista");
	lista_t* lista = lista_crear();
	void (*ptr_cambiar_signo)(void*, void*) = cambiar_signo;
	int* dato = NULL;
	int suma_opuestos = 0;
	int primer_numero = 0;
	int ultimo_numero = 0;
	int numero_en_posicion = 0;
	int uno = 1;
	int dos = 2;
	int tres = 3;
	int cuatro = 4;
	
	lista_insertar(lista,&uno); // lista: 1
	lista_insertar_en_posicion(lista,&dos,0); // lista: 2,1
	lista_insertar_en_posicion(lista,&cuatro,2); // lista: 2,1,4
	lista_insertar_en_posicion(lista,&tres,2); // lista: 2,1,3,4
	lista_borrar(lista); // lista: 2,1,3
	lista_borrar_de_posicion(lista,1); // Lista: 2,3
	lista_apilar(lista,&uno); // Lista: 2,3,1
	lista_apilar(lista,&cuatro); // Lista: 2,3,1,4
	lista_desencolar(lista); // Lista: 3,1,4

	//A partir de aca no toco mas la lista

	primer_numero = *(int*)lista_primero(lista);
	ultimo_numero = *(int*)lista_ultimo(lista);
	numero_en_posicion = *(int*)lista_elemento_en_posicion(lista,1);

	afirmar(tester,"primer elemento luego de varias operaciones sobre lista",primer_numero == 3);
	afirmar(tester,"ultimo elemento luego de varias operaciones sobre lista",ultimo_numero == 4);
	afirmar(tester,"elemento en posicion luego de varias operaciones sobre lista",numero_en_posicion == 1);
	evento("Creo un iterador externo para la lista actual");

	//Invierto el signo de todos los numeros de la lista con iterador externo
	lista_iterador_t* it = lista_iterador_crear(lista);

	while(lista_iterador_tiene_siguiente(it))
	{
		dato =  (int*)lista_iterador_siguiente(it);
		*dato *= -1;
	}

	/*Vuelvo a invertir los signos de todos los numeros de la lista y ademas calculo la suma
	  de los opuestos.	
	*/
	lista_con_cada_elemento(lista,ptr_cambiar_signo,&suma_opuestos);

	afirmar(tester,"iterar con el iterador externo y operar sobre lista con iterador interno",suma_opuestos == 8);

	lista_iterador_destruir(it);
	lista_destruir(lista);
}



/*


gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0


valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
*/