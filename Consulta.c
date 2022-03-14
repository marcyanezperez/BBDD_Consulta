#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int posicion;
	char fecha[20];
	char jugador[60];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDJuego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
		// Posicion del jugador que me indica el usuario, en la partida
		// del fecha que se indique.
		printf ("Digam el nom del jugador: \n"); 
		scanf ("%s", jugador);
		printf ("Data de la partida: \n"); 
		scanf ("%s", fecha);
			
		
		strcpy (consulta,"SELECT Participacion.Posicion from (Jugadores,Partidas,Participacion) WHERE Jugadores.username = '"); 
		strcat (consulta, jugador);
		strcat (consulta,"'AND Jugadores.IDj = Participacion.Jugador AND Partidas.fecha = '");
		strcat (consulta, fecha);
		strcat (consulta, "'AND Participacion.Partida = Partidas.IDp");
		
		// hacemos la consulta 
		err=mysql_query (conn, consulta);
				
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else
			printf ("La posicio del jugador %s es: %s\n", jugador, row[0] );
		 
		mysql_close (conn);
		exit(0);
}

