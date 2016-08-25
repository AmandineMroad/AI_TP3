/* 
 * File:   Result.cpp
 * Author: amandine
 * 
 * Created on 25 août 2016, 12:54
 */

#include "Result.h"

Result::Result(int nbContoursReference) {
    this->contoursReference = nbContoursReference;
}


float Result::GetPerf() {
    this->perf = contoursCorrects/(contoursCorrects+fauxNegatifs+fauxPositifs);
    return perf;
}


float Result::GetTxFauxNeg() {
    this->txFauxNeg = fauxNegatifs/(contoursCorrects + fauxNegatifs + fauxPositifs);
    return txFauxNeg;
}

float Result::GetTxFauxPos() {
    this->txFauxPos = fauxPositifs/(contoursCorrects + fauxNegatifs + fauxPositifs);
    return txFauxPos;
}

void Result::SetFauxNegatifs(int fauxNegatifs) {
    this->fauxNegatifs = fauxNegatifs;
}

int Result::GetFauxNegatifs() const {
    return fauxNegatifs;
}

void Result::SetFauxPositifs(int fauxPositifs) {
    this->fauxPositifs = fauxPositifs;
}

int Result::GetFauxPositifs() const {
    return fauxPositifs;
}

void Result::SetContoursCorrects(int contoursCorrects) {
    this->contoursCorrects = contoursCorrects;
}

int Result::GetContoursCorrects() const {
    return contoursCorrects;
}

void Result::SetContoursReference(const int contoursReference) {
    this->contoursReference = contoursReference;
}

const int Result::GetContoursReference() const {
    return contoursReference;
}

void Result::SetContoursDetectes(int contoursDetectes) {
    this->contoursDetectes = contoursDetectes;
}

int Result::GetContoursDetectes() const {
    return contoursDetectes;
}

void Result::SetName(string name) {
    this->name = name;
}

string Result::GetName() const {
    return name;
}

