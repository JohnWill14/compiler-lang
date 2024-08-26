#define bool int
#include <stdio.h>
#include <ctype.h>  // Para isdigit()
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <float.h> 

//functions

struct sym_function
{
    char *name; 
    char** parameter_array;
    int parameter_tam;
    char* return_type;
    struct sym_function *next; 
};

typedef struct sym_function symfunc;
symfunc *sym_func_first =  NULL;
symfunc *sym_func_last =  NULL; 


symfunc * get_fuction_list (){
    return sym_func_first;
}

symfunc * putsymfunc (char *sym_name, char** parameters, int num_par, char* return_type ){
    symfunc *ptr;

    ptr = (symfunc *) malloc (sizeof(symfunc));
    ptr->name = (char *) malloc (strlen(sym_name)+1);
    strcpy (ptr->name,sym_name);
    ptr->parameter_array =  (char **) malloc(sizeof(char *) * num_par);

    for(int i=0;i<num_par;i++){
        ptr->parameter_array[i] = (char *) malloc (strlen(parameters[i])+1);
        strcpy (ptr->parameter_array[i],parameters[i]);
    }

    ptr->parameter_tam = num_par;

    ptr->return_type = (char *) malloc (strlen(return_type)+1);
    strcpy (ptr->return_type,return_type);
   
    if(sym_func_first == NULL){
        sym_func_first = ptr;
        sym_func_last = ptr;
    } else {
        sym_func_last->next = ptr;
        sym_func_last = ptr;
    }
    
    return ptr;
}

symfunc * getsymfunc (char *sym_name){
    symfunc *ptr;
    for ( ptr = get_fuction_list (); ptr != NULL; ptr = (symfunc *)ptr->next )
        if (strcmp (ptr->name,sym_name) == 0)
            return ptr;
    return NULL;
}


void showFuncTable() {
    // Encontra o tamanho máximo das colunas para formatação
    int max_name_len = 0;
    int max_return_len = 0;
    int max_params_len = 0;

    symfunc *ptr = get_fuction_list();
    while (ptr != NULL) {
        max_name_len = (int)strlen(ptr->name) > max_name_len ? (int)strlen(ptr->name) : max_name_len;
        max_return_len = (int)strlen(ptr->return_type) > max_return_len ? (int)strlen(ptr->return_type) : max_return_len;

        int params_len = 0;
        for (int i = 0; i < ptr->parameter_tam; i++) {
            params_len += (int)strlen(ptr->parameter_array[i]);
            if (i < ptr->parameter_tam - 1) {
                params_len += 2; // Conta com o espaço e a vírgula
            }
        }
        if (ptr->parameter_tam == 0) {
            params_len = 4; // "Void"
        }
        max_params_len = params_len > max_params_len ? params_len : max_params_len;

        ptr = ptr->next;
    }

    // Imprime cabeçalho da tabela
    printf("\n\n          TABELA DE FUNCOES       \n");
    printf("-------------------------------------\n");
    printf("| %-*s | %-*s | %-*s |\n", max_name_len, "Nome", max_return_len, "Retorno", max_params_len, "Parâmetros");
    printf("-------------------------------------\n");

    // Imprime linhas da tabela
    ptr = get_fuction_list();
    while (ptr != NULL) {
        printf("| %-*s | %-*s | %-*s |\n",
               max_name_len, ptr->name,
               max_return_len, ptr->return_type,
               max_params_len, (ptr->parameter_tam > 0) ?
               ptr->parameter_array[0] : "Void");

        if (ptr->parameter_tam > 1) {
            for (int i = 1; i < ptr->parameter_tam; i++) {
                printf("| %-*s | %-*s | %-*s |\n",
                       max_name_len, "",
                       max_return_len, "",
                       max_params_len, ptr->parameter_array[i]);
            }
        }
        printf("-------------------------------------\n");

        ptr = ptr->next;
    }
}

// variaveis

struct sym_variable
{
    char *name; 
    int nivel;
    char* function; 
    bool constante;
    char* type; 
    struct sym_variable *next; 
};

typedef struct sym_variable symvar;
symvar* sym_var_first = NULL;
symvar* sym_var_last = NULL;

symvar * get_var_list (){
    return sym_var_first;
}

symvar * putsymVar (char *sym_name, int nivel, char* name_function, bool constante, char* type){
    symvar *ptr;

    ptr = (symvar *) malloc (sizeof(symvar));
    ptr->name = (char *) malloc (strlen(sym_name)+1);
    strcpy (ptr->name,sym_name);

    ptr->nivel =  nivel;
    
    ptr->function = (char *) malloc (strlen(name_function)+1);
    strcpy (ptr->function,name_function);

    ptr->constante = constante;

    ptr->type = (char *) malloc (strlen(type)+1);
    strcpy (ptr->type,type);

    if(sym_var_first == NULL){
        sym_var_first = ptr;
        sym_var_last = ptr;
    } else {
        sym_var_last->next = ptr;
        sym_var_last = ptr;
    }
    

    return ptr;
}


