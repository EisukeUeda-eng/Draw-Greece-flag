// ギリシャの国旗作成

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mypnm.h"

#define WIDTH 640
#define HEIGHT 480
#if 1
int main()
{
    int i, x, y;
    unsigned char *red, *grn, *blu;

  
    red = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    grn = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    blu = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    //if(output==NULL) return -1;

    for(i = 0; i < 9; i++){
        if(i % 2 == 0){
           for(y = (HEIGHT / 9) * i; y < (HEIGHT / 9) * (i + 1); y++){
               for(x = 0; x < WIDTH; x++){
                   red[y*WIDTH+x] = 13;
                   grn[y*WIDTH+x] = 94;
                   blu[y*WIDTH+x] = 175;
               }
           }
        }
        // 奇数段目は青色
        else{
            for(y = (HEIGHT / 9) * i; y < (HEIGHT / 9) * (i + 1); y++){
                for(x = 0; x < WIDTH; x++){
                    red[y*WIDTH+x] = 255;
                    grn[y*WIDTH+x] = 255;
                    blu[y*WIDTH+x] = 255;
                }
            }
        }
        // 偶数段目は白色
    }
    // 青色と白色のの縞模様作成
    
    for(y = 0; y < HEIGHT / 9 * 5; y++){
        for(x = 0; x < HEIGHT / 9 * 5; x++){
            red[y*WIDTH+x] = 13;
            grn[y*WIDTH+x] = 94;
            blu[y*WIDTH+x] = 175;
        }
    }
    // 左上の青色の正方形の作成
    
    for(y = HEIGHT / 9 * 2; y < HEIGHT / 9 * 3; y++){
        for(x = 0; x < HEIGHT / 9 * 5; x++){
            red[y*WIDTH+x] = 255;
            grn[y*WIDTH+x] = 255;
            blu[y*WIDTH+x] = 255;
        }
    }
    // 白色の十字の横部分の作成
    
    for(x = HEIGHT / 9 * 2; x != (HEIGHT / 9 * 2) + (HEIGHT / 9); x++){
        for(y = 0; y < HEIGHT / 9 * 5; y++){
            red[y*WIDTH+x] = 255;
            grn[y*WIDTH+x] = 255;
            blu[y*WIDTH+x] = 255;
        }
    }
    // 白色の十字の縦部分の作成

    save_ppm( "Greece.ppm", red, grn, blu, WIDTH, HEIGHT ); //画像の保存

    free(red);
    free(grn);
    free(blu);
    
    return 0;
}

#endif

