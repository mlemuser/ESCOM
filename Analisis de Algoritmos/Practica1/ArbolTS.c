#define ABB_VACIO NULL
#define TRUE 1
#define FALSE 0

typedef struct _nodo {
   int dato;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

void Insertar(Arbol *a, int dat) {
   pNodo padre = NULL; /* (1) */
   pNodo actual = *a;  /* (2) */

   while(!Vacio(actual) && dat != actual->dato) {  /* (3) */
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;  /* (3-a) */
      else if(dat > actual->dato) actual = actual->derecho; /* (3-b) */
   }

   if(!Vacio(actual)) return;  /* (4) */
   if(Vacio(padre)) {  /* (5) */
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
   }
   else if(dat < padre->dato) { /* (6) */
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
   }
   else if(dat > padre->dato) { /* (7) */
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
  }
}

int Vacio(Arbol r) {
   return r==NULL;
}

void InOrden(Arbol a, void (*func)(int*)) {
   if(a->izquierdo) InOrden(a->izquierdo, func); /* Subárbol izquierdo */
   func(&(a->dato)); /* Aplicar la función al dato del nodo actual */
   if(a->derecho) InOrden(a->derecho, func);     /* Subárbol derecho */
}