symvar * getsymVar (char *sym_name, int nivel, char* name_function){
    symvar *ptr;
    for ( ptr = get_var_list(); ptr != (symvar *) 0; ptr = (symvar *)ptr->next ){
        if (strcmp (ptr->function,name_function) == 0){
            if(strcmp (ptr->name,sym_name) == 0){
                if(ptr->nivel <= nivel)
                return ptr;
            }
        }
    }
        
    return NULL;
}

void showVarTable() {
    // Encontra o tamanho máximo das colunas para formatação
    int max_name_len = 0;
    int max_type_len = 0;
    int max_function_len = 0;

    symvar *ptr = get_var_list();
    while (ptr != NULL) {
        max_name_len = (int)strlen(ptr->name) > max_name_len ? (int)strlen(ptr->name) : max_name_len;
        max_type_len = (int)strlen(ptr->type) > max_type_len ? (int)strlen(ptr->type) : max_type_len;
        max_function_len = (int)strlen(ptr->function) > max_function_len ? (int)strlen(ptr->function) : max_function_len;
        ptr = ptr->next;
    }

    // Imprime cabeçalho da tabela
    printf("\n\n          TABELA DE VARIAVEIS       \n");
    printf("-----------------------------------------\n");
    printf("| %-*s | %-*s | %-*s | %-*s |\n", 
           max_name_len, "Nome", 
           max_type_len, "Tipo", 
           max_function_len, "Função", 
           8, "Constante"); // 8 para a coluna "Constante"
    printf("-----------------------------------------\n");

    // Imprime linhas da tabela
    ptr = get_var_list();
    while (ptr != NULL) {
        printf("| %-*s | %-*s | %-*s | %-*s |\n",
               max_name_len, ptr->name,
               max_type_len, ptr->type,
               max_function_len, ptr->function,
               8, ptr->constante ? "true" : "false");
        printf("-----------------------------------------\n");
        ptr = ptr->next;
    }
}




// call

struct sym_call
{ 

    int nivel;
    int line;
    char** parameter_array;
    int parameter_tam;
    char* function;
    char* targetFunction;
    struct sym_call *next; 
};

typedef struct sym_call sym_call;
sym_call* sym_call_first = NULL;
sym_call* sym_call_last = NULL;

sym_call * get_call_list (){
    return sym_call_first;
}

sym_call * putsymCall (int line, char* name_function,char* targetFunction, char** parameter_array, int parameter_tam, int nivel){
    sym_call *ptr;

    ptr = (sym_call *) malloc (sizeof(sym_call));

    ptr->line =  line;
    ptr->function = (char *) malloc (strlen(name_function)+1);
    strcpy (ptr->function,name_function);


    ptr->targetFunction = (char *) malloc (strlen(targetFunction)+1);
    strcpy (ptr->targetFunction,targetFunction);

    ptr->parameter_array =  (char **) malloc(sizeof(char *) * parameter_tam);

    for(int i=0;i<parameter_tam;i++){
        ptr->parameter_array[i] = (char *) malloc (strlen(parameter_array[i])+1);
        strcpy (ptr->parameter_array[i],parameter_array[i]);
    }
    ptr->parameter_tam=parameter_tam;
    ptr->nivel = nivel;
    if(sym_call_first == NULL){
        sym_call_first = ptr;
        sym_call_last = ptr;
    } else {
        sym_call_last->next = ptr;
        sym_call_last = ptr;
    }

    return ptr;
}

