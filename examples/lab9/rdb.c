/* RPC Client application for rdb: rdb.c */

#include <stdio.h>
#include <ctype.h>
#include <rpc/rpc.h>
#include "rdb.h"

void print_record(record *pRec)
{

	if (pRec == NULL) {
		printf("No Record Found \n");
		return;
	}

        printf("First Name : %s \n", pRec->first_name);
        printf("Last Name  : %s \n", pRec->last_name);
        printf("Student Id : %s \n", pRec->student_id);
        printf("Major      : %s \n", pRec->major);
        printf("Level      : %s \n", pRec->level);
        printf("User Id    : %s \n", pRec->user_id);

}

int main(int argc, char *argv[])
{
        CLIENT  *cli;
        char    *value;
        int     key;

        if (argc != 4) {
                printf("Usage: rdb <server> <key> <field> \n");
                exit(1);
        }

        if (!(cli = clnt_create(argv[1], RDBPROG, RDBVERS, "tcp"))) {
                clnt_pcreateerror(argv[1]);
                exit(1);
        }

        value = argv[3];
        key = atoi(argv[2]);

        switch (key) {
                case LASTNAME_KEY:
                        print_record(lastname_key_1(&value, cli));
                        break;
                case STUDENTID_KEY:
                        print_record(studentid_key_1(&value, cli));
                        break;
                case USERID_KEY:
                        print_record(userid_key_1(&value, cli));
                        break;
                default:
                        printf("Error: unknown key: %d \n", key);
                        exit(1);
        }

        exit(0);
}


