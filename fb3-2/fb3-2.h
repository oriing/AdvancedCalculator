/*Declarations for a calculator fb3-2.h*/

extern int yylineno;
void yyerror(char *s, ...);

//add
struct symbol { /* a variable name */
	 char *name;
	 double value;
	 struct ast *func; /* stmt for the function */
	 struct symlist *syms; /* list of dummy args */
};

/*add*/
#define NHASH 9997
extern struct symbol symtab[NHASH];

/*add*/
struct symbol *lookup(char*);

/*add*/
struct symlist {
	struct symbol *sym;
	struct symlist *next;
};

/*add*/
enum bifs { /* built-in functions */
 B_sqrt = 1,
 B_exp,
 B_log,
 B_print
};

struct ast{
	int nodetype;
	struct ast *l;
	struct ast *r;
};

/*add*/
struct fncall { /* built-in function */
	int nodetype; /* type F */
	struct ast *l;
	enum bifs functype;
};

/*add*/
struct ufncall { /* user function */
	int nodetype; /* type C */
	struct ast *l; /* list of arguments */
	struct symbol *s;
};

/*add*/
struct flow {
	int nodetype; /* type I or W */
	struct ast *cond; /* condition */
	struct ast *tl; /* then branch or do list */
	struct ast *el; /* optional else branch */
};

struct numval{
	int nodetype;
	double number;
};

/*add*/
struct symref {
	int nodetype; /* type N */
	struct symbol *s;
};

/*add*/
struct symasgn {
	int nodetype; /* type = */
	struct symbol *s;
	struct ast *v; /* value */
};

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);

/*add*/
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
struct symlist* newsymlist(struct symbol* sym, struct symlist* next);

/*add*/
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

double eval(struct ast *);

void treefree(struct ast *);
