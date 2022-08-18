#include <iostream>
using namespace std;

//타입변환 포인터
class Item
{
public:
    Item()
    {
        cout << "item()" << endl;
    }
    Item(const Item& item)
    {
        cout << "item(const item&)" << endl;
    }
    ~Item()
    { 
        cout << "~item()" << endl;
    }

public:
    int _itemType = 0;
    int _itemDdid = 0;

    char _dummy[4096] = {};
};

void TestItem(Item item)
{
    //데이터 복사
    //생성될때 생성자 생성
    //사라질때 소멸자 생성
}

void TestItemPtr(Item* item)
{

}

int main()
{
    //복습
    {
        // 스택메모리 [ type4 + dbid4 + dummy4096]
        Item item;

        // 스택 [ 주소(4~8) ] -> 힙영역 주소 [ type4 + dbid4 + dummy4096]
        Item* item2 = new Item();

        TestItem(item);
        TestItem(*item2);

        TestItemPtr(&item);
        TestItemPtr(item2);

        //2번째 방식에서는 점점 가용메모리가 줄어서 크래시가 남 메모리누수발생
        delete item2;
    }
    //배열
    {
        cout << "-----------------------" << endl;
        // 진짜 아이템이 100개 있는것 (스택 메모리에 올라와 있는)
        //생성자 100번뜸
        Item item3[100] = {};

        cout << "-----------------------" << endl;
        // 아이템이 100개 있을까?
        // 아이템을 가르키는 100개, 실제 아이템은 1개도 없을수도있음
        //생성자 안뜸
        Item* item4[100] = {};

        for (int i = 0; i < 100; i++)
        {
            item4[i] = new Item();
        }
        cout << "-----------------------" << endl;
        for (int i = 0; i < 100; i++)
        {
            delete item4[i];
        }
    }
}