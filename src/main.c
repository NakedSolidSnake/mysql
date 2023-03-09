#include <mysql.h>
#include <stdio.h>

int main (int argc, char *argv[])
{

	MYSQL mysql;
	MYSQL_RES *result_set;
	MYSQL_ROW row;
	unsigned int num_fields;
	unsigned int i;

	char buffer [1024] = {0};
	// char *query = "insert into person_tb (name, age) values ('%s', %d);";

	// char *query = "UPDATE person_tb SET name = '%s' WHERE id = %d;";

	// char *query = "DELETE FROM person_tb WHERE id = %d;";

	char *query = "SELECT * FROM person_tb;";

	mysql_init(&mysql);

	if (mysql_real_connect(&mysql,"db","root","root","person_db",0,NULL,0) != NULL)
	{
		fprintf(stdout, "Connected to database\n");
	}
	else 
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
	}

	snprintf (buffer, 1024, query, 1);

	mysql_query(&mysql, buffer);

	result_set = mysql_store_result(&mysql);
    if (result_set)  // there are rows
    {
        num_fields = mysql_num_fields(result_set);
        while ((row = mysql_fetch_row(result_set)))
		{
			unsigned long *lengths;
			lengths = mysql_fetch_lengths(result_set);
			for(i = 0; i < num_fields; i++)
			{
				printf("[%.*s] ", (int) lengths[i],	row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}

		mysql_free_result(result_set);
    }

	mysql_close(&mysql);

	return 0;
}