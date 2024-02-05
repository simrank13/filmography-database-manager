/**
 * 251292956 - skullar5
*/
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include "movieTheaterDB_movie.h"
#include "movieTheaterDB_actor.h"

// created structure representing movie and actor code with unique movie and actor code and pointer to next movie in linked list
struct movie_actor_code {
    int movieCode;
    int actorCode;
    struct movie_actor_code *next;
};
// declaring typedef for structure
typedef struct movie_actor_code movie_actor_code;

// insertRelation function inserts new movie/actor relationship into linked list
void insertRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead);

// searchRelation function searches for new movie/actor relationship 
void searchRelation(movie_actor_code **relationHead);

// printAllRelations function prints list of all movie/actor relations
void printAllRelations(movie_actor_code **relationHead);

//printMovieRelation function prints list of all movie details for actor code enters
void printMovieRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead);

//printActorRelation function prints list of all actor details for movie code enters
void printActorRelation(Movie **movieHead, Actor **actorHead, movie_actor_code **relationHead);

//eraseRelation function erases movie relationships in database 
void eraseRelation(movie_actor_code **relationHead);

#endif
