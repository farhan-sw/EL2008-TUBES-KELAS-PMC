

// Define the structure for the patient node
typedef struct Patient {
    char name[50];
    int age;
    char gender;
    char lastControlDate[20];
    struct History *history;
    struct Patient *next;
} Patient;

// Define the structure for the history node
typedef struct History {
    char disease[50];
    char medicine[50];
    char nextControlDate[20];
    float medicinePrice;
    float visitCost;
    struct History *next;
} History;