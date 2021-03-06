/**
 * @file avl_tree.h
 */

#pragma once

#include <cstdio>

namespace genecis {
namespace tree {

	template<class T>
	struct avl_node {

		public:
		
		    typedef T                       value_type ;
		    typedef char                    balance_type ;
		    typedef avl_node<value_type>    node_type ;
		    typedef node_type*              node_ptr ;
	
			value_type key ;
			balance_type balance ;
			node_ptr left ;
			node_ptr right ;
			node_ptr parent ;

	};
	
	template <class T>
	class avl_tree {

		public:
		
		    typedef T                                   value_type ;
		    typedef std::size_t                         size_type ;
		    typedef avl_tree<value_type>                self_type ;
		    typedef avl_node<value_type>                node_type ;
		    typedef typename node_type::node_ptr        node_ptr ;
		    typedef typename node_type::balance_type    balance_type ;
		
			// Constructor
			avl_tree() {
				root = NULL ;
			}
				
			// Destructor
			virtual ~avl_tree() {
				clear_tree( root ) ;
			}
	
			/**
			 * Inserts a new leaf into the avl_tree with the new key
			 *
			 * @param key	key that the new leaf will have
			 */
			void insert( const value_type key ) {
				ancestor = NULL ;
				temp = root ;
				node_ptr leaf = new node_type ;
				leaf->key = key ;
				leaf->balance = ' ' ;
				leaf->left = NULL ;
				leaf->right = NULL ;
				leaf->parent = NULL ;
				insert( leaf ) ;
			}
		
			/**
			 * Searches throughout the tree looking for a leaf that has
			 * the requested key. Returns false if key does not exist
			 * in the tree.
			 *
			 * @param key	key to search for in the tree
			 */
			bool search( const value_type key ) const {
				return search( root, key ) ;
			}
		
			/**
			 * Prints out the avl_tree to the display
			 */
			void print_tree() {
				cout << "Printing AVL_tree..." << endl;
				cout << "Root Node: " << root->key << " balance: "
					 << root->balance << "\n\n";
				print_tree( root ) ;
			}

		private:
	
			/**
			 * Create the root node of the avl_tree and two other nodes
			 * that allow us to keep track of where we are and where
			 * we need to go with inserting, rotating, and balancing the
			 * tree.
			 */
			node_ptr root ;
			node_ptr ancestor ;
			node_ptr temp ;
			
			/**
			 * This function takes a newly created leaf and inserts it
			 * within the avl_tree using the binary tree schema.
			 *
			 * @param leaf		New leaf to be inserted into tree.
			 */
			void insert( node_ptr leaf ) {
				if( root == NULL ) {
					root = leaf ;
					return ;
				}

				if( temp == NULL ) {
					temp = leaf ;
					restore_avl_tree( ancestor, leaf ) ;
				} else
				if( temp->key < leaf->key ) {
					leaf->parent = temp ;
					if( temp->balance == '=' ) { ancestor = temp ; }
					temp = temp->left ;
					insert( leaf ) ;
				} else {
					leaf->parent = temp ;
					if( temp->balance == '=' ) { ancestor = temp ; } 
					temp = temp->right ;
					insert( leaf ) ;
				}
			}
		
			bool search( node_ptr leaf, const value_type key) const {
				if( leaf != NULL ) {
					if( leaf->key == key ) {
						return true ;
					} else
					if( key < leaf->key ) {
						search( leaf->left, key ) ;
					} else {
						search( leaf->right, key ) ;
					}
				} else {
					cout << "Key: " << key << " is not within the tree."
						 << endl ;
					return false ;
				}
			}
		
			/**
			 * Primary function that does all of the work to make sure
			 * that the avl_tree follows the correct schema. This function
			 * is called after inserting a new leaf to the tree and restores
			 * the correct orientation of the leaves in the tree.
			 *
			 * @param history	Last tree leaf that has to be rebalanced
			 * @param newleaf	The leaf that we just inserted
			 */
			void restore_avl_tree( node_ptr history, node_ptr newleaf ) {
				//--------------------------------------------------------------
				// Case 1: history is NULL, ie all balance factors are '='
				//--------------------------------------------------------------
				if( history == NULL ) {
					if( newleaf->key < root->key ) {
						root->balance = 'L' ;
					} else {
						root->balance = 'R' ;
					}
					adjustbalance( root, newleaf ) ;
				} else
	
				//--------------------------------------------------------------
				// Case 2: placed newleaf in the opposite side of the history's
				//         subtree.
				// history->balance = 'L' and newleaf is on the right
				//               OR
				// history->balance = 'R' and newleaf is on the left
				//--------------------------------------------------------------
				if( (history->balance == 'L' && newleaf->key > history->key) ||
					(history->balance == 'R' && newleaf->key < history->key) )
				{
					history->balance = '=' ;
					adjustbalance( history, newleaf ) ;
				} else
	
				//--------------------------------------------------------------
				// Case 3: history->balance = 'R' and newleaf was put on the
				//         right subtree of history's right child.
				//--------------------------------------------------------------
				if( history->balance == 'R' &&
					newleaf->key > history->right->key )
				{
					history->balance = '=' ;
					rotateLeft( history ) ;
					adjustbalance( history->parent, newleaf ) ;
				} else
	
				//--------------------------------------------------------------
				// Case 4: history->balance = 'L' and newleaf was put on the
				//         left subtree of history's left child.
				//--------------------------------------------------------------
				if( history->balance == 'L' &&
					newleaf->key < history->left->key )
				{
					history->balance = '=' ;
					rotateRight( history ) ;
					adjustbalance( history->parent, newleaf ) ;
				} else
	
				//--------------------------------------------------------------
				// Case 5: history->balance = 'R' and newleaf was put on the
				//		   left subtree of history's right child.
				//--------------------------------------------------------------
				if( history->balance == 'R' &&
					newleaf->key < history->right->left->key )
				{
					rotateRight( history->right ) ;
					rotateLeft( history ) ;
					adjustRightLeft( history, newleaf ) ;
				} else
	
				//--------------------------------------------------------------
				// Case 6: history->balance = 'L' and newleaf was put on the
				//         right subtree of history's left child.
				//--------------------------------------------------------------
				{
					rotateLeft( history->left ) ;
					rotateRight( history ) ;
					adjustLeftRight( history, newleaf ) ;
				}
			}

