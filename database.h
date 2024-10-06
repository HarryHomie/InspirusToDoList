#ifndef DATABASE_H
#define DATABASE_H

#include "structs.h"
#include "sqlite/sqlite3.h"
#include <iostream>

using namespace std;

sqlite3 *database;
const char* dbName = "ToDoList.db";
bool isDbOpen = false;



int openDatabase()
{
    if (isDbOpen)
    {
        return 0;
    }

    int rc;

    rc = sqlite3_open(dbName, &database);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(database) << std::endl;
        return rc;
    }
    else
    {
        isDbOpen = true;
    }

    // sqlite3_stmt* statement;

    const char* query = 
    "CREATE TABLE IF NOT EXISTS todo ("
    "id INTEGER PRIMARY KEY,"
    "task TEXT,"
    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
    ");";


    rc = sqlite3_exec(database, query, nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(database) << std::endl;
        sqlite3_close(database);
        return rc;
    }

    return 0;

}



int saveData(toDoList list)
{
    openDatabase();

    const char* query = "INSERT INTO todo (task) VALUES (?);";

    sqlite3_stmt* statement;

    int rc;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
        return rc;
    }


    for (int i = 0; i < list.length; i++)
    {
        // Bind the values
        sqlite3_bind_text(statement, 1, list.list[i].c_str(), -1, SQLITE_STATIC);

        // Execute the statement
        rc = sqlite3_step(statement) ;
        if (rc!= SQLITE_DONE) {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(database) << std::endl;
            return rc;
        }
    }

    // Clean up
    sqlite3_finalize(statement);

    return 0;

}


toDoList getData()
{
    toDoList list(10);
}

#endif