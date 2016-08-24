
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
IplImage *img, *imgSobel, *imgLaplace, *imgCanny, *imgReference, *imgGauss;
int seuil_sobel = 70;
int seuil_laplace = 125;
int seuil_canny_bas=50, seuil_canny_haut =100;

//Compte le nombre de pixels contours dans l'image
// (à appeler sur l'image calculée et celle de référence)
float contours(IplImage *in){
	float compteur =0;
	CvScalar v;

	//On parcourt toute l'image,
	for(int i = 0; i < in->height; i++){
		for(int j = 0; j < in->width; j++){
		//Si le pixel est noir on le compte
			v = cvGet2D(in, i, j);
			if( v.val[0] == 0) compteur ++;
		}
	}
        

	return compteur;
}

//Compte combien de contours ont étés correctement trouvés
//cad pour chaque pixel dans l'image de référence est ce qu'il y'en a un au même endroit (au voisinage près)
float contours_corrects(IplImage *calculee, IplImage *reference){
	float compteur = 0;
	CvScalar v, voisin;
	bool correspond;
	
	//On parcourt toute l'image,
	for(int i = 1; i < reference->height; i++){
		for(int j = 1; j < reference->width; j++){
			correspond = false;
			v = cvGet2D(reference, i, j);
			//Si ce pixel est noir dans l'image de reference
			if( v.val[0] == 0){
				//Est ce qu'il y en a un noir aussi au voisinage de sa position dans l'image calculée
				for(int k=-1; k<2;k++){
					for(int l=-1; l<2; l++){
						voisin= cvGet2D(calculee, i+k, j+l);
						if(voisin.val[0] == 0) {
							correspond = true;
							break; //dès qu'on en trouve un plus besoin de tester les autres
						}
					}
				}
				if(correspond) compteur++;
			}
		}
	}

	return compteur;
}

//Applique un seuil
IplImage* seuiller(IplImage *in, int seuil){
	IplImage* out = cvCreateImage( cvGetSize(in), IPL_DEPTH_8U, 1 );
    CvScalar v;
	
	for(int i = 0; i < in->height; i++){
		for(int j = 0; j < in->width; j++){
			v = cvGet2D(in, i, j);
			if( v.val[0] < seuil )
				v.val[0] = 255;
			else
				v.val[0] = 0;
			cvSet2D(out, i, j, v);
		}
	}
	return out;
}

//Soustraction d'images
IplImage* soustraction(IplImage *in1, IplImage*in2){
	IplImage* out = cvCreateImage( cvGetSize(in1), IPL_DEPTH_8U, 1 );
	CvScalar v1, v2, vout;
	int diff;

	for(int i = 0; i < in1->height; i++){
		for(int j = 0; j < in1->width; j++){
			v1 = cvGet2D(in1, i, j);
			v2 = cvGet2D(in2, i, j);

			diff = v1.val[0] - v2.val[0];
			if(diff < 0) diff = 0;
			vout.val[0] = diff;

			cvSet2D(out, i, j, vout);
		}
	}
	return out;
}

//Sobel
IplImage* sobel(IplImage* in){
    IplImage* out = cvCreateImage( cvGetSize(in), IPL_DEPTH_8U, 1 );
    CvScalar v;
	int dx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int dy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	/* Filtre de Prewitt, pour tester
	int dx[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1}};
	int dy[3][3] = {{-1,-1,-1},{0,0,0},{1,1,1}};*/

	int sx, sy, somme;
	for(int i = 1; i < in->height-2; i++){
		for(int j = 1; j < in->width-2; j++){
			//Initialisation de la somme
			sx = 0;
			sy = 0;
			//Parcours des voisins centrés sur le pixel (i,j)
			for(int voisin_h = -1; voisin_h <= 1; voisin_h++){
				for(int voisin_v = -1; voisin_v <= 1; voisin_v++){
					//On récupère la valeur du voisin
					v = cvGet2D(in, i+voisin_h, j+voisin_v);
					//On met à jour la somme
					//les (+1) sont là pour ne pas avoir d'indice négatif
					sx += (int)v.val[0] * dx[voisin_h+1][voisin_v+1]; 
					sy += (int)v.val[0] * dy[voisin_h+1][voisin_v+1]; 
				}
			}
			//somme = abs(sx)+abs(sy); Donne approximativement le même résultat que la méthode sqrt des carrés pour une complexité /2
			somme = sqrt( (sx*sx)+(sy*sy) );
			if( somme > 255 ) v.val[0] = 255;
			else v.val[0] = somme;
			cvSet2D(out, i, j, v);
		}
	}
	out = seuiller(out,seuil_sobel);
    return out;
}

