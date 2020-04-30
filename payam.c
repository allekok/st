#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_NUM 4
#define COLOR_LEN 9
#define COLOR_LIGHT_FN ".color-light"
#define COLOR_DARK_FN  ".color-dark"

char **get_colorname (char **def) {
	char buf[2048], path[2048];
	char *home = getenv("HOME");
	static char c[COLOR_NUM][COLOR_LEN];
  
	FILE *f = fopen("/sys/devices/platform/applesmc.768/light", "r");
	fgets(buf, 3, f);
	fclose(f);
  
	if((buf[1]-0x30) > 2) strcpy(buf, COLOR_LIGHT_FN);
	else strcpy(buf, COLOR_DARK_FN);
	sprintf(path, "%s/%s", home, buf);
  
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
