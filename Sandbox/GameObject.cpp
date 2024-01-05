#include "GameObject.h"
#include "GameState.h"

int GameObject::m_next_id = 0;

GameObject::GameObject(GameState* gs, const std::string& name)
{
	this->m_state = gs;
	this->m_id = GameObject::m_next_id;
	this->m_name = name;
	GameObject::m_next_id++;
}

void GameObject::update(float dt) 
{

}

void GameObject::init()
{
}

void GameObject::draw()
{
}

GameObject::~GameObject() 
{
}

bool GameObject::isActive() 
{
	return m_active; 
}
void GameObject::setActive(bool a) 
{ 
	m_active = a; 
}