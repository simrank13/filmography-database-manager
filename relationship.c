
// include header file for movie/actor relationship of movie theater database 
#include "relationship.h"
// include standard input output, library, string manipulation, character functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// insertRelation function inserts new movie/actor relationship into linked list
void insertRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead) {
    // declaration of movieCode and actorCode variabels which will store movie and actor code
    int movieCode, actorCode;
    // pointers m, a, relationship and existing to Movie, Actor, and movie_actor_code structure
    struct Movie *m;
    struct Actor *a;
    struct movie_actor_code *relationship, *existing;

    // prompt user to enter movie code 
    printf("        Enter movie code: ");

    // read movie code from user and store in movie code variable and if code is invalid input then
    if (scanf("%d", &movieCode) != 1) {
        // clear characters from buffer and return from function
        clearCharMovie();
        return;
    }
    // clear any remaining characters from buffer
    clearCharMovie();

    // call find_movie function to find movie with movie code and set it as m
    m = find_movie(*movieHead, movieCode);

     // if movie with movie code isnt found then print to screen that movie is not in database 
    if (m == NULL) {
        printf("Movie is not found in the database; add the movie first.\n");
        return;
    }

    // prompt user to enter actor code
    printf("        Enter actor code: ");

    // read actor code from user and store in actor code variable and if code is invalid input then
    if (scanf("%d", &actorCode) != 1) {
        // clear characters from buffer and return from function
        clearCharActor();
        return;
    }
    // clear any remaining characters from buffer
    clearCharActor();

    // call find_actor function to find actor with actpr code and set it as a
    a = find_actor(*actorHead, actorCode);

    // if actor with actor code isnt found then print to screen that movie is not in database 
    if (a == NULL) {
        printf("Actor is not found in the database; add the actor first.\n");
        return;
    }
    // iterate through existing relationships in tlinked list to check for duplicates
    for (existing = *relationHead; existing != NULL; existing = existing->next) {
        // if current relationship has same movie code and actor code as input then print to screen that relationship already exists in database
        if (existing->movieCode == movieCode && existing->actorCode == actorCode) {
            printf("Duplicate error: relationship already exists.\n");
            return;
        }
    }
    // allocate memory for new relationship node
    relationship = malloc(sizeof(struct movie_actor_code));

    // if memory allocation fails then print to screen malloc has failed
    if (relationship == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    // initialize fields of relationship node with movie and actor codes
    relationship->movieCode = movieCode;
    relationship->actorCode = actorCode;
    // set next pointer of relationship node to point to current head of (relationship) linked list
    relationship->next = *relationHead;

    // update head of relationship linked list to point to relationship node
    *relationHead = relationship;
}
// searchRelation function searches for new movie/actor relationship 
void searchRelation(movie_actor_code **relationHead) {
    // declaration of movieCode and actorCode variabels which will store movie and actor code
    int movieCode, actorCode;
    // pointer p point to movie_actor_code structure
    struct movie_actor_code *p;

    // prompt user to enter movie code
    printf("        Enter movie code: ");

    // read movie code from user and store in movie code variable and if movie code is invalid input then print to screen enter valid movie code
    if (scanf("%d", &movieCode) != 1) {
        printf("enter valid movie code.\n");
        return;
    }

    // prompt user to enter actor code
    printf("        Enter actor code: ");

    // read actor code from user and store in actor code variable and if actor code is invalid input then print to screen enter valid actor code
    if (scanf("%d", &actorCode) != 1) {
        printf("enter valid actor code.\n");
        return;
    }
    // iterate through relationships in linked list to find specific relationship
    for(p = *relationHead; p != NULL; p = p->next) {
        // if current relationship has same movie code and actor code as input
        if(p->movieCode == movieCode && p->actorCode == actorCode) {
            // print header of relationship details following the movie code and actore code 
            printf("%-73s%-73s\n", "Movie Code", "Actor Code");
            printf("%-73d%-73d\n", p->movieCode, p->actorCode);
            return;
        }
    }
    // otherwise print to screen that invalid movie and/or actor code
    printf("please try again, movie code and/or actor code isnt in the database");

    //print new line to screen
    printf("\n");

    
}

// printAllRelations function prints list of all movie/actor relations
void printAllRelations(movie_actor_code **relationHead) {
    // pointer p point to movie_actor_code structure
    struct movie_actor_code *p;
    
    // set p to be head of linked list
    p  = *relationHead;

    // print header with formatting specifiers for relationship 
    printf("%-60s%-60s\n", "Movie Code", "Actor Code");

    // iterate through linked list and print details of each relationship
    while (p != NULL) {
        // print values of movie code and actor code for current relationship with formatting specifiers then get th enxt relationship in linked list
        printf("%-60d%-60d\n", p->movieCode, p->actorCode);
        p = p->next;
    }
}

//printMovieRelation function prints list of all movie details for actor code enters
void printMovieRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead) {
    // declaration of actorCode variable which will store actor code
    int actorCode;

    // prompt user to enter actor code
    printf("        Enter actor code: ");

    // read actor code from user and store in actor code variable and if actor code is invalid input then print to screen enter valid actor  code
    if (scanf("%d", &actorCode) != 1) {
        printf("enter valid actor code.\n");
        return;
    }

    // find actor with entered actor code in actor linked list
    struct Actor *actor = find_actor(*actorHead, actorCode);

    // if actor is not found, print to screen actor is not found 
    if (actor == NULL) {
        printf("Actor is not found in the database.\n");
        return;
    }
    // print movie header with formatting specifiers
    printf("%-12s%-65s%-50s%-s\n", "Movie Code", "Movie Name", "Movie Genre", "Movie Rating");

    // pointer p point to movie_actor_code structure
    struct movie_actor_code *p;

    // iterate through relationship linked list
    for (p = *relationHead; p != NULL; p = p->next) {
        // if current relationship is associated with prompted actor code then 
        if (p->actorCode == actorCode) {
            // Find movie corresponding to movie code in relationship
            struct Movie *movie = find_movie(*movieHead, p->movieCode);

            // if movie is found, then print its details
            if (movie != NULL) {
                // initialize array which represents copy of movie name that will be striped to limit to 64 characters (including null character)
                char strippedName[64];
                // strncpy copies at max 63 characters from original movie name to striped array
                strncpy(strippedName, movie->movieName, 63);
                // set the last element in the striped array to null character to end string
                strippedName[63] = '\0';
       
                // initialize array which represents copy of movie genre that will be striped to limit to 49 characters (including null character)
                char strippedGenre[49];
                // strncpy copies at max 48 characters from original movie genre to striped array
                strncpy(strippedGenre, movie->movieGenre, 48);
                // set the last element in the striped array to null character to end string
                strippedGenre[48] = '\0';

                // print movie code, title, genre and rating columns with formatting for alignment and spacing
                // movie code left aligned in 12 character wide column, movie name left aligned in 65 character wide column, 
                // movie genre left aligned in 50 character wide column, movie rating displayed with one decimal place
                printf("%-12d%-65s%-50s%.1f\n", movie->code, strippedName, strippedGenre, movie->movieRating);
            }
        }
    }
}

