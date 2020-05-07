#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_NUM 4
#define COLOR_LEN 9

char **get_colorname (char **def) {
	char buf[2048], path[2048];
	static char c[COLOR_NUM][COLOR_LEN];

	sprintf(path, "%s/.color-now", getenv("HOME"));
	FILE *f = fopen(path, "r");
	fgets(buf, sizeof(buf), f);
	fclose(f);
  
	sprintf(path, "%s/.color-%s", getenv("HOME"), buf);
	f = fopen(path, "r");
	for(int i = 0; i < COLOR_NUM; i++) {
		fgets(c[i], COLOR_LEN, f);
		c[i][COLOR_LEN-2] = '\0';
	}
	fclose(f);
  
	def[0] = c[0]; /* Background */
	def[7] = c[1]; /* Foreground */
	def[15] = c[1]; /* Cursor Color */

	return def;
}
