#include "soccer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(char *clubName, char *league, char *leagueRegion,
                 char *stadium, int leagueTitles, FILE *fp) {

  Soccer *team = calloc(1, sizeof(Soccer) - sizeof(Soccer*));

  strcpy(team->club_name, clubName);
  strcpy(team->league, league);
  strcpy(team->league_region, leagueRegion);
  strcpy(team->stadium, stadium);
  team->league_titles = leagueTitles;

  fwrite(team, sizeof(Soccer) - sizeof(Soccer*), 1, fp);
}

void secret(char *begin, char *variable, char *end) {
  printf("%s", begin);
  printf("\033[0;31m");
  printf("%s", variable);
  printf("\033[0m");
  printf("%s", end);
}

void printOut(Soccer *team) {

  char *str = malloc(3);

  while (team->next != NULL) {

    secret("\nTheir team name is ", team->club_name, ",\n");
    secret("They play in the ", team->league, " League,\n");
    secret("Their team is based in ", team->league_region, ",\n");
    secret("They play at ", team->stadium, ",\n");
    sprintf(str, "%d", team->league_titles);
    secret("They have won ", str, " League Title(s).\n");

    team = team->next;
  }

  printf("\n");
}

int main(void) {

  // INITIALIZING VARIABLES ----------------------------------------------------
  Soccer *team = calloc(1, sizeof(Soccer));
  long numBytesRead;

  // OPENING FILE FOR WRITING --------------------------------------------------
  FILE *fp;

  fp = fopen("soccer.dat", "wb");

  if (fp == NULL) {
    printf("failed to open file\n");
    return 1;
  }

  // WRITING STRUCTS TO FILE---------------------------------------------------
  writeToFile("Sounders", "MLS", "Seattle", "Lumen Field", 2, fp);
  writeToFile("Galaxy", "MLS", "Los Angeles", "Dignity Health Sports Park", 5,
              fp);
  writeToFile("Fire", "MLS", "Chicago", "Soldier Field", 1, fp);
  writeToFile("Rapids", "MLS", "D.C.", "Audi Field", 1, fp);
  writeToFile("Crew", "MLS", "Columbus", "Lower.com Field", 2, fp);

  // CLOSING FILE FOR WRITING --------------------------------------------------
  fclose(fp);

  // OPENING FILE FOR READING --------------------------------------------------
  fp = fopen("soccer.dat", "rb");
  if (fp == NULL) {
    printf("No2\n");
    return 2;
  }

  // OUTPUTTING STRUCT DATA THAT WAS READ IN -----------------------------------

  numBytesRead = fread(team, sizeof(Soccer) - sizeof(team), 1, fp);
  Soccer *tail = team;

  while (numBytesRead != 0) {
    Soccer *tmpTeam = calloc(1, sizeof(Soccer));
    numBytesRead = fread(tmpTeam, sizeof(Soccer) - sizeof(team), 1, fp);
    tail->next = tmpTeam;
    tail = tmpTeam;
  }

  printOut(team);

  // CLOSING FILE --------------------------------------------------------------
  fclose(fp);

  return 0;
}
