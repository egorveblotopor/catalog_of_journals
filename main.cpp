#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>

/*
реализовать сортировки:
- по цене
- по тиражу
- по названию
- по издательствам
- по льготам
Реализовать поиск по названию.
*/

/*
 Подготовить справочник для подписки на издания.
Для проведения подписки имеется информация о газетах и журналах (индекс, название, тираж,
сроки подписки, периодичность выхода, цена, льготы, издательство и т.п.), а также об издающих их издательствах (наименование, адрес и т.п.).
Необходимо обеспечить эффективную выдачу сведений:
- упорядоченных по цене, тиражу, названию газет и/или журналов,
- о газетах и журналах, выпускаемых определенным издательством,
- об определенной газете или журнале,
- на какие газеты и/или журналы предоставляется льготная подписка.
 */

//using namespace std;


int commit;
const int N = 8;// играл с размером чаров... проиграл
int user_input;


struct Magazine{
    int id; //индекс
    char name[N]; //название
    int release_number; //тираж
    int release_frequency; // частота выхода (коллличество номеров за квартал)
    int price; // цена
    int discounts; // скидки
    char publisher[N]; // издатель

    struct Magazine *next; // указатели на некст и прев элементы
    struct Magazine *prev;
};


struct Publishers{
public:
    char index[N];
    char name[N];
    char address[N];
    struct Publishers *next;
    struct Publishers *prev;
};


// инфосистема представленна в виде двусвязкого списка
// реализовать
// 1) размещение инфы внутри класса
// 2) запись на диск и чтение инфы с диска в память
// 3) алгоритмы сортировок и поиска


class InformationSystem{
public:
    Magazine *Head, *Tail;

// конструктор
    InformationSystem(): Head(nullptr), Tail(nullptr){};

// деструктор
    ~InformationSystem(){
        while (Head) {
            Tail = Head->next;
            delete Head;
            Head = Tail;
        }
    }

    void show_main(){
        Magazine *node_element = Head;

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "List of magazines" << std::endl;

        while (node_element != nullptr)
        {

            std::cout << std::endl;
            std::cout << '|'  <<  std::setfill(' ') << std::setw(5) << "id - " <<  std::setfill(' ') << std::setw(5) << node_element->id
                      << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                      << "|" <<  std::setfill(' ') << std::setw(15) << "release num - " <<  std::setfill(' ') << std::setw(15) << node_element->release_number << "|" << std::endl
                      << "|" <<  std::setfill(' ') << std::setw(20) << "release frequency - " <<  std::setfill(' ') << std::setw(15) << node_element->release_frequency << "|" << std::endl
                      << "|" <<  std::setfill(' ') << std::setw(20) << "price - " <<  std::setfill(' ') << std::setw(15) << node_element->price << "|" << std::endl
                      << "|" <<  std::setfill(' ') << std::setw(20) << "discounts - " <<  std::setfill(' ') << std::setw(15) << node_element->discounts << "|" << std::endl
                      << "|" <<  std::setfill(' ') << std::setw(20) << "publisher - " <<  std::setfill(' ') << std::setw(15) << node_element->publisher << "|" << std::endl;
            std::cout << std::endl;
            node_element = node_element->next;
        }

        just.show();
        std::cout << "Type 0 for back to main menu " << std::endl;
        std::cin >> user_input;
        switch (user_input)
        {
            case 1:
                add();
                break;
            case 0:
                menu();
                break;
        }
    }


    class Publishers_list{
    public:
        Publishers *Head, *Tail;
        // конструктор
        Publishers_list(): Head(nullptr), Tail(nullptr){};

        // деструктор
        ~Publishers_list(){
            while (Head) {
                Tail = Head->next;
                delete Head;
                Head = Tail;
            }
        }

        char pub_list_name_pub[N];

        int counter(){
            int index_loco = 0;
            Publishers *node_element = Head;
            while (node_element != nullptr)
            {
                index_loco += 1;
                node_element = node_element->next;
            }
            return index_loco;
        }

