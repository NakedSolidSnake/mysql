#include <mysql.h>
#include <stdio.h>

int main (int argc, char *argv[])
{

	MYSQL mysql;

	mysql_init(&mysql);

	if (mysql_real_connect(&mysql,"db","root","root","person_db",0,NULL,0) != NULL)
	{
		fprintf(stdout, "Connected to database\n");
	}
	else 
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
	}

	mysql_close(&mysql);

	return 0;
}