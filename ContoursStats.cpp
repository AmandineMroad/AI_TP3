#include "ContoursStats.h"


ContoursStats::ContoursStats(IplImage * imageContours) {
    this->imgContours = imageContours;
}

float ContoursStats::GetPerf() {
    this->perf = contoursCorrects/(contoursCorrects+fauxNegatifs+fauxPositifs);
    return this->perf;
}


float ContoursStats::GetTxFauxNeg() {
    this->txFauxNeg = fauxNegatifs/(contoursCorrects + fauxNegatifs + fauxPositifs);
    return txFauxNeg;
}

float ContoursStats::GetTxFauxPos() {
    this->txFauxPos = fauxPositifs/(contoursCorrects + fauxNegatifs + fauxPositifs);
    return txFauxPos;
}


const char * ContoursStats::GetPerfString(){
    stringstream stream;
    stream << this->GetPerf();
    return stream.str().c_str();
}

const char * ContoursStats::GetTxFauxPosString(){
    stringstream stream;
    stream << this->GetTxFauxPos();
    return stream.str().c_str();
}

const char * ContoursStats::GetTxFauxNegString(){
    stringstream stream;
    stream << this->GetTxFauxNeg();
    return stream.str().c_str();
}

const IplImage* ContoursStats::GetImgContours()  {
    return imgContours;
}

void ContoursStats::SetContoursReference(int contoursReference) {
    this->contoursReference = contoursReference;
}

int ContoursStats::GetFauxNegatifs() const {
    return fauxNegatifs;
}

int ContoursStats::GetFauxPositifs() const {
    return fauxPositifs;
}

void ContoursStats::SetContoursCorrects(int contoursCorrects) {
    this->contoursCorrects = contoursCorrects;
}

int ContoursStats::GetContoursCorrects() const {
    return contoursCorrects;
}

const int ContoursStats::GetContoursReference() const {
    return contoursReference;
}

void ContoursStats::SetContoursDetectes(int contoursDetectes) {
    this->contoursDetectes = contoursDetectes;
}

int ContoursStats::GetContoursDetectes() const {
    return contoursDetectes;
}

void ContoursStats::SetNbFaux(){
    fauxPositifs = contoursDetectes - contoursCorrects;
    fauxNegatifs = contoursReference - contoursCorrects;
}