#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "math/mathematics.h"

using namespace std ;

int main() {

//	matrix<int> m(3,3) ;
//	m(0,0) = 1 ; m(0,1) = 4 ; m(0,2) = 7 ;
//	m(1,0) = 0 ; m(1,1) = 1 ; m(1,2) = 0 ;
//	m(2,0) = 0 ; m(2,1) = 0 ; m(2,2) = 1 ;
//	cout << "m: " << m << endl ;

//	srand(time(NULL)) ;
	matrix<double> mymatx(5,5) ;
//	for(unsigned i=0; i<mymatx.nrow(); ++i) {
//		for(unsigned j=0; j<mymatx.ncol(); ++j) {
//			mymatx(i,j) = rand() % 15 ;
////			mymatx(i,j) = (16+i*8 - j*2) % 7 ;
//		}
//	}
////	for(unsigned i=0; i<mymatx.nrow(); ++i) {
////		mymatx(i,i) = 1 ;
////	}
//	matrix<double> omatx(5,1) ;
//	for(unsigned i=0; i<omatx.nrow(); ++i) {
//		for(unsigned j=0; j<omatx.ncol(); ++j) {
//			omatx(i,j) = i+j ;
//		}
//	}

////	bool result = typeid(double) == typeid(int) ;
////	cout << "double == int: " ;
////	cout << ((result) ? "true" : "false") << endl ;

//	cout << "mymatx: " << mymatx << endl ;
//	mymatx.transpose() ;
//	cout << "transpose: " << mymatx << endl ;
//	cout << "omatx: " << omatx << endl ;
////	omatx.transpose() ;
////	cout << "transpose: " << omatx << endl ;
////	omatx = mymatx ;
////	cout << "reassign: " << omatx << endl ;

	matrix<double> mtx ;
//	mtx.transpose() ;
//	cout << "mtx: " << mtx << endl ;
//	mtx *= omatx ;
//	cout << "after *= mtx: " << mtx << endl ;
////	omatx *= mymatx ;
////	cout << "new omatx: " << omatx << endl ;
////	mtx = &omatx ;
////	matrix<int>* mtx = new matrix<int>(2,2) ;
////	for(unsigned i=0; i<mtx->nrow(); ++i) {
////		for(unsigned j=0; j<mtx->ncol(); ++j) {
////			(*mtx)(i,j) = i*900+j*100 ;
////		}
////	}
////	cout << "mtx: " << *mtx << endl ;
////	(*mtx)(0,0) = 2 ;
////	(*mtx)^2 ;
////	cout << "mtx^2: " << *mtx << endl ;
//	
	matrix<double> dmtx(2,2) ;
	for(unsigned i=0; i<dmtx.nrow(); ++i) {
		for(unsigned j=0; j<dmtx.ncol(); ++j) {
			dmtx(i,j) = i+j*0.0234+1 ;
		}
	}
	cout << "dmtx: " << dmtx << endl ;
	dmtx.swap_row(0,1) ;
	cout << "dmtx after swap_row: " << dmtx << endl ;
	dmtx.swap_col(0,1) ;
	cout << "dmtx after swap_col: " << dmtx << endl ;
//	
//	omatx = omatx + omatx ;
//	cout << "+omatx: " << omatx << endl ;
////	dmtx.inverse() ;
	dmtx.lu_decomp(mtx,mymatx) ;
	cout << "dmtx decomp: upper" << endl ;
	cout << mtx << endl ;
	cout << "lower" << endl ;
	cout << mymatx << endl ;
	cout << "LU" << endl ;
	cout << mymatx*mtx << endl ;

//	matrix<double> omatx2 ;
//	omatx.transpose(omatx2) ;
//	cout << "omatx2: " << omatx2 << endl ;
//	cout << "omatx: " << omatx << endl ;
	
//	srand(time(0)) ;
	unsigned N = 3 ;
	matrix<double> m2(N,N) ;
	matrix<double>* temp = new matrix<double>;
//	boost::numeric::ublas::matrix<double> m3(N,N) ;
	for(unsigned i=0; i<N; ++i) {
		for(unsigned j=0; j<N; ++j) {
			m2(i,j) = rand() % 10 + 1 ;
//			m3(i,j) = rand() % 10 + 1 ;
		}
	}
	cout << "m2: " << m2 << endl ;
	(*temp) = m2*2.0 ;
	cout << "m2*2.0: " << (*temp) << endl ;
	cout << "Starting matrix multiply" << endl ;
	struct timeval time ;
    struct timezone zone ;
    double start ;
    double complete ;
    double avg = 0 ;
    for(unsigned i=0; i<N; ++i) {
	    gettimeofday( &time, &zone ) ;
    	start = time.tv_sec + time.tv_usec * 1e-6 ;
//	temp = m2 * m2 ;
//		prod(m3, m3) ;
		m2 * 4.0 ;
		gettimeofday( &time, &zone ) ;
    	complete = time.tv_sec + time.tv_usec * 1e-6 ;
    	avg += (complete-start) ;
//    	cout << "matrix.h Complete...time: " << (complete-start) << endl ;
    }
    cout << "Average execute time: " << avg/N << endl ;
//    cout << "temp: " << temp << endl ;
//    gettimeofday( &time, &zone ) ;
//    start = time.tv_sec + time.tv_usec * 1e-6 ;
//	gettimeofday( &time, &zone ) ;
//    complete = time.tv_sec + time.tv_usec * 1e-6 ;
//    cout << "Ublas Complete...time: " << (complete-start) << endl ;

}
