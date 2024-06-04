/********************************************************************/
/*                                                                  */
/*  Put your linked list code from A1 into                          */
/*  this file                                                       */
/*                                                                  */
/********************************************************************/
template <typename T>
class CacheList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		int accessCount_;
		Node(const T& data=T{}, Node* next = nullptr, Node* prev = nullptr, int accessCount = 0){
			data_ = data;
			next_ = next;
			prev_ = prev;
			accessCount_ = accessCount;
		}
	};
	Node* front_;
	Node* back_;
public:
	class const_iterator{
	protected:
		friend class CacheList;
		const CacheList* linkedList_;
		Node* curr_;
		const_iterator(Node* curr, const CacheList* list) {
			curr_ = curr;
			linkedList_ = list;
		}
	public:
		const_iterator(){
			linkedList_ = nullptr;
			curr_ = nullptr;
		}
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator OldNode = *this;
			curr_ = curr_->next_;
			return OldNode;
		}
		const_iterator operator--(){
			if(curr_){
				curr_ = curr_->prev_;
			}
			else{
				if(linkedList_){
					curr_ = linkedList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int){
			const_iterator oldNode = *this;
			if(curr_){
				curr_ = curr_->prev_;
			}
			else{
				if(linkedList_){
					curr_ = linkedList_->back_;
				}
			}
			return oldNode;
		}
		bool operator==(const_iterator rhs){
			if(linkedList_ == rhs.linkedList_ && curr_ == rhs.curr_){
				return true;
			}
			else{
				return false;
			}
		}
		bool operator!=(const_iterator rhs){
			if(curr_ != rhs.curr_){
				return true;
			}
			else{
				return false;
			}
		}
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	class iterator:public const_iterator{
	protected:
		friend class CacheList;
        iterator(Node* curr, CacheList* linkedList):const_iterator(curr, linkedList){}
	public:

		iterator():const_iterator(){}
		iterator operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			iterator oldNode = *this;
			if(this->curr_){
				this->curr_ = this->curr_->next_;
			}
			return oldNode;
		}
		iterator operator--(){
			if(this->curr_){
				this->curr_ = this->curr_->prev_;
			}
			return *this;
		}
		iterator operator--(int){
			iterator oldNode = *this;
			if(this->curr_){
				this->curr_ = this->curr_->prev_;
			}
			return oldNode;
		}
		T& operator*(){
			return this->curr_->data_;
		}
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	CacheList();
	~CacheList();
	CacheList(const CacheList& rhs);
	CacheList& operator=(const CacheList& rhs);
	CacheList(CacheList&& rhs);
	CacheList& operator=(CacheList&& rhs);

	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;

	iterator insert(const T& data);
	iterator search(const T& data);

	iterator erase(iterator it);

	bool empty() const;
	int size() const;
};

template <typename T>
CacheList<T>::CacheList(){
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;

}
template <typename T>
CacheList<T>::~CacheList(){
	Node* currentNode = front_;
	while(currentNode != nullptr){
		Node* tempNode = currentNode;
		currentNode = currentNode->next_;
		delete tempNode;
	}
}
//copy constructor
template <typename T>
CacheList<T>::CacheList(const CacheList& rhs){
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	Node* current = rhs.front_->next_;
	while(current != rhs.back_){
		Node* tmp = new Node(current->data_, nullptr, nullptr, current->accessCount_);
		tmp->next_ = back_;
		tmp->prev_ = back_->prev_;
		back_->prev_->next_ = tmp;
		back_->prev_ = tmp;
		current = current->next_;
	}
}

//copy assignment 
template <typename T>
CacheList<T>& CacheList<T>::operator=(const CacheList& rhs){
	if(this != &rhs){
		CacheList tmp(rhs);
		Node* swapFront;
		Node* swapBack;

		swapFront = front_;
		front_ = tmp.front_;
		tmp.front_ = swapFront;

		swapBack = back_;
		back_ = tmp.back_;
		tmp.back_ = swapBack;
	}
	return *this;
}


//move constructor
template <typename T>
CacheList<T>::CacheList(CacheList&& rhs){
	front_ = rhs.front_;
	back_ = rhs.back_;
	
	rhs.front_ = new Node();
	rhs.back_ = new Node();

	rhs.front_->next_ = rhs.back_;
	rhs.back_->prev_ = rhs.front_;
}

//move assignment
template <typename T>
CacheList<T>& CacheList<T>::operator=(CacheList&& rhs){
	Node* tmpFront = front_;
	Node* tmpBack = back_;

	front_ = rhs.front_;
	back_ = rhs.back_;
	rhs.front_ = tmpFront;
	rhs.back_ = tmpBack;

	return *this;
}


template <typename T>
typename CacheList<T>::iterator CacheList<T>::begin(){
	return iterator(front_->next_, this);
}
template <typename T>
typename CacheList<T>::iterator CacheList<T>::end(){
	return iterator(back_, this);
}

template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cbegin() const{
	return const_iterator(front_->next_, this);

}
template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cend() const{
	return const_iterator(back_, this);

}


//insert
template <typename T>
typename CacheList<T>::iterator CacheList<T>::insert(const T& data){
	Node* newNode = new Node(data, nullptr, nullptr, 0);
	if (size() == 0){
		front_->next_ = newNode;
		newNode->prev_ = front_;
		newNode->next_ = back_;
		back_->prev_ = newNode;
		return iterator(newNode, this);
	}
	else{
		Node* currentNode = front_->next_;
		while (currentNode != back_ && currentNode->accessCount_ != 0){
			currentNode = currentNode->next_;
		}
		if (currentNode == back_){
			newNode->prev_ = back_->prev_;
			back_->prev_->next_ = newNode;
			newNode->next_ = back_;
			back_->prev_ = newNode;
			return iterator(newNode, this);
		}
		else{
			newNode->prev_ = currentNode->prev_;
			currentNode->prev_->next_ = newNode;
			newNode->next_ = currentNode;
			currentNode->prev_ = newNode;
			return iterator(newNode, this);
		}
	}
}

template <typename T>
typename CacheList<T>::iterator CacheList<T>::search(const T& data){                            
	Node* currentNode = back_;
	if (front_->next_ != back_){
		currentNode = front_->next_;
		while (currentNode->data_ != data && currentNode != back_){
			currentNode = currentNode->next_;
		}
		if (currentNode != back_){
			currentNode->accessCount_++;
			Node* locationNode = currentNode->prev_;
			while (currentNode->accessCount_ >= locationNode->accessCount_ && locationNode != front_){
				locationNode = locationNode->prev_;
			}
			currentNode->next_->prev_ = currentNode->prev_;
			currentNode->prev_->next_ = currentNode->next_;
			currentNode->next_ = locationNode->next_;
			currentNode->prev_ = locationNode;
			locationNode->next_->prev_ = currentNode;
			locationNode->next_ = currentNode;
		}
	}
	return iterator(currentNode, this);
}

template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator it){
	Node* curr = it.curr_;
	Node* prev = curr->prev_;
	Node* next = curr->next_;
	prev->next_ = next;
	next->prev_ = prev;
	delete curr;
	return iterator(next, this);
}


template <typename T>
bool CacheList<T>::empty() const{
	return (size() == 0 ? true : false);
}
template <typename T>
int CacheList<T>::size() const{
	int size = 0;
	for (const_iterator i = cbegin(); i != cend(); i++) {
		size++;
	}
	return size;
}
