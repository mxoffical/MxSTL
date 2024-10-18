#pragma once

#include <new>
#include <utility>

template <typename T>
struct allocator
{
	T* allocate(size_t _size)
	{
		return (T*) malloc(_size * sizeof(T));
	}

	void deallocate(T* elems)
	{
		free(elems);
	}

	template <typename ...args>
	T* construct(T* _ptr, args&&... _args)
	{
		return new (_ptr) (T)(std::forward<args>(_args)...);
	}

	void destroy(T* _ptr)
	{
		_ptr->~T();
	}
};