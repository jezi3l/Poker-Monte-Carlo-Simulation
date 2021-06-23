#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_card_ptr(future_cards_t * fc, size_t index, card_t * ptr) {

  if(fc->decks[index].n_cards == 0) {
    fc->decks[index].n_cards++;
    fc->decks[index].cards = malloc(sizeof(*fc->decks[index].cards));
    *fc->decks[index].cards = ptr;
  }
  else {
    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards) * sizeof(*fc->decks[index].cards));
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
  }
}

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  //check if empty future decks
  // fprintf(stderr,"%d%d\n", ptr->value, ptr->suit);
  if(fc->n_decks == 0) {
    fc->decks = malloc((index + 1) * sizeof(*fc->decks));
    fc->n_decks = index + 1;
    for (int i = 0; i < fc->n_decks; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    add_card_ptr(fc, index, ptr);
    //g fc->decks[index].cards->value = 0;
    //fc->decks[index].cards->suit = 0;
  }
  //Add decks
  else if(index >= fc->n_decks){
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
    for(int i = fc->n_decks; i <= index; i++){
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index + 1;
    add_card_ptr(fc, index, ptr);
  }
  //  add_card_ptr(fc, index, ptr);
  else {
    add_card_ptr(fc, index, ptr);
  }
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  //    fprintf(stderr,"FC from deck\n");
  int *indexList = NULL;
  size_t listSize = 0;
  for(int i = 0; i < fc->n_decks; i++){
    if(fc->decks[i].n_cards != 0) {
      listSize++;
      indexList = realloc(indexList, listSize * sizeof(*indexList));
      indexList[listSize - 1] = i;
    }
  }
  for(int i = 0; i < listSize; i++) {
    //printf("%d A\n", i);
    for(int j = 0; j < fc->decks[indexList[i]].n_cards; j++) {
      // printf("%d B\n", j);
      fc->decks[indexList[i]].cards[j]->value = deck->cards[i]->value;
      fc->decks[indexList[i]].cards[j]->suit = deck->cards[i]->suit;
    }
  }
  
  free(indexList);
  //printf("freed\n");
}
