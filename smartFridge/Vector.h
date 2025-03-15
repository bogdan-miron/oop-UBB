#pragma once
#include <cassert>
#include <iostream>

template<typename T>

class Vector {
public:
	Vector() {
		ReAlloc(2);
	}

	~Vector() {
		delete[] elems;
	}

	void PushBack(const T& value) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		elems[m_Size++] = value;
	}

	//rvalue ref
	void PushBack(T&& value) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		elems[m_Size++] = std::move(value);
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		new(&elems[m_Size]) T(std::forward<Args>(args)...);
		//elems[m_Size] = T(std::forward<Args>(args)...);
		return elems[m_Size++];
	}

	void PopBack() {
		if (m_Size > 0) {
			--m_Size;
			elems[m_Size].~T();
		}
	}

	void Clear() {
		while (m_Size > 0) {
			PopBack();
		}
		m_Size = 0;
	}

	size_t Size() const {
		return m_Size;
	}

	const T& operator[](size_t index) const {
		assert(index < m_Size);
		return elems[index];
	}

	T& operator[](size_t index) {
		assert(index < m_Size);
		return elems[index];
	}

	class Iterator {
	public:
		Iterator(T* ptr) : m_Ptr(ptr) {}

		T& operator*() {
			return *m_Ptr;
		}

		const T& operator*() const {
			return *m_Ptr;
		}

		T* operator->() {
			return m_Ptr;
		}

		const T* operator->() const {
			return m_Ptr;
		}

		Iterator& operator++() {
			++m_Ptr;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const Iterator& other) const {
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const Iterator& other) const {
			return m_Ptr != other.m_Ptr;
		}

	private:
		T* m_Ptr;
	};

	Iterator begin() {
		return Iterator(elems);
	}

	Iterator end() {
		return Iterator(elems + m_Size);
	}

private:
	void ReAlloc(size_t newCapacity) {
		T* newBlock = new T[newCapacity];

		if (newCapacity < m_Size) {
			m_Size = newCapacity;
		}

		for (size_t i = 0; i < m_Size; ++i) {
			newBlock[i] = std::move(elems[i]); // cast as rvalue and move, don't copy
		}

		delete[] elems;
		elems = newBlock;
		m_Capacity = newCapacity;
	}
private:
	T* elems = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;

};
