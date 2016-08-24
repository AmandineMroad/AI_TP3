/* 
 * File:   constantes.h
 * Author: amandine
 *
 * Created on 23 août 2016, 22:54
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H

/*      Mode debug      */
const bool DEBUG = true;

/*      Noms des fenetres    */
#ifndef FENETRES
#define FENETRES
    const char * const SOBEL = "Sobel";
    const char * const LAPLACE = "Laplace";
    const char * const CANNY = "Canny";
    const char * const INIT = "Image initiale";
#endif

#ifndef TRACKBARS
#define TRACKBARS
    const char * const TB_X = "sobelX";
    const char * const TB_Y = "sobelY";
    const char * const TB_MIN = "cannyMin";
    const char * const TB_MAX = "cannyMax";
    
#endif


/*      Positions des images dans le tableau contours.images*/
enum{
    POS_INIT=0, POS_SOBEL=1,  POS_LAPLACE=2, POS_CANNY=3, POS_CONTOURS=4
};

#endif	/* CONSTANTES_H */

