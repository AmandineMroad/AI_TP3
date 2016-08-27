#ifndef RESULT_H
#define	RESULT_H

#include <iostream>
#include <sstream>
#include <opencv/cv.h>

using namespace std;

class ContoursStats {
public:
    ContoursStats(IplImage * imageBase, IplImage * imageContours);

    float GetPerf() ;
    float GetTxFauxNeg() ;
    float GetTxFauxPos() ;
    int GetFauxNegatifs() const;
    int GetFauxPositifs() const;
    int GetContoursCorrects() const;
    const int GetContoursReference() const;
    int GetContoursDetectes() const;
    
    const char * GetPerfString();
    const char * GetTxFauxPosString();
    const char * GetTxFauxNegString();
    const IplImage* GetImgContours();
    
    ContoursStats * getResults(IplImage * imgFiltre);
    
    
protected:
    int contoursDetectes;
    int contoursReference;
    int contoursCorrects;
    int fauxPositifs;
    int fauxNegatifs;
    
    IplImage * imgContours;
    IplImage * imgBase;
    
    float txFauxPos;
    float txFauxNeg;
    float perf;
    
    
    
    
private:
    
    

};

#endif	/* RESULT_H */