			/**
			 * This function is called to make sure that all balance
			 * variables of all the nodes are appropriately set.
			 *
			 * @param end		last leaf up the tree that needs to be 
			 *					adjusted
			 * @param start		leaf that was just inserted
			 */
			void adjustbalance( node_ptr end, node_ptr start ) {
				if( start != end ) {
					if( start->key < start->parent->key ) {
						start->parent->balance = 'L' ;
						adjustbalance( end, start->parent ) ;
					} else {
						start->parent->balance = 'R' ;
						adjustbalance( end, start->parent ) ;
					}
				}
			}

			/**
			 * Perform a left rotation about the designated leaf. This
			 * will rotate LLnode's parent into LLnode's left child and
			 * LLnode's left child will become the former parent's
			 * right child.
			 *
			 * @param LLnode	leaf that needs to be rotated around
			 */
			void rotateLeft( node_ptr LLnode ) {
				node_ptr ltemp = LLnode->right ;
				LLnode->right = ltemp->left ;
				if( ltemp->left != NULL ) {
					ltemp->left->parent = LLnode ;
				}
				if( LLnode->parent == NULL ) {
					root = ltemp ;
					ltemp->parent = NULL ;
				} else
				if( LLnode->parent->left == LLnode ) {
					LLnode->parent->left = ltemp ;
				} else {
					LLnode->parent->right = ltemp ;
				}
	
				ltemp->left = LLnode ;
				LLnode->parent = ltemp ;
			}
		
			/**
			 * Perform a right rotation about the designated leaf. This
			 * will rotate RRnode's parent into RRnode's right child and
			 * RRnode's right child will become the former parent's
			 * left child.
			 *
			 * @param RRnode	leaf that needs to be rotated around
			 */
			void rotateRight( node_ptr RRnode ) {
				node_ptr rtemp = RRnode->left ;
				RRnode->left = rtemp->right ;
				if( rtemp->right != NULL ) {
					rtemp->right->parent = RRnode ;
				}
				if( RRnode->parent == NULL ) {
					root = rtemp ;
					rtemp->parent = NULL ;
				} else
				if( RRnode->parent->left == RRnode ) {
					RRnode->parent->left = rtemp ;
				} else {
					RRnode->parent->right = rtemp ;
				}
	
				rtemp->right = RRnode ;
				RRnode->parent = rtemp ;
			}
		
			/**
			 * Performs Right to Left balancing
			 *
			 * @param end	 last leaf up tree that needs adjusting
			 * @param start	 leaf that was just inserted
			 */
			void adjustRightLeft( node_ptr end, node_ptr start ) {
				if( end == root ) {
					end->balance = '=' ;
				} else
				if( start->key < end->parent->key ) {
					end->balance = 'R' ;
					adjustbalance( end->parent->left, start ) ;
				} else {
					end->balance = '=' ;
					end->parent->left->balance = 'L' ;
					adjustbalance( end, start ) ;
				}
			}
		
			/**
			 * Performs Left to Right balancing
			 *
			 * @param end	 last leaf up tree that needs adjusting
			 * @param start	 leaf that was just inserted
			 */
			void adjustLeftRight( node_ptr end, node_ptr start ) {
				if( end == root ) {
					end->balance = '=' ;
				} else
				if( start->key > end->parent->key ) {
					end->balance = 'L' ;
					adjustbalance( end->parent->right, start ) ;
				} else {
					end->balance = '=' ;
					end->parent->right->balance = 'R' ;
					adjustbalance( end, start ) ;
				}
			}
		
			/**
			 * Prints out the avl_tree nodes and information
			 *
			 * @param leaf		Leaf with information we want to output
			 */
			void print_tree( node_ptr leaf ) {
				if( leaf != NULL ) {
					cout << "Node: " << leaf->key << " balance: "
						 << leaf->balance << "\n" ;
					if( leaf->left != NULL ) {
						cout << "\t moving left\n" ;
						print_tree( leaf->left ) ;
						cout << "Returning to Node" << leaf->key
							 << " from its' left subtree\n" ;
					} else {
						cout << "\t left subtree is empty\n" ;
					}

					if( leaf->right != NULL ) {
						cout << "\t moving right\n" ;
						print_tree( leaf->right ) ;
						cout << "Returning to Node" << leaf->key 
							 << " from its' right subtree\n" ;
					} else {
						cout << "\t right subtree is empty\n" ;
					}
				}
			}
		
			/**
			 * Destroys the tree from the bottom up
			 *
			 * @param leaf	leaf to delete
			 */
			void clear_tree( node_ptr leaf ) {
				if( leaf != NULL ) {
					clear_tree( leaf->left ) ;
					clear_tree( leaf->right ) ;
					delete leaf ;
				}
			}

	};
	
}	// end of namespace tree
}	// end of namespace genecis
