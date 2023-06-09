#include "ObjectManager.h"

namespace Utilities
{
    Object::ID ObjectManager::m_nextId = 0;

    ObjectManager::ObjectManager()
        : m_lastError(Error::none)
    {
       
    }
    ObjectManager::~ObjectManager()
    {
        clear();
    }

    Object::ID ObjectManager::generateID()
    {
        size_t id = m_nextId++;
        while (m_objects.count(id) != 0) {
            id = m_nextId++;
        }
        return id;
    }

    bool ObjectManager::addObject(Object* obj)
    {
        if (!obj)
        {
            m_lastError = Error::object_is_nullptr;
            return false;
        }
        Object& objRef = *obj;
        size_t id = objRef.getID();
        auto it = m_objects.find(id);
        if (it != m_objects.end())
        {
            if (it->second == obj)
            {
                m_lastError = Error::object_already_in_manager;
                return false;
            }
            m_lastError = Error::object_with_ID_already_exists;
            return false;
        }
        /*ObjectManager* otherManager = obj->getManager();
        if (otherManager && otherManager != this)
        {
            obj->freeFromManager();
        }*/
        objRef.freeFromManager();
        m_objects[id] = obj;
        objRef.setManager(this);
        return true;
    }
    bool ObjectManager::removeObject(Object::ID id)
    {
        auto it = m_objects.find(id);
        if (it != m_objects.end())
        {
            if (it->second)
            {
                it->second->setManager(nullptr);
            }
            m_objects.erase(it);
            return true;
        }
        return false;
    }
    bool ObjectManager::exists(Object::ID id)
    {
        auto it = m_objects.find(id);
        if (it != m_objects.end())
            return true;
        return false;
    }
    Object* ObjectManager::getObject(Object::ID id) const
    {
        auto it = m_objects.find(id);
        if (it != m_objects.end()) {
            return it->second;
        }
        m_lastError = Error::no_object_with_such_id;
        return nullptr;
        //return this->operator[](id);
    }
    Object* ObjectManager::operator[](Object::ID id) const
    {
        auto it = m_objects.find(id);
        if (it != m_objects.end()) {
            return it->second;
        }
        m_lastError = Error::no_object_with_such_id;
        return nullptr;
    }
    void ObjectManager::reserve(size_t capacity)
    {
        m_objects.reserve(capacity);
    }
    size_t ObjectManager::getObjectCount() const
    {
        return m_objects.size();
    }
    void ObjectManager::clear()
    {
        for (auto& it : m_objects) {
            Object* obj = it.second;
            if (obj)
            {
                obj->setManager(nullptr);
            }
        }
        m_objects.clear();
    }

    ObjectManager::Error ObjectManager::getLastError() const
    {
        return m_lastError;
    }
    void ObjectManager::resetLastError() const
    {
        m_lastError = Error::none;
    }

    ObjectManager::iterator::iterator(typename std::unordered_map<Object::ID, Object*>::iterator iter) 
        : 
        it(iter) 
    {

    }

    ObjectManager::iterator ObjectManager::iterator::operator++() {
        ++it;
        return *this;
    }

    Object*& ObjectManager::iterator::operator*() {
        return it.operator*().second;
    }

    bool ObjectManager::iterator::operator==(const iterator& other) const {
        return it == other.it;
    }

    bool ObjectManager::iterator::operator!=(const iterator& other) const {
        return it != other.it;
    }

    ObjectManager::iterator ObjectManager::begin() {
        return iterator(m_objects.begin());
    }

    ObjectManager::iterator ObjectManager::end() {
        return iterator(m_objects.end());
    }

}