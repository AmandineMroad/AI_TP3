#include "affichage.h"

IplImage**  images = new IplImage*[5];
IplImage* imgResult ;

int sobelOrderX = 1, 
        sobelOrderY = 1;
int cannySeuilMin = 0,
        cannySeuilMax = 255;

/**
 * Fixe l'image de référence
 * @param init image initiale
 */
void setBaseImage(IplImage * init){
    images[POS_INIT] = init;
}
/**
 * Fixe l'image de reference des contours
 * @param contours l'image des contours
 */
void setContoursImage(IplImage * contours){
    images[POS_CONTOURS] = contours;
}

/**
 * Renvoie l'image correspondant à la position
 * @param position l'indice de l'image
 * @return 
 */
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
    //TODO TMP
    cvNamedWindow("diff");
    initResultWindow();
    
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
    recalculeSobel(0);
    //cvShowImage(LAPLACE, images[POS_LAPLACE]);
    calculeLaplace();
    //cvShowImage(CANNY, images[POS_CANNY]);
    recalculeCanny(0);
    
}

/**
 * Initialise les images pour les transformations
 */
void initImages(){
    IplImage * imgBase = images[POS_INIT];
    
    CvSize size = cvSize(imgBase->width, imgBase->height);
    int depth = imgBase->depth;
    int nChannels = imgBase->nChannels;
    
    //Creation et initialisation des images modifiees
    images[POS_SOBEL] = cvCreateImage( size, depth, nChannels);
    cvSobel(imgBase, images[POS_SOBEL], sobelOrderX, sobelOrderY);
    images[POS_LAPLACE] = cvCreateImage( size, depth, nChannels);
    cvLaplace(imgBase, images[POS_LAPLACE]);
    images[POS_CANNY] =cvCreateImage( size, depth, nChannels);
    cvCanny(imgBase, images[POS_CANNY], cannySeuilMin, cannySeuilMax);
}

/** Variables pour affichage des résultats **/
CvFont font = cvFont(1);
CvScalar white = cvScalar(255,255,255,0);
CvScalar black = cvScalar(0,0,0,0);

//point pour écriture des résultats
CvPoint pt_res_sobel_perf = cvPoint(PT_ABS_RESULT, PT_ORD_SOBEL_PERF);
CvPoint pt_res_sobel_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_SOBEL_FP);
CvPoint pt_res_sobel_tfn = cvPoint(PT_ABS_RESULT,PT_ORD_SOBEL_FN);

CvPoint pt_res_canny_perf =cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_PERF);
CvPoint pt_res_canny_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_FP);
CvPoint pt_res_canny_tfn = cvPoint(PT_ABS_RESULT, PT_ORD_CANNY_FN);

CvPoint pt_res_laplace_perf = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_PERF);
CvPoint pt_res_laplace_tfp = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_FP);
CvPoint pt_res_laplace_tfn = cvPoint(PT_ABS_RESULT, PT_ORD_LAPLACE_FN);

/**
 * Affiche les resultats de la detection de contours
 * @param sobelResult   les stats de sobel
 * @param cannyResult   les stats de canny
 * @param laplaceResult les stats de laplace
 */
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

/**
 * Ecrit la valeur des taux calculés
 * @param result    les stats à afficher
 * @param pt_perf   point où écrire le tx de performances
 * @param pt_fp     point où écrire le tx de faux positifs
 * @param pt_fn     point où écrire le tx de faux negatifs
 */
void putResultText(ContoursStats* result, CvPoint pt_perf, CvPoint pt_fp, CvPoint pt_fn){
    erasePreviousResult(pt_perf);
    cvPutText(imgResult, result->GetPerfString(), pt_perf, &font, white);
    erasePreviousResult(pt_fp);
    cvPutText(imgResult, result->GetTxFauxPosString(), pt_fp, &font, white);
    erasePreviousResult(pt_fn);
    cvPutText(imgResult, result->GetTxFauxNegString(), pt_fn, &font, white);
}

/**
 * Efface la zone de résultat correspondant au point pt
 * @param pt le point déterminant la "ligne" à effcer
 */
void erasePreviousResult(CvPoint pt){
    cvRectangle(imgResult, cvPoint(pt.x, pt.y-15), cvPoint(LARGEUR_FENETRE,pt.y),black,-1);
}

/**
 * Initialise la fenêtre d'affichage des résultats.
 * Sépare les blocs et écrit les titres
 */
void initResultWindow(){
    cvNamedWindow(RESULTS);
    imgResult = cvCreateImage(cvSize(LARGEUR_FENETRE,HAUTEUR_FENETRE), IPL_DEPTH_8U, 1);
    
    cvPutText(imgResult, SOBEL, cvPoint(PT_ABS_TITRE, PT_ORD_SOBEL_TITRE), &font, white);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_PERF), &font, white);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_FP), &font, white);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_SOBEL_FN), &font, white);
    
    cvLine(imgResult,cvPoint(0,HAUTEUR_BLOC), cvPoint(LARGEUR_FENETRE, HAUTEUR_BLOC), white);
    cvPutText(imgResult, CANNY, cvPoint(PT_ABS_TITRE, PT_ORD_CANNY_TITRE), &font, white);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_PERF), &font, white);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_FP), &font, white);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_CANNY_FN), &font, white);
    
    cvLine(imgResult,cvPoint(0,2*HAUTEUR_BLOC), cvPoint(LARGEUR_FENETRE, 2*HAUTEUR_BLOC), white);
    cvPutText(imgResult, LAPLACE, cvPoint(PT_ABS_TITRE, PT_ORD_LAPLACE_TITRE), &font, white);
    cvPutText(imgResult, PERF, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_PERF), &font, white);
    cvPutText(imgResult, TX_FP, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_FP), &font, white);
    cvPutText(imgResult, TX_FN, cvPoint(PT_ABS_TAUX, PT_ORD_LAPLACE_FN), &font, white);
}