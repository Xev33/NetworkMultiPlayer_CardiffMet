#ifndef _TEST_OBJECT_H_
#define _TEST_OBJECT_H_

#include <string>
class InputMemoryStream;
class OutputMemoryStream;

class TestObject
{
private:
  int a;
  float b;

  std::string name;
public:
  TestObject();
  TestObject(int inA, float inB, std::string inName);
  ~TestObject();

  void setA(int a);
  int getA();

  void setB(float b);
  float getB(void);

  void setName(std::string name);
  std::string getName();

  bool operator==(TestObject& other);

  void Read(InputMemoryStream& in);
  void Write(OutputMemoryStream& out);

};
#endif //_TEST_OBJECT_H_
