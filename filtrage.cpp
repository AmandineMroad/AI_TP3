#include "filtrage.h"
#include "detection.h"

IplImage* imgSobel,
       * imgCanny,
       * imgBase;



void setImages(IplImage ** array){
    imgCanny=array[POS_CANNY];
    imgSobel=array[POS_SOBEL];
    imgBase=array[POS_INIT];
}

int echo(){
    return 10;
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
    
    
}

void recalculeCanny(int pos){
    int min = getTrackbarPos(TB_MIN, CANNY);
    int max = getTrackbarPos(TB_MAX, CANNY);
    
    cvCanny(imgBase, imgCanny, min, max);
    cvShowImage(CANNY, imgCanny);
    soustraction(imgBase, imgCanny);
}



IplImage * soustraction (IplImage * base, IplImage * filtree){
    CvScalar val1, val2, valOut;
    IplImage * out = cvCreateImage(cvGetSize(base), IPL_DEPTH_8U, 1);
    int diff,
            width = base->width,
            height=base->height;
    int i,j;
    for (i = 0; i<width; i++){
        for(j=0; j<height; j++){
            val1 = cvGet2D(base,i,j);
            val2 = cvGet2D(filtree, i, j);
            
            diff = val1.val[0] - val2.val[0];
            if (diff < 0) { diff = 0; }
            valOut.val[0] = diff;
            
            cvSet2D(out, i, j, valOut);
        }
    }
    
    if(DEBUG){
        cvNamedWindow("contours calculés");
        cvShowImage("contours calculés",out);
    }
    
    return out;
}




void test(int a, void * gz){
    cout<<echo()<<endl;
}