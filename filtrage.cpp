#include "filtrage.h"

ContoursStats* resultSobel = new ContoursStats(getImage(POS_CONTOURS));
ContoursStats* resultCanny = new ContoursStats(getImage(POS_CONTOURS));
ContoursStats* resultLaplace= new ContoursStats(getImage(POS_CONTOURS));

void recalculeSobel(int pos){
        
    int x = getTrackbarPos(TB_X, SOBEL);
    int y = getTrackbarPos(TB_Y, SOBEL);
    
    if (x == 0 && y ==0){
        displayOverlay(SOBEL, "X et Y ne peuvent pas valoir 0 en meme temps", 1000);
        setTrackbarPos(TB_X, SOBEL,1);
        x =1;
    }
    IplImage * imgSobel = getImage(POS_SOBEL);
    cvSobel(getImage(POS_INIT), imgSobel,x,y);
    cvShowImage(SOBEL, imgSobel);
    displayResults(getStat(imgSobel, resultSobel), NULL);
    
}

void recalculeCanny(int pos){
    int min = getTrackbarPos(TB_MIN, CANNY);
    int max = getTrackbarPos(TB_MAX, CANNY);
    IplImage * imgCanny = getImage(POS_CANNY);
    cvCanny(getImage(POS_INIT), imgCanny, min, max);
    cvShowImage(CANNY, imgCanny);
    displayResults(NULL,getStat(imgCanny, resultCanny));
}