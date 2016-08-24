#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>


#include "affichage.h"


using namespace std;
using namespace cv;


/* Fonctions*/
int checkArgs(int nbArgs, char** args);

void changeState(int state, void * nom);

    
/* Attributs */







int main(int argc, char** argv) {
    //Vérification de la validité des arguments
    if (checkArgs(argc, argv)) return EXIT_FAILURE;
    
    //Initialisation des fenetres
    initFenetre();
    
    
    cvWaitKey(0);
    return EXIT_SUCCESS;
}
/**
 * Verifie la validité des arguments
 * @param nbArgs le nombre d'arguments passés
 * @param args les arguments
 * @return 0 si les arguments sont valides, EXIT_FAILURE sinon;
 */
int checkArgs(int nbArgs, char** args){
    //Verification du nombre d'arguments
    if (nbArgs != 3){
        cerr << "Utilisation: \n\t contours <nom_fichier_image> <nom_fichier_contour>\n";
            return EXIT_FAILURE;
    }
    
    //Chargement des images
    IplImage * tmp = cvLoadImage(args[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (tmp == 0){
        cerr << "Impossible de lire : " << args[1] << "\n";
            return EXIT_FAILURE;
    }
    setBaseImage(cvCloneImage(tmp));
    
    tmp = cvLoadImage(args[2], CV_LOAD_IMAGE_GRAYSCALE);
    if (tmp == 0){
      cerr << "Impossible de lire : " << args[2] << "\n";
            return EXIT_FAILURE;  
    }
    setContoursImage(cvCloneImage(tmp));
    
    //Vérification de la taille des images
    if (getImage(POS_CONTOURS) ->imageSize != getImage(POS_INIT) ->imageSize){
        cerr <<args[1]<< " et " << args[2] << "n'ont pas la meme taille. Traitement impossible.\n";
            return EXIT_FAILURE;
    }
    return 0;
}



