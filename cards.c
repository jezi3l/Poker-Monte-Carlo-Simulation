#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

/*
- void assert_card_valid(card_t c);
  This function should use assert() to check
  that the card passed in has valid values.
  In particular, its value should be between
  2 and VALUE_ACE (inclusive of both),
  and its suit should be between SPADES
  and CLUBS (inclusive of both).
*/

void assert_card_valid(card_t c)
{
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

/*
- const char * ranking_to_string(hand_ranking_t r);
  This function should convert the
  hand_ranking_t enumerated value passed
  in to a string that describes it.  Remember
  that Drew showed you a nice way to do this
  with emacs keyboard macros!
*/

const char * ranking_to_string(hand_ranking_t r)
{
  switch (r)
    {
    case STRAIGHT_FLUSH:
      return "STRAIGHT_FLUSH";
    case FOUR_OF_A_KIND:
      return "FOUR_OF_A_KIND";
    case FULL_HOUSE:
      return "FULL_HOUSE";
    case FLUSH:
      return "FLUSH";
    case STRAIGHT:
      return "STRAIGHT";
    case THREE_OF_A_KIND:
      return "THREE_OF_A_KIND";
    case TWO_PAIR:
      return "TWO_PAIR";
    case PAIR:
      return "PAIR";
    default:
      return "NOTHING";
    }
}

/*
- char value_letter(card_t c);
  This function should return the character that textually represents
  the value of the passed-in card.  For values 2-9, this should
  be that digit.  For 10, it should be '0', and for Jack, Queen, King, and Ace,
  it should be 'J', 'Q', 'K', and 'A' respectively.
  Hint: remember everything is a number.
  For example, the character '0' has the decimal value 48,
  and the character '5' has the decimal value 53, so you could represent
  '5' as '0' + 5.
*/

char value_letter(card_t c)
{
  const char* value_letters = "234567890JQKA";
  return (c.value >= 2 && c.value <= VALUE_ACE) ? value_letters[c.value - 2] : '?';
}

/*
- char suit_letter(card_t c);
  This function should return the letter that textually represents
  the suit of the card passed in ('s', 'h', 'd', or 'c' for SPADES,
  HEARTS, DIAMONDS, or CLUBS).
*/

char suit_letter(card_t c)
{
  const char* suit_letters = "shdc";
  return (c.suit >= SPADES && c.suit <= CLUBS) ? suit_letters[c.suit] : '?';
}

/*
- void print_card(card_t c);
  This function should print out the textual
  representation of the card (hint: use the functions
  you previously wrote). It should print
  the value first, then the suit.  For example,
  As  (for Ace of spades)
  0d  (for 10 of diamonds)
  Kc  (for King of clubs) etc.
  This function should not print any additional
  spaces or newlines after the card's text.
*/

void print_card(card_t c)
{
  printf("%c%c", value_letter(c), suit_letter(c));
}

/*
- card_t card_from_letters(char value_let, char suit_let);
  This function should make and return a
  card_t whose value and suit correspond
  to the letters passed in. If the values passed
  in are invalid, you should use assert()
  or print an error message and exit(EXIT_FAILURE).
*/

card_t card_from_letters(char value_let, char suit_let)
{
  const char* value_letters = "234567890JQKA";
  const char* suit_letters = "shdc";

  card_t temp;

  // get value
  temp.value = 99; /* invalid */
  for (int i=0; i<13; i++)
    {
      if (value_letters[i] == value_let)
	{
	  temp.value = i + 2;
	  break;
	}
    }
  if (temp.value == 99)
    {
      printf("Invalid value letter: %c\n", value_let);
      exit(EXIT_FAILURE);
    }

  // get suit
  temp.suit = NUM_SUITS;
  for (int i=0; i<4; i++)
    {
      if (suit_letters[i] == suit_let)
	{
	  temp.suit = i;
	  break;
	}
    }
  if (temp.suit == NUM_SUITS)
    {
      printf("Invalid suit letter: %c\n", suit_let);
      exit(EXIT_FAILURE);
    }

  return temp;
}

/*
 card_t card_from_num(unsigned c);
  This function should take a number from 0 (inclusive)
  to 52 (exclusive) and map it uniquely to
  a card value/suit combination.  Exactly
  how you map the numbers to values/suits
  is up to you, but you must guarantee
  that each valid value/suit combination
  corresponds to exactly one input value
  in the range [0,52). 
  Hint: you may want to use the mod
  operator % to find the remainder of a number divided by 13.
  (In Course 3, this function will be used
  to make a deck of cards by iterating
  over that range and calling it once
  for each value--you just need
  to learn about arrays first so you
  have a place to put all those
  cards.)
*/

card_t card_from_num(unsigned c)
{
  card_t temp;
  temp.suit = c / 13;
  temp.value = c % 13 + 2;
  return temp;
}
