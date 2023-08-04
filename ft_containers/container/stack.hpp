#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{	
		template <class _T, class _Container>
		friend bool	operator==(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool	operator!=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool	operator<(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool	operator<=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool	operator>(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool	operator>=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		private:
			container_type	data;

		public:
			explicit stack (const container_type& ctnr = container_type())
			{ this->data = ctnr; }

			bool	empty() const
			{ return (this->data.empty()); }

			void	pop()
			{ this->data.pop_back(); }

			void	push(const value_type& val)
			{ this->data.push_back(val); }

			size_type	size() const
			{ return (this->data.size()); }

			value_type&	top()
			{ return *(--this->data.end()); }
			const value_type&	top() const
			{ return *(--this->data.end()); }
	};

	template <class T, class Container>
	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data == rhs.data); }

	template <class T, class Container>
	bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data != rhs.data); }

	template <class T, class Container>
	bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data < rhs.data); }

	template <class T, class Container>
	bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data <= rhs.data); }

	template <class T, class Container>
	bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data > rhs.data); }

	template <class T, class Container>
	bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lhs.data >= rhs.data); }
}