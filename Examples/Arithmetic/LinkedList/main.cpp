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
    struct Node {
        int val;
        Node *next;
        Node(int x) : val(x), next(nullptr) {}
    };

    MyLinkedList()
    {
        size = 0;
        head = nullptr;
    }

    int get(int index)
    {
        if(index < 0 || index >(size-1)) return -1;
        Node *cur = head;
        while((index--)) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        Node *newnode = new Node(val);
        newnode->next = head;
        head = newnode;
        size++;
    }

    void addAtTail(int val)
    {
        if(size == 0)
        {
            addAtHead(val);
            return;
        }
        Node *cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        Node *newnode = new Node(val);
        newnode->next = cur->next;
        cur->next = newnode;
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if(index <= 0) addAtHead(val);
        else if(index == size) addAtTail(val);
        else if(index > size) return;
        else {
            Node *newnode = new Node(val);
            Node *cur = head;
            Node *last = nullptr;
            while (index--) {
                last = cur;
                cur = cur->next;
            }
            newnode->next = cur;
            if(last)
            {
                last->next = newnode;
            } else {
                last = newnode;
            }

            size++;
        }
    }

    void deleteAtIndex(int index)
    {
        if(index<0||index>=size) return;
        Node *last = nullptr;
        Node *cur = head;
        while (index--) {
           last = cur;
           cur = cur->next;
        }
        if(last)
        {
            last->next = cur->next;
        } else {
            head = cur->next;
        }
        delete cur;
        cur = nullptr;
        size--;
    }

private:
    int size;
    Node *head;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MyLinkedList linkedList;
    /*
    linkedList.addAtHead(1);
    linkedList.addAtTail(3);
    linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
    qDebug() << QString::number(linkedList.get(1));            //返回2
    linkedList.deleteAtIndex(0);  //现在链表是1-> 3
    qDebug() << QString::number(linkedList.get(0));            //返回3
    */
    linkedList.addAtTail(1);
    qDebug() << QString::number(linkedList.get(0));            //返回2


    return app.exec();
}
