/*
 ============================================================================
 Name        : DoublyDynamicList.c
 Author      : Natasha Kaweski
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list DList;
struct list {
	DList* prev;
	char data;
	DList* next;
};

int emptyList(DList* list);

/*
 * Starts the list
 */
DList* startList() {
	return NULL;
}

DList* insertList(DList* list, char ch) {

	DList* aux;
	aux = (DList*) malloc(sizeof(DList)); // Creates a new pointer
	aux->prev = NULL; // Sets the first value of the list
	aux->data = ch; // Sets the char value
	aux->next = list; // Links the next pointer to list

	if ( !emptyList(list) ) // And if the list is not empty, it links to aux too.
		list->prev = aux;

	return aux;
}

/*
 * Prints the list
 */
void printList(DList* list) {
	while ( !emptyList(list) ) {
		printf("List: %c\n", list->data);
		list = list->next;
	}
}

/*
 * Checks if the list is empty
 */
int emptyList(DList* list) {
	if ( (list != NULL) )
		return 0;
	return 1;
}

/*
 * Searchs a char in the list
 */
DList* searchList(DList* list, char ch) {
	while ( emptyList(list) ) {
		if ( list->data == ch )
			return list; // Must return the address memory of a register.
		list = list->next;
	}
	return list; // Can be replaced by "NULL"
}

/*
 * Remove the entire list.
 */
DList* freeList(DList* list) {
	DList* aux;

	while ( list != NULL ) {
		aux = list;
		list = list->next;
		free(aux);
	}
	return list;
}

/*
 * Removes a char of the list.
 */
DList* removeChar(DList* list, char ch) {

	if ( !emptyList(list) ) {

		DList* aux = searchList(list, ch);
		if ( !emptyList(aux) ) {

			// If the list has just one insertion, it enters in this condition
			if ( aux->prev == NULL && aux->next == NULL ) {
				list = list->next;

			// Checks if the first register pointers to NULL
			} else if ( aux->prev == NULL ) {
				list = list->next;
				list->prev = startList();

			// Checks if the last register pointers to NULL
			} else if ( aux->next == NULL ) {
				aux->prev->next = startList();

			} else {
				aux->prev->next = aux->next; // Links the right one
				aux->next->prev = aux->prev; // Links the left one
			}

			free(aux);
		}
	}
	return list;
}

int main(void) {

	DList* mainList;
	mainList = startList();

	//mainList = insertList(mainList, 'L');
	//mainList = insertList(mainList, 'I');
	//mainList = insertList(mainList, 'S');
	mainList = insertList(mainList, 'T');

	printList(mainList);

	// Tests if the entire list is correct (only if the list has more than tree inserts.
	//printf("%c\n", mainList->next->next->next->prev->prev->prev->data);

	printf("\n--------------------------------------\n");

	//mainList = removeChar(mainList, 'T');

	mainList = freeList(mainList);

	printf("List: \n ");
	printList(mainList);

	return 0;
}
