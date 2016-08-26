
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>

#include "affichage.h"


IplImage**  images = new IplImage*[5];
IplImage* imgResult ;


int sobelOrderX = 1, 
        sobelOrderY = 1;
int cannySeuilMin = 0,
        cannySeuilMax = 255;

void setBaseImage(IplImage * init){
    images[POS_INIT] = init;
}
void setContoursImage(IplImage * contours){
    images[POS_CONTOURS] = contours;
}

IplImage * getImage(int position){
    return images[position];
}


/**
 * Initialise les fenêtres, y insère les images et ajoute les trackbars
 */
void initFenetre(){
    //Affichage de l'image initiale
    cvNamedWindow(INIT);
    cvShowImage(INIT, images[POS_INIT]);
    
    //Création des fenetres
    cvNamedWindow(SOBEL);
    cvNamedWindow(LAPLACE);
    cvNamedWindow(CANNY);
    cvNamedWindow(RESULTS);
    cvResizeWindow(RESULTS, 600, 600);
    
    //Positionnement des fenetres
    cvMoveWindow(INIT, 0,0);
    cvMoveWindow(SOBEL, 20,20);
    cvMoveWindow(LAPLACE, 40,40);
    cvMoveWindow(CANNY, 60,60);
    
    //Ajout des trackbar
    
    cvCreateTrackbar(TB_X,SOBEL,&sobelOrderX,2,recalculeSobel);
    cvCreateTrackbar(TB_Y,SOBEL,&sobelOrderY,2,recalculeSobel);

    cvCreateTrackbar(TB_MIN, CANNY, &cannySeuilMin, 255,recalculeCanny);
    cvCreateTrackbar(TB_MAX,CANNY, &cannySeuilMax, 255,recalculeCanny);
    
    //Insertion des images
    initImages();
    cvShowImage(SOBEL, images[POS_SOBEL]);
    cvShowImage(LAPLACE, images[POS_LAPLACE]);
    cvShowImage(CANNY, images[POS_CANNY]);
    
    //Settings
    createSettings();
    
}

/**
 * Initialise les images pour les transformations
 */
void initImages(){
    IplImage * imgBase = images[POS_INIT];
    //Creation et initialisation des images modifiees
    CvSize size = cvSize(imgBase->width, imgBase->height);
    int depth = imgBase->depth;
    int nChannels = imgBase->nChannels;
    
    images[POS_SOBEL] = cvCreateImage( size, depth, nChannels);
    cvSobel(imgBase, images[POS_SOBEL], sobelOrderX, sobelOrderY);
    images[POS_LAPLACE] = cvCreateImage( size, depth, nChannels);
    cvLaplace(imgBase, images[POS_LAPLACE]);
    images[POS_CANNY] =cvCreateImage( size, depth, nChannels);
    cvCanny(imgBase, images[POS_CANNY], cannySeuilMin, cannySeuilMax);
    
}

void createSettings(){
    //TODO
    createButton("bouton sobel", changeWindowState, (void * ) SOBEL,QT_CHECKBOX, true);
}

void hideWindow(const char * name){
    if (DEBUG) cout<<"hide "<<(const char *)name<<endl;
    cvSaveWindowParameters(name);
    cvDestroyWindow(name);
}

void displayWindow(const char * name){
    if (DEBUG) cout<<"display "<<(const char *)name<<endl;
    
    IplImage * img = NULL;
    
    if (strcmp(name, SOBEL) == 0){
         img = images[POS_SOBEL];
    } else if (strcmp(name, LAPLACE) == 0){
        img = images[POS_LAPLACE];
    } else if (strcmp(name, CANNY) == 0){
        img = images[POS_CANNY];
    }
    
    cvNamedWindow(name);
    cvShowImage(name, img); //FIXME doesn't work at all !!
    cvLoadWindowParameters(name);
    if (DEBUG) cout<<"waiting ... "<<endl;
    cvWaitKey();
    if (DEBUG) cout<<"stop waiting"<<endl;
}

void changeWindowState(int i, void * name){
if (DEBUG) cout<<"change window state of : "<<(const char *)name<<" _ i = "<<i<<endl;
     if (i == 0){
         hideWindow((const char *)name);
     } else {
         displayWindow((const char *)name);
     }
     
}

CvFont font = cvFont(1);
CvScalar color = cvScalar(255,255,255,0);


CvPoint pt_res_sobel_perf = cvPoint(PT_ABS_RESULT, PT_ORD_SOBEL_PERF);
CvPoint pt_res_sobel_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_SOBEL_FP);
CvPoint pt_res_sobel_tfn = cvPoint(PT_ABS_RESULT,PT_ORD_SOBEL_FN);

CvPoint pt_res_canny_perf =cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_PERF);
CvPoint pt_res_canny_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_FP);
CvPoint pt_res_canny_tfn = cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_FN);

CvPoint pt_res_laplace_perf = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_PERF);
CvPoint pt_res_laplace_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_FP);
CvPoint pt_res_laplace_tfn = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_FN);

void displayResults(ContoursStats* sobelResult, ContoursStats*cannyResult , ContoursStats*laplaceResult ){
    if (sobelResult != NULL){
        putResultText(sobelResult, pt_res_sobel_perf, pt_res_sobel_tfp, pt_res_sobel_tfn);
    }
    if (cannyResult != NULL){
        putResultText(cannyResult, pt_res_canny_perf, pt_res_canny_tfp, pt_res_canny_tfn);
    }
    if (laplaceResult != NULL){
        putResultText(laplaceResult, pt_res_laplace_perf, pt_res_laplace_tfp, pt_res_laplace_tfn);
    }
    
    cvShowImage(RESULTS, imgResult);
}

void putResultText(ContoursStats* result, CvPoint pt_perf, CvPoint pt_fp, CvPoint pt_fn){
    cvPutText(imgResult, result->GetPerfString(), pt_res_sobel_perf, &font, color);
    cvPutText(imgResult, result->GetTxFauxPosString(), pt_res_sobel_tfp, &font, color);
    cvPutText(imgResult, result->GetTxFauxNegString(), pt_res_sobel_tfn, &font, color);
}

void initResultWindow(){
    cvNamedWindow(RESULTS);
    imgResult = cvCreateImage(cvSize(LARGEUR_FENETRE,HAUTEUR_FENETRE), IPL_DEPTH_8U, 1);
    
    cvPutText(imgResult, SOBEL, cvPoint(PT_ABS_TITRE, PT_ORD_SOBEL_TITRE), &font, color);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_PERF), &font, color);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_FP), &font, color);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_FN), &font, color);
    
    cvLine(imgResult,cvPoint(0,HAUTEUR_BLOC), cvPoint(LARGEUR_FENETRE, HAUTEUR_BLOC), color);
    cvPutText(imgResult, CANNY, cvPoint(PT_ABS_TITRE, PT_ORD_CANNY_TITRE), &font, color);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_PERF), &font, color);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_FP), &font, color);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_FN), &font, color);
    
    cvLine(imgResult,cvPoint(0,2*HAUTEUR_BLOC), cvPoint(LARGEUR_FENETRE, 2*HAUTEUR_BLOC), color);
    cvPutText(imgResult, LAPLACE, cvPoint(PT_ABS_TITRE, PT_ORD_LAPLACE_TITRE), &font, color);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_PERF), &font, color);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_FP), &font, color);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_FN), &font, color);
}