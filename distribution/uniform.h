/**
 * @file uniform.h
 */
 
#ifndef DISTRIBUTION_UNIFORM_H
#define DISTRIBUTION_UNIFORM_H
 
#include "distribution_model.h"

class uniform : public distribution_model {

	private:
	
		double _lower ;
		double _upper ;
		double _norm ;
		double _a, _b ;
		double _result ;

	public:
	
		virtual double integrate(double a, double b) {
			_a = min( _upper, max(a, _lower) ) ;
			_b = max( _lower, min(b, _upper) ) ;
			_result = ( _b - _a ) * _norm ;
			return _result ;
		}

		virtual double integrate(double a) {
			if(_a <= a || a < _b) {
				return a * _norm ;
			} else {
				return 0.0 ;
			} 
		}
		
		///constructor
		uniform( double lower, double upper ) :
		_lower(lower), _upper(upper) {
			_norm = 1.0 / ( _upper - _lower ) ;
		}

};

#endif
