#ifndef _GESTION_H_
#define _GESTION_H_

typedef struct
{
	char *nombre;
	char genero;
	double precio;
	char valoracion;


}Pelicula;

void ventas();

void anyadirPelicula();

void imprimirAlquiladas();

void alquilarPelicula();

void comentarPelicula();

void verComentarios();

void listaPelicula();

int menuAdmin(void);

int menuUsuario(void);

#endif