#define MAX_ROWS 5
#define MAX_COLS 9

void makeOptimalMove(int* pile, int n);
void modifyPyramidFromPile(int* pile, int pyramid[MAX_ROWS][MAX_COLS]);
void generatePile(int pyramid[MAX_ROWS][MAX_COLS], int* pile);
void writeOldPile(int* pile);
