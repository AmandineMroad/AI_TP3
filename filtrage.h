
#ifndef FILTRAGE_H
#define	FILTRAGE_H

#include "constantes.h"
#include "detection.h"
#include "affichage.h"

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/types_c.h>

using namespace std;
using namespace cv;

void initResultsObjects();

void calculeLaplace();
void recalculeSobel(int pos);
void recalculeCanny(int pos);

#endif	/* FILTRAGE_H */
