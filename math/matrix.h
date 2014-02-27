/**
 * @file new matrix class
 */

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <typeinfo>

using namespace std ;

template<class _type> class matrix ;

template<class _type>
std::ostream& operator<< (std::ostream& os, matrix<_type>& output) ;

template<class _type> class matrix {

		typedef matrix<_type> self_type ;

	public:
		inline unsigned nrow() {
			return _nrow ;
		}

		inline unsigned ncol() {
			return _ncol ;
		}

		inline bool singular() {
			return _singular ;
		}
		
		inline _type det() {
			if ( _verify ) {
				singularity() ;
			}
			return _det ;
		}
		
		inline _type* data() {
			return _data ;
		}

/************************* Operators ******************************/
		/* Accessor and Assigner */
		inline _type& operator() (unsigned i, unsigned j) {
			_index = i * _ncol + j ;
			return _data[_index] ;
		}

		inline void operator= (_type value) {
			_verify = true ;
			_data[_index] = value ;
		}

	/*================= Matrix Scalar Operators ================*/
		inline matrix<_type>& operator* (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] *= value ;
				}
			}
			return *this ;
		}

		inline void operator*= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] *= value ;
				}
			}
		}

		inline matrix<_type>& operator/ (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] /= value ;
				}
			}
			return *this ;
		}

		inline void operator/= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] /= value ;
				}
			}
		}

		inline matrix<_type>& operator+ (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] += value ;
				}
			}
			return *this ;
		}

		inline void operator+= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] += value ;
				}
			}
		}

		inline matrix<_type>& operator- (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] -= value ;
				}
			}
			return *this ;
		}

		inline void operator-= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] -= value ;
				}
			}
		}

		inline matrix<_type>& operator% (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] %= value ;
				}
			}
			return *this ;
		}

		inline void operator%= (_type value) {
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					_data[i*_ncol+j] %= value ;
				}
			}
		}

	/*================ Matrix Matrix Operators =================*/
		inline matrix<_type>& operator* (matrix<_type>& other) {
			try {
				if( _ncol != other.nrow() ) {
					throw 1;
				} else {
					matrix<_type>* temp = new matrix<_type>(_nrow,other.ncol()) ;
					_type value = 0 ;
					for(unsigned n=0; n<temp->nrow(); ++n) {
						for(unsigned m=0; m<temp->ncol(); ++m) {
							for(unsigned i=0; i<_ncol; ++i) {
								value += (*this)(n,i) * other(i,m) ;
							}
							(*temp)(n,m) = value ;
							value = 0 ;
						}
					}
					if( _singular || other.singular() ) {
						temp->_singular = true ;
					} else {
						temp->_singular = false ;	
					}
					return *temp ;
				}
			} catch (int e) {
				cout << "matrix::operator*: A ncol(" << _ncol
					 << ") must equal B nrow(" << other.nrow()
					 << ")." << endl ;
				exit(e) ;
			}
		}

		inline void operator*= (matrix<_type>& other) {
			try {
				if( _ncol != other.nrow() ) {
					throw 1;
				} else {
					matrix<_type> temp = *this ;
					*this = temp * other ;
					if( other.singular() ) { _singular = true ; }
				}
			} catch (int e) {
				cout << "matrix::operator*=: A ncol(" << _ncol
					 << ") must equal B nrow(" << other.nrow()
					 << ")." << endl ;
				exit(e) ;
			}
		}
		
		inline matrix<_type>& operator+ (matrix<_type>& other) {
			try {
				if( _nrow != other.nrow() || _ncol != other.ncol() ) {
					throw 1 ;
				} else {
					matrix<_type>* temp = new matrix<_type>(_nrow,other.ncol()) ;
					for(unsigned i=0; i<_nrow; ++i) {
						for(unsigned j=0; j<_ncol; ++j) {
							(*temp)(i,j) = (*this)(i,j) + other(i,j) ;
						}
					}
					return *temp ;
				}
			} catch (int e) {
				cout << "matrix::operator+: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << other << endl ;
				exit(e) ;
			}
		}
		
		inline void operator+= (matrix<_type>& other) {
			try {
				if( _nrow != other.nrow() || _ncol != other.ncol() ) {
					throw 1 ;
				} else {
					matrix<_type> temp = *this ;
					*this = temp + other ;
					_verify = true ;
				}
			} catch (int e) {
				cout << "matrix::operator+=: Only defined for matrices with "
					 << "the same number of rows and columns." << endl ;
				cout << *this << endl ;
				cout << other << endl ;
				exit(e) ;
			}
		}
		
		inline void operator/ (matrix<_type>& other) {
			cout << "matrix::operator/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		inline void operator/= (matrix<_type>& other) {
			cout << "matrix::operator=/: Matrix division is ill-defined "
				 << "and not implemented at this time." << endl ;
			exit(1) ;
		}

		/**
		 * Mutates the matrix into its transpose.
		 */
		inline void transpose() {
			matrix<_type>* temp = new matrix<_type>(_ncol,_nrow) ;
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					(*temp)(j,i) = (*this)(i,j) ;
				}
			}
			*this = *temp ;
			temp->_data = NULL ;
			delete temp ;
		}
		
		/**
		 * Mutates the passed in matrix into the transpose of the
		 * matrix that called this function. The calling matrix
		 * remains unaltered.
		 */
		inline void transpose(matrix<_type>& m_trans) {
			m_trans.resize(_ncol, _nrow) ;
			for(unsigned i=0; i<_nrow; ++i) {
				for(unsigned j=0; j<_ncol; ++j) {
					m_trans(j,i) = (*this)(i,j) ;
				}
			}
		}
		
		/**
		 * Calculates the determinant of the matrix. If the determinant
		 * is returned as zero, _singular flag is set to true. 
		 * Otherwise it is set to true. In both cases the _verify
		 * flag is then set to false.
		 */
		inline _type determinant() {
			_type result = 0 ;
			_det = result ;
			return result ;
		}
		
		/**
		 * Mutates the calling matrix into its inverse, if it exists.
		 * Otherwise an exit status is passed and the program ends.
		 */
		inline matrix<_type>& inverse() {
			try {
				singularity() ;
				if( _singular || _det == 0 ) {
					throw 1 ;
				} else {
					matrix<_type>* inv_mtx = this ;
					cout << "something" << endl ;
					return *inv_mtx ;
				}
			} catch (int e) {
				cout << "matrix::inverse(): inverse not defined for"
					 << " singular matrices at this time." << endl ;
				cout << "Non-singular matrices must be square and"
					 << " have a non-zero determinant." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		/**
		 * Exponent operator. When called on a matrix it will mutate
		 * the matrix it operates on into a new matrix equal to the
		 * original matrix times itself n times, where n is the
		 * exponent.
		 * For an exponent of zero, the matrix will take on the form
		 * of the identity matrix.
		 * For an exponent of -1, the matrix will become the original
		 * matrix's inverse.
		 *
		 * NOTE: At present only integer values for the exponent are
		 * accepted.
		 */
		inline void operator^ (int exp) {
			try {
				if( _ncol != _nrow ) {
					throw 1 ;
				} else {
					if( exp < 0 ) {
						if( exp == -1 ) {
							inverse() ;
						} else {
							cout << "do some other negative power > 1" << endl ;
						}
					} else if( exp == 0 ) {
						cout << "return identity matrix" << endl ;
					} else {
						int i = 1 ;
						matrix<_type> temp = *this ;
						while(i < exp) {
							*this *= temp ;
							++i ;
						}
					}
				}
			} catch(int e) {
				cout << "matrix<_type>::operator^ "
					<< "only valid for square matrices." << endl ;
				cout << *this << endl ;
				exit(e) ;
			}
		}

		inline void ul_decomp(matrix<_type>& upper, matrix<_type>& lower) {
			upper.resize(_nrow, _ncol) ;
			lower.resize(_nrow, _ncol) ;
			cout << "matrix::ul_decomp:: Decompose the matrix into "
				 << "an upper and lower triangular matrix."
				 << endl ;
		}

		/**
		 * Resizes matrix to have r rows and c columns. Data
		 * is then deleted and reallocated to the new size.
		 * Data is not preserved at resizing a matrix!!
		 */
		inline void resize(const unsigned& r, const unsigned& c) {
			this->_nrow = r ;
			this->_ncol = c ;
			delete this->_data ;
			this->_data = new _type[r*c] ;
		}
		
		/**
		 * Swaps row a with row b.
		 */
		inline void swap_row(const unsigned& a, const unsigned& b) {
			_type temp ;
			for(unsigned i=0; i<_ncol; ++i) {
				temp = (*this)(a,i) ;
				(*this)(a,i) = (*this)(b,i) ;
				(*this)(b,i) = temp ;
			}
		}
		
		/**
		 * Swaps column a with column b
		 */
		inline void swap_col(const unsigned& a, const unsigned& b) {
			_type temp ;
			for(unsigned i=0; i<_nrow; ++i) {
				temp = (*this)(i,a) ;
				(*this)(i,a) = (*this)(i,b) ;
				(*this)(i,b) = temp ;
			}
		}
		
	/*================== Comparison Operators ==================*/
		inline bool operator== (matrix<_type>& other) {
			int n = memcmp( _data, other.data(), 
						    sizeof(_type)*sizeof(_data) ) ;
			if ( _nrow == other.nrow() &&
				 _ncol == other.ncol() && n == 0 )
			{
				return true ;
		 	} else {
		 		return false ;
		 	}
		}

		inline bool operator!= (matrix<_type>& other) {
			return !(*this==other) ;
		}

/******************** Constructor/Destructors *********************/
		/**
		 * Main  Constructor
		 * Creates an NxM matrix from a basic array
		 * Defaults to a 1x1 matrix
		 */
		matrix(unsigned nrow=1, unsigned ncol=1) : 
			_nrow(nrow), _ncol(ncol) 
		{
			size_t N = _nrow * _ncol ;
			_data = new _type[N] ;
			memset(_data, 0, N * sizeof(_type)) ;
			if( _nrow != _ncol ) {
				_singular = true ;
				_det = 0 ;
				_verify = false ;
			} else {
				_verify = true ;
			}
		}

		/**
		 * Copy Constructor
		 */
		matrix(matrix<_type>& other) :
			_nrow(other.nrow()), _ncol(other.ncol()),
			_singular(other.singular()), _det(other.det())
		{
			size_t N = _nrow * _ncol ;			
			_data = new _type[N] ;
			_verify = false ;
			memcpy(_data, other.data(), N * sizeof(_type)) ;
		}

		/**
		 * Assign Constructor
		 */
		inline matrix<_type>& operator= (matrix<_type>& other) {
			_nrow = other.nrow() ;
			_ncol = other.ncol() ;
			_singular = other.singular() ;
			_det = other.det() ;
			_verify = false ;
			delete _data ;
			_data = other.data() ;
			return *this ;
		}
		
		/**
		 * Destructor
		 */
		~matrix<_type>() {
			if( _data != NULL ) {
				delete _data ;
			}
		}

/********************** IO Stream overloads ***********************/
		friend std::ostream& operator<< <> (std::ostream& os, matrix& output) ;

	private:
		unsigned _nrow ;
		unsigned _ncol ;
		unsigned _index ;
		bool _singular ;
		bool _verify ;
		_type _det ;
		_type* _data ;


		/**
		 * Determine if the matrix is singular
		 * This function is used to determine if a matrix is singular
		 * by first looking to see if a zero row or column exists.
		 * If one exists, the _singular member variable is set to
		 * true and _det is set to zero.
		 * If a zero row/column is not found, the determinant of the
		 * matrix is then calculated and checked to be non-zero.
		 *
		 * This function only checks for singular-ness when either
		 * a data value is altered, such as populating a matrix
		 */		
		inline void singularity() {
			if( _verify ) {
			
				// check for a zero row
				for(unsigned i=0; i<_nrow; ++i) {
					bool _zero = false ;
					if( (*this)(i,0) == 0 ) {
						for(unsigned j=1; j<_ncol; ++j) {
							if( (*this)(i,j) != 0 ) {
								_zero = false ;
								break ;
							} else {
								_zero = true ;
							}
						}
					}
					if( _zero ) {
						_singular = true ;
						_det = 0 ;
						break ;
					}
				}
				
				// check for a zero column
				if( !_singular ) {
					for(unsigned i=0; i<_ncol; ++i) {
						bool _zero = false ;
						if( (*this)(0,i) == 0 ) {
							for(unsigned j=1; j<_nrow; ++j) {
								if( (*this)(j,i) != 0 ) {
									_zero = false ;
									break ;
								} else {
									_zero = true ;
								}
							}
						}
						if( _zero ) {
							_singular = true ;
							_det = 0 ;
							break ;
						}
					}
				}
				
				// check for determinant equals zero
				if( !_singular ) {
					_type zero = determinant() ;
					if( zero == 0 ) {
						_singular = true ;
					} else {
						_singular = false ;
					}
				}
				
				_verify = false ;
			}
		}

};

template <class _type>
inline std::ostream& operator<< (std::ostream& os, matrix<_type>& output) {
	os << "rows: " << output.nrow() << "   cols: " << output.ncol() 
	   << "   det: " << output.det() << endl ;
	for(unsigned i=0; i<output.nrow(); ++i) {
		os << "| " ;
		for(unsigned j=0; j<output.ncol(); ++j) {
			char buf[32];
            _type data = output(i,j);
            if( typeid(_type) == typeid(int) ) {
            	if( data >= 1e5 ) {
            		sprintf(buf, "%1.1e ", (double)data) ;
            	} else {
        			sprintf(buf, "%7d ", (int)data) ;
        		}
            } else {
            	if( (abs(data) >= 1e10) || (abs(data) <= 1e-4) ) {
            		sprintf(buf, "%10.3e ", (double)data) ;
            	} else {
        			sprintf(buf, "%10.3f ", (double)data) ;
        		}
            }
            os <<  buf ;
		}
		os << " |" << endl ;
	}
	return os ;
}

#endif
