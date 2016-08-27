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
    const char * const SOBEL = "Sobel";
    const char * const LAPLACE = "Laplace";
    const char * const CANNY = "Canny";
    const char * const INIT = "Image initiale";
    const char * const RESULTS = "Resultats";

/*      Trackbars   */
    const char * const TB_X = "sobelX";
    const char * const TB_Y = "sobelY";
    const char * const TB_MIN = "cannyMin";
    const char * const TB_MAX = "cannyMax";
    
/*      Positions des images dans le tableau contours.images*/
enum{
    POS_INIT=0, POS_SOBEL=1,  POS_LAPLACE=2, POS_CANNY=3, POS_CONTOURS=4
};

/*      Texte resultats     */
const char * const PERF = "- Performance :";
const char * const TX_FP = "- Taux de faux positifs :";
const char * const TX_FN = "- Taux de faux negatifs :";

/*      Points resultats    */
const int HAUTEUR_FENETRE = 240;
const int LARGEUR_FENETRE = 400;
const int HAUTEUR_BLOC = HAUTEUR_FENETRE/3;
const int PT_ABS_RESULT = 250;
const int PT_ABS_TITRE = 10;
const int PT_ABS_TAUX = 20;
const int PT_ORD_SOBEL_TITRE = 15;
const int PT_ORD_SOBEL_PERF = 30;
const int PT_ORD_SOBEL_FP = 45;
const int PT_ORD_SOBEL_FN = 60;
const int PT_ORD_CANNY_TITRE = PT_ORD_SOBEL_TITRE+HAUTEUR_BLOC;
const int PT_ORD_CANNY_PERF = PT_ORD_SOBEL_PERF+HAUTEUR_BLOC;
const int PT_ORD_CANNY_FP = PT_ORD_SOBEL_FP + HAUTEUR_BLOC;
const int PT_ORD_CANNY_FN = PT_ORD_SOBEL_FN + HAUTEUR_BLOC;
const int PT_ORD_LAPLACE_TITRE = PT_ORD_CANNY_TITRE+HAUTEUR_BLOC;
const int PT_ORD_LAPLACE_PERF = PT_ORD_CANNY_PERF+HAUTEUR_BLOC;
const int PT_ORD_LAPLACE_FP = PT_ORD_CANNY_FP + HAUTEUR_BLOC;
const int PT_ORD_LAPLACE_FN = PT_ORD_CANNY_FN + HAUTEUR_BLOC;

#endif	/* CONSTANTES_H */

