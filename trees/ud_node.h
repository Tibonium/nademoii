/**
 *	@file ud_node.h
 */

#ifndef UD_NODE_H
#define UD_NODE_H

#include <stdlib.h>
#include <string>

using namespace std ;

template<class _T> class ud_node {

	public:
		/**
		 * Main accessors
		 */
		ud_node<_T>* parent ;
		ud_node<_T>* child ;
		string key ;
		_T data ;
		
		/**
		 * Constructor
		 */
		ud_node<_T>(string _key, _T _data) {
			parent = NULL ;
			child = NULL ;
			key = _key ;
			data = _data ;
		}
		
		inline ud_node(_T)& operator= (ud_node<_T>& other) {
			parent = other->parent ;
			child = other->child ;
			key = other->key ;
			data = other->data ;
			return *this ;
		}
		
		/**
		 * Destructor
		 */
		~ud_node<_T>() {
			delete parent ;
			delete child ;
			delete key ;
			delete data ;
		}

};

#endif