void showCallTable() {
    // Encontra o tamanho máximo das colunas para formatação
    int max_function_len = 0;
    int max_target_len = 0;
    int max_params_len = 0;

    sym_call *ptr = get_call_list();
    while (ptr != NULL) {
        max_function_len = (int)strlen(ptr->function) > max_function_len ? (int)strlen(ptr->function) : max_function_len;
        max_target_len = (int)strlen(ptr->targetFunction) > max_target_len ? (int)strlen(ptr->targetFunction) : max_target_len;

        int params_len = 0;
        for (int i = 0; i < ptr->parameter_tam; i++) {
            params_len += (int)strlen(ptr->parameter_array[i]);
            if (i < ptr->parameter_tam - 1) {
                params_len += 2; // Conta com o espaço e a vírgula
            }
        }
        if (ptr->parameter_tam == 0) {
            params_len = 4; // "Void"
        }
        max_params_len = params_len > max_params_len ? params_len : max_params_len;

        ptr = ptr->next;
    }

    // Imprime cabeçalho da tabela

    printf("\n\n          CHAMADA DE FUNCAO       \n");
    printf("-----------------------------------------\n");
    printf("| %-*s | %-*s | %-*s | %-*s |\n",
           max_function_len, "Função",
           max_target_len, "Chamada",
           max_params_len, "Parâmetros",
           6, "Linha"); // 6 para a coluna "Linha"
    printf("-----------------------------------------\n");

    // Imprime linhas da tabela
    ptr = get_call_list();
    while (ptr != NULL) {
        printf("| %-*s | %-*s | %-*s | %-*d |\n",
               max_function_len, ptr->function,
               max_target_len, ptr->targetFunction,
               max_params_len, (ptr->parameter_tam > 0) ?
               ptr->parameter_array[0] : "Void",
               6, ptr->line);

        if (ptr->parameter_tam > 1) {
            for (int i = 1; i < ptr->parameter_tam; i++) {
                printf("| %-*s | %-*s | %-*s | %-*d |\n",
                       max_function_len, "",
                       max_target_len, "",
                       max_params_len, ptr->parameter_array[i],
                       6, "");
            }
        }
        printf("-----------------------------------------\n");

        ptr = ptr->next;
    }
}
int isInteger(const char *str) {
    // Verifica se a string está vazia ou é NULL
    if (str == NULL || *str == '\0') {
        return 0;
    }

    // Se o primeiro caractere for um sinal de negativo ou positivo
    if (*str == '-' || *str == '+') {
        str++;
    }

    // Verifica se todos os caracteres restantes são dígitos
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;  // Se encontrar um caractere não numérico, retorna 0 (falso)
        }
        str++;
    }

    return 1;  // Se todos os caracteres são dígitos, retorna 1 (verdadeiro)
}

int isLong(const char *str) {
    // Verifica se a string está vazia ou é NULL
    if (str == NULL || *str == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;  // Reseta o errno antes de usar strtol()

    // Converte a string para long
    long val = strtol(str, &endptr, 10);

    // Verifica se a conversão falhou devido a estouro/subtrução
    if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) {
        return 0;
    }

    // Verifica se a string era um número válido
    if (*endptr != '\0') {
        return 0;
    }

    return 1;
}


