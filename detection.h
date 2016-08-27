#ifndef DETECTION_H
#define	DETECTION_H

#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

#include "constantes.h"
#include "ContoursStats.h"


IplImage * soustraction (IplImage * base, IplImage * filtree);

int getNbContours(const IplImage * image);
int getNbContoursCorrects(const IplImage * imageRef, const IplImage * image);

#endif	/* DETECTION_H */

