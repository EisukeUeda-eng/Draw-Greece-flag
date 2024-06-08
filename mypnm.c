#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mypnm.h"

#define BUFSIZE 1024

//PGM�t�@�C���̕ۑ�
int save_pgm(char *filename, unsigned char *image, int width, int height)
{
	FILE *fp;

	if((fp = fopen(filename,"wb"))==NULL){
		fprintf(stderr,"cannot open output PGMfile");
		return -1;
	}
	fprintf(fp,"P5\n%d %d\n255\n",width,height);	//�w�b�_�o��
	fwrite(image,sizeof(char),(size_t)width*height,fp);
	fclose(fp);
	return 0;
}

//PGM�t�@�C���̓ǂݍ���
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
	if (strncmp(magic, "P5", 2)) {    //���ʎq�̊m�F
		fprintf(stderr, "Error: %s is not raw pgm format!\n", filename);
		return -1;
	}
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //�R�����g���X�L�b�v
	sscanf(buff, "%d %d", width, height);    //�摜�T�C�Y�̎擾
	imgsize = (*width)*(*height);
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //�R�����g���X�L�b�v
	sscanf(buff, "%d", &maxlevel);    //�P�x���x���̎擾

	(*img) = (unsigned char *)malloc(imgsize);    //�摜�p�������m��
	if(*img==NULL) {
		fprintf(stderr,"Error:cannot allocate image memory");
		fclose(fp);
		return -1;
	}
	
	fread(*img,sizeof(char),(size_t)(imgsize),fp);    //�f�[�^��ǂݍ���
	
	fclose(fp);
	return 0;
}


//PPM�t�@�C���̕ۑ�
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height)
{
	int i;
	FILE *fp;
	unsigned char *image;

	if((fp = fopen(filename,"wb"))==NULL){
		fprintf(stderr,"cannot open output PGMfile");
		return -1;
	}
	fprintf(fp,"P6\n%d %d\n255\n",width,height);	//�w�b�_�o��

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


//PPM�t�@�C���̓ǂݍ���
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height)
{
	int i;
	FILE *fp;
	char buff[BUFSIZE], magic[BUFSIZE];
	int maxlevel, imgsize;
	unsigned char *img; //�摜�f�[�^�ꎞ�i�[�p

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open %s\n", filename);
		return -1;
	}

	fgets(buff, BUFSIZE, fp);
	sscanf(buff, "%s", magic);
	if (strncmp(magic, "P6", 2)) {    //���ʎq�̊m�F
		fprintf(stderr, "Error: %s is not raw pgm format!\n", filename);
		return -1;
	}
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //�R�����g���X�L�b�v
	sscanf(buff, "%d %d", width, height);    //�摜�T�C�Y�̎擾
	imgsize = (*width)*(*height);
	
	fgets(buff, BUFSIZE, fp);
	while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    //�R�����g���X�L�b�v
	sscanf(buff, "%d", &maxlevel);    //�P�x���x���̎擾


	img = (unsigned char *)malloc(imgsize*3);
	if(img==NULL) {
		fprintf(stderr,"Error:cannot allocate image memory");
		fclose(fp);
		return -1;
	}
	fread(img,sizeof(char),(size_t)(imgsize*3),fp);    //�f�[�^��ǂݍ���
	fclose(fp);

	//RGB�ɕ��בւ�
	(*red) = (unsigned char *)malloc(imgsize);    //�摜�p�������m��
	(*grn) = (unsigned char *)malloc(imgsize);    //�摜�p�������m��
	(*blu) = (unsigned char *)malloc(imgsize);    //�摜�p�������m��
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
