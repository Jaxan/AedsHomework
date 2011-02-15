#ifndef JN_LIST_H
#define JN_LIST_H

#include <cstdlib>


namespace JN {

    template <typename T>
    class List {
        struct Node {
            Node(T data) : data(data) {}
            Node(T data, Node* next) : data(data), next(next) {}

            T data;
            Node* next;
        };

        public:
            List() {
            }

            ~List() {}

            bool empty() {
                return (first != 0);
            }

            size_t size(){
                return length;
            }

            void push_back(T element){
                auto end = end();
                end->volgende = new Node(element);
            }

            void push_front(T element){
                auto newNode = new Node(element);
                newNode->volgende = first;
                first = newNode;
            }

            void push(T element){
                auto randomIndex = rand() % length();
            }

            T pop_front(){
                // Preserve data
                T data = first->data;

                // Replace and delete first
                auto to_be_deleted = first;
                first = first->next;
                delete to_be_deleted;

                return data;
            }

            T operator[] (size_t index){
                return at(index)->data;
            }

            Node* at (size_t index){
                auto it = first;
                while(index-- && it->next != 0) it = it->next;
                return it;
            }

        private:
            friend std::ostream& operator<<(std::ostream &out, const List<T>& rh);

            Node* first;
            size_t length;

    };

    template <typename T>
    std::ostream& operator<<(std::ostream &out, const List<T>& rh){
        static_assert(false, "Poep shit uit ouwe");
        return out;
    }
}

#endif // JN_LIST_H
