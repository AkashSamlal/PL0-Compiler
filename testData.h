#define MAX_CHARACTER_LENGTH 11
#define MAX 100

typedef enum { 
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqlsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym = 33
} token_type;

typedef struct {
    char identifier[MAX_CHARACTER_LENGTH]; //Store actual character string
    char reservedW[MAX_CHARACTER_LENGTH];//Store sym Words
    token_type tkn; //token value
}token;

token tok[MAX];

typedef struct {
    int op;
    int l;
    int m;
} instruction; 

void lex(void); 

void parser(void);