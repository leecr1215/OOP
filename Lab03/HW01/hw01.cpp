#include <iostream>
class SetValue {
private:
	int x, y;
public:
	void setX(int a)
	{
		x = a;
	}
	void setY(int a)
	{
		y = a;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};

int main() {
	SetValue obj;
	obj.setX(33);
	obj.setY(44);

	std::cout << "X = " << obj.getX() << " ,Y = " << obj.getY() << std::endl;
	return 0;
}
