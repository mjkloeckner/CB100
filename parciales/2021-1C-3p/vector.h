#ifndef VECTOR_H
#define VECTOR_H
#define	VECTOR_STARTING_CAPACITY	5

template <typename Type>
class Vector {
private:
	Type *data;
	unsigned int size;
	unsigned int alloc;

public:
	Vector() {
		this->data = new Type[VECTOR_STARTING_CAPACITY];
		this->alloc = VECTOR_STARTING_CAPACITY;
		this->size = 0;
	}

	virtual ~Vector() {
		delete[] this->data;
	}

	void append(Type value) {
		if(this->size == this->alloc) {
			this->alloc *= 2;
			Type *newData = new Type[this->alloc];
			for(size_t i = 0; i < this->size; ++i) {
				newData[i] = this->data[i];
			}
			delete[] this->data;
			this->data = newData;
		}
		this->data[this->size] = value;
		this->size++;
	}

	unsigned int getSize() {
		return this->size;
	}

	Type getAtIndex(unsigned int index) {
		if(index > this->size) {
			throw "index out of bounds";
		}
		return this->data[index];
	}
};

#endif
