#include "ContoursStats.h"

ContoursStats::ContoursStats(IplImage * imageBase, IplImage * imageContours){
    this->imgBase = imageBase;
    this->imgContours = imageContours;
    this->contoursReference = getNbContours(imgContours);
}

float ContoursStats::GetPerf() {
    this->perf = ((float)contoursCorrects/((float)contoursCorrects+(float)fauxNegatifs+(float)fauxPositifs))*100;
    return this->perf;
}

float ContoursStats::GetTxFauxNeg() {
    this->txFauxNeg = ((float)fauxNegatifs/((float)contoursCorrects + (float)fauxNegatifs +(float) fauxPositifs))*100;
    return this->txFauxNeg;
}

float ContoursStats::GetTxFauxPos() {
    this->txFauxPos = ((float)fauxPositifs/((float)contoursCorrects + (float)fauxNegatifs + (float)fauxPositifs))*100;
    return this->txFauxPos;
}

const char * ContoursStats::GetPerfString(){
    stringstream stream;
    stream << this->GetPerf()<<" %";
    return stream.str().c_str();
}

const char * ContoursStats::GetTxFauxPosString(){
    stringstream stream;
    stream << this->GetTxFauxPos()<<" %";
    return stream.str().c_str();
}

const char * ContoursStats::GetTxFauxNegString(){
    stringstream stream;
    stream << this->GetTxFauxNeg()<<" %";
    return stream.str().c_str();
}

const IplImage* ContoursStats::GetImgContours()  {
    return imgContours;
}

int ContoursStats::GetFauxNegatifs() const {
    return fauxNegatifs;
}

int ContoursStats::GetFauxPositifs() const {
    return fauxPositifs;
}

int ContoursStats::GetContoursCorrects() const {
    return contoursCorrects;
}

const int ContoursStats::GetContoursReference() const {
    return contoursReference;
}

int ContoursStats::GetContoursDetectes() const {
    return contoursDetectes;
}

ContoursStats * ContoursStats::getResults(IplImage * imgFiltre){
    //Soustraction imageBase - imgFiltre
    IplImage * imgDetails = soustraction(imgBase, imgFiltre);
    cvShowImage("diff", imgDetails);
    //Comptage nb contours dans imgDetail
    contoursDetectes = getNbContours(imgDetails);
    //Comparaison imgFiltre / image contours de reference
    contoursCorrects = getNbContoursCorrects(imgContours,imgDetails);
    //MAJ des indicateurs
    fauxPositifs = contoursDetectes - contoursCorrects;
    fauxNegatifs = contoursReference - contoursCorrects;

    return this;
}