
// include header file for movies of movie theater database 
#include "movieTheaterDB_movie.h"
// include standard input output, library, string manipulation, character functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// readMovie function reads string with specified length n
int readMovie(char str[], int n) {
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

// findMovie function finds movie by its associated code in linked list
struct Movie *find_movie(struct Movie *movieHead, int code) {
    // declaration of pointer p to Movie structure
    struct Movie *p;

    // iterate through linked list until specified code isnt found or reached end of linked list
    for(p = movieHead; p != NULL && code != p->code; p = p->next);
   
    // return pointer to movie found (or null if no movie found)
    return p;
}

// insertMovie function inserts new movie into linked list
void insertMovie(Movie **movieHead) {
    // declaration of pointers representing current node, previous node, and new node pointing to Movie structure
    struct Movie *cur, *prev, *new_node;

    // allocate memory for new node of Movie structure
    new_node = malloc(sizeof(struct Movie));

    // if malloc failed meaning new node is allocated memory of null then print message that malloc failed otherwise if malloc succeeded
    if (new_node == NULL) {
        printf("Database is full (malloc failed), can't add more movies.\n");
        return;
    }

    // prompt user for movie code and store it as code in Movie structure
    printf("        Enter movie code: ");
    scanf("%d", &new_node->code);

    // if prompted movie code isnt positive integer then print to screen that it is invalid movie code 
    if(new_node->code < 0) {
        printf("Please try again, invalid movie code (needs to positive unique integer).\n");
        free(new_node);
        return;
    }
    // otherwise if it is positive integer then
    // iterate through linked list to get right position in which to insert the new node depending movie code 
    for (cur = *movieHead, prev = NULL; cur != NULL && new_node->code > cur->code; prev = cur, cur = cur->next);

    // if movie with same code is already in link list then print to screen that movie already exists in database
    // then free allocated memory for new node
    if (cur != NULL && new_node->code == cur->code) {
        printf("Movie already exists.\n");
        free(new_node);
        return;
    }
    
    // prompt user for movie name and read movie name string with length 100
    printf("        Enter movie name: ");
    readMovie(new_node->movieName, 100);

    // prompt user for movie genre and read movie genre string with length 25
    printf("        Enter movie genre: ");
    readMovie(new_node->movieGenre, 25);

    // prompt user for movie rating and store as rating in Movie structure 
    printf("        Enter movie rating: ");
    scanf("%f", &new_node->movieRating);

    // if prompted movie rating is less than 0 or greater than 10 then print to screen invalid movie rating then free allocated memory for new node
    if(new_node->movieRating < 0.0 || new_node->movieRating > 10.0) {
        printf("Please try again, invalid movie rating. Needs to be in range (0.0-10.0)\n");
        free(new_node);
        return;
    }
    // set new nodes next node as cur node connecting new node and cur node
    new_node->next = cur;

    // if the prev node is null (new node is inserted at start of linked list) then set head of linked list to new node 
    if (prev == NULL) {
        *movieHead = new_node;
    // otherwise set the prev nodes next node as new node connecting prev node and new node
    } else {
        prev->next = new_node;
    }

   

}
// searchMovie function search for movie by its associated code
void searchMovie(Movie **movieHead) {
    // declaration of code variable which will store prompted movie code
    int code;
    // declaration of pointer p to Movie structure
    struct Movie *p;

    // prompt user for movie code and store it in code variable
    printf("        Enter movie code: ");
    scanf("%d", &code);

    // call find_movie function to find movie with specified code and set it as p
    p = find_movie(*movieHead, code);
    // if movie with specified code is found then 
    if(p != NULL) {
        // print header with column title indicating column of code, title, genre and rating with formatting for alignment and spacing
        // movie code left aligned in 12 character wide column, movie name left aligned in 65 character wide column, 
        // movie genre left aligned in 50 character wide column, movie rating displayed with one decimal place
        printf("%-12s%-65s%-50s%-s\n", "Movie Code", "Movie Name", "Movie Genre", "Movie Rating");
        
        // initialize array which represents copy of movie name that will be striped to limit to 64 characters (including null character)
        char strippedName[64];
        // strncpy copies at max 63 characters from original movie name to striped array
        strncpy(strippedName, p->movieName, 63);
        // set the last element in the striped array to null character to end string
        strippedName[63] = '\0';

        // initialize array which represents copy of movie genre that will be striped to limit to 26 characters (including null character)
        char strippedGenre[26];
        // strncpy copies at max 25 characters from original movie genre to striped array
        strncpy(strippedGenre, p->movieGenre, 25);
        // set the last element in the striped array to null character to end string
        strippedGenre[25] = '\0';
        
        // print movie code, title, genre and rating columns with formatting for alignment and spacing
        // movie code left aligned in 12 character wide column, movie name left aligned in 65 character wide column, 
        // movie genre left aligned in 50 character wide column, movie rating displayed with one decimal place
        printf("%-12d%-65s%-50s%.1f\n", p->code, strippedName, strippedGenre, p->movieRating);
        
    }
    //otherwise print to screen movie isnt found in database
    else {
        printf("Movie not found.\n");
    }
    // print newline after list to screen
    printf("\n");
}

// clearCharMovie function clears characters from buffer (if exceeded maximum striped length)
void clearCharMovie() {
    // declaration of character variable representing characters read from  buffer 
    int character;

    // read characters from buffer until meets new line or end of file
    while ((character = getchar()) != '\n' && character != EOF) ;
}

// updateMovie function updates movie's details
void updateMovie(Movie **movieHead) {
    // declaration of oldCode and newCode variable which will store the old and new movie code
    int oldCode, newCode;
    // declaration of pointer p and existing to Movie structure 
    struct Movie *p, *existing;

    // prompt user to enter movie code 
    printf("        Enter movie code: ");

    // read movie code from user and store in old code variable and if code is invalid input then
    if (scanf("%d", &oldCode) != 1) {
        // clear characters from buffer and return from function
        clearCharMovie();
        return;
    }
    // clear any remaining characters from buffer
    clearCharMovie();

    // call find_movie function to find movie with old code and set it as p
    p = find_movie(*movieHead, oldCode);
    // if movie with specified code is found then
    if (p != NULL) {
        // prompt user to enter movie code 
        printf("        Enter movie code: ");

        // read movie code from user and store in new code variable and if code is invalid input then
        if (scanf("%d", &newCode) != 1) {
            // clear characters from buffer and return from function
            clearCharMovie();
            return;
        }
        // clear any remaining characters from buffer
        clearCharMovie();

        // if new code isnt same as old code then 
        if (newCode != oldCode) {

            // call find_movie function to find movie with new code and set it as existing
            existing = find_movie(*movieHead, newCode);

            // if movie with new code exists in linked list then print to screen that code already exists
            if (existing != NULL) {
                printf("Duplicate error: enter different code that isn't %d.\n", oldCode);
            } else {
                // Update the code only if the new code is not already present
                p->code = newCode;

                // prompt user for movie name and read movie name string with length 100
                printf("        Enter movie name: ");
                readMovie(p->movieName, 100);

                // prompt user for movie genre and read movie genre string with length 25
                printf("        Enter movie genre: ");
                readMovie(p->movieGenre, 25);

                // prompt user for movie rating and
                // read updated movie rating from user and if input invalid then clear characters from buffer and return from function
                printf("        Enter movie rating: ");
                if (scanf("%f", &p->movieRating) != 1) {
                    clearCharMovie();
                    return;
                }
                // clear any remaining characters from buffer
                clearCharMovie();
            }

        } 
        // otherwise if movie is not found in database (index is -1) then print to screen that movie is not in database
    } else {
        printf("Movie not found.\n");
    }
}


// printMovie function prints list of movie and its details
void printMovie(Movie **movieHead) {
    // declaration of pointer p to Movie structure
    struct Movie *p;

    // print header with column title indicating column of code, title, genre and rating with formatting for alignment and spacing
    // movie code left aligned in 12 character wide column, movie name left aligned in 65 character wide column, 
    // movie genre left aligned in 50 character wide column, movie rating displayed with one decimal place     
    printf("%-12s%-65s%-50s%-s\n", "Movie Code", "Movie Name", "Movie Genre", "Movie Rating");

    // iterate through the linked list of movies
    for(p = *movieHead; p != NULL; p = p->next) {
        // initialize array which represents copy of movie name that will be striped to limit to 64 characters (including null character)
        char strippedName[64];
        // strncpy copies at max 63 characters from original movie name to striped array
        strncpy(strippedName, p->movieName, 63);
        // set the last element in the striped array to null character to end string
        strippedName[63] = '\0';

        // initialize array which represents copy of movie genre that will be striped to limit to 26 characters (including null character)
        char strippedGenre[26];
        // strncpy copies at max 25 characters from original movie genre to striped array
        strncpy(strippedGenre, p->movieGenre, 25);
        // set the last element in the striped array to null character to end string
        strippedGenre[25] = '\0';

        // print movie code, title, genre and rating columns with formatting for alignment and spacing
        // movie code left aligned in 12 character wide column, movie name left aligned in 65 character wide column, 
        // movie genre left aligned in 50 character wide column, movie rating displayed with one decimal place
        printf("%-12d%-65s%-50s%.1f\n", p->code, strippedName, strippedGenre, p->movieRating);
    }
    //print new line to screen
    printf("\n");

}

// eraseMovie function erase movies from database
void eraseMovie(Movie **movieHead) {
    // declaration of code variable which will store prompted movie code
    int code;
    // declaration of pointer cur and prev to Movie structure
    struct Movie *cur, *prev;

    // prompt user for movie code and store it in code variable
    printf("        Enter movie code: ");
    scanf("%d", &code);

    // iterate through the linked list and find movie with specified code
    for(cur = *movieHead, prev = NULL; cur != NULL && cur->code != code; prev = cur, cur = cur-> next);

    // if movie with specified code is found then 
    if(cur != NULL && cur->code == code) {
        // if the prev node is null (new node is inserted at start of linked list) then set head of linked list to cur nodes next node 
        if(prev == NULL) {
            *movieHead = cur->next;
        }
        // otherwise set the prev nodes next node as cur nodes next node
        else {
            prev->next = cur->next;
        }
        // free memory that was allocated by removed movie
        free(cur);
    }
    // otherwise if movie was not found in database then print to screen it is not in database
    else {
        printf("movie with %d is not in database, cannot erase.\n", code);
    }
      
}


