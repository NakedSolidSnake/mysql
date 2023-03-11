#include <mysql.h>
#include <stdio.h>
#include <string.h>

#define INSERT_STMT	"INSERT INTO person_tb (name, age) VALUES (?, ?)"

int main (int argc, char *argv[])
{

	MYSQL mysql;
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[2];

	char *name = "Cristiano";
	unsigned long name_size = strlen (name);
	int age = 36;

	mysql_init(&mysql);

	if (mysql_real_connect(&mysql,"db","root","root","person_db",0,NULL,0) != NULL)
	{
		fprintf(stdout, "Connected to database\n");
	}
	else 
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
	}

	stmt = mysql_stmt_init (&mysql);

	mysql_stmt_prepare (stmt, INSERT_STMT, sizeof (INSERT_STMT));

	memset (bind, 0, sizeof (bind));

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = (char *)name;
	bind[0].buffer_length = name_size;
	bind[0].is_null = 0;
	bind[0].length = &name_size;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = (char *)&age;
	bind[1].length = 0;
	bind[1].is_null = 0;

	mysql_stmt_bind_param (stmt, bind);

	mysql_stmt_execute (stmt);

	mysql_stmt_close (stmt);

	mysql_close(&mysql);

	return 0;
}