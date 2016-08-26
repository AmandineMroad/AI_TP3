#ifndef RESULT_H
#define	RESULT_H

#include <iostream>
#include <sstream>
#include <opencv/cv.h>

using namespace std;

class ContoursStats {
public:
    ContoursStats(IplImage * imageContours);

    float GetPerf() ;
    float GetTxFauxNeg() ;
    float GetTxFauxPos() ;
    int GetFauxNegatifs() const;
    int GetFauxPositifs() const;
    void SetContoursCorrects(int contoursCorrects);
    int GetContoursCorrects() const;
    const int GetContoursReference() const;
    void SetContoursDetectes(int contoursDetectes);
    int GetContoursDetectes() const;
    
    void SetNbFaux();
    
    const char * GetPerfString();
    const char * GetTxFauxPosString();
    const char * GetTxFauxNegString();
    const IplImage* GetImgContours();
    void SetContoursReference(int contoursReference);
    
protected:
    int contoursDetectes;
    int contoursReference;
    int contoursCorrects;
    int fauxPositifs;
    int fauxNegatifs;
    
    IplImage * imgContours;
    
    float txFauxPos;
    float txFauxNeg;
    float perf;
    
    
    
    
private:
    
    

};

#endif	/* RESULT_H */

