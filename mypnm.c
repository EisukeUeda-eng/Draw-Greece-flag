#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mypnm.h"

#define BUFSIZE 1024

//PGMファイルの保存
int save_pgm(char *filename, unsigned char *image, int width, int height)
{
	FILE *fp;

	if((fp = fopen(filename,"wb"))==NULL){
		fprintf(stderr,"cannot open output PGMfile");
		return -1;
	}
	fprintf(fp,"P5\n%d %d\n255\n",width,height);	//ヘッダ出力
	fwrite(image,sizeof(char),(size_t)width*height,fp);
	fclose(fp);
	return 0;
}

//PGMファイルの読み込み
int load_pgm(char *filename, unsigned char **img, int *width, int *height)
{
	FILE *fp;
	char buff[BUFSIZE], magic[BUFSIZE];
	int maxlevel, imgsize;

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open %s\n", filename);
		return -1;
	}

	fgets(buff, BUFSIZE, fp);
	sscanf(buff, "%s", magic);
	if (strncmp(magic, "P5", 2)) {    //識別子の確認
		fprintf(stderr, "Error: %s is not raw pgm format!\n", filename);
		return -1;
	}
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //コメントをスキップ
	sscanf(buff, "%d %d", width, height);    //画像サイズの取得
	imgsize = (*width)*(*height);
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //コメントをスキップ
	sscanf(buff, "%d", &maxlevel);    //輝度レベルの取得

	(*img) = (unsigned char *)malloc(imgsize);    //画像用メモリ確保
	if(*img==NULL) {
		fprintf(stderr,"Error:cannot allocate image memory");
		fclose(fp);
		return -1;
	}
	
	fread(*img,sizeof(char),(size_t)(imgsize),fp);    //データを読み込み
	
	fclose(fp);
	return 0;
}


//PPMファイルの保存
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height)
{
	int i;
	FILE *fp;
	unsigned char *image;

	if((fp = fopen(filename,"wb"))==NULL){
		fprintf(stderr,"cannot open output PGMfile");
		return -1;
	}
	fprintf(fp,"P6\n%d %d\n255\n",width,height);	//ヘッダ出力

	image = (unsigned char *)malloc(width*height*3);
	for(i=0; i<width*height; i++) {
		image[i*3] = red[i];
		image[i*3+1] = grn[i];
		image[i*3+2] = blu[i];
	}

	fwrite(image,sizeof(char),(size_t)width*height*3,fp);
	fclose(fp);
	return 0;
}


//PPMファイルの読み込み
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height)
{
	int i;
	FILE *fp;
	char buff[BUFSIZE], magic[BUFSIZE];
	int maxlevel, imgsize;
	unsigned char *img; //画像データ一時格納用

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open %s\n", filename);
		return -1;
	}

	fgets(buff, BUFSIZE, fp);
	sscanf(buff, "%s", magic);
	if (strncmp(magic, "P6", 2)) {    //識別子の確認
		fprintf(stderr, "Error: %s is not raw pgm format!\n", filename);
		return -1;
	}
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //コメントをスキップ
	sscanf(buff, "%d %d", width, height);    //画像サイズの取得
	imgsize = (*width)*(*height);
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //コメントをスキップ
	sscanf(buff, "%d", &maxlevel);    //輝度レベルの取得


	img = (unsigned char *)malloc(imgsize*3);
	if(img==NULL) {
		fprintf(stderr,"Error:cannot allocate image memory");
		fclose(fp);
		return -1;
	}
	fread(img,sizeof(char),(size_t)(imgsize*3),fp);    //データを読み込み
	fclose(fp);

	//RGBに並べ替え
	(*red) = (unsigned char *)malloc(imgsize);    //画像用メモリ確保
	(*grn) = (unsigned char *)malloc(imgsize);    //画像用メモリ確保
	(*blu) = (unsigned char *)malloc(imgsize);    //画像用メモリ確保
	if(*red==NULL || *grn==NULL || *blu==NULL) {
		fprintf(stderr,"Error:cannot allocate image memory");
		fclose(fp);
		return -1;
	}

	for(i=0;i<imgsize;i++) {
		(*red)[i] = img[i*3];
		(*grn)[i] = img[i*3+1];
		(*blu)[i] = img[i*3+2];
	}

	return 0;
}
