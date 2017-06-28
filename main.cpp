

#include <iostream>
using namespace std;

#include "MyGroupManager.h"


template<class T>
class ALWAYS : public wiz::MGM::Condition<T>
{
public:
	virtual bool operator() (const wiz::MGM::Item<T>& item, const wiz::MGM::Group<T>& group) const {
		return true;
	}
};

class PlusOne : public wiz::MGM::Func<int>
{
public:
	virtual void operator()(wiz::MGM::Item<int>& item)
	{
		item.setValue(item.getValue() + 1);
	}
};


template <class T>
class Print : public wiz::MGM::Func<T>
{
public:
	virtual void operator()(wiz::MGM::Item<T>& item)
	{
		std::cout << item.getName() << " " << item.getValue() << std::endl;
	}
};

int main(void)
{
	wiz::MGM::GroupManager<int> test("global");
	
	test.NewItem("chk", 1);
	test.NewItem("chk2", 2);

	test.NewGroup("test", 1, 1);

	test.AddItemToGroup("chk", "test");
	test.AddItemToGroup("chk2", "test");

	test.Do("test", Print<int>(), ALWAYS<int>());
	test.Do("test", PlusOne(), ALWAYS<int>());
	test.Do("test", Print<int>(), ALWAYS<int>());

	return 0;
}

