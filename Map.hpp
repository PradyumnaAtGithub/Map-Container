#include<iostream>
#include<utility>
#include<string.h>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<stdexcept>
#define _LEVELS 100
namespace cs540{

	template <typename K, typename M>
	class Map;

	//contains the {key, value} pair
	template <typename K, typename M>
	class Node{
		public:
			friend class Map<K, M>;
			typedef std::pair<const K, M> ValueType;

			Node(std::size_t _level){
				int _temp_level = _level+1;
				_forward_links = new Node*[_temp_level];
				size_t _total_size = sizeof(Node*)*(_temp_level);
				memset(_forward_links, '\0', _total_size);
				_value = NULL;
				_prev = NULL;
			}

			Node(std::size_t _level, const ValueType& _val){
				int _temp_level = _level+1;
				_forward_links = new Node*[_temp_level];
				size_t _total_size = sizeof(Node*)*(_temp_level);
				memset(_forward_links, '\0', _total_size);
				_value = new std::pair<const K, M>(_val);
				_prev = NULL;
			}

			//delete forward links and value
			~Node(){
				delete [] _forward_links;
				delete _value;
			}

		private:
			Node** _forward_links;
			Node* _prev;
			ValueType *_value;
	};

	//maintains a skiplists of nodes
	template <typename K, typename M>
	class Map{
		public:
			//member type
			typedef std::pair<const K, M> ValueType;

