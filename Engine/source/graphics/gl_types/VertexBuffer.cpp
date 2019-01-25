#include "VertexBuffer.h"
#include "pch.h"


using namespace graphics;

VertexBuffer::VertexBuffer(const void* vertices, const unsigned int size)
	:id(0)
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

void VertexBuffer::Delete()
{
	GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::PushLayout(unsigned int layoutSize, unsigned int type, bool normalized)
{
	stride += GetSizeOfType(type)* layoutSize;
	vbLayout.push_back(std::forward_as_tuple( layoutSize, type, normalized ));
}

unsigned int VertexBuffer::GetSizeOfType(unsigned int type)
{
	switch (type) 
	{
	case GL_FLOAT:			return 4;
	case GL_UNSIGNED_INT:   return 4;
	case GL_UNSIGNED_BYTE:  return 1;
	}
	return -1;
}