/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rdb.h"
#define DATABASE "roster.dat"

bool_t
xdr_record (XDR *xdrs, record *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->first_name, MAX_STR))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->last_name, MAX_STR))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->student_id, MAX_STR))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->major, MAX_STR))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->level, MAX_STR))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->user_id, MAX_STR))
		 return FALSE;
	return TRUE;
}
