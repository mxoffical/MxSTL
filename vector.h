#pragma once

#include "iterator.h"
#include "allocator.h"
#include <utility>

namespace mx
{
	template <typename T>
	class vector
	{
	public:
		vector()
		{
		}

		vector(const vector<T>& _other)
		{
			m_elems = m_allocator.allocate(_other.capacity());
			m_size = _other.m_size;
			for (size_t i = 0; i < _other.size(); ++i)
			{
				m_allocator.construct(m_elems + i, *(_other.m_elems + i));
			}
		}

		vector(vector<T>&& _other) 
		{
			m_allocator = std::move(_other.m_allocator);
			m_elems = _other.m_elems;
			m_size = _other.m_size;
			_other.m_size = 0;
			_other.m_elems = nullptr;
		}

		vector(size_t _size, const T& _elem) : resize(_size, _elem)
		{
		}

		~vector()
		{
		}

		vector<T> operator = (const vector<T>& _other)
		{
			m_elems = m_allocator.allocate(_other.capacity());
			m_size = _other.m_size;
			for (size_t i = 0; i < _other.size(); ++i)
			{
				m_allocator.construct(m_elems + i, *(_other.m_elems + i));
			}

			return *this;
		}

		vector<T> operator = (vector<T>&& _other)
		{
			m_allocator = std::move(_other.m_allocator);
			m_elems = _other.m_elems;
			m_size = _other.m_size;
			_other.m_size = 0;
			_other.m_elems = nullptr;
			return *this;
		}

		void reserve(size_t _capacity)
		{
			if (capacity() < _capacity)
			{
				m_capacity = _capacity;

				T* old_elems = m_elems;

				m_elems = m_allocator.allocate(capacity());

				for (size_t i = 0; i < size(); ++i)
				{
					m_allocator.construct(m_elems + i, std::move(*(old_elems + i)));
				}

				m_allocator.deallocate(old_elems);
			}
		}

		void resize(size_t _size, const T& _elem)
		{
			size_t curSize = _size;

			reserve(_size);

			while (curSize < _size)
			{
				m_allocator.construct(m_allocator.ptr() + curSize, _elem);

				++curSize;
			}
		}

		void shirink_to_fit()
		{
		}

		T& operator [] (size_t Index) const
		{
			return m_elems[Index];
		}

		T& at(size_t Index) const
		{
			return *this[Index];
		}

		T& front() const
		{
			return *this[0];
		}

		T& back() const
		{
			return *this[size() - 1];
		}

		size_t size() const
		{
			return m_size;
		}

		size_t capacity() const
		{
			return m_capacity;
		}

		bool empty()
		{
			return size() > 0;
		}

		void clear()
		{
			for (size_t i = 0; i < size(); ++i)
			{
				m_allocator.destroy(m_elems[i]);
			}

			m_allocator.deallocate(m_elems);
			m_capacity = m_size = 0;
		}

		void push_back(const T& _elem)
		{
			emplace_back(_elem);
		}

		void push_back(T&& _elem)
		{
			emplace_back(std::move(_elem));
		}

		iterator<T> begin()
		{
			return iterator<T>(m_elems);
		}

		iterator<T> end()
		{
			return iterator<T>(m_elems + size());
		}

		template <typename _T>
		void emplace_back(_T&& _elem)
		{
			reserve(size() + 1);

			m_allocator.construct(m_elems + size(), std::forward<_T>(_elem));

			++m_size;
		}

		T* m_elems = nullptr;
		allocator<T> m_allocator;
		size_t m_capacity;
		size_t m_size = 0;
	};

}
