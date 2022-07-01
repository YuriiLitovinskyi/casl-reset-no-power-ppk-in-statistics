#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Current program will reset all no-power states (table edvice), which leads to removing device from No-power in Statistics


int main(int argc, char *argv[]) {
	
    sqlite3 *db;
    char *err_msg = 0;
  
    
    // Open CASL DB
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open CASL Cloud database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    }
    
    
    // query to change status of the device from "no-power" to "power is ok"
    char deleteBrokenStatus[256] = "UPDATE device SET no_power = 0";
    
    rc = sqlite3_exec(db, deleteBrokenStatus, 0, 0, &err_msg);   
        
     
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
    
    sqlite3_close(db);  
    
    printf("\nDevices power statuses were reseted successfully! \n");
    
    system("pause");   
       
	return 0;
}
