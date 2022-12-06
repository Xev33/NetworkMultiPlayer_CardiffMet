#include "TestObject.h"

#include "InputMemoryStream.h"
#include "OutputMemoryStream.h"

#include <cmath>

TestObject::TestObject()
:a(0),
b(0.0f),
name("")
{

}

TestObject::TestObject(int inA, float inB, std::string inName)
:a(inA),
b(inB),
name(inName)
{

}

TestObject::~TestObject()
{

}

void TestObject::setA(int a)
{
    this->a = a;
}

int TestObject::getA()
{
  return this->a;
}

void TestObject::setB(float b)
{
    this->b = b;
}

float TestObject::getB(void)
{
  return this->b;
}

void TestObject::setName(std::string name)
{
  this->name = name;
}

std::string TestObject::getName()
{
  return this->name;
}

bool TestObject::operator==(TestObject& other)
{
    if(a != other.a) return false;
    if(std::abs(b - other.b) > 0.00001f) return false;
    if(!(name == other.name)) return false;

    return true;
}

void TestObject::Read(InputMemoryStream& in)
{
  int len = 0;
  char temp = 0;

  in.Read(a);
  in.Read(b);
  in.Read(len);

  for(int i = 0; i < len; i++)
  {
    in.Read(temp);
    name += temp;
  }

}

void TestObject::Write(OutputMemoryStream& out)
{
  out.Write(a);
  out.Write(b);

  int len = name.length();
  out.Write(len);

  for(char& c : name) //if this throws an error your compiler can't handle C++11!
    out.Write(c);

}
