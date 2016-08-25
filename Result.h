/* 
 * File:   Result.h
 * Author: amandine
 *
 * Created on 25 août 2016, 12:54
 */

#ifndef RESULT_H
#define	RESULT_H

#include <iostream>

using namespace std;

class Result {
public:
    Result(int nbContoursReference);

    float GetPerf() ;
    float GetTxFauxNeg() ;
    float GetTxFauxPos() ;
    void SetFauxNegatifs(int fauxNegatifs);
    int GetFauxNegatifs() const;
    void SetFauxPositifs(int fauxPositifs);
    int GetFauxPositifs() const;
    void SetContoursCorrects(int contoursCorrects);
    int GetContoursCorrects() const;
    void SetContoursReference(const int contoursReference);
    const int GetContoursReference() const;
    void SetContoursDetectes(int contoursDetectes);
    int GetContoursDetectes() const;
    void SetName(string name);
    string GetName() const;
    
protected:
    string name;
    int contoursDetectes;
    int contoursReference;
    int contoursCorrects;
    int fauxPositifs;
    int fauxNegatifs;
    
    float txFauxPos;
    float txFauxNeg;
    float perf;
    
    
    
    
private:
    
    

};

#endif	/* RESULT_H */