//printActorRelation function prints list of all actor details for movie code enters
void printActorRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead) {
    // declaration of movieCode variable which will store movie code
    int movieCode;

    // prompt user to enter movie code
    printf("        Enter movie code: ");

    // read movie code from user and store in movie code variable and if movie code is invalid input then print to screen enter valid movie  code
    if (scanf("%d", &movieCode) != 1) {
        printf("enter valid movie code.\n");
        return;
    }

    // find movie with entered movie code in movie linked list
    struct Movie *movie = find_movie(*movieHead, movieCode);

    // if movie is not found, print to screen movie is not found
    if (movie == NULL) {
        printf("Movie is not found in the database.\n");
        return;
    }

    // print movie header with formatting specifiers
    printf("%-12s%-52s%-7s%-s\n", "Actor Code", "Actor Name", "Age", "IMDB Profile Page");

    // pointer p point to movie_actor_code structure
    struct movie_actor_code *p;

    // iterate through relationship linked list
    for (p = *relationHead; p != NULL; p = p->next) {
        // if current relationship is associated with prompted movie code then
        if (p->movieCode == movieCode) {
            // Find actor corresponding to actor code in relationship
            struct Actor *actor = find_actor(*actorHead, p->actorCode);

            // if actor is found, then print its details
            if (actor != NULL) {
                // initialize array which represents copy of movie name that will be striped to limit to 51 characters (including null character)
                char strippedName[51];
                // strncpy copies at max 50 characters from original movie name to striped array
                strncpy(strippedName, actor->actorName, 50);
                // set the last element in the striped array to null character to end string
                strippedName[50] = '\0';

                // initialize array which represents copy of movie genre that will be striped to limit to 51 characters (including null character)
                char strippedProfile[51];
                // strncpy copies at max 50 characters from original movie genre to striped array
                strncpy(strippedProfile, actor->imdbProfile, 50);
                // set the last element in the striped array to null character to end string
                strippedProfile[50] = '\0';

                // print movie code, title, genre and rating columns with formatting for alignment and spacing
                // movie code left aligned in 12 character wide column, movie name left aligned in 52 character wide column, 
                // movie genre left aligned in 7 character wide column, movie rating displayed with one decimal place
                printf("%-12d%-52s%-7d%s\n", actor->actorCode, strippedName, actor->age, strippedProfile);
            }
        }
    }
}

