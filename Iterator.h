#pragma once

namespace mx
{
	template <typename T>
	struct iterator
	{
		iterator(T* _elem) : m_elem(_elem)
		{
		}

		iterator<T> operator++()
		{
			return iterator<T>(++m_elem);
		}

		iterator<T> operator--()
		{
			return iterator<T>(--m_elem);
		}

		T* operator*()
		{
			return m_elem;
		}

		T* operator->()
		{
			return *(*this);
		}

		bool operator != (const iterator<T>& _other)
		{
			return m_elem != _other.m_elem;
		}

	private:
		T* m_elem;
	};
}
