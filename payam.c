#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_NUM 4
#define COLOR_LEN 9
#define COLOR_LIGHT_FN ".color-light"
#define COLOR_DARK_FN  ".color-dark"

char **get_colorname (char **def)
{
  time_t t = time(NULL);
  struct tm *T = localtime(&t);
  char *home = getenv("HOME");
  int path_len;
  char *path;
  FILE *f;
  static char c[COLOR_NUM][COLOR_LEN];
  int i;

  path_len = sizeof(char) * strlen(home) + 1 + strlen(COLOR_LIGHT_FN) + 1;
  path = (char *) malloc(path_len);
  
  if(path == NULL) return def;

  for(i = 0; i < path_len; i++)
    path[i] = '\0';
  strcat(path, home);
  strcat(path, "/");
  
  if( T->tm_hour > 6 && T->tm_hour <= 22 )
    strcat(path, COLOR_LIGHT_FN);
  else
    strcat(path, COLOR_DARK_FN);

  f = fopen(path, "r");
  free(path);
        
  for(i = 0; i < COLOR_NUM; i++)
    {
      fgets(c[i], COLOR_LEN, f);
      c[i][COLOR_LEN-2] = '\0';
    }

  fclose(f);
  
  def[0] = c[0]; // bg
  def[7] = c[1]; // fg
  
  return def;
}