//eraseRelation function erases movie relationships in database 
void eraseRelation(movie_actor_code **relationHead) {
    // declaration of movieCode and actorCode variabels which will store movie and actor code
    int movieCode, actorCode;

    // prompt user to enter movie code
    printf("        Enter movie code: ");

    // read movie code from user and store in movie code variable and if movie code is invalid input then print to screen enter valid movie  code
    if (scanf("%d", &movieCode) != 1) {
        printf("Enter a valid movie code.\n");
        return;
    }

    // prompt user to enter actor code
    printf("        Enter actor code: ");

    // read actor code from user and store in actor code variable and if actor code is invalid input then print to screen enter valid actor  code
    if (scanf("%d", &actorCode) != 1) {
        printf("Enter a valid actor code.\n");
        return;
    }
    //pointer cur and prev point to movie_actor_code structure
    struct movie_actor_code *cur, *prev;

    // iterate through relationship linked list to find specified relationship
    for (cur = *relationHead, prev = NULL; cur != NULL && (cur->movieCode != movieCode || cur->actorCode != actorCode); prev = cur, cur = cur->next);

    // if specified relationship is found in linked list
    if (cur != NULL && cur->movieCode == movieCode && cur->actorCode == actorCode) {
        // declaration of removed variable 
        char removed;

        //prompt user for if they first deleted movie and actor for the relationship they want to delete then store their prompt into removed variable
        printf("Did you remove the actor and movie for this relationship (y- (yes)/n- (no))? ");
        scanf(" %c", &removed);

        // if user entered y then 
        if (removed == 'y') {

            // if relationship is at beginning of list then set cur nodes next node as head of linked list
            if (prev == NULL) {
                *relationHead = cur->next;
            // otherwise in middle or end of list set prev nodes next node as cur ndoes next node
            } else {
                prev->next = cur->next;
            }
            // free memory allocated to removed relationship
            free(cur);
        } 
        // otherwise let user know to first remove the movie and actor they wish to delete the relationship of
        else {
            printf("please remove movie and actor before their relationships");
        }
    // otherwise print to screen that relationship is not in database
    } else {
        printf("Relationship is not in the database, cannot erase.\n");
    }
}


