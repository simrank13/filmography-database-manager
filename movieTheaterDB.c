/**
 * 251292956 - skullar5
*/
// include header file for movie theater database 
// include header file for movies/actors relationships of movie theater database 
#include "movieTheaterDB.h"
#include "relationship.h"
// include standard input output, library, string manipulation, character functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//printHelp function which provides description of program
void printHelp(void) {
    // Explanation of what each commands mean, represent and what they do 
    printf("-------------------Help Menu -------------------------------------------\n");
    printf("In this program, the user must enter either command m for movies or a for actors\n"
           "(or p for printing help or q for quitting program). Once you have prompted for\n"
           "movies or actors information, you will be asked to enter command i for inserting\n"
           "movies/actors, command p for printing movies/actors, command u for updating\n"
           "movies/actors, command e for erasing movies/actors, or command s for searching\n"
           "movies/actors and also command q to quit. Once the user has chosen one of these commands,\n"
           "the program will ask the user again to choose for movies, actors, help, or quit then the commands\n"
           "i, s, p, u, e, or q in a loop until the user doesn't prompt to quit (q).\n");
    printf("For movies and their information, enter command m.\n");
    printf("For actors and their information, enter command a.\n");
    printf("To quit the program, enter command q.\n");
    printf("To get more help on understanding what these commands mean and do, enter command p.\n");
    printf("After entering command m:\n");
    printf("    To insert movies into the database, enter command i.\n");
    printf("    To print movies list (with their details) that is currently in the database, enter command p.\n");
    printf("    To update movies and their details in the database, enter command u.\n");
    printf("    To erase movies and their details from the database, enter command e.\n");
    printf("    To search for movies in the database, enter command s.\n");
    printf("After entering command a:\n");
    printf("    To insert actors into the database, enter command i.\n");
    printf("    To print actors list (with their details) that are currently in the database, enter command p.\n");
    printf("    To update actors in the database, enter command u.\n");
    printf("    To erase actors from the database, enter command e.\n");
    printf("    To search for actors in the database, enter command s.\n");
    printf("For relationships enter r, and to insert new relation, enter i, update relation, u, print all relations- p, \n");
    printf("print movie relations - m, print actor relations - a, erase relat ions - e.\n");
}


int main(void) {
    // print header
    printf("*********************\n* 2211 Movie Cinema *\n*********************\n\n");

     // initialize pointers for movies, actors, and relationships to NULL
    struct Movie *movies = NULL;
    struct Actor *actors = NULL;
    struct movie_actor_code *relationship = NULL;

    // variable to store the prompted operation code
    char operationCode; 

    // infinite loop for main menu
    for(;;) {
        // prompt user to enter operation code (m, a, q, h, r) then store prompt into operationCode
        printf("Enter operation code (m(movie)/a(actor)/q(quit)/h(help)/r(relationship)): ");
        scanf(" %c", &operationCode);

        // clear input buffer
        while(getchar() != '\n');
        
        // if user entered m then 
        if(operationCode == 'm') {
            // prompt user to enter movie operation code (i, s, u, p, e) and then store prompt into operationCode
            printf("Enter operation code for Movies (i(insert)/s(search)/u(update)/p(print)/e(erase)): ");
            scanf(" %c", &operationCode);
           
            // using switch case
            switch (operationCode) {
                // if user entered i then call insertMovie function to insert a movie to database then return from function
                case 'i': insertMovie(&movies);
                    break;
                // if user entered s then call searchMovie function to search a movie in database then return from function
                case 's': searchMovie(&movies);
                    break;
                // if user entered u then call updateMovie function to update a movie in database then return from function
                case 'u': updateMovie(&movies);
                    break;
                // if user entered p then call printMovie function to print movie list in database then return from function
                case 'p': printMovie(&movies);
                    break;
                // if user entered e then call eraseMovie function to erase a movie in database then return from function
                case 'e': eraseMovie(&movies);
                    break;
                // otherwise, if user did not enter i, s, u, p, or q, then print to screen that incorrect operation code has been entered
                default: printf("Incorrect code. Please enter code i, s, u, p, or q.\n");
            }
            
            // print new line to screen
            printf("\n");
        }

        // if user entered a then 
        else if(operationCode == 'a') {
            // prompt user to enter actor operation code (i, s, u, p, e) and then store prompt into operationCode
            printf("Enter operation code for Actors (i(insert)/s(search)/u(update)/p(print)/e(erase)): ");
            scanf(" %c", &operationCode);

            // using switch case
            switch (operationCode) {
                // if user entered i then call insertActor function to insert a actor to database then return from function
                case 'i': insertActor(&actors);
                    break;
                // if user entered s then call searchActor function to search a actor in database then return from function
                case 's': searchActor(&actors);
                    break;
                // if user entered u then call updateActor function to update a actor in database then return from function
                case 'u': updateActor(&actors);
                    break;
                // if user entered p then call printActor function to print actor list in database then return from function
                case 'p': printActor(&actors);
                    break;
                // if user entered e then call eraseActor function to erase a actor in database then return from function
                case 'e': eraseActor(&actors);
                    break;
                // otherwise, if user did not enter i, s, u, p, or q, then print to screen that incorrect operation code has been entered
                default: printf("Incorrect code. Please enter code i, s, u, p, or q.\n");
            }
            // print new line to screen
            printf("\n");
        }

        // if user entered h then call printHelp method to guide user with description of program
        else if(operationCode == 'h') {
            printHelp();
        }

        // if user entered r then 
        else if(operationCode == 'r') {
            // prompt user to enter relationships operation code (i, s, u, p, e) and then store prompt into operationCode
            printf("Enter operation code for Movie Actor Relationships (i(insert)/s(search)/p(print)/e(erase)): ");
            scanf(" %c", &operationCode);

            // using switch case
            switch(operationCode) {
                // if user entered i then call insertRelation function to insert a relation to database then return from function
                case 'i': insertRelation(&movies, &actors, &relationship);
                    break;
                // if user entered s then call searchRelation function to search a relation in database then return from function
                case 's': searchRelation(&relationship);
                    break;
                // if user entered p then call printRelation function to print all relations (relation list) in database then return from function
                case 'p': printAllRelations(&relationship);
                    break;
                // if user entered m then call printMovieRelation function to print movie relations for actor code in database then return from function
                case 'm': printMovieRelation(&movies, &actors, &relationship);
                    break;
                // if user entered a then call printActorRelation function to print actor relations for movie code in database then return from function
                case 'a': printActorRelation(&movies, &actors, &relationship);
                    break;
                // if user entered e then call eraseRelation function to erase a relation in database then return from function
                case 'e': eraseRelation(&relationship);
                    break;
                // otherwise, if user did not enter i, s, u, p, or q, then print to screen that incorrect operation code has been entered                        
                default: printf("Incorrect code. Please enter code i, s, u, p, or q.\n");
            }
        }
       // if user entered q then end the program
        else if(operationCode == 'q') {
            return 0;
            break;
        }
        // othwerwise print to screen that user entered invalid command 
        else {
            printf("Invalid command. Please enter m, a, or q.\n");
        }


    }

}