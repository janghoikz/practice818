#include <iostream>
using namespace std;

//타입변환 포인터
class Knight
{
public:
    int _hp = 0;
};
class Item
{
public:
    Item()
    {
        cout << "item()" << endl;
    }
    Item(int itemType) : _itemType(itemType)
    {
        cout << "item(int itemType)" << endl;
    }
    Item(const Item& item)
    {
        cout << "item(const item&)" << endl;
    }
    ~Item()
    { 
        cout << "~item()" << endl;
    }
    void Test()
    {
        cout << "Test Item" << endl;
    }

public:
    int _itemType = 0;
    int _itemDdid = 0;

    char _dummy[4096] = {};
};
enum ItemType
{
    IT_WEAPON = 1,
    IT_ARMOR = 2
};

class Weapon : public Item
{
public:
    Weapon() : Item(IT_WEAPON)
    {
        cout << "Weapon()" << endl;
        _damege = rand() % 100;
    }
    ~Weapon()
    {
        cout << "~Weapon()" << endl;
    }
    void Test()
    {
        cout << "Test Weapon" << endl;
    }
public:
    int _damege = 0;
};

class Armor : public Item
{
public:
    Armor() : Item(IT_ARMOR)
    {
        _itemType = 2;
        cout << "Armor()" << endl;
    }
    ~Armor()
    {
        cout << "~Armor()" << endl;
    }
};

void TestItem(Item item)
{
    //데이터 복사
    //생성될때 생성자 생성
    //사라질때 소멸자 생성
}

void TestItemPtr(Item* item)
{
    item->Test();
}

int main()
{
    //복습
    {
        //// 스택메모리 [ type4 + dbid4 + dummy4096]
        //Item item;

        //// 스택 [ 주소(4~8) ] -> 힙영역 주소 [ type4 + dbid4 + dummy4096]
        //Item* item2 = new Item();

        //TestItem(item);
        //TestItem(*item2);

        //TestItemPtr(&item);
        //TestItemPtr(item2);

        //2번째 방식에서는 점점 가용메모리가 줄어서 크래시가 남 메모리누수발생
        /*delete item2;*/
    }
    //배열
    {
        cout << "-----------------------" << endl;
        // 진짜 아이템이 100개 있는것 (스택 메모리에 올라와 있는)
        //생성자 100번뜸
        //Item item3[100] = {};

        cout << "-----------------------" << endl;
        // 아이템이 100개 있을까?
        // 아이템을 가르키는 100개, 실제 아이템은 1개도 없을수도있음
        //생성자 안뜸
        /*Item* item4[100] = {};

        for (int i = 0; i < 100; i++)
        {
            item4[i] = new Item();
        }
        cout << "-----------------------" << endl;
        for (int i = 0; i < 100; i++)
        {
            delete item4[i];
        }*/
        //연관성이 없는 클래스 사이의 포인터 변환 테스트
        //{
        //    //stack [주소] -> Heap [_hp(4)]
        //    // 암시적으로는 no
        //    // 명시적으로는 가능
        //    Knight* knight = new Knight;

        //    //stack [주소]
        //    Item* item = (Item*)knight;
        //    item->_itemType = 1;
        //    item->_itemDdid = 2;

        //    delete knight;
        //}
        // 부모 -> 자식 변환 테스트
        //{
        //    Item* item = new Item();

        //    //엉뚱한 메모리가 건들여져서 크래쉬가 남
        //    //Weapon* weapon = (Weapon*)item;

        //    delete item;
        //}
        //// 자식 -> 부모 변환 테스트
        //{
        //    Weapon* weapon = new Weapon();

        //    //암시적으로도 가능;
        //    Item* item = weapon;

        //    delete weapon;
        //}
        // 명시적으로 타입 변환할때는 항상 항상 조심해야한다!
        // 암시적으로 될때는 안전하다?
        // ->평생 명시적으로 타입 변환안하면되는거 아닌가?
    }

    Item* inventory[20] = {};
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < 20; i++)
    {
        int randValue = rand() % 2;
        switch (randValue)
        {
        case 0:
            inventory[i] = new Weapon();
            break;
        case 1:
            inventory[i] = new Armor();
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        Item* item = inventory[i];
        if (item == nullptr)
        {
            continue;
        }
        if (item->_itemType == IT_WEAPON)
        {
            Weapon* weapon = (Weapon*)item;
            cout << "Weapon Damage : " << weapon->_damege << endl;
        }
    }
    // ****************** 매우 중요 ************************
    for (int i = 0; i < 20; i++)
    {
        Item* item = inventory[i];
        if (item == nullptr)
        {
            continue;
        }
        delete item;
    }
    // 결론
    // - 포인터 vs 일반타입 : 차이를 이해하자
    // - 포인터 사이의 타입변환(캐스팅)을 할때는 매우매우 조심해야한다!
    // 부모-자식 관게에서 부모클래스의 소멸자에는 까먹지 말고 virtual을 붙이자!!
}