
//PGM���m�N���摜�p���o�͊֐�
int save_pgm(char *filename, unsigned char *image, int width, int height);
int load_pgm(char *filename, unsigned char **image, int *width, int *height);


//PPM�J���[�摜�p���o�͊֐�
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height);
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height);

