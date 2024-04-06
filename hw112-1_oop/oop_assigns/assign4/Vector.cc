#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

ostream &operator<< (ostream &out, Vector target){
	cout << "(";
	for(int i = 0; i < (target.fDimension-1); i++){
		cout << target.fElements[i] << ", ";
	}
	cout << target.fElements[target.fDimension - 1] << ")";

	return out;
}

Vector::Vector(){
	fDimension = 2;
	fElements = new double[fDimension];
	for(int i = 0; i < fDimension; i++){
		fElements[i] = 0;
	}
}

Vector::Vector(int dimension){
	fDimension = dimension;
	fElements = new double[fDimension];
	for(int i = 0; i < fDimension; i++){
		fElements[i] = 0;
	}
}

Vector::Vector(int size, const double elements[]){
	fDimension = size;
	fElements = new double[fDimension];
	for(int i = 0; i < fDimension; i++){
		fElements[i] = elements[i];
	}
}

Vector::Vector(const Vector &source){
	fDimension = source.fDimension;
	fElements = new double[fDimension];
	for(int i = 0; i < fDimension; i++){
		fElements[i] = source.fElements[i];
	}
}

Vector::~Vector(){
	delete [] fElements;
}

int Vector::getDimension() const{
	return fDimension;
}

void Vector::setDimension(int dimension){
	initialize(dimension);
	fDimension = dimension;
}

double Vector::length() const{
	double ans = 0;
	for(int i = 0; i < fDimension; i++){
		ans += ( fElements[i]*fElements[i] );
	}

	return sqrt(ans);
}

void Vector::initialize(int size){
	double *temp_element;
	if(fDimension >= size){
		return;
	}else{
		temp_element = new double[size];

		for(int i = 0; i < fDimension; i++){
			temp_element[i] = fElements[i];
		}
		for(int i = fDimension; i < size; i++){
			temp_element[i] = 0;
		}

		delete [] fElements;
		fElements = temp_element;
	}

}

// start overloding

Vector Vector::operator= (const Vector &target){
	fDimension = target.fDimension;
	if(fElements != NULL){
		delete [] fElements;
	}
	fElements = new double[fDimension];

	for(int i = 0; i < fDimension; i++){
		fElements[i] = target.fElements[i];
	}

	return *this;
}

// unary minus
Vector Vector::operator- (){
	Vector temp_vector = *this;

	for(int i = 0; i < temp_vector.fDimension; i++){
		temp_vector.fElements[i] *= -1;
	}

	return temp_vector;
}

Vector Vector::operator+ (const Vector &target){
	Vector temp_vector;

	if(fDimension != target.fDimension){
		cout << "ERROR!!!\n";
		return temp_vector;
	}else{
		temp_vector.fDimension = fDimension;
		delete [] temp_vector.fElements;
		temp_vector.fElements = new double[fDimension];

		for(int i = 0; i < fDimension; i++){
			temp_vector.fElements[i] = fElements[i] + target.fElements[i];
		}

		return temp_vector;
	}

}

Vector Vector::operator- (const Vector &target){
	Vector temp_vector;

	if(fDimension != target.fDimension){
		cout << "ERROR!!!\n";
		return temp_vector;
	}else{
		temp_vector.fDimension = fDimension;
		delete [] temp_vector.fElements;
		temp_vector.fElements = new double[fDimension];

		for(int i = 0; i < fDimension; i++){
			temp_vector.fElements[i] = fElements[i] - target.fElements[i];
		}

		return temp_vector;
	}

}

Vector Vector::operator* (double scalar){
	Vector temp_vector(fDimension);

	for(int i = 0; i < fDimension; i++){
		temp_vector.fElements[i] = (fElements[i] * scalar);
	}

	return temp_vector;
}

//outside multiplication
Vector operator* (double scale, Vector v){
	for(int i = 0; i < v.fDimension; i++){
		v.fElements[i] *= scale;
	}

	return v;
}

Vector Vector::operator+= (const Vector &target){
	if(fDimension != target.fDimension){
		cout << "ERROR!!!\n";
		return *this;
	}else{
		for(int i = 0; i < fDimension; i++){
			fElements[i] += target.fElements[i];
		}

		return *this;
	}
}

Vector Vector::operator-= (const Vector &target){
	if(fDimension != target.fDimension){
		cout << "ERROR!!!\n";
		return *this;
	}else{
		for(int i = 0; i < fDimension; i++){
			fElements[i] -= target.fElements[i];
		}

		return *this;
	}
}

Vector Vector::operator*= (double scalar){
	for(int i = 0; i < fDimension; i++){
		fElements[i] *= scalar;
	}

	return *this;
}

bool Vector::operator== (const Vector &target){
	if(fDimension != target.fDimension){
		return false;
	}else{
		for(int i = 0; i < fDimension; i++){
			if(fElements[i] != target.fElements[i]){
				return false;
			}
		}

		return true;
	}
}

bool Vector::operator!= (const Vector &target){
	bool ans;

	ans = ((*this) == target);

	if(ans == true){
		return false;
	}else{
		return true;
	}
}

double Vector::operator[] (int index){
	if((index < 0) || (index >= fDimension)){
		cout << "ERROR!!!\n";
		return 0;
	}else{
		return fElements[index];
	}
}
