#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestion.h"
#include "gestion.hpp"
#include "Persona.hpp"
#include "Usuario.hpp"
#include "Admin.hpp"
#include <iostream>
#include <vector>
#include "string"
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <sstream>



using namespace std;

void clear_if_needed(char *str);

#define MAX_LENGHT 50
#define ADMIN_IN "admin"
#define ADMIN_PASSWORD "admin"
#define USU_IN "usuario"
#define USU_PASSWORD "usuario"
#define MAX_PELICULAS 	5

void LeerUsuarios(vector<Usuario> & vectorUsuarios)
{
  cout <<"Leyendo datos del fichero..."<< endl;
  vectorUsuarios.clear();
  vector<string> atributos;

  string nombre;
  string apellido;
  int num_socio;
  
  string line;
  string usuario;
  ifstream ifs("Usuario.txt");


  int i=0;
  while(getline(ifs, line))
  {
    usuario+= line;

          istringstream iss(usuario);
          string s;
          while ( getline( iss, s, ' ' ) ) 
          {
         
             atributos.push_back(s);
          }
          if(atributos.size()<4)
          {
     
         	 nombre= atributos[0].c_str();
         	 apellido=atributos[1].c_str();
          	 num_socio = atoi(atributos[2].c_str());
         	
          Usuario u (nombre, apellido, num_socio);
          cout<<u<<endl;

          vectorUsuarios.push_back(u);

          }
          else 
          {
            cout<< "NO COINCIDEN LOS DATOS"<< endl;
            break;
          }

          atributos.clear();
                   
    usuario ="";
   	i++;

  
  }

  ifs.close();
}
void GuardarUsuarios(vector<Usuario> & vectorUsuarios)
{
  ofstream ofs("Usuario.txt");

  for (vector< Usuario>:: iterator i= vectorUsuarios.begin(); i!= vectorUsuarios.end(); i++)
  {
    ofs << *i << '\n' ;
  }
  
  ofs.close();
}
int eliminarUsuario()
{	
	bool comprobacion=false;
	string nombre;
	string apellido;
	int num_socio;
	vector<Usuario>vectorUsuarios;
	LeerUsuarios(vectorUsuarios);

	cout<<endl<<endl;
	cout<<"Introduzca el nombre del usuario que desea eliminar"<<endl;
	cin>>nombre;

	
	for(int i=0; i<vectorUsuarios.size();i++)
	{
		string nombreUsuario=vectorUsuarios[i].getNombre();
	
		if(nombre==nombreUsuario)
		{
			comprobacion=true;
			

			cout<<"Eliminando usuario..."<<nombre<<endl;

			
			vectorUsuarios.erase(vectorUsuarios.begin()+i);

			GuardarUsuarios(vectorUsuarios);

			cout<<endl<<"ELIMINADO!!"<<endl; 

			
			
		}
		
		
	}
		
		
	if(comprobacion==false)
		{
			cout<<"El usuario introducido no se encuentra en el sistema"<<endl;
			eliminarUsuario();
		}
	
}

int main(int argc, char **argv, char **vectorUsuarios)
{
	int option;
	int total = 0;
	vector <Usuario> VectUsuarios;
  	

	Pelicula peliculas[MAX_PELICULAS];
		

	if(argc < 3 || argc > 3)
	{
		printf("Se esperan recibir 3 argumentos. Ten en cuenta que se suma el nombre del archivo. \n");
		exit(1);
	}
	if(argc == 3)
	{		
		if(strcmp(argv[1],ADMIN_IN)==0 && strcmp(argv[2],ADMIN_PASSWORD)==0)
		{
			do
			{

				option = menuAdmin();

				switch (option)
				{
					case 1: 

						anyadirPelicula();				
						break;

					case 2: 
				
						listaPelicula();
						break;

					case 3: 
						
						ventas();						
						break;

					case 4:
						
						altaUsuario();
						break;


					case 5: 

						eliminarUsuario();
						break;

					case 6:

						listaUsuario();
						break;

					

					case 7:

						datosAdmin();
						break;

					

					default:
						return -1;
						break;
			
				}
			}while(option!=0);	

		}
		else if(strcmp(argv[1],USU_IN)==0 && strcmp(argv[2],USU_PASSWORD)==0)
		{
			do
			{

				option = menuUsuario();


				switch (option)
				{
					case 1:

					if (total < MAX_PELICULAS) 
					{
						alquilarPelicula(&peliculas[total], total);
						total++;
					} else
					{
						printf("No puedes alquilar mas peliculas\n");
					}
					break;	


					case 2: 
						listaPelicula();
						break;

					case 3: 				
						verComentarios();
						break;

					case 4: 
						
						comentarPelicula();
						break;
					case 5:
					
						imprimirAlquiladas(peliculas, total);
						break;

					default:
						return -1;
						break;
			
				}
			}while(option != 0);	
		}
		else
		{
			printf("Nombre y/o contraseña incorrectos\n");
			exit(1);
		}
	}
	return 0;


	
}

int menuAdmin(void)
{
	char str[MAX_LENGHT];
	int option;
	int len;
	do
	{

		printf("BIENVENIDO A VIDEOCLUB UD!! (ADMIN)\n");
		printf("Indique su opcion: \n");
		printf("1. Anyadir pelicula\n");
		printf("2. Lista de peliculas \n");
		printf("3. Consultar ventas\n");
		printf("4. Alta usuario\n");
		printf("5. Eliminar usuario\n");
		printf("6. Lista de los usuarios\n");		
		printf("7. Datos del administrador\n");
		
		printf("(q para salir)\n");
		printf("\n");

		fgets(str, 50, stdin);
		clear_if_needed(str); 

		len = sscanf(str, "%d", &option); 
		printf("\n");

	}while ((len == 0 && str[0] != 'q') || (len > 0 && (option > 7 || option < 1)));
	
	return (str[0] == 'q')?0:option;

}

int menuUsuario(void)
{
	char str[MAX_LENGHT];
	int option;
	int len;
	do
	{
		printf("\n");
		printf("BIENVENIDO A VIDEOCLUB UD!!\n");
		printf("Indique su opcion: \n");
		
		printf("1. Alquilar pelicula\n");
		printf("2. Lista de peliculas\n");
		printf("3. Ver comentarios \n");
		printf("4. Valorar pelicula\n");
		printf("5. Listado de peliculas alquiladas\n");
		printf("(q para salir)\n");
		printf("\n");
		
		fgets(str, 50, stdin);
		clear_if_needed(str); 

		len = sscanf(str, "%d", &option); 
		printf("\n");

	}while ((len == 0 && str[0] != 'q') || (len > 0 && (option > 5 || option < 1)));
	
	return (str[0] == 'q')?0:option;

}


void clear_if_needed(char *str)
{
	if (str[strlen(str) - 1] != '\n')
	{
		int c;    
    	while ( (c = getchar()) != EOF && c != '\n');
    }

}
void liberarMemoria(Pelicula *a, int total)
{
	int i;
	for (i = 0; i < total; i++)
		free(a[i].nombre);
}








