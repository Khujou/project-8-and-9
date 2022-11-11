#include "soccer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(char *clubName, char *league, char *leagueRegion, char *stadium, int leagueTitles, FILE *fp) {

  Soccer *team = malloc(sizeof(Soccer));

  strcpy(team->club_name, clubName);
  strcpy(team->league, league);
  strcpy(team->league_region, leagueRegion);
  strcpy(team->stadium, stadium);
  team->league_titles = leagueTitles;

  fwrite(&team, sizeof(team), 1, fp);
}

void redTextColor() {
  printf("\033[0;31m");
}

void resetTextColor() {
  printf("\033[0m");
}

void secret(char*begin, char*variable, char*end){
  printf("%s", begin);
  redTextColor();
  printf("%s", variable);
  resetTextColor();
  printf("%s", end);
  
}

void printOut(Soccer *teams[5]) {

  char* str = malloc(3);

  for (int i = 0; i < 5; i++) {

    secret("\nTheir team name is ", teams[i]->club_name, ",\n");
    secret("They play in the ", teams[i]->league, " League,\n");
    secret("Their team is based in ", teams[i]->league_region, ",\n");
    secret("They play at ", teams[i]->stadium, ",\n");
    sprintf(str, "%d", teams[i]->league_titles);
    secret("They have won ", str, " League Title(s).\n");
    
  }
  printf("\n");
  
}

int main(void) {

  // INITIALIZING VARIABLES ----------------------------------------------------
  Soccer *teams[5] = {0};
  long numBytesRead;

  // OPENING FILE FOR WRITING --------------------------------------------------
  FILE *fp = fopen("soccer.dat", "wb");
  if (fp == NULL) {
    printf("failed to open file\n");
    return 1;
  }

  // WRITING STRUCTS TO FILE ---------------------------------------------------
  writeToFile("Sounders", "MLS", "Seattle", "Lumen Field", 2, fp);
  writeToFile("Galaxy", "MLS", "Los Angeles",
              "Dignity Health Sports Park", 5, fp);
  writeToFile("Fire", "MLS", "Chicago", "Soldier Field", 1, fp);
  writeToFile("Rapids", "MLS", "D.C.", "Audi Field", 1, fp);
  writeToFile("Crew", "MLS", "Columbus", "Lower.com Field", 2, fp);

  // CLOSING FILE FOR WRITING --------------------------------------------------
  fclose(fp);

  // OPENING FILE FOR READING --------------------------------------------------
  fopen("soccer.dat", "rb");
  if (fp == NULL) {
    printf("No2\n");
    return 2;
  }
  
  // OUTPUTTING STRUCT DATA THAT WAS READ IN -----------------------------------

  int i = 0;
  numBytesRead = fread(&teams[i], sizeof(teams[i]), 1, fp);

  while (numBytesRead != 0) {
    i++;
    numBytesRead = fread(&teams[i], sizeof(teams[i]), 1, fp);
  }

  printOut(teams);

  // CLOSING FILE --------------------------------------------------------------
  fclose(fp);

  return 0;
}
