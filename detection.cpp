
#include "detection.h"

IplImage * soustraction(IplImage * base, IplImage * filtree) {
    CvScalar val1, val2, valOut;
    IplImage * out = cvCreateImage(cvGetSize(base), IPL_DEPTH_8U, 1);
    int diff,
            width = base->width,
            height = base->height;

    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            val1 = cvGet2D(base, i, j);
            val2 = cvGet2D(filtree, i, j);

            diff = val1.val[0] - val2.val[0];
            if (diff < 0) {
                diff=0;
            } else {
                diff = 255;
            }
                valOut.val[0] = diff;
            cvSet2D(out, i, j, valOut);
        }
    }
    return out;
}

int getNbContours(const IplImage * image) {
    float nbContours = 0;
    CvScalar vect;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            //Comptage pixel noir
            vect = cvGet2D(image, i, j);
            if (vect.val[0] == 0) nbContours++;
        }
    }
    return nbContours;
}

int getNbContoursCorrects(const IplImage * imageRef, const IplImage * image) {
    float nbCorrects = 0;
    CvScalar vect,
            voisin;
    bool correspond;

    int height = imageRef->height,
            width = imageRef->width;

    //Parcours de l'image            
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            correspond = false;
            vect = cvGet2D(imageRef, i, j);
            //Si pixel noir dans imageRef
            if (vect.val[0] == 0) {
                //Verification du voisinage de l'image
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        voisin = cvGet2D(image, i + k, j + l);
                        if (voisin.val[0] == 0) {
                            correspond = true;
                            break;
                        }
                    }
                    if (correspond) {
                        break;
                    }
                }
                if (correspond) {
                    nbCorrects++;
                }
            }
        }
    }

    return nbCorrects;
}