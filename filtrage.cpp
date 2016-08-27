#include "filtrage.h"

/*ContoursStats* resultSobel = new ContoursStats(getImage(POS_CONTOURS));
ContoursStats* resultCanny = new ContoursStats(getImage(POS_CONTOURS));
ContoursStats* resultLaplace= new ContoursStats(getImage(POS_CONTOURS));
*/
ContoursStats* resultSobel ;
ContoursStats* resultCanny ;
ContoursStats* resultLaplace;

void initResultsObjects(){
    resultSobel = new ContoursStats(getImage(POS_INIT),getImage(POS_CONTOURS));
    resultCanny = new ContoursStats(getImage(POS_INIT),getImage(POS_CONTOURS));
    resultLaplace= new ContoursStats(getImage(POS_INIT),getImage(POS_CONTOURS));
}

void recalculeSobel(int pos){
        if (DEBUG) cout<<"recalculeSobel"<<endl;
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
    displayResults(resultSobel->getResults(imgSobel), NULL);
    
}

void recalculeCanny(int pos){
    if (DEBUG) cout<<"recalculeCanny"<<endl;
    int min = getTrackbarPos(TB_MIN, CANNY);
    int max = getTrackbarPos(TB_MAX, CANNY);
    IplImage * imgCanny = getImage(POS_CANNY);
    cvCanny(getImage(POS_INIT), imgCanny, min, max);
    cvShowImage(CANNY, imgCanny);
    displayResults(NULL,resultCanny->getResults(imgCanny));
}

void calculeLaplace(){
    IplImage * imgLaplace = getImage(POS_LAPLACE);
    cvShowImage(LAPLACE, imgLaplace);
    displayResults(NULL,NULL, resultLaplace->getResults(imgLaplace));
}