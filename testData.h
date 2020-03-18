typedef struct {

} instruction; 

void checkProgram(FILE *ifp);
void checkProgramPeriod(FILE *ifp, FILE *ofp);
char printSymbols(char temp, FILE *ifp);
void convertAlphaReserved();
void convertDigitReserved();
void convertSymbolReserved();
void printTable(FILE *ofp);
void printLexemeList(FILE *ofp);
void printSymbolicRepresentation(FILE *ofp);
void lex(void); 