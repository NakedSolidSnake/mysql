#include <mysql.h>
#include <stdio.h>

int main (int argc, char *argv[])
{

	MYSQL mysql;

	char buffer [1024] = {0};
	// char *query = "insert into person_tb (name, age) values ('%s', %d);";

	char *query = "UPDATE person_tb SET name = '%s' WHERE id = %d;";

	mysql_init(&mysql);

	if (mysql_real_connect(&mysql,"db","root","root","person_db",0,NULL,0) != NULL)
	{
		fprintf(stdout, "Connected to database\n");
	}
	else 
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
	}

	snprintf (buffer, 1024, query, "Samuel", 2);

	mysql_query(&mysql, buffer);

	mysql_close(&mysql);

	return 0;
}