        void save(){
            std::cout << "saving..." << std::endl;
            Publishers *node_element = Head;
            while (node_element != nullptr)
            {
                std::string loco = node_element->index;
                loco += " ";
                loco += node_element->name;
                loco += " ";
                loco += node_element->address;
                loco += " ";
                loco += '\n';
                std::ofstream out;
                out.open("E:\\database_publishers.txt", std::ofstream::out | std::ofstream::app);
                out << loco;
                out.close();
                node_element = node_element->next;// двигаемся к следующему элементу
            }
            std::cout << "Your data is saved!" << std::endl;
        }

        // переменные для переноса из функции считывателя в загрузчик
        char first_pub[N];
        char second_pub[N];
        char third_pub[N];

        void load(){
            std::ifstream file("E:\\database_publishers.txt");
            std::string data_from_file;
            int local_index = 1;
            std::string loco; // локальная переменная для изменения данных
            int change_index = -1;
            while (getline(file, data_from_file, ' ')) {
                switch (local_index) {
                    case 1:
                    {
                        loco = data_from_file;
                        change_index = loco.find('\n');

                        if (change_index != -1){
                            loco = loco.erase(change_index, loco.length()-1);
                        }
                        strcpy(first_pub, loco.c_str());
                        local_index += 1;
                        break;
                    }
                    case 2: //name char
                    {
                        strcpy(second_pub, data_from_file.c_str());
                        local_index += 1;
                        break;
                    }
                    case 3: // release num int
                    {
                        std::cout << data_from_file.length() << "|" << data_from_file << std::endl;
                        strcpy(third_pub, data_from_file.c_str());
                        adder();
                        local_index = 1;
                        break;
                    }
                }
            }
            file.close();
            std::cout << "load is successfully done!" << std::endl;
        }

        void adder(){
            Publishers *node_element = new Publishers;
            node_element->next = nullptr;
            strcpy(node_element->index, first_pub);
            strcpy(node_element->name, second_pub);
            strcpy(node_element->address, third_pub);

            if (Head != nullptr) {
                node_element->prev = Tail;
                Tail->next = node_element;
                Tail = node_element;
            } else {
                node_element->prev = nullptr;
                Head =Tail = node_element;
            }
        }

        void show(){
            Publishers *node_element = Head;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "List of publishers" << std::endl;
            while (node_element != nullptr)
            {
                std::cout << std::endl;
                std::cout << '|'  <<  std::setfill(' ') << std::setw(10) << "index - " <<  std::setfill(' ') << std::setw(10) << node_element->index
                          << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                          << "|" <<  std::setfill(' ') << std::setw(10) << "address - " <<  std::setfill(' ') << std::setw(20) << node_element->address << "|" << std::endl;
                std::cout << std::endl;
                node_element = node_element->next;
            }
        }

        void add_new(){
            std::cout << "add..." << std::endl;
            std::cout << std::endl;

            Publishers *node = new Publishers;
            node->next = nullptr;

            if (Head != nullptr)
            {
                node->prev = Tail; //Указываем адрес на предыдущий элемент в соотв. поле
                Tail->next = node; //Указываем адрес следующего за хвостом элемента
                Tail = node; //Меняем адрес хвоста

                std::cout << "add index" << std::endl;
                std::cin >> node->index;

                std::cout << "add name" << std::endl;
                std::cin >> node->name;
                strcpy(pub_list_name_pub, node->name);

                std::cout << "add address" << std::endl;
                std::cin >> node->address;
            }
            else
            {
                node->prev = nullptr; //Предыдущий элемент указывает в пустоту
                Head = Tail = node; //Голова=Хвост=тот элемент, что сейчас добавили

                std::cout << "add index" << std::endl;
                std::cin >> node->index;

                std::cout << "add name" << std::endl;
                std::cin >> node->name;
                strcpy(pub_list_name_pub, node->name);

                std::cout << "add address" << std::endl;
                std::cin >> node->address;
            }
        }

