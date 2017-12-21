#pragma once
#include <list>
using std::list;

template<typename V, typename E>
class Edge;

template<typename V, typename E>
class Graph;

//static int position = 0;

template<typename V, typename  E>
class Vertex
{
	friend Graph<V, E>;
public:
	Vertex();
	Vertex(V data);
	Vertex(const Vertex & copy);
	Vertex<V, E> & operator =(const Vertex & rhs);
	V getData();
	list<Edge<V, E>*> & getList();
	void SetData(V data);
	void Setprocessed(bool processed);
	bool Getprocessed() const;
	void Setposition(int pos);
	int Getposition();
	~Vertex();

private:
	int m_position;
	bool m_processed;
	V m_data;
	list<Edge<V, E>*> m_List;

};

template<typename V, typename E>
inline Vertex<V, E>::Vertex() : m_processed(false)
{
}

template <typename V, typename E>
Vertex<V, E>::Vertex(V data) : m_data(data), m_processed(false)
{
}

template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex& copy) : m_processed(copy.m_processed), m_List(copy.m_List), m_data(copy.m_data)
{
}

template<typename T, typename Y>
inline Vertex<T, Y>& Vertex<T, Y>::operator=(const Vertex & rhs)
{
	if (this != &rhs)
	{
		m_processed = rhs.m_processed;
		m_data = rhs.m_data;
		m_List = rhs.m_List;
	}
	return *this;
}

template <typename V, typename E>
V Vertex<V, E>::getData()
{
	return m_data;
}

template <typename V, typename E>
list<Edge<V, E>*> & Vertex<V, E>::getList()
{
	return m_List;
}

template <typename V, typename E>
void Vertex<V, E>::SetData(V data)
{
	m_data = data;
}

template<typename V, typename E>
inline void Vertex<V, E>::Setprocessed(bool processed)
{
	m_processed = processed;
}

template <typename V, typename E>
bool Vertex<V, E>::Getprocessed() const
{
	return m_processed;
}

template <typename V, typename E>
void Vertex<V, E>::Setposition(int pos)
{
	m_position = pos;
}

template <typename V, typename E>
int Vertex<V, E>::Getposition()
{
	return m_position;
}

template<typename V, typename E>
inline Vertex<V, E>::~Vertex()
{
	Edge<V, E> * temp = nullptr;
	typename list<Edge<V, E> *>::iterator traversal = m_List.begin();

	while (traversal != m_List.end())
	{
		temp = (*traversal);
		++traversal;
		delete temp;
		temp = nullptr;
	}

	m_List.clear();
}
