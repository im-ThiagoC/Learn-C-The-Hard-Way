#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

/*#define MAX_DATA 512
#define MAX_ROWS 100*/

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int MAX_DATA;
    int MAX_ROWS;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

//Foward Functions

//Memory free
void Database_close(struct Connection *conn);
//Print error
void die(struct Connection *conn, const char* message);


void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS);
void Database_load(struct Connection *conn);
struct Connection *Database_open(const char *filename, char mode);
void Database_write(struct Connection *conn);
void Database_set(struct Connection *conn, int id, const char* name, const char* email);
void Address_print(struct Address *addr);
void Database_get(struct Connection *conn, int id);
void Database_delete(struct Connection *conn, int id);
void Database_list(struct Connection *conn);
void Database_findByName(struct Connection *conn, char *name);
void Database_findByEmail(struct Connection *conn, char *email);


void Database_close(struct Connection *conn){
    if(conn){
        if(conn->file){
            fclose(conn->file);
        }
        if(conn->db){
            free(conn->db);
        }

        free(conn);
    }
}

void die(struct Connection *conn, const char* message){
    if(errno){
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    Database_close(conn);
    exit(1);
}

void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS){

    //Save MAXs in database struct
    conn->db->MAX_DATA = MAX_DATA;
    conn->db->MAX_ROWS = MAX_ROWS;

    conn->db->rows = malloc(MAX_ROWS * sizeof(struct Address));
    if(conn->db->rows == NULL){
        die(conn, "ERROR: In memory allocation for ROWS");
    }


    for(int i = 0; i < MAX_ROWS; i++){
        //make a prototype to inicialize it
        struct Address addr = {.id = i, .set = 0};

        //memory allocate for name and email
        addr.name = (char *)malloc(MAX_DATA * sizeof(char));
        addr.email = (char *)malloc(MAX_DATA * sizeof(char));
        if(addr.name == NULL || addr.email == NULL){
            die(conn, "ERROR: Memory allocation for name or email field");
        }

        conn->db->rows[i] = addr;
    }

    
}

void Database_load(struct Connection *conn){
    fread(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
    fread(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
    
    conn->db->rows = malloc(conn->db->MAX_ROWS * sizeof(struct Address));
    if(conn->db->rows == NULL){
        die(conn, "Fail to allocate in Database_load ROWS");
    }

    //More legible
    int MAX_DATA = conn->db->MAX_DATA;
    int MAX_ROWS = conn->db->MAX_ROWS;

    for(int i = 0; i < MAX_ROWS; i++){
        //Read ID and SET
        fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
        fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
        
        //Allocation for Name and Email
        conn->db->rows[i].name = malloc (MAX_DATA * sizeof(char));
        conn->db->rows[i].email = malloc (MAX_DATA * sizeof(char));

        //Read Name and Email
        fread(conn->db->rows[i].name, MAX_DATA * sizeof(char), 1, conn->file);
        fread(conn->db->rows[i].email, MAX_DATA * sizeof(char), 1, conn->file);
    }
}

struct Connection *Database_open(const char *filename, char mode){
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn){
        die(conn, "Memory error!");
    }

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db){
        die(conn, "Memory error2!");
    }

    if(mode == 'c'){
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "rb+");

        if(conn->file){
            Database_load(conn);
        }
    }

    if(!conn->file){
        die(conn, "Archive fail");
    }

    return conn;
}   