        void get_from_list(){
            Publishers *node_element = Head;
            if (Head != nullptr){
                show();
                std::cout << "pick the publisher" << std::endl;
                std::cin >> user_input;
                std::cout << "you entered - " << user_input << std::endl;
                while (node_element != nullptr)
                {
                    std::string loco_1, loco_2;
                    loco_1 = user_input;
                    loco_2 = node_element->name;
                    if (loco_1 == loco_2)
                    {
                        std::cout << "OK" << std::endl;
                        strcpy(pub_list_name_pub, node_element->name);
                    }
                    else
                    {
                        std::cout << "its not work!!!!!" << std::endl;
                    }
                    node_element = node_element->next;
                }
            }
            else{
                std::cout << "Publishers list is empty, please add new" << std::endl;
                add_new();
            }
        }
    };


    Publishers_list just;

    void add_pub_menu(){
        std::cout << "choose the option" << std::endl;
        std::cout << "1 - Add new publisher with keyboard " << std::endl;
        std::cout << "0 - Get it from list" << std::endl;
        std::cin >> user_input;
        switch (user_input) {
            case 1:
                just.add_new();
                break;
            case 2:
                just.get_from_list();
                break;
        }
    }

    void add() {
        std::cout << "add..." << std::endl;
        std::cout << std::endl;
        Magazine *node = new Magazine; //Выделение памяти под новый элемент структуры
        node->next = nullptr; //Указываем, что изначально по следующему адресу пусто

        if (Head != nullptr) //Если список не пуст
        {
            node->prev = Tail; //Указываем адрес на предыдущий элемент в соотв. поле
            Tail->next = node; //Указываем адрес следующего за хвостом элемента
            Tail = node; //Меняем адрес хвоста

            std::cout << "add index" << std::endl;
            node->id = count();

            std::cout << "enter name of magazine" << std::endl;
            std::cin >> node->name;//Записываем значение в структуру

            std::cout << "input release number" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            std::cout << "input release frequency, parts in year (example: 12)" << std::endl;
            std::cin >> node->release_frequency;//Записываем значение в структуру

            std::cout << "How much does it cost?" << std::endl;
            std::cin >> node->price;//Записываем значение в структуру

            std::cout << "input information about discounts in % (example: 30)" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            add_pub_menu();
            strcpy(node->publisher, just.pub_list_name_pub);

        }
        else //Если список пустой
        {
            node->prev = nullptr; //Предыдущий элемент указывает в пустоту
            Head = Tail = node; //Голова=Хвост=тот элемент, что сейчас добавили

            std::cout << "add index" << std::endl;
            node->id = 1;

            std::cout << "enter name of magazine" << std::endl;
            std::cin >> node->name;//Записываем значение в структуру

            std::cout << "input release number" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            std::cout << "input release frequency, parts in year (example: 12)" << std::endl;
            std::cin >> node->release_frequency;//Записываем значение в структуру

            std::cout << "How much does it cost?" << std::endl;
            std::cin >> node->price;//Записываем значение в структуру

            std::cout << "input information about discounts in % (example: 30)" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            add_pub_menu();
            strcpy(node->publisher, just.pub_list_name_pub);
        }

        std::cout << "choose the option" << std::endl;
        std::cout << "1 - Make one more notation " << std::endl;
        std::cout << "0 - Exit to main menu" << std::endl;
        std::cin >> user_input;
        switch (user_input) {
            case 1:
                add();
                break;
            case 0:
                menu();
                break;
        }
    }

    void delete_function(){
        std::cout << "delete element" << std::endl;
    }

    void edit(){
        std::cout << "edit" << std::endl;
    }

    void save(){
        std::cout << "saving..." << std::endl;
        Magazine *node_element = Head;
        while (node_element != nullptr)
        {
            std::string loco = std::to_string(node_element->id);
            loco += " ";
            loco += node_element->name;
            loco += " ";
            loco += std::to_string(node_element->release_number);
            loco += " ";
            loco += std::to_string(node_element->release_frequency);
            loco += " ";
            loco += std::to_string(node_element->price);
            loco += " ";
            loco += std::to_string(node_element->discounts);
            loco += " ";
            loco += node_element->publisher;
            loco += " ";
            loco += "\n";
            std::ofstream out;
            out.open("E:\\database.txt", std::ofstream::out | std::ofstream::app);
            out << loco;
            out.close();
            node_element = node_element->next;// двигаемся к следующему элементу
        }
        just.save();
        std::cout << "Your data is saved!" << std::endl;
        menu();
    }

    // переменные для переноса из функции считывателя в загрузчик
    int first;
    char second[N];
    int third;
    int fourth;
    int fifth;
    int sixth;
    char seventh[N];

    void load() {
        std::ifstream file("E:\\database.txt");
        std::string data_from_file;
        int local_index = 1;
        std::string loco; // локальная переменная для изменения данных
        int change_index = -1;
        while (getline(file, data_from_file, ' ')) {
            switch (local_index) {
                case 1:
                {
                    InformationSystem::first = atoi(data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 2: //name char
                {
                    loco = data_from_file;
                    change_index = loco.find('\n');
                    if (change_index != -1){
                        loco = loco.erase(change_index, loco.length()-1);
                    }
                    strcpy(second, loco.c_str());
                    local_index += 1;
                    change_index = -1;
                    break;
                }
                case 3: // release num int
                {
                    InformationSystem::third = atoi(data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 4: // release_frequency int
                {
                    InformationSystem::fourth = atoi(data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 5: // price
                {
                    InformationSystem::fifth = atoi(data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 6: //discounts
                {
                    InformationSystem::sixth = atoi(data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 7: // publisher char
                {
                    strcpy(seventh, data_from_file.c_str());
                    adder();
                    local_index = 1;
                    break;
                }
            }
        }
        file.close();
        std::cout << "load is successfully done!" << std::endl;
        just.load();
        menu();
    }

    void adder(){
        Magazine *node_element = new Magazine;
        node_element->next = nullptr;
        node_element->id = first;
        strcpy(node_element->name, second);
        node_element->release_number = third;
        node_element->release_frequency = fourth;
        node_element->price = fifth;
        node_element->discounts = sixth;
        strcpy(node_element->publisher, seventh);
        if (Head != nullptr) {
            node_element->prev = Tail;
            Tail->next = node_element;
            Tail = node_element;
        } else {
            node_element->prev = nullptr;
            Head =Tail = node_element;
        }
    }

    void exit(){
        std::cout << "Do you want save data before exit???" << std::endl;
        std::cout << "1 - save & exit" << std::endl;
        std::cout << "2 - exit without saving" << std::endl;
        std::cin >> user_input;
        switch (user_input) {
            case 1:{
                std::cout << "saving..." << std::endl;
                save();
                std::cout << "end of program" << std::endl;
                break;
            }
            case 2:{
                std::cout << "end of program without saving" << std::endl;
                break;
            }
        }
    }

    int count(){
        // данная функция подсчитывает кол-во эл-тов в списке
        int counter = 0;
        Magazine *node = Head;
        if (Head !=nullptr){
            while (node != nullptr)
            {
            counter ++;
            node = node->next;
            }
        }
        return counter;
    }

    void menu(){
        int loco_counter;
        loco_counter = count();
        int loco_counter_1;
        loco_counter_1 = just.counter();

        std::cout  << '.'  <<  std::setfill('_') << std::setw(50) << '.' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(35) << "Journals in memory: " <<  std::setfill(' ') << std::setw(5) << loco_counter <<  std::setfill(' ') << std::setw(10) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(35) << "Publishers in memory: " <<  std::setfill(' ') << std::setw(5) << loco_counter_1 <<  std::setfill(' ') << std::setw(10) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(35) << "Please choose the action."  <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Show information - 1" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Add information - 2" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Delete information - 3" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Edit information - 4" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Save information to file - 5" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Load information from file - 6" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Exit - 0" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill('_') << std::setw(50) << '|' << std::endl;
        std::cout << "Your choice: ";
        std::cin >> user_input;
        std::cout << std::endl;
        switch (user_input) {
            case 1:{
                show_main();
                break;
            }
            case 2:{
                add();
                break;
            }
            case 3:{
                delete_function();
                break;
            }
            case 4:{
                edit();
                break;
            }
            case 5:{
                save();
                break;
            }
            case 6:{
                load();
                break;
            }
            case 0: {
                exit();
                break;
            }
        }
    }
};

int main() {
    InformationSystem test;
    test.menu();
    return 0;
}