//Laplace
IplImage* laplace(IplImage* in){
    IplImage* out = cvCreateImage( cvGetSize(in), IPL_DEPTH_8U, 1 );

	cvLaplace(in,out,3);
    
   	out = seuiller(out, seuil_laplace);
    return out;
}

//Canny 
IplImage* canny(IplImage* in){
	int seuil_bas, seuil_haut, ouverture;
	ouverture =3; //taille du noyau

	IplImage* out = cvCreateImage( cvGetSize(in), IPL_DEPTH_8U, 1 );

	//Canny prend 2 seuils : Si l'amplitude du gradient dépasse le seuil haut, alors l'algo trace un contour
	// dans cette direction, jusqu'à ce que l'amplitude tombe en dessous du seuil bas ou que le gradient change de direction
	cvCanny( in, out, seuil_canny_bas, seuil_canny_haut, ouverture);
	out = seuiller(out, 255);

	return out;
}	

//Libération de l'espace mémoire
void detruireFenetres()
{
    cvDestroyWindow( "image" );
    cvDestroyWindow( "sobel" );
    cvDestroyWindow( "laplace" );
    cvDestroyWindow( "canny" );
    cvDestroyWindow( "reference" );
}

//Stats entre l'image de contours qu'on calcule et celle de reference
void mesures(IplImage *calculee, IplImage *reference, char *nomFiltre){
	//Nombre de pixels de contours dans l'image calculée
	float contoursDetectes = contours(calculee);
	//Nombre de pixels de contours dans l'image de reference
	float contoursReference = contours(reference);
	//Nombre de pixels contours correctement détectés dans l'image calculée	par rapport à l'image de ref
	float contoursCorrects = contours_corrects(calculee, reference);
	//Nombre de pixels detectés comme contours mais non contours dans l'image ref
	float fauxPositifs = contoursDetectes - contoursCorrects;
	//Nombre de pixels contours non détectés dans l'image calculée mais contours dans l'image de ref
	float fauxNegatifs = contoursReference - contoursCorrects;

	float performance = (float)(contoursCorrects/(contoursCorrects+fauxPositifs+fauxNegatifs)); 
	float TFP = (float)(fauxPositifs/(contoursCorrects+fauxPositifs+fauxNegatifs));
	float TFN = (float)(fauxNegatifs/(contoursCorrects+fauxPositifs+fauxNegatifs));

	printf("------ Stats pour %s ------\n", nomFiltre);
	printf("%.0f contours détectés\n", contoursDetectes);
	printf("%.0f contours reference\n", contoursReference);
	printf("%.0f contours corrects \n", contoursCorrects);
	printf("%.0f faux positifs \n", fauxPositifs);
	printf("%.0f faux negatifs \n", fauxNegatifs);
	printf("performance = %.2f %%\nTaux faux positifs = %.2f %%\nTaux faux negatifs = %.2f %%\n",performance*100,TFP*100,TFN*100);
	printf("\n");

}

//Les trackbars rappellent les algos sur l'image
void on_trackbar_sobel(int, void* ) {
	imgSobel = sobel(imgGauss);
	cvShowImage( "sobel", imgSobel);
	mesures(imgSobel, imgReference, (char*)"Sobel");	
}

