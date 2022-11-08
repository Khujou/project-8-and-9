#ifndef SOCCER_TEAM
#define SOCCER_TEAM
// soccer team struct
typedef struct struct_soccer 
{
    char club_name[50] ;    // name of the club
    char league[50] ;     // The league they are competiting
    char league_region[10] ;    // Which region this club is from
    char stadium[50] ;      // The club's stadium name
    int league_titles;      // How many times this club wins their league
} Soccer ;
#endif