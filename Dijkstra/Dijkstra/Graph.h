#pragma once
#include<stack>
#include<queue>
#include<string>
#include<queue>
#include "Edge.h"
using std::stack;
using std::queue;

template< typename V, typename E>
class Graph
{

public:
	Graph();
	Graph(Graph & copy);
	Graph & operator =(Graph & rhs);
	~Graph();

	void Purge();
	void Reset();
	void DepthFirst(void(*visit)(V));
	void BreadthFirst(void(*visit)(V));
	bool isEmpty();
	void InsertEdge(V from, V to, E edge, double weight);
	void DeleteEdge(V from, V to, E edge);
	void InsertVertex(V data);
	void DeleteVertex(V data);
	list<Vertex<V, E> *> getGraph();

private:
	list<Vertex<V, E> *> m_graph;
};

template <typename V, typename E>
Graph<V, E>::Graph()
{
}

template<typename V, typename E>
inline Graph<V, E>::Graph(Graph<V, E> & copy)
{
	*this = copy;
}

template <typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(Graph<V, E>& rhs)
{
	if (this != &rhs)
	{
		Purge();
		typename list<Vertex<V, E>*>::iterator traversal = rhs.m_graph.begin();
		Vertex<V, E> * temp;
		list<Edge<V, E>*> edgelist; //= (*traversal)->getList();
		typename list<Edge<V, E>*>::iterator edges;// = edgelist.begin();
		while (traversal != rhs.m_graph.end())
		{
			InsertVertex((*traversal)->getData());
			++traversal;
		}
		traversal = rhs.m_graph.begin();
		while (traversal != rhs.m_graph.end())
		{
			temp = (*traversal);
			++traversal;
			edgelist = temp->getList();
			edges = edgelist.begin();
			while (edges != edgelist.end())
			{
				if (traversal != rhs.m_graph.end())
				{
					InsertEdge(temp->getData(), (*traversal)->getData(), (*edges)->getData(), (*edges)->getWeight());
				}
				++edges;
			}
		}
	}
	return *this;
}

template <typename V, typename E>
Graph<V, E>::~Graph()
{
	Purge();
}

template<typename V, typename E>
inline void Graph<V, E>::Purge()
{
	Vertex<V, E> * temp = nullptr;

	typename list<Vertex<V, E>*>::iterator traversal = m_graph.begin();

	while (traversal != m_graph.end())
	{
		temp = (*traversal);
		++traversal;
		delete temp;
		temp = nullptr;
	}
	m_graph.clear();
}

template <typename V, typename E>
void Graph<V, E>::Reset()
{
	typename list<Vertex<V, E>*>::iterator traversal = m_graph.begin();
	while (traversal != m_graph.end())
	{
		(*traversal)->Setprocessed(false);
		++traversal;
	}
}

template <typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit)(V))
{
	Reset();
	if (!isEmpty())
	{
		typename list<Vertex<V, E>*>::iterator traversal = m_graph.begin();
		Vertex<V, E> * temp = nullptr;
		list<Edge<V, E>*> edgetemp = (*traversal)->getList();
		typename list<Edge<V, E>*>::iterator getedges = edgetemp.begin();
		stack<Vertex<V, E>*> mystack;
		mystack.push((*traversal));
		while (!mystack.empty())
		{
			temp = mystack.top();
			mystack.pop();
			edgetemp = temp->getList();
			getedges = edgetemp.begin();
			visit(temp->getData());
			temp->Setprocessed(true);
			while (getedges != edgetemp.end())
			{
				if ((*getedges)->getDest()->Getprocessed() == false)
				{
					mystack.push((*getedges)->getDest());
					(*getedges)->getDest()->Setprocessed(true);
				}
				++getedges;
			}
			edgetemp.clear();
		}
	}

}

template <typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit)(V))
{

	Reset();
	if (!isEmpty())
	{
		typename list<Vertex<V, E>*>::iterator traversal = m_graph.begin();
		Vertex<V, E> * temp = (*traversal);
		list<Edge<V, E>*> edgetemp = (*traversal)->getList();
		typename list<Edge<V, E>*>::iterator getedges = edgetemp.begin();
		queue<Vertex<V, E>*> myque;
		myque.push(temp);
		while (!myque.empty())
		{
			temp = myque.front();
			myque.pop();
			visit(temp->getData());
			edgetemp = temp->getList();
			getedges = edgetemp.begin();
			temp->Setprocessed(true);
			while (getedges != edgetemp.end())
			{
				if ((*getedges)->getDest()->Getprocessed() == false)
				{
					myque.push((*getedges)->getDest());
					(*getedges)->getDest()->Setprocessed(true);
				}
				++getedges;
			}
		}

	}
}

template <typename V, typename E>
bool Graph<V, E>::isEmpty()
{
	return m_graph.empty();
}

template <typename V, typename E>
void Graph<V, E>::InsertEdge(V from, V to, E edge, double weight)
{
	if (!isEmpty())
	{
		typename list<Vertex<V, E>*>::iterator findfrom = m_graph.begin();
		typename list<Vertex<V, E>*>::iterator findto = m_graph.begin();
		while (findfrom != m_graph.end() && (*findfrom)->getData() != from)
		{
			++findfrom;
		}
		if (findfrom != m_graph.end() && (*findfrom)->getData() == from)
		{
			while (findto != m_graph.end() && (*findto)->getData() != to)
			{
				++findto;
			}
			if (findto != m_graph.end() && to == (*findto)->getData())
			{
				Edge<V, E> * newedgeto = new Edge<V, E>(edge, weight, (*findto));
				Edge<V, E> * newedgefrom = new Edge<V, E>(edge, weight, (*findfrom));
				(*findfrom)->getList().push_back(newedgeto);
				(*findto)->getList().push_back(newedgefrom);
			}
		}
	}
}

template <typename V, typename E>
void Graph<V, E>::DeleteEdge(V from, V to, E edge)
{
	if (!isEmpty())
	{
		typename list<Vertex<V, E> *>::iterator findfrom = m_graph.begin();
		typename list<Vertex<V, E>*>::iterator findto = m_graph.begin();
		while (findfrom != m_graph.end() && (*findfrom)->getData() != from)
		{
			++findfrom;
		}
		while (findto != m_graph.end() && (*findto)->getData() != to)
		{
			++findto;
		}
		if (findfrom != m_graph.end() && findto != m_graph.end())
		{
			typename list<Edge<V, E> *>::iterator findedgefrom = (*findfrom)->getList().begin();
			typename list<Edge<V, E> *>::iterator findedgeto = (*findto)->getList().begin();
			Edge<V, E> * temp = nullptr;
			while (findedgefrom != (*findfrom)->getList().end() && (*findedgefrom)->getData() != edge)
			{
				++findedgefrom;
			}
			while (findedgeto != (*findto)->getList().end() && (*findedgeto)->getData() != edge)
			{
				++findedgeto;
			}
			if (findedgefrom != (*findfrom)->getList().end())
			{
				temp = (*findedgefrom);
				(*findfrom)->getList().remove((*findedgefrom));
				delete temp;
				temp = nullptr;
			}
			if (findedgeto != (*findto)->getList().end())
			{
				temp = (*findedgeto);
				(*findto)->getList().remove((*findedgeto));
				delete temp;
				temp = nullptr;
			}
		}
	}
}

template<typename V, typename E>
inline void Graph<V, E>::InsertVertex(V data)
{
	typename list<Vertex<V, E>*>::iterator exists = m_graph.begin();
	while (exists != m_graph.end() && (*exists)->getData() != data)
	{
		++exists;
	}
	if (exists == m_graph.end())
	{
		Vertex<V, E> * newvertex = new Vertex<V, E>(data);
		m_graph.push_back(newvertex);
	}
}

template <typename V, typename E>
void Graph<V, E>::DeleteVertex(V data)
{
	if (!isEmpty())
	{
		typename list<Vertex<V, E> *>::iterator findvertex = m_graph.begin();
		while (findvertex != m_graph.end() && (*findvertex)->getData() != data)
		{
			++findvertex;
		}
		if (findvertex != m_graph.end())
		{
			list<Edge<V, E> *> templist = (*findvertex)->getList();
			typename list<Edge<V, E>*>::iterator getedges = templist.begin();
			while (getedges != templist.end())
			{
				DeleteEdge((*findvertex)->getData(), (*getedges)->getDest()->getData(), (*getedges)->getData());
				++getedges;
			}
			Vertex<V, E> * temp = (*findvertex);
			m_graph.remove((*findvertex));
			delete temp;
			temp = nullptr;
		}
	}
}

template <typename V, typename E>
list<Vertex<V, E>*> Graph<V, E>::getGraph()
{
	return m_graph;
}
