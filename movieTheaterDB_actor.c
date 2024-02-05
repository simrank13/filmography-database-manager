/**
 * 251292956 - skullar5
*/
// include header file for actors of movie theater database 
#include "movieTheaterDB_actor.h"
// include standard input output, library, string manipulation, character functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// readActor function reads string with specified length n
int readActor(char str[], int n) {
    // declaration and initialization of variable character and i representing characters in string an index
    int character, i = 0;

    // read characters until non-whitespace character is found
    while (isspace(character = getchar()));

    // read characters until new line or end of file then
    while (character != '\n' && character != EOF) {
        // if index is with specified max length n then store character in string str
        // and increment index by 1 each time
        if (i < n) {
            str[i++] = character;
        }
        // get next character 
        character = getchar();
    }
    //and if reached new line or end of file then set character as \0 (null) 
    str[i] = '\0';
    // return index i
    return i;
}
// findActor function finds actor by its associated code in linked list
struct Actor *find_actor(struct Actor *actorHead, int code) {
    // declaration of pointer p to Actor structure
    struct Actor *p;

    // iterate through linked list until specified code isnt found or reached end of linked list
    for(p = actorHead; p != NULL && code != p->actorCode; p = p->next);

     // return pointer to actor found (or null if no actor found)
    return p;

}

// insertActor function inserts new actor into linked list
void insertActor(Actor **actorHead) {
    // declaration of pointers representing current node, previous node, and new node pointing to Actor structure
    struct Actor *cur, *prev, *new_node;

    // allocate memory for new node of Actor structure
    new_node = malloc(sizeof(struct Actor));

    // if malloc failed meaning new node is allocated memory of null then print message that malloc failed otherwise if malloc succeeded
    if(new_node == NULL) {
        printf("Database is full (malloc failed); can't add more actors.\n");
        return;
    }
    // prompt user for actor code and store it as code in Actor structure
    printf("        Enter actor code: ");
    scanf("%d", &new_node->actorCode);

    // if prompted actor code isnt positive integer then print to screen that it is invalid actor code 
    if(new_node->actorCode < 0) {
        printf("Please try again, invalid actor code (needs to positive unique integer).\n");
        free(new_node);
        return;
    }

    // otherwise if it is positive integer then
    // iterate through linked list to get right position in which to insert the new node depending actor code 
    for (cur = *actorHead, prev = NULL; cur != NULL && new_node->actorCode > cur->actorCode; prev = cur, cur = cur->next);

    // if actor with same code is already in link list then print to screen that actor already exists in database
    // then free allocated memory for new node
    if (cur != NULL && new_node->actorCode == cur->actorCode) {
        printf("Actor already exists.\n");
        free(new_node);
        return;
    }  

    // prompt user for actor name and read actor name string with length 50
    printf("        Enter actor name: ");
    readActor(new_node->actorName, 50);

    // prompt user for actor age and store as age in Actor structure
    printf("        Enter actor age: ");
    scanf("%d", &new_node->age);

    // if prompted actor age is less than 0 or greater than 120 then print to screen invalid actor rating then free allocated memory for new node
    if(new_node->age < 0 || new_node->age > 120) {
        printf("Please try again, invalid actor age. Needs to be in range (0-120)\n");
        free(new_node);
        return;
    }
    
    // prompt user for imdb profile and read actor imdb profile string with length 50
    printf("        Enter IMDB profile page: ");
    readActor(new_node->imdbProfile, 50);

    // set new nodes next node as cur node connecting new node and cur node
    new_node->next = cur;

    // if the prev node is null (new node is inserted at start of linked list) then set head of linked list to new node 
    if (prev == NULL) {
        *actorHead = new_node;
    // otherwise set the prev nodes next node as new node connecting prev node and new node
    } else {
        prev->next = new_node;
    }
}
// searchActor function search for actor by its associated code
void searchActor(Actor **actorHead) {
    // declaration of code variable which will store prompted actor code
    int code;
    // declaration of pointer p to Actor structure
    struct Actor *p;

    // prompt user for actor code and store it in code variable
    printf("        Enter actor code: ");
    scanf("%d", &code);

    // call find_actor function to find actor with specified code and set it as p
    p = find_actor(*actorHead, code);
    // if actor with specified actor is found then 
    if(p != NULL) {
        // print header with column title indicating column of code, name, age and imdb profile with formatting for alignment and spacing
        // actor code left aligned in 12 character wide column, actor name left aligned in 52 character wide column, 
        // age left aligned in 7 character wide column, and then imdb profile 
        printf("%-12s%-52s%-7s%-s\n", "Actor Code", "Actor Name", "Age", "IMDB Profile Page");
        
        // initialize array which represents copy of actor name that will be striped to limit to 51 characters (including null character)
        char strippedName[51];
        // strncpy copies at max 50 characters from original actor name to striped array
        strncpy(strippedName, p->actorName, 50);
        // set the last element in the striped array to null character to end string
        strippedName[50] = '\0';
        
        // initialize array which represents copy of imdb profile that will be striped to limit to 51 characters (including null character)
        char strippedProfile[51];
        // strncpy copies at max 50 characters from original imdb profile to striped array
        strncpy(strippedProfile, p->imdbProfile, 50);
        // set the last element in the striped array to null character to end string
        strippedProfile[50] = '\0';
        
        // print actor code, name, age and imdb profile columns with formatting for alignment and spacing
        printf("%-12d%-52s%-7d%s\n", p->actorCode, strippedName, p->age, strippedProfile);
    } 
    //otherwise print to screen movie isnt found in database
    else {
        printf("Actor not found.\n");
    }
}

