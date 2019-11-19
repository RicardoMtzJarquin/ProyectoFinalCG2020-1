#ifndef CLinkedListH
#define CLinkedListH

#include <stdio.h>

class CItem
{
public:
	CItem(){next=NULL; prev=NULL;};
	CItem* next;
    CItem* prev;
};

template <class T> class CLinkedList
{
public:
	CLinkedList();
   ~CLinkedList();

	bool InsertFirst(T*);	//Function to insert a element as the begining of the list
	bool InsertLast(T*);    //Function to insert a element as the end of the list
    bool EraseFirst();  //Function to delete the first element in the list
    bool EraseLast();   //Function to delete the last element of the list
	T* EraseCurrent();
	T* Erase(T*);

    bool First2Last();

	T* begin;
	T* end;
	T* current;
};

template <class T>
CLinkedList<T>::CLinkedList()
{
	begin=NULL;
	end=NULL;
}

template <class T>
CLinkedList<T>::~CLinkedList()
{
	current=begin;
	while(current!=NULL)
	{
		T* temp=current;
		current=(T*)current->next;
		delete temp;
	}

	begin=NULL;
	end=NULL;
	current=NULL;
}

template <class T>
bool CLinkedList<T>::InsertFirst(T* _item)
{
	if(_item != NULL)
	{
		if(begin==NULL && end==NULL)
		{
			begin=_item;
			end  =_item;
		}
		else
		{
			_item->next=begin;
            begin->prev=_item;
			begin=_item;
		}
		return true;
	}
    return false;
}

template <class T>
bool CLinkedList<T>::InsertLast(T* _item)
{
	if(_item != NULL)
	{
        if(begin==NULL && end==NULL)
        {
            begin=_item;
            end  =_item;
        }
        else
        {
		    end->next=_item;
            _item->prev=end;
            end=_item;
        }
	    return true;
	}
	return false;
}

template <class T>
bool CLinkedList<T>::EraseFirst()
{
    if(begin!=NULL)
    {
        if(begin==end)
        {
            delete begin;
            begin=NULL;
            end=NULL;
            return true;
        }

		T* temp=begin;
        begin=(T*)temp->next;
        begin->prev=NULL;
        delete temp;
        return true;
    }
    return false;
}

template <class T>
bool CLinkedList<T>::EraseLast()
{
    if(end!=NULL)
    {
        if(begin==end)
        {
            delete end;
            begin=NULL;
            end=NULL;
            return true;
        }

		T* temp=end;
        end=(T*)temp->prev;
        end->next=NULL;

        delete temp;
        return true;
    }
    return false;
}

template<class T>
T* CLinkedList<T>::EraseCurrent()
{
	if(current != NULL)
	{
		if(begin==end)
        {
			if(current==begin)
			{
				delete current;
				begin=NULL;
				end=NULL;
				return NULL;
			}
        }
        else
        {
            if(current==begin)
            {
                begin=(T*)current->next;
                begin->prev=NULL;
                delete current;
				return begin;
            }
            else
            {
                if(current==end)
                {
                    end=(T*)current->prev;
                    end->next=NULL;
                    delete current;
                    return end;
                }
                else
                {
                    current->next->prev=current->prev;
                    current->prev->next=current->next;
                    T* temp=(T*)current->next;
                    delete current;
                    return temp;
                }
            }
        }
	}
	return NULL;
}

template<class T>
T* CLinkedList<T>::Erase(T* _item)
{
	T* temp=begin;
	while(temp)
	{
		if(temp==_item)
		{
			if((temp==end) && (temp==begin))	//si es el unico elemento en la lista
			{				
				delete temp;
				begin=NULL;
				end=NULL;
				return NULL;
				
			}
			else
			{
				if(temp==begin)	//si es el primer elemento
				{
					begin=(T*)temp->next;
					begin->prev=NULL;
					delete temp;
					return begin;
				}
				else
				{
					if(temp==end)		//si es el fin de la lista
					{
						end=(T*)temp->prev;
						end->next=NULL;
						delete temp;
						return end;
					}
					else				//esta en medio de la lista
					{
						temp->next->prev=temp->prev;
						temp->prev->next=temp->next;
						T* t=(T*)temp->next;
						delete temp;
						return t;
					}
				}
			}
			break;
		}
		temp=(T*)temp->next;
	}
	return NULL;    
}

template<class T>
bool CLinkedList<T>::First2Last()
{
    if(begin!=end)
    {
        T* temp=begin;
        begin=(T*)temp->next;
        begin->prev=NULL;
        end->next=temp;
        temp->prev=end;
        temp->next=NULL;
        end=temp;
        return true;
    }
    return false;
}

#endif
