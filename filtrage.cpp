#include "filtrage.h"
#include "detection.h"
#include "affichage.h"

IplImage* imgSobel,
       * imgCanny,
       * imgBase;



void setImages(IplImage ** array){
    imgCanny=array[POS_CANNY];
    imgSobel=array[POS_SOBEL];
    imgBase=array[POS_INIT];
}

void recalculeSobel(int pos){
        
    int x = getTrackbarPos(TB_X, SOBEL);
    int y = getTrackbarPos(TB_Y, SOBEL);
    
    if (x == 0 && y ==0){
        displayOverlay(SOBEL, "X et Y ne peuvent pas valoir 0 en meme temps", 1000);
        setTrackbarPos(TB_X, SOBEL,1);
        x =1;
    }
    
    cvSobel(imgBase, imgSobel,x,y);
    cvShowImage(SOBEL, imgSobel);
    displayResults(NULL,NULL,NULL);
    
}

void recalculeCanny(int pos){
    int min = getTrackbarPos(TB_MIN, CANNY);
    int max = getTrackbarPos(TB_MAX, CANNY);
    
    cvCanny(imgBase, imgCanny, min, max);
    cvShowImage(CANNY, imgCanny);
    soustraction(imgBase, imgCanny);
}