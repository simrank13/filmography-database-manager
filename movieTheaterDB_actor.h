
#ifndef MOVIE_THEATER_DB_ACTOR_H
#define MOVIE_THEATER_DB_ACTOR_H

// created structure representing actor with unique actor code, actor name of 50 characters max, 
//age, imdb profile of 50 characters max and pointer to next actor in linked list
struct Actor {
    int actorCode;
    char actorName[50];
    int age;
    char imdbProfile[50];
    struct Actor *next;
};
// declaring typedef for structure
typedef struct Actor Actor;

// readActor function reads actor from user's prompt
int readActor(char str[], int n);

// findActor function finds actor by its associated code in linked list
struct Actor *find_actor(struct Actor *actorHead, int code);

// clearCharActor function clears character array for actor 
void clearCharActor();

// insertActor function inserts new actor into linked list
void insertActor(Actor **actorHead);

// printActor function print all actors in linked list
void printActor(Actor **actorHead);

// searchActor function searches for actor by its associated code
void searchActor(Actor **actorHead);

// updateActor function updates actor's details
void updateActor(Actor **actorHead);

//eraseActor function erase actor from linked list
void eraseActor(Actor **actorHead);

#endif