			/*
			defining Iterator class
			helps iterate through elements of the map
			*/
			class Iterator{
				public:
					Iterator(const Iterator& _iter) : _cur(_iter.get_cur()){}
					Iterator(Node<K, M>* _node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					//defining operators for Iterator
					Iterator& operator=(const Iterator& _iter){
						_cur = _iter.get_cur();
						return *this;
					}
					Iterator& operator++(){
						if(_cur == NULL) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					Iterator operator++(int){
						Map<K, M>::Iterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_forward_links[0];
						return _this;
					}
					Iterator& operator--(){
						if(_cur == NULL) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					Iterator operator--(int){
						 Map<K, M>::Iterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ValueType& operator*() const{
						return *_cur->_value;
					}
					ValueType* operator->() const{
						return _cur->_value;
					}

					~Iterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;

			};

			/*
			defining ConstIterator class
			works exactly like the Iterator but values are const and cannot be changed
			*/
			class ConstIterator{
				public:
					ConstIterator(const ConstIterator& _citer) : _cur(_citer.get_cur()){}
					ConstIterator(const Iterator& _iter) : _cur(_iter.get_cur()){}
					ConstIterator(Node<K, M> *_node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					//defining operators for ConstIterator
					ConstIterator& operator=(const ConstIterator& _citer){
						_cur = _citer.get_cur();
						return *this;
					}
					ConstIterator& operator++(){
						if(_cur == NULL) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					ConstIterator operator++(int){
						Map<K, M>::ConstIterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_forward_links[0];
						return _this;
					}
					ConstIterator& operator--(){
						if(_cur == NULL) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					ConstIterator operator--(int){
						Map<K, M>::ConstIterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					const ValueType& operator*() const{
						return *_cur->_value;
					}
					const ValueType* operator->() const{
						return _cur->_value;
					}

					~ConstIterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;
			};

			/*
			defining ReverseIterator
			iterator through the elements of the map in reverse order
			*/
			class ReverseIterator{
				public:
					ReverseIterator(const ReverseIterator& _riter) : _cur(_riter.get_cur()){}
					ReverseIterator(Node<K, M> *_node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					//defining operators for ReverseIterator
					ReverseIterator& operator=(const ReverseIterator& _riter){
						_cur = _riter.get_cur();
						return *this;
					}
					ReverseIterator& operator++(){
						if(_cur == NULL) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					ReverseIterator operator++(int){
						 Map<K, M>::ReverseIterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ReverseIterator& operator--(){
						if(_cur == NULL) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					ReverseIterator operator--(int){
						Map<K, M>::ReverseIterator _this = *this;
						if(_cur == NULL) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ValueType& operator*() const{
						return *_cur->_value;
					}
					ValueType* operator->() const{
						return _cur->_value;
					}

					~ReverseIterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;
			};

			Map(){
				map_ctor();
			}

			Map(const Map& _map){
				map_ctor();
				Node<K, M> *_temp = _map.get_head()->_forward_links[0];
				while(_temp != _map.get_tail()){
					ValueType& _val = *(_temp->_value);
					insert(_val);
					_temp = _temp->_forward_links[0];
				}
			}

			Map(std::initializer_list<std::pair<const K, M>> _l){
				map_ctor();
				auto _iter = _l.begin();
				while(_iter != _l.end()){
					insert(*_iter);
					_iter++;
				}
			}

			//delete every node in the map
			~Map(){
				Node<K, M> *_temp_head = _head;
				Node<K, M> *_temp;
				while(_temp_head != NULL){
					_temp = _temp_head->_forward_links[0];
					delete _temp_head;
					_temp_head = _temp;
				}
			}

			Node<K, M>* get_head() const{
				return _head;
			}
			Node<K, M>* get_tail() const{
				return _tail;
			}

			//constructs the map
			void map_ctor(){
				init_head_tail();
				init_assign_head_tail();
				init_size();
			}
			//init parameters
			void init_head_tail(){
				_head = new Node<K, M>(_LEVELS);
				_tail = new Node<K, M>(_LEVELS);
			}
			void init_assign_head_tail(){
				_head->_forward_links[0] = _tail;
				_tail->_prev = _head;
				_head->_prev = NULL;
				_tail->_forward_links[0] = NULL;
			}
			void init_size(){
				 _max = 0;
				_size = 0;
			}

			//reset parameters
			void reset_head_tail(){
				_head = NULL;
				_tail = NULL;
			}
			void reset_size(){
				_max = 0;
				_size = 0;
			}

			//return Iterator pointing to the node which has key given by _key
			Iterator find(const K& _key){
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == NULL){
					return Map<K, M>::Iterator(_tail);
				}
				return Map<K, M>::Iterator(_temp_head);
			}

			//return ConstIterator pointing to the node which has key given by _key
			ConstIterator find(const K& _key) const{
				 Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == NULL){
					return Map<K, M>::ConstIterator(_tail);
				}
				return Map<K, M>::ConstIterator(_temp_head);
			}

			/*
			begin() -- return iterator pointing to the first element in the map
			end() -- return iterator pointing to one past the last element in the map (logically)
			rbegin() -- works like begin() for ReverseIterator
			rend() -- works like end() for ReverseIterator
			*/
			Iterator begin(){return Map<K, M>::Iterator(_head->_forward_links[0]);}
			Iterator end(){return Map<K, M>::Iterator(_tail);}
			ConstIterator begin() const{return ConstIterator(_head->_forward_links[0]);}
			ConstIterator end() const{return ConstIterator(_tail);}
			ReverseIterator rbegin(){return ReverseIterator(_tail->_prev);}
			ReverseIterator rend(){return ReverseIterator(_head);}

			std::size_t size() const{return _size;}
			bool empty() const{return (_size == 0)? true : false;}

			//return mapped type for the given key
			M& at(const K& _key){
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == NULL){
					throw std::out_of_range("out of range");
				}
				else return _temp_head->_value->second;

			}
			//return const reference to mapped type for given key
			const M& at(const K& _key) const{
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == NULL){
					throw std::out_of_range("out of range");
				}
				else return _temp_head->_value->second;
			}

			//comparison operators on iterator
			friend bool operator==(const Iterator& _iter1, const Iterator& _iter2){
				return (_iter1.get_cur() == _iter2.get_cur())? true : false;
			}
			friend bool operator!=(const Iterator& _iter1, const Iterator& _iter2){
				return (_iter1.get_cur() != _iter2.get_cur())? true : false;
			}
			friend bool operator==(const ConstIterator& _citer1, const ConstIterator& _citer2){
				return (_citer1.get_cur() == _citer2.get_cur())? true : false;
			}
			friend bool operator!=(const ConstIterator& _citer1, const ConstIterator& _citer2){
				return (_citer1.get_cur() != _citer2.get_cur())? true : false;
			}
			friend bool operator==(const ReverseIterator& _riter1, const ReverseIterator& _riter2){
				return (_riter1.get_cur() == _riter2.get_cur())? true : false;
			}
			friend bool operator!=(const ReverseIterator& _riter1, const ReverseIterator& _riter2){
				return (_riter1.get_cur() != _riter2.get_cur())? true : false;
			}
			friend bool operator==(const Iterator& _iter, const ConstIterator& _citer){
				return (_iter.get_cur() == _citer.get_cur())? true : false;
			}
			friend bool operator==(const ConstIterator& _citer, const Iterator& _iter){
				return (_citer.get_cur() == _iter.get_cur())? true : false;
			}
			friend bool operator!=(const Iterator& _iter, const ConstIterator& _citer){
				return (_iter.get_cur() != _citer.get_cur())? true : false;
			}
			friend bool operator!=(const ConstIterator& _citer, const Iterator& _iter){
				return (_citer.get_cur() != _iter.get_cur())? true : false;
			}

			//clear all nodes in the map
			void clear();
			//operator[] for accessing mapped type for key
			M& operator[](const K&);
			//level randomizer for insert
			size_t random_level(Node<K, M>**);
			//getting node for key using bottom link
			Node<K, M>* find_at_bottom(const K& _key) const;
			//insert ValueType into map and return iterator positioned at that node
			std::pair<Iterator, bool> insert(const ValueType&);
			//range based insert
			template <typename IT_T>
			void insert(IT_T range_beg, IT_T range_end);
			//remove node pointed to by iterator
			void erase(Iterator);
			//remove node which has given key
			void erase(const K&);
			//assignment of maps
			Map& operator=(const Map&);
			//map comparisons
			bool operator!=(const Map&) const;
			template <typename Key, typename Mapped>
			friend bool operator==(const Map<Key, Mapped>&, const Map<Key, Mapped>&);
			template <typename Key, typename Mapped>
			friend bool operator<(const Map<Key, Mapped>&, const Map<Key, Mapped>&);
			template <typename Key, typename Mapped>
			friend bool operator!=(const Map<Key, Mapped>&, const Map<Key, Mapped>&);

		private:
			Node<K, M>* _head;
			Node<K, M>* _tail;
			std::size_t _max;
			std::size_t _size;
	};

	template <typename K, typename M>
	M& Map<K, M>::operator[](const K& _key){
		Node<K, M> *_temp_head = find_at_bottom(_key);
		if(_temp_head == NULL){
			Map<K, M>::Iterator _iter = insert(std::make_pair(_key, M())).first;
			return _iter.get_cur()->_value->second;
		}
		return _temp_head->_value->second;
	}

	template <typename K, typename M>
	size_t Map<K, M>::random_level(Node<K, M>** _nodes){
		size_t _level = 0;
		while(_level < _LEVELS && rand() < RAND_MAX*0.5){
			++_level;
		}
		if(_level > _max){
			size_t _temp = _max+1;
			while(_temp <= _level){
				_nodes[_temp] = _head;
				++_temp;
			}
			_max = _level;
		}
		return _level;
	}

	template <typename K, typename M>
	Map<K, M>& Map<K, M>::operator=(const Map<K, M>& _map){
		if(this == &_map){
			return *this;
		}
		Node<K, M> *_temp_head = _head;
		Node<K, M> *_temp;
		while(_temp_head != NULL){
			_temp = _temp_head->_forward_links[0];
			delete _temp_head;
			_temp_head = NULL;
			_temp_head = _temp;
		}

		map_ctor();
		Node<K, M> *_first = _map.get_head()->_forward_links[0];
		if(_first == _map.get_tail()) return *this;
		while(_first != _map.get_tail()){
			insert(*(_first->_value));
			_first = _first->_forward_links[0];
		}
		return *this;
	}

	template <typename K, typename M>
	std::pair<typename Map<K, M>::Iterator, bool> Map<K, M>::insert(const std::pair<const K, M>& _val){
		const K& _key = _val.first;
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != NULL && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
		Node<K, M> *_first_updated = _updated[0];
		_first_updated = _first_updated->_forward_links[0];
		if(_first_updated->_value != NULL && _first_updated->_value->first == _val.first){
			delete [] _updated;
			return std::make_pair(Map<K, M>::Iterator(_first_updated), false);
		}

		size_t _level = random_level(_updated);
		_first_updated = NULL;
		_first_updated = new Node<K, M>(_level, _val);
		i = 0;
		while(i <= _level){
			_first_updated->_forward_links[i] = _updated[i]->_forward_links[i];
			_updated[i]->_forward_links[i] = _first_updated;
			++i;
		}
		_first_updated->_prev = _updated[0];
		if(_first_updated->_forward_links[0] != _tail){
			_first_updated->_forward_links[0]->_prev = _first_updated;
		}
		else{
			_tail->_prev = _first_updated;
		}
		++_size;
		delete [] _updated;
		return std::make_pair(Map<K, M>::Iterator(_first_updated), true);
	}

	template <typename K, typename M>
	template <typename IT_T>
	void Map<K, M>::insert(IT_T range_beg, IT_T range_end){
		auto _iter = range_beg;
		while(_iter != range_end){
			insert(*_iter);
			++_iter;
		}
	}

	template <typename K, typename M>
	void Map<K, M>::erase(const K& _key){
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != NULL && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
                Node<K, M> *_first_updated = _updated[0];
                _first_updated = _first_updated->_forward_links[0];
                if(_first_updated->_value->first == _key){
                        i = 0;
                        while(i <= _max && _updated[i]->_forward_links[i] == _first_updated){
                                _updated[i]->_forward_links[i] = _first_updated->_forward_links[i];
                                ++i;
                        }

                        if(_first_updated->_forward_links[0] != _tail){
                                _first_updated->_forward_links[0]->_prev = _first_updated->_prev;
                        }
                        else{
                                _tail->_prev = _first_updated->_prev;
                                _first_updated->_prev->_forward_links[0] = _tail;
                        }

                        delete _first_updated;
                        while(_max > 0 && _head->_forward_links[_max] == NULL){
                                --_max;
                        }
                        --_size;
                        delete [] _updated;
                }
                else{
                        throw std::out_of_range("out of range");
                }
	}

	template <typename K, typename M>
	void Map<K, M>::erase(Map<K, M>::Iterator _iter){
		const K& _key = _iter.get_cur()->_value->first;
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != NULL && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
                Node<K, M> *_first_updated = _updated[0];
                _first_updated = _first_updated->_forward_links[0];
                if(_first_updated->_value->first == _key){
                        i = 0;
                        while(i <= _max && _updated[i]->_forward_links[i] == _first_updated){
                                _updated[i]->_forward_links[i] = _first_updated->_forward_links[i];
                                ++i;
                        }

                        if(_first_updated->_forward_links[0] != _tail){
                                _first_updated->_forward_links[0]->_prev = _first_updated->_prev;
                        }
                        else{
                                _tail->_prev = _first_updated->_prev;
                                _first_updated->_prev->_forward_links[0] = _tail;
                        }

                        delete _first_updated;
                        while(_max > 0 && _head->_forward_links[_max] == NULL){
                                --_max;
                        }
                        --_size;
                        delete [] _updated;
                }
                else{
                        throw std::out_of_range("out of range");
                }
	}

	template <typename K, typename M>
	void Map<K, M>::clear(){
		Node<K, M> *_temp_head = _head;
		Node<K, M> *_temp;
		while(_temp != NULL){
			_temp = _temp_head->_forward_links[0];
			delete _temp_head;
			_temp_head = _temp;
		}
		reset_size();
		reset_head_tail();
		map_ctor();
	}

	template <typename K, typename M>
	Node<K, M>* Map<K, M>::find_at_bottom(const K& _key) const{
		Node<K, M> *_temp = _head;
		int i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != NULL && _temp->_forward_links[i]->_value->first < _key){
                                _temp = _temp->_forward_links[i];
                        }
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_temp = _temp->_forward_links[0];
		if(_temp == _tail) return NULL;
		if(_temp != NULL){
			if(_temp->_value->first == _key)
				return _temp;
		}
		return NULL;
	}

	template <typename K, typename M>
	bool Map<K, M>::operator!=(const Map<K, M>& _map) const{
		if(*this == _map) return false;
		return true;
	}

	template <typename K, typename M>
	bool operator==(const Map<K, M>& _map1, const Map<K, M>& _map2){
		if(_map1.size() != _map2.size()) return false;
		auto _iter1 = _map1.begin();
		auto _iter2 = _map2.begin();
		while(_iter1 != _map1.end() && _iter2 != _map2.end()){
			if(*_iter1 != *_iter2){
				return false;
			}
			++_iter1;
			++_iter2;
		}
		return true;
	}

	template <typename K, typename M>
	bool operator!=(const Map<K, M>& _map1, const Map<K, M>& _map2){
		return !(_map1 == _map2);
	}

	template <typename K, typename M>
	bool operator<(const Map<K, M>& _map1, const Map<K, M>& _map2){
		size_t _size1 = _map1.size();
		size_t _size2 = _map2.size();
		if(_size1 < _size2) return true;
		if(_size2 < _size1) return false;
		//same size
		auto _iter1 = _map1.begin();
		auto _iter2 = _map2.begin();
		while(_iter1 != _map1.end() && _iter2 != _map2.end()){
			bool _less = (*_iter1).first < (*_iter2).first;
			bool _less2 = (*_iter2).first < (*_iter1).first;
			if(_less) return true;
			if(_less2) return false;
			++_iter1;
			++_iter2;
		}
		//maps are same
		return false;
	}
}
