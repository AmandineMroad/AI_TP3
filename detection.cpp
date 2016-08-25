

#include "detection.h"


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
    return out;
}