int isFloat(const char *str) {
    // Verifica se a string está vazia ou é NULL
    if (str == NULL || *str == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;  // Reseta o errno antes de usar strtof()

    // Converte a string para float
    float val = strtof(str, &endptr);

    // Verifica se a conversão falhou devido a estouro/subtração
    if (errno == ERANGE && (val == FLT_MAX || val == FLT_MIN)) {
        return 0;
    }

    // Verifica se a string era um número válido
    if (*endptr != '\0') {
        return 0;
    }

    return 1;
}

int isDouble(const char *str) {
    // Verifica se a string está vazia ou é NULL
    if (str == NULL || *str == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;  // Reseta o errno antes de usar strtod()

    // Converte a string para double
    double val = strtod(str, &endptr);

    // Verifica se a conversão falhou devido a estouro/subtração
    if (errno == ERANGE && (val == DBL_MAX || val == DBL_MIN)) {
        return 0;
    }

    // Verifica se a string era um número válido
    if (*endptr != '\0') {
        return 0;
    }

    return 1;
}

int isBoolean( char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
        return 1;
    }

    return 0;
}


int verifyFunctionMain();
int verifyCallFunction();
int validParam(char* expected, char* code, int nivel, char* function);
int validParamVariavelFuncao(char* expected, char* code, int nivel, char* function);
int checkString(char* str, int nivel, char* name_function);
int validParamPrimitivo(char* expected, char* code, int nivel, char* function);


int valid(){
    int erros = 0;
    erros += verifyFunctionMain();
    erros += verifyCallFunction();
    return erros;
}

int verifyFunctionMain(){
    symfunc* function = getsymfunc ("main");

    if(function != NULL){
        return 0;
    }

    puts("Function main not found ");

    return 1;
}


int verifyCallFunction(){
    for ( sym_call * ptr = get_call_list (); ptr != NULL; ptr = (sym_call *)ptr->next ){
        symfunc* function = getsymfunc (ptr->function);

        if(function == NULL){
            printf("Function %s not found, line %d\n", ptr->function, ptr->line);
            return 1;
        }        

         if(ptr->parameter_tam != function->parameter_tam){
            printf("function %s with incorrect number of parameters, line %d\n", ptr->function, ptr->line);
            return 1;
         }

           int error = 0;
           if(function->parameter_tam > 0){
                for(int i=0;i<function->parameter_tam;i++){
                    error += validParam(function->parameter_array[i],ptr->parameter_array[i], ptr->nivel, ptr->targetFunction );
                }
            }

            if(error>0){
                printf("\nfunction %s with incorrect parameters, line %d\n", ptr->function, ptr->line);
                return 1;
            }
    }

    return 0;
}

char **extrair_interpolacoes(const char *string, int *n_interpolacoes) {
  *n_interpolacoes = 0;
  char *aux = strdup(string);
  char *p = aux; // Ponteiro para o início da string

  char **interpolacoes = NULL;
  while (*p != '\0') { // Enquanto não encontrar o fim da string
    if (strstr(p, "%{") != NULL) { // Verifica se contém interpolação
      char *nome = strstr(p, "%{") + 2;
      nome[strcspn(nome, "}")] = '\0'; // Remove o "}"

      // Aloca memória para o array de interpolações
      interpolacoes = realloc(interpolacoes, (*n_interpolacoes + 1) * sizeof(char *));
      interpolacoes[*n_interpolacoes] = strdup(nome); // Copia o nome para o array
      (*n_interpolacoes)++;
      p += strlen(nome) + 3; // Avança o ponteiro para o próximo caractere após a interpolação
    } else {
      p++; // Avança o ponteiro para o próximo caractere
    }
  }

  free(aux);
 
  return interpolacoes;
}


int validParam(char* expected, char* code, int nivel, char* function){
    int vf = validParamVariavelFuncao(expected, code,nivel, function);

    if(vf == 0){
        return 0;
    }
    int result = 1;
    if(vf == 3){
        result = validParamPrimitivo(expected, code,  nivel, function);
    }
    return result;
}

int validParamVariavelFuncao(char* expected, char* code, int nivel, char* function){
    symvar* s = getsymVar(code, nivel, function);
    if(s!=NULL){
        if(strcmp(s->type, expected) == 0){
            return 0;
        }
        printf("Variable %s type %s\n", code, s->type);
        return 1;
    }
    symfunc * f = getsymfunc(code);

    if(f!=NULL){
        if(strcmp(f->return_type, expected) == 0){
            return 0;
        }
        printf("Function %s with return %s\n", code, f->return_type);
        return 1;
    }

    return 3;
}

int validParamPrimitivo(char* expected, char* code, int nivel, char* function){

        if (strcmp(expected, "Int") == 0){
            int check = isInteger(code);
            if(check == 0){
                printf("%s is not Int", code);
                return 1;
            }
        } else if (strcmp(expected, "Long") == 0){
            int check = isLong(code);
            if(check == 0){
                printf("%s is not Long", code);
                return 1;
            }
        } else if (strcmp(expected, "String") == 0){
            int check = checkString(code, nivel,  function);
            if(check == 1){
                printf("%s is not a valid string ", code);
                return 1;
            }
        } else if (strcmp(expected, "Float") == 0){
            int check = isFloat(code);
            if(check == 0){
                printf("%s is not Float", code);
                return 1;
            }
        } else if (strcmp(expected,"Double") == 0){
            int check = isDouble(code);
            if(check == 0){
                printf("%s is not Double", code);
                return 1;
            }
        } else if (strcmp(expected, "Boolean") == 0){
            int check = isBoolean(code);
                if(check == 0){
                    printf("%s is not Boolean", code);
                    return 1;
                }
        } else {
            printf("%s\n", code);
            return 1;
        }

    return 0;
}


int checkString(char* str, int nivel, char* name_function){
    int length = strlen(str);
    if(length <2){
        return 1;
    }

    if(str[0] != '\"'||str[length-1]!='\"'){
        return 1;
    }

    int n_interpolacoes = 0;
    char **interpolacoes = extrair_interpolacoes(str, &n_interpolacoes);

    int errors = 0;
    for(int i=0;i<n_interpolacoes;i++){
            symvar* s = getsymVar(interpolacoes[i], nivel, name_function);
            if (s == NULL){ 
                if(errors>0){
                    puts("");
                }
                errors++;
                printf( "error in interpolation variable %s not is defined.\n", interpolacoes[i]);
                return 1;
            }
    }

    return errors >0 ? 1:0;
}



int check_var_is_Constant (char *sym_name, int nivel, char* name_function){
    symvar *ptr = getsymVar(sym_name, nivel,  name_function);
    if(ptr == NULL || ptr->constante){
        printf("Variable %s is a constant\n", ptr->name);
        return 1;
    }
    return 0;
}

