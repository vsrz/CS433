#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

#include "rdb.h"

FILE *fp = NULL;
record *pRec = NULL;

int read_record()
{

        char buf[MAX_STR];

        if (!pRec) {
                pRec = (record *)malloc(sizeof(record));
                pRec->first_name = (char *)malloc(MAX_STR);
                pRec->last_name = (char *)malloc(MAX_STR);
                pRec->student_id = (char *)malloc(MAX_STR);
                pRec->major = (char *)malloc(MAX_STR);
                pRec->level = (char *)malloc(MAX_STR);
                pRec->user_id = (char *)malloc(MAX_STR);
        }

        if (!fgets(buf, MAX_STR-1,fp))
                return(0);
        if (sscanf(buf, "%s %s %s %s %s %s",pRec->last_name, pRec->first_name,
                   pRec->student_id, pRec->major,
                   pRec->level, pRec->user_id) != 6)
                return(0);

        return(1);
}
 
record *lastname_key_1(char **name, CLIENT *cli)
{


   if (!(fp = fopen(DATABASE, "r")))
        return((record *)NULL);


   while (read_record())
   {
	printf("pRec->last_name %s name %s \n", pRec->last_name, *name);
        if (!strcmp(pRec->last_name, *name)) break;
   }

        if (feof(fp)) {
                fclose(fp);
                return((record *)NULL);
        }

        fclose(fp);

        return((record *) pRec);
}
 
record *studentid_key_1(char **name, CLIENT *cli)
{

        if (!(fp = fopen(DATABASE, "r")))
                return((record *)NULL);

        while (read_record())
                if (!strcmp(pRec->student_id, *name))
                        break;
        if (feof(fp)) {
                fclose(fp);
                return((record *)NULL);
        }

        fclose(fp);

        return((record *) NULL);
}

record *userid_key_1(char **name, CLIENT *cli)
{

        if (!(fp = fopen(DATABASE,"r")))
                return((record *)NULL);

        while (read_record())
            if (!strcmp(pRec->user_id, *name))
                 break;

        if (feof(fp)) {
                fclose(fp);
                return((record *)NULL);
        }

        fclose(fp);

        return((record *)NULL);
}

