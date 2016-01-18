#ifndef _database_h_
#define _database_h_

#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

class Database{

    private:
        sqlite3 *database;
    public:
        Database(char *filename);
        bool open(char *filename);
        vector<vector<string> > query (char *query);
        void close();
};
#endif // _database_h_