void Database_write(struct Connection *conn){
    rewind(conn->file);

    //More legible
    int MAX_DATA = conn->db->MAX_DATA;
    int MAX_ROWS = conn->db->MAX_ROWS;

    //Save the MAXs in Database
    fwrite(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
    fwrite(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);


    //Write in database all the rows.
    for(int i = 0; i < MAX_ROWS; i++){
        fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
        fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
        fwrite(conn->db->rows[i].name, MAX_DATA * sizeof(char), 1, conn->file);
        fwrite(conn->db->rows[i].email, MAX_DATA * sizeof(char), 1, conn->file);
    }

    //Retorna 0 se o buffer foi liberado com êxito
    int rc = fflush(conn->file);
    if(rc == -1){
        die(conn, "Cannot flush database.");
    }
}

void Database_set(struct Connection *conn, int id, const char* name, const char* email){
    struct Address *addr = &conn->db->rows[id];

    //more legible, default: 512
    int MAX_DATA = conn->db->MAX_DATA;

    if(addr->set){
        die(conn, "Already set, delete it first.");
    }
    addr->set = 1;

    //Copy name to addr->name
    char* res = strncpy(addr->name, name, MAX_DATA);
    addr->name[MAX_DATA-1] = '\0';
    //Check
    if(!res){
        die(conn, "Name copy failed");
    }

    //Copy email to addr->email  
    res = strncpy(addr->email, email, MAX_DATA);
    addr->email[MAX_DATA-1] = '\0';
    //Check
    if(!res){
        die(conn, "Email copy failed");
    }
}

void Address_print(struct Address *addr){
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_get(struct Connection *conn, int id){
    struct Address *addr = &conn->db->rows[id];

    if(addr->set){
        Address_print(addr);
    } else {
        die(conn, "ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id){
    struct Address *addr = &conn->db->rows[id];
    addr->id = 0, addr->set = 0;
}

void Database_list(struct Connection *conn){

    int i = 0;

    struct Database *db = conn->db;
    
    for(i = 0; i < db->MAX_ROWS; i++){
        struct Address *cur = &db->rows[i];

        if(cur->set){
            Address_print(cur);
        }
    }
}

void *lowerString(char *string){
    int i = 0;

    while(string[i]){
        string[i] = tolower((unsigned char)string[i]);
        i++;
    }
    return string;
}

void Database_findByName(struct Connection *conn, char *name){
    struct Database *db = conn->db;

    for(int i = 0; i < db->MAX_ROWS; i++){
        struct Address *cur = &db->rows[i];

        if(cur->set && (strstr(lowerString(cur->name), lowerString(name)))){
            Address_print(cur);
        }
    }
}

void Database_findByEmail(struct Connection *conn, char *email){
    struct Database *db = conn->db;

     for(int i = 0; i < db->MAX_ROWS; i++){
        struct Address *cur = &db->rows[i];

        if(cur->set && (strstr(lowerString(cur->email), lowerString(email)))){
            Address_print(cur);
        }
    }
}

int main(int argc, char* argv[]){
    int MAX_DATA = 512;
    int MAX_ROWS = 100;

    if(argc < 3){
        printf("USAGE: ex17 <dbfile> <action> [action params]");
    }

    char* filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3){
        id = atoi(argv[3]);
    }

    if(id >= MAX_ROWS){
        die(conn, "There's not that many records.");
    }

    switch (action)
    {
    case 'c':
        if(argc != 5){
            Database_create(conn, MAX_DATA, MAX_ROWS);
            Database_write(conn);
        }
        else {
            MAX_DATA = atoi(argv[3]);
            MAX_ROWS = atoi(argv[4]);
            Database_create(conn, MAX_DATA, MAX_ROWS);
            Database_write(conn);
        }
        
        break;

    case 'g':
        if(argc != 4){
            die(conn, "Need an id to get");
        }
        Database_get(conn, id);
        break;

    case 's':
        if(argc != 6){
            die(conn, "Need id, name, email to set");
        }

        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);
        break;
    
    case 'd':
        Database_delete(conn, id);
        Database_write(conn);
        break;
    
    case 'l':
        Database_list(conn);
        break;

    case 'n':
        if(argc != 4){
            die(conn, "Need only name");
        }
        Database_findByName(conn, argv[3]);
        break;
    
    case 'e':
        if(argc != 4){
            die(conn, "Need only email");
        }
        Database_findByEmail(conn, argv[3]);
        break;
    
    default:
        die(conn, "Invalid action: c=create, g=get, s=set, l=list, d=del, f=find");
    }

    Database_close(conn);

    return 0;   
}