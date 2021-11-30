#include <QCoreApplication>
#include <QDebug>

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
class MyLinkedList {
public:
    struct SinglyListNode {
        int val;
        SinglyListNode *next;
        SinglyListNode(int x) : val(x), next(nullptr) {}
    };

    MyLinkedList()
    {
        size = 0;
        head = nullptr;
    }

    int get(int index)
    {
        if(size == 0)
        {
            return -1;
        } else if(size < index) {
            return -1;
        } else {
            int curindex = 0;
            SinglyListNode *last = head;
            SinglyListNode *next = last->next;

            while (last->next) {
                if(curindex == index)
                {
                    break;
                }
                last = next;
                next = next->next;
                curindex++;
            }
            return last->val;
        }
    }

    void addAtHead(int val)
    {
        if(size == 0)
        {
            head = new SinglyListNode(val);
        } else {
            SinglyListNode *node = new SinglyListNode(val);
            node->next = head;
            head = node;
        }
        size++;
    }

    void addAtTail(int val)
    {
        if(size == 0)
        {
            head = new SinglyListNode(val);
        } else {
            SinglyListNode *temp = head;
            SinglyListNode *last = temp;
            while (temp) {
                last = temp;
                temp = temp->next;
            }
            temp = new SinglyListNode(val);
            last->next = temp;
        }
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if(index<=0) addAtHead(val);//插入index的时候，如果下标是=0,就相当于从头插入，所以要包含<=
        else if(index==size) addAtTail(val);
        else if(index>size) return ;
        else {
            SinglyListNode *node = new SinglyListNode(val);
            SinglyListNode *cur = head;
            SinglyListNode *last = cur;
            while (index--) {
                last = cur;
                cur = cur->next;
            }
            node->next = last->next;
            last->next = node;
            size++;
        }

    }

    void deleteAtIndex(int index)
    {
        if(size != 0 && index >= 0 && index <= size)
        {
            int curindex = 0;
            SinglyListNode *last = head;
            SinglyListNode *next = last->next;
            SinglyListNode *temp = nullptr;
            while (last->next) {
                if(curindex == index)
                {
                    break;
                }
                temp = last;
                last = next;
                next = next->next;
                curindex++;
            }
            delete last;
            last = nullptr;
            last = next;
            if(temp) temp->next = last;

            size--;
        }
    }

private:
    int size;
    SinglyListNode *head;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MyLinkedList linkedList;
    linkedList.addAtHead(1);
    linkedList.addAtTail(3);
    linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
    qDebug() << QString::number(linkedList.get(1));            //返回2
    linkedList.deleteAtIndex(1);  //现在链表是1-> 3
    qDebug() << QString::number(linkedList.get(1));            //返回2


    return app.exec();
}
