/**
 * 251292956 - skullar5
*/
#ifndef MOVIE_THEATER_DB_MOVIE_H
#define MOVIE_THEATER_DB_MOVIE_H

// created structure representing movie with unique movie code, movie name of 100 characters max, 
//movie genre of 25 characters max, movie rating and pointer to next movie in linked list
struct Movie {
    int code;
    char movieName[100];
    char movieGenre[25];
    float movieRating;
    struct Movie *next;
    
};
// declaring typedef for structure
typedef struct Movie Movie;

// readMovie function reads movie from user's prompt
int readMovie(char str[], int n);

// findMovie function finds movie by its associated code in linked list
struct Movie *find_movie(struct Movie *movieHead, int code);

// clearCharMovie function clears character array for movie 
void clearCharMovie();

// insertMovie function inserts new movie into linked list
void insertMovie(Movie **movieHead);

// printMovie function print all movies in linked list
void printMovie(Movie **movieHead);

// searchMovie function searches for movie by its associated code
void searchMovie(Movie **movieHead);

// updateMovie function updates movie's details
void updateMovie(Movie **movieHead);

//eraseMovie function erase movie from linked list
void eraseMovie(Movie **movieHead);

#endif 