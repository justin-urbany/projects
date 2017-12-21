#pragma once
#include "Vertex.h"


template<typename V, typename E>
class Edge
{
public:
	Edge();
	Edge(E data, double Weight, Vertex<V, E> * destination);
	Edge(const Edge & copy);
	Edge<V, E> & operator=(const Edge<V, E> & rhs);
	Vertex<V, E> * getDest();
	E getData();
	double getWeight();
	~Edge();

private:
	E m_data;
	double m_weight;
	Vertex<V, E> * m_destination;

};

template <typename V, typename E>
::Edge<V, E>::Edge() : m_weight(0), m_destination(nullptr)
{
}

template<typename V, typename E>
inline Edge<V, E>::Edge(E data, double Weight, Vertex<V, E> * destination) : m_data(data), m_weight(Weight), m_destination(destination)
{
}

template <typename V, typename E>
Edge<V, E>::Edge(const Edge& copy)
{
	*this = copy;
}

template <typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(const Edge<V, E>& rhs)
{
	if (this != &rhs)
	{
		m_weight = rhs.m_weight;
		m_destination = rhs.m_destination;
		m_data = rhs.m_data;
	}
	return *this;
}

template <typename V, typename E>
Vertex<V, E>* Edge<V, E>::getDest()
{
	return m_destination;
}

template <typename V, typename E>
E Edge<V, E>::getData()
{
	return m_data;
}

template <typename V, typename E>
double Edge<V, E>::getWeight()
{
	return m_weight;
}

template<typename V, typename E>
inline Edge<V, E>::~Edge()
{

}