// clearCharActor function clears characters from buffer (if exceeded maximum striped length)
void clearCharActor() {
    // declaration of character variable representing characters read from  buffer 
    int character;

    // read characters from buffer until meets new line or end of file
    while ((character = getchar()) != '\n' && character != EOF) ;
}

// updateActor function updates actor's details
void updateActor(Actor **actorHead) {
    // declaration of oldCode and newCode variable which will store the old and new actor code
    int oldCode, newCode;
    // declaration of pointer p and existing to Actor structure 
    struct Actor *p;

    // prompt user to enter actor code 
    printf("        Enter actor code: ");
    
    // read actor code from user and store in old code variable and if code is invalid input then
    if (scanf("%d", &oldCode) != 1) {
        // clear characters from buffer and return from function
        clearCharActor();
        return;
    }
    // clear any remaining characters from buffer
    clearCharActor();

    // call find_actor function to find actor with old code and set it as p
    p = find_actor(*actorHead, oldCode);
    // if actor with specified code is found then
    if (p != NULL) {
        // prompt user to enter actor code 
        printf("        Enter actor code: ");
        // read actor code from user and store in new code variable and if code is invalid input then
        if (scanf("%d", &newCode) != 1) {
            // clear characters from buffer and return from function
            clearCharActor();
            return;
        }
        // clear any remaining characters from buffer
        clearCharActor();

        // if new code isnt same as old code then 
        if (newCode != oldCode) {
            // call find_actor function to find actor with new code
            // if actor with new code exists in linked list then print to screen that code already exists
            if (find_actor(*actorHead, newCode) != NULL) {
                printf("Duplicate error: enter different code that isn't %d.\n", oldCode);
            } else {
                // Update the code only if the new code is not already present
                p->actorCode = newCode;
                // prompt user for actor name and read actor name string with length 50
                printf("        Enter actor name: ");
                readActor(p->actorName, 50);

                // prompt user for actor age and
                // read updated actor age from user and if input invalid then clear characters from buffer and return from function
                printf("        Enter actor age: ");
                if (scanf("%d", &p->age) != 1) {
                    clearCharActor();
                    return;
                }
                // clear any remaining characters from buffer
                clearCharActor();

                // prompt user for imdb profile and read imdb profile string with length 50
                printf("        Enter IMDB profile page: ");
                readActor(p->imdbProfile, 50);
            }
        } 
    // otherwise if actor is not found in database (index is -1) then print to screen that actor is not in database
    } else {
        printf("Actor not found.\n");
    }
}


// printActor function prints list of actor and its details
void printActor(Actor **actorHead) {
    // declaration of pointer p to Actor structure
    struct Actor *p;
    
    // print header with column title indicating column of code, name, age and imdb profile with formatting for alignment and spacing
    // actor code left aligned in 12 character wide column, actor name left aligned in 52 character wide column, 
    // age left aligned in 7 character wide column, and then imdb profile 
    printf("%-12s%-52s%-7s%-s\n", "Actor Code", "Actor Name", "Age", "IMDB Profile Page");

    // iterate through the linked list of actors
    for(p = *actorHead; p != NULL; p = p->next) {
        // initialize array which represents copy of actor name that will be striped to limit to 51 characters (including null character)
        char strippedName[51];
        // strncpy copies at max 50 characters from original actor name to striped array
        strncpy(strippedName, p->actorName, 50);
        // set the last element in the striped array to null character to end string
        strippedName[50] = '\0';
        
        // initialize array which represents copy of actor genre that will be striped to limit to 51 characters (including null character)
        char strippedProfile[51];
        // strncpy copies at max 50 characters from original actor genre to striped array
        strncpy(strippedProfile, p->imdbProfile, 50);
        // set the last element in the striped array to null character to end string
        strippedProfile[50] = '\0';
        
        // print actor code, name, age and imdb profile columns with formatting for alignment and spacing
        printf("%-12d%-52s%-7d%s\n", p->actorCode, strippedName, p->age, strippedProfile);
    }
    //print new line to screen
    printf("\n");
}

// eraseActor function erase actors from database
void eraseActor(Actor **actorHead) {
    // declaration of code variable which will store prompted actor code
    int code;
    // declaration of pointer cur and prev to Actor structure
    struct Actor *cur, *prev;

    // prompt user for actor code and store it in code variable
    printf("        Enter actor code: ");
    scanf("%d", &code);

    // iterate through the linked list and find actor with specified code
    for(cur = *actorHead, prev = NULL; cur != NULL && cur->actorCode != code; prev = cur, cur = cur-> next);
    
    // if actor with specified code is found then
    if(cur != NULL && cur->actorCode == code) {
        // if the prev node is null (new node is inserted at start of linked list) then set head of linked list to cur nodes next node 
        if(prev == NULL) {
            *actorHead = cur->next;
        }
        // otherwise set the prev nodes next node as cur nodes next node
        else {
            prev->next = cur->next;
        }
        // free memory that was allocated by removed actor
        free(cur);
    }
    // otherwise if actor was not found in database then print to screen it is not in database
    else {
        printf("actor with %d is not in database, cannot erase.\n", code);
    }
}