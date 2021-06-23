#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "deck.h"
#include <string.h>
#include <ctype.h>
#include "deck.h"
#include <signal.h>

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t **decks = NULL;
  char * originaline = NULL;
  char * line = NULL;
  size_t sz = 0;
  fc->n_decks = 0;
  fc->decks = NULL;
  *n_hands = 0;
  size_t n_lines = 0;
  //store line
  while(getline(&line, &sz, f) >= 0) {
    originaline = line;
    fprintf(stderr, "%s", originaline);
    if (*originaline != '\n') {
      //create space for deck array and decks
      //      fprintf(stderr, "Last stop 1\n");
      decks = realloc(decks, (n_lines + 1) * sizeof(*decks));
      decks[n_lines] = malloc(sizeof(**decks));
      decks[n_lines]->n_cards = 0;
      decks[n_lines]->cards = NULL;
      while(!(line == NULL || *line == '\n')){
	//if card sequence is more than 2 characters, throw error
	//	printf("%s\n", line);
	if(!(line[2] == ' ' || line[2] == '\n' || line[2] == '\0' || isdigit(line[2]))) {
	  //  fprintf(stderr, "Last stop, %s\n", line);
	  printf("Invalid card in deck");
	  exit(EXIT_FAILURE);
	}
	if(*line == '?'){
	  // fprintf(stderr, "Last stop 3\n");
	  add_empty_card(decks[n_lines]);
	  // printf("?? %s\n", line);
	  // printf("%d\n", atoi(line + 1));
	  add_future_card(fc, atoi(line + 1), decks[n_lines]->cards[decks[n_lines]->n_cards - 1]);
	  //  if (isdigit(line[2])){
	  //  line += 2;
	  // }
	}
	else {
	  // fprintf(stderr, "Last stop 4\n");
	  add_card_to(decks[n_lines], card_from_letters(line[0], line[1]));
	}
	//look for next space character
	line = strchr(line, ' ');
	if (line != NULL) {
	  //line = space;
	  //move line pointer forward until you find a char
	  while(!(isalpha(*line) || isdigit(*line) || *line == '?' || *line == '\n' || line == NULL)){
	    line++;
	  }
	}
      }      
   
      //if a hands is less than 5 cards, throw error
      if(decks[n_lines]->n_cards < 5){
	//	fprintf(stderr, "Last stop 5\n");
	printf("Hand %zu is less than 5 cards", n_lines);
	exit(EXIT_FAILURE);
      }
      n_lines++;
      (*n_hands)++;
    }
  }
  free(line);
  return decks;
}
