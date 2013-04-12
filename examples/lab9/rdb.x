/* RPCL protocol definition file: rdb.x */

%#define DATABASE "roster.dat"

const MAX_STR = 256;

struct record {
        string first_name<MAX_STR>;
        string last_name<MAX_STR>;
        string student_id<MAX_STR>;
        string major<MAX_STR>;
        string level<MAX_STR>;
        string user_id<MAX_STR>;
};

program RDBPROG {
        version RDBVERS {
                record LASTNAME_KEY(string) = 1;
                record STUDENTID_KEY(string) = 2;
                record USERID_KEY(string) = 3;
        } = 1;
}= 0x20000001;

