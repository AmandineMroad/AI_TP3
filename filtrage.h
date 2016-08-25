/* 
 * File:   filtrage.h
 * Author: amandine
 *
 * Created on 23 août 2016, 22:42
 */

#ifndef FILTRAGE_H
#define	FILTRAGE_H

#include "constantes.h"


#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/types_c.h>

using namespace std;
using namespace cv;

void setImages(IplImage ** array);

void recalculeSobel(int pos);
void recalculeCanny(int pos);




#endif	/* FILTRAGE_H */

