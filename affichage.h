/* 
 * File:   affichage.h
 * Author: amandine
 *
 * Created on 23 août 2016, 22:52
 */

#ifndef AFFICHAGE_H
#define	AFFICHAGE_H

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types_c.h>


#include "filtrage.h"
#include "Result.h"

using namespace cv;

void setBaseImage(IplImage * init);
void setContoursImage(IplImage * contours);
IplImage * getImage(int position);

void initFenetre();
void initImages();
void createSettings();

void displayWindow(char * name);
void hideWindow(char * name);

void changeWindowState(int i, void * name);

void displayResults(Result sobelResult, Result laplaceResult, Result cannyResult);

#endif	/* AFFICHAGE_H */

