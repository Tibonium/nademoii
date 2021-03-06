/**
 * @file quadtree_functors.h
 */

#pragma once

namespace genecis {
namespace tree {

/** Forward declaration of the quad class **/
template<class T> class quad ;

template<class T, int N>
struct max_count {
    typedef quad<T>*  argument_type ;
    typedef bool      result_type ;
    
    static result_type check( argument_type a ) {
        return (a->size() >= N) ;
    }
};

template<class B, class I>
struct split_points {
    typedef I               item_type ;
    typedef quad<item_type> node_type ;
    typedef node_type*      argument_type ;
    typedef argument_type   result_type ;
    typedef std::size_t     size_type ;
    typedef B               bound_functor ;
    typedef typename node_type::coord_type  coord_type ;
    
    static 
    result_type apply( argument_type a ) {
        size_type size( a->size() ) ;
        argument_type new_node = new node_type( a ) ;
        new_node->create_children( size ) ;

        // split the elemnts into each node
        for(size_type i=0; i<size; ++i) {
            item_type curr = a->data(i) ;
            bool left = bound_functor::left( a, curr ) ;
            bool right = bound_functor::right( a, curr ) ;
            bool top = bound_functor::top( a, curr ) ;
            bool bottom = bound_functor::bottom( a, curr ) ;
            if( (left || right) && (top || bottom) ) {
                if( left ) {
                    if( top ) {
                        new_node->top_left()->add( curr ) ;
                    } else {
                        new_node->bottom_left()->add( curr ) ;
                    }
                } else {
                    if( top ) {
                        new_node->top_right()->add( curr ) ;
                    } else {
                        new_node->bottom_right()->add( curr ) ;
                    }   // end if/else top
                }   // end if/else left
            } else {
                new_node->add( curr ) ;
            }   // end if/else in parent
        }   // end for in i
        return new_node ;
    }   // end function apply
};

template<class I>
struct bound_box {
    typedef quad<I>*     bounding_node ;
    typedef I           item_type ;
    typedef bool        result_type ;
    
    static result_type left( bounding_node n,
                             item_type item )
    {
        return ( item.x < (n->__x + 0.5 * n->__width) ) ;
    }

    static result_type right( bounding_node n,
                             item_type item )
    {
        return ( item.x > (n->__x + 0.5 * n->__width) ) ;
    }
    
    static result_type top( bounding_node n,
                            item_type item )
    {
        return ( item.y > (n->__y + 0.5 * n->__height) ) ;
    }
    
    static result_type bottom( bounding_node n,
                            item_type item )
    {
        return ( item.y < (n->__y + 0.5 * n->__height) ) ;
    }
};

}   // end of namespace tree
}   // end of namespace genecis
