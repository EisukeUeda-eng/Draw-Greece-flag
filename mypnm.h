
//PGMモノクロ画像用入出力関数
int save_pgm(char *filename, unsigned char *image, int width, int height);
int load_pgm(char *filename, unsigned char **image, int *width, int *height);


//PPMカラー画像用入出力関数
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height);
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height);