void on_trackbar_canny(int, void* ) {
	imgCanny = canny(imgGauss);
	cvShowImage( "canny", imgCanny);
	mesures(imgCanny, imgReference, (char*)"Canny");
}

void on_trackbar_laplace(int, void* ) {
	imgLaplace = laplace(img);
	cvShowImage( "laplace", imgLaplace);
	mesures(imgLaplace, imgReference,(char*)"Laplace");
}

int main( int argc, char** argv )
{
	//le nom pour aller chercher l'image de base et celle de contours de référence en même temps
    char fic[1024];

    //Vérification des arguments
    if( argc < 2 ) {
        fprintf( stderr, "Utilisation: Contours <image>\n" );
        return 1;
    }
    
    //Chargement de l'image d'origine
    sprintf(fic, "%s.jpg", argv[1]);
    img = cvLoadImage( fic, CV_LOAD_IMAGE_GRAYSCALE );
    if( img == 0 ) {
		fprintf( stderr, "Impossible de lire : %s!\n", argv[1] );
        return 1;
    }

    printf("Deplacez une trackbar pour changer les valeurs de seuil et calculer les statistiques\n");
    //On diminue un peu le bruit sur l'image de base
    imgGauss = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 );
	cvSmooth( img, imgGauss, CV_GAUSSIAN, 11, 11 );

    //Affichage de l'image d'origine
    cvNamedWindow( "image", CV_WINDOW_NORMAL);
    cvMoveWindow("image", 475, 0);
    cvShowImage( "image", img );

    //Image de référence   
	sprintf(fic, "%s_gt_binary.jpg", argv[1]);
	imgReference = cvLoadImage( fic, CV_LOAD_IMAGE_GRAYSCALE );
    cvNamedWindow("reference", CV_WINDOW_NORMAL);
    cvMoveWindow("reference", 1000, 0);
    cvShowImage( "reference", imgReference);

    //Sobel (sur l'image floutée pour une meilleure detection)
    imgSobel = sobel(imgGauss);
    cvNamedWindow("sobel", CV_WINDOW_NORMAL);
    cvMoveWindow("sobel", 0, 600);
    cvShowImage( "sobel", imgSobel);

    //Laplace (sur l'image floutée pour une meilleure detection)
    imgLaplace = laplace(img);
    cvNamedWindow("laplace", CV_WINDOW_NORMAL);
    cvMoveWindow("laplace", 475, 600);
    cvShowImage( "laplace", imgLaplace);

    //Canny
    imgCanny = canny(imgGauss);
    cvNamedWindow("canny", CV_WINDOW_NORMAL);
    cvMoveWindow("canny", 900, 600);
    cvShowImage( "canny", imgCanny);
	
	//Gestion des trackbars pour changer les valeurs de seuil à la volée
	createTrackbar("Valeur de seuil","sobel", &seuil_sobel, 255, on_trackbar_sobel);
	createTrackbar("Valeur de seuil","laplace", &seuil_laplace, 255, on_trackbar_laplace);
	createTrackbar("Seuil bas","canny", &seuil_canny_bas, 255, on_trackbar_canny);
	createTrackbar("Seuil haut","canny", &seuil_canny_haut, 255, on_trackbar_canny);

	cvResizeWindow("image", 400, 400);
	cvResizeWindow("reference", 400, 400);
	cvResizeWindow("sobel", 400, 400);
	cvResizeWindow("laplace", 400, 400);
	cvResizeWindow("canny", 400, 400);

	mesures(imgSobel, imgReference, (char*)"Sobel");
	mesures(imgLaplace, imgReference,(char*)"Laplace");	
   	mesures(imgCanny, imgReference, (char*)"Canny");

    //Temporisation (attends qu'une touche soit tapée)   
    cvWaitKey(0);

    //Libération de l'espace mémoire
    detruireFenetres();   
    cvReleaseImage( &img );
    cvReleaseImage( &imgSobel );
    cvReleaseImage( &imgLaplace );
    cvReleaseImage( &imgCanny );
    cvReleaseImage( &imgReference );
    
    return 0;
}
