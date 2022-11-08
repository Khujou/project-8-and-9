#include "soccer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(Soccer *team, char *clubName, char *league, char *leagueRegion,
                 char *stadium, int leagueTitles, FILE *fp) {

  strcpy(team->club_name, clubName);
  strcpy(team->league, league);
  strcpy(team->league_region, leagueRegion);
  strcpy(team->stadium, stadium);
  team->league_titles = leagueTitles;

  fwrite(&team, sizeof(team), 1, fp);
}

void printOut(Soccer *teams[5]) {

  for (int i = 0; i < 5; i++) {
    printf("Their team name is %s,\nThey play in the %s League,\nTheir team is "
           "based in %s,\nThey play at %s,\nThey have %d League Title(s)\n\n",
           teams[i]->club_name, teams[i]->league, teams[i]->league_region,
           teams[i]->stadium, teams[i]->league_titles);
  }
  
}

int main(void) {

  // INITIALIZING VARIABLES ----------------------------------------------------
  Soccer *sounders = malloc(sizeof(Soccer));
  Soccer *galaxy = malloc(sizeof(Soccer));
  Soccer *fire = malloc(sizeof(Soccer));
  Soccer *united = malloc(sizeof(Soccer));
  Soccer *crew = malloc(sizeof(Soccer));
  long numBytesRead;

  // OPENING FILE FOR WRITING --------------------------------------------------
  FILE *fp = fopen("soccer.dat", "wb");
  if (fp == NULL) {
    printf("failed to open file\n");
    return 1;
  }

  // WRITING STRUCTS TO FILE ---------------------------------------------------
  writeToFile(sounders, "Sounders", "MLS", "Seattle", "Lumen Field", 2, fp);
  writeToFile(galaxy, "Galaxy", "MLS", "Los Angeles",
              "Dignity Health Sports Park", 5, fp);
  writeToFile(fire, "Fire", "MLS", "Chicago", "Soldier Field", 1, fp);
  writeToFile(united, "Rapids", "MLS", "D.C.", "Audi Field", 1, fp);
  writeToFile(crew, "Crew", "MLS", "Columbus", "Lower.com Field", 2, fp);

  // CLOSING FILE FOR WRITING --------------------------------------------------
  fclose(fp);

  // OPENING FILE FOR READING --------------------------------------------------
  fopen("soccer.dat", "rb");
  if (fp == NULL) {
    printf("No2\n");
    return 2;
  }

  // INITIALIZING ARRAY TO READ IN STRUCTS -------------------------------------
  Soccer *teams[5] = {malloc(sizeof(Soccer)), malloc(sizeof(Soccer)),
                      malloc(sizeof(Soccer)), malloc(sizeof(Soccer)),
                      malloc(sizeof(Soccer))};

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
