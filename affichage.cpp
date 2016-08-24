
#include <opencv2/highgui/highgui_c.h>

#include "affichage.h"


IplImage**  images = new IplImage*[5];

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
    
    setImages(images);
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

