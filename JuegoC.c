#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) 
{
	
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) 
	{
		printf ("Error al crear la conexi\ufff3n: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexin
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	char consulta [100];
	strcpy (consulta, "SELECT (Jugador.Nombre) FROM (Jugador,Participacion) WHERE Participacion.Posicion = 1 AND Participacion.Id_J = Jugador.Id ORDER BY Jugador.Nombre DESC");
	err=mysql_query (conn, consulta);
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
	{
		int suma = 0;
		char ganador[20];
		char persona_anterior[20];
		strcpy(persona_anterior, row[0]);
		int jug = 0;
		int i = 0;
		while (row!=NULL) 
		{
			char persona[30];
			strcpy(persona, row[0]);
			
			if (strcmp(persona, persona_anterior)==0)
				i++;
			else {
				i=1;
				strcpy(persona_anterior, persona);
			}
			if (i>suma) {
				strcpy(ganador, persona);
				suma=i;
			}
			row = mysql_fetch_row (resultado);
		}
		printf ("El que mas veces ha ganado es %s y ha ganado %d veces.", ganador, suma);
	}	
	mysql_close (conn);
	exit(0);
}
