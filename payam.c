#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_NUM 4
#define COLOR_LEN 9
#define COLOR_LIGHT_FN ".color-light"
#define COLOR_DARK_FN  ".color-dark"

char **get_colorname (char **def) {
  time_t t = time(NULL);
  struct tm *T = localtime(&t);
  char *home = getenv("HOME");
  char path[2048];  
  static char c[COLOR_NUM][COLOR_LEN];
  
  if(T->tm_hour > 6 && T->tm_hour <= 22)
    sprintf(path, "%s/%s", home, COLOR_LIGHT_FN);
  else sprintf(path, "%s/%s", home, COLOR_DARK_FN);
  
  FILE *f = fopen(path, "r");
  for(int i = 0; i < COLOR_NUM; i++) {
    fgets(c[i], COLOR_LEN, f);
    c[i][COLOR_LEN-2] = '\0';
  }
  fclose(f);
  
  def[0] = c[0]; /* Background */
  def[7] = c[1]; /* Foreground */
  
  return def;
}
