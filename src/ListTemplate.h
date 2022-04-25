#pragma once
template <typename ElementType>
class IteratorListTemplate;

template <typename ElementType>
class ListTemplate
{
public:
	/**
	 * @brief Default constructor
	 * Allocate memory for 2 elements by default
	*/
	ListTemplate();
	/**
	 * @brief Copy constructor
	 * @param lt ListTemplate&
	*/
	ListTemplate(const ListTemplate& lt);

	/**
	 * @brief Default de-constructor
	*/
	~ListTemplate();

	/**
	 * @brief Assignment operator
	 * @param lt ListTemplate
	 * @return Copies the element from lt to this.
	*/
	ListTemplate& operator=(const ListTemplate& lt);

	/**
	 * @brief Removes element at given position
	 * @param pos int
	*/
	void remove(const int pos);

	/**
	 * @brief Move constructor
	 * @param lt ListTemplate &&
	*/
	ListTemplate(ListTemplate&& lt) noexcept;

	/**
	 * @brief Move assignment
	 * @param lt ListTemplate &&
	 * @return Moves content from lt to this
	*/
	ListTemplate& operator=(ListTemplate&& lt) noexcept;

	/**
	 * @brief Adds element to List
	 * @param el ElementType&
	*/
	void add(const ElementType& el);

	/**
	 * @brief Get element at given position
	 * @param pos int 
	 * @return ElementType&
	*/
	ElementType& get(int pos) const;

	/**
	 * @brief Set element at given position
	 * @param pos int
	 * @param el ElementType &
	*/
	void set(int pos, ElementType& el);

	/**
	 * @brief Number of elements
	 * @return int
	*/
	int size() const noexcept;

	ElementType* getAll();
private:
	int len;
	int cap;
	ElementType* elements;

	void ensureCapacity();
};

template <typename ElementType>
ListTemplate<ElementType>::ListTemplate() : elements{new ElementType[5]}, cap{5}, len{0}
{
}

template <typename ElementType>
ListTemplate<ElementType>::ListTemplate(const ListTemplate& lt)
{
	elements = new ElementType[lt.cap];
	for (int i = 0; i < lt.len; ++i)
	{
		elements[i] = lt.elements[i];
	}
	len = lt.len;
	cap = lt.cap;
}

template <typename ElementType>
ListTemplate<ElementType>::~ListTemplate()
{
	delete[] elements;
}

template <typename ElementType>
ListTemplate<ElementType>& ListTemplate<ElementType>::operator=(const ListTemplate& lt)
{
	if (this == &lt)
		return *this;

	delete[] elements;

	elements = new ElementType[lt.cap];

	for (int i = 0; i < lt.len; ++i)
	{
		elements[i] = lt.elements[i];
	}

	len = lt.len;
	cap = lt.cap;

	return *this;
}

template <typename ElementType>
void ListTemplate<ElementType>::remove(const int pos)
{
	for (int i = pos; i < len - 1; ++i)
	{
		elements[i] = elements[i + 1];
	}
	len--;
}

template <typename ElementType>
ListTemplate<ElementType>::ListTemplate(ListTemplate&& lt) noexcept
{
	elements = lt.elements;
	len = lt.len;
	cap = lt.cap;

	lt.elements = nullptr;
	lt.len = 0;
	lt.cap = 0;
}

template <typename ElementType>
void ListTemplate<ElementType>::add(const ElementType& el)
{
	ensureCapacity();
	elements[len++] = el;
}

template <typename ElementType>
ElementType& ListTemplate<ElementType>::get(int pos) const
{
	return elements[pos];
}

template <typename ElementType>
void ListTemplate<ElementType>::set(int pos, ElementType& el)
{
	elements[pos] = el;
}

template <typename ElementType>
int ListTemplate<ElementType>::size() const noexcept
{
	return len;
}

template <typename ElementType>
ElementType* ListTemplate<ElementType>::getAll()
{
	return elements;
}

template <typename ElementType>
void ListTemplate<ElementType>::ensureCapacity()
{
	if (len < cap)
	{
		return; //mai avem loc
	}
	cap *= 2;
	ElementType* aux = new ElementType[cap];
	for (int i = 0; i < len; i++)
	{
		aux[i] = elements[i];
	}
	delete[] elements;
	elements = aux;
}


template <typename ElementType>
class IteratorListTemplate
{
private:
	const ListTemplate<ElementType>& v;
	int poz = 0;
public:
	/**
	 * @brief Default constructor
	 * @param v ListTemplate
	 * @return
	*/
	IteratorListTemplate(const ListTemplate<ElementType>& v) noexcept;
	/**
	 * @brief Constructor with given postion
	 * @param v LIstTemplate
	 * @param poz int 
	 * @return 
	*/
	IteratorListTemplate(const ListTemplate<ElementType>& v, int poz) noexcept;
	/**
	 * @brief Function to check if a Iterator is valid
	 * @return true if is valid, false otherwise 
	*/
	bool valid() const;
	/**
	 * @brief Current element
	 * @return ElementType
	*/
	ElementType& element() const;
	/**
	 * @brief Next element
	*/
	void next();
	/**
	 * @brief Current element address
	 * @return ElementType&
	*/
	ElementType& operator*();
	/**
	 * @brief Increment operator
	 * @return new value after increment
	*/
	IteratorListTemplate& operator++();
	/**
	 * @brief Equal operator
	 * @param ot checking equality with 
	 * @return true if equally, false otherwise
	*/
	bool operator==(const IteratorListTemplate& ot) noexcept;
	/**
	 * @brief Not equal operator
	 * @param ot checking equality with 
	 * @return false if equally, true otherwise
	*/
	bool operator!=(const IteratorListTemplate& ot) noexcept;
};


template <typename ElementType>
IteratorListTemplate<ElementType>::IteratorListTemplate(const ListTemplate<ElementType>& v) noexcept: v{v}
{
}

template <typename ElementType>
IteratorListTemplate<ElementType
>::IteratorListTemplate(const ListTemplate<ElementType>& v, int poz) noexcept : v{v}, poz{poz}
{
}

template <typename ElementType>
bool IteratorListTemplate<ElementType>::valid() const
{
	return poz < v.len;
}

template <typename ElementType>
ElementType& IteratorListTemplate<ElementType>::element() const
{
	return v.elements[poz];
}

template <typename ElementType>
void IteratorListTemplate<ElementType>::next()
{
	poz++;
}

template <typename ElementType>
ElementType& IteratorListTemplate<ElementType>::operator*()
{
	return element();
}

template <typename ElementType>
IteratorListTemplate<ElementType>& IteratorListTemplate<ElementType>::operator++()
{
	next();
	return *this;
}

template <typename ElementType>
bool IteratorListTemplate<ElementType>::operator==(const IteratorListTemplate<ElementType>& ot) noexcept
{
	return poz == ot.poz;
}

template <typename ElementType>
bool IteratorListTemplate<ElementType>::operator!=(const IteratorListTemplate<ElementType>& ot) noexcept
{
	return !(*this == ot);
}
