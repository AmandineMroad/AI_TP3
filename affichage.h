/* 
 * File:   affichage.h
 * Author: amandine
 *
 * Created on 23 août 2016, 22:52
 */

#ifndef AFFICHAGE_H
#define	AFFICHAGE_H

#include "filtrage.h"
#include "ContoursStats.h"

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types_c.h>

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

void initResultWindow();
void displayResults(ContoursStats* sobelResult, ContoursStats*cannyResult , ContoursStats*laplaceResult=NULL);
void putResultText(ContoursStats* result, CvPoint pt_perf, CvPoint pt_fp, CvPoint pt_fn);
void erasePreviousResult(CvPoint pt);
#endif	/* AFFICHAGE_H */

