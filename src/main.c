#include <mysql.h>
#include <stdio.h>
#include <string.h>

#define INSERT_STMT	"INSERT INTO person_tb (name, age) VALUES (?, ?)"

typedef struct 
{
	char *name;
	int age;
} person_t;

typedef struct 
{
	person_t list [10];
	unsigned short amount;
} persons_t;

int main (int argc, char *argv[])
{

	persons_t persons = 
	{
		.list = 
		{
			{.name = "Albert Einstein", .age = 76},
			{.name = "Stephen Hawking", .age = 76},
			{.name = "Marie Curie",     .age = 66},
			{.name = "Richard Feynman", .age = 69},
			{.name = "Isaac Newton",    .age = 84},
			{.name = "Galileu Galilei", .age = 77},
			{.name = "Nikola Tesla",    .age = 86},
			{.name = "Max Planck",      .age = 89},
			{.name = "Charles Darwin",  .age = 73},
			{.name = "Ada Lovelace",    .age = 36}
		},
		.amount = 10
	};

	MYSQL mysql;
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[2];

	char name_buffer[1024];
	unsigned long name_size;
	int age;

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
	bind[0].buffer = (char *)name_buffer;
	bind[0].buffer_length = 1024;
	bind[0].is_null = 0;
	bind[0].length = &name_size;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = (char *)&age;
	bind[1].length = 0;
	bind[1].is_null = 0;

	mysql_stmt_bind_param (stmt, bind);

	mysql_autocommit (&mysql, 0);

	for (int i = 0; i < persons.amount; i++)
	{
		strncpy (name_buffer, persons.list[i].name, 1024);
		name_size = strlen (name_buffer);
		age = persons.list[i].age;

		if (i == 5)
		{
			mysql_rollback (&mysql);
			break;
		}


		mysql_stmt_execute (stmt);
	}

	mysql_commit (&mysql);

	mysql_stmt_close (stmt);

	mysql_close(&mysql);

	return 0;
}