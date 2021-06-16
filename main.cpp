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


const int N = 8;// играл с размером чаров... проиграл
int user_input_int;
char user_input_char[N];

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


//struct StreamlineNode{
//public:
//    int id;
//    char name[N]; //название
//    int parameter_int; // сюда заносим параметр для сортировкис
//    struct StreamlineNode *next;
//    struct StreamlineNode *prev;
//};


class InformationSystem{
public:
    Magazine *Head, *Tail;
//    StreamlineNode *Head_0, Tail_0;

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
                out.open("X:\\database_publishers.txt", std::ofstream::out | std::ofstream::app);
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
            std::ifstream file("X:\\database_publishers.txt");
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
                        //std::cout << data_from_file.length() << "|" << data_from_file << std::endl;
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
                std::cin >> user_input_char;
                std::cout << "you entered - " << user_input_int << std::endl;
                while (node_element != nullptr)
                {

                    char loco_1[N], loco_2[N];
                    strcpy(loco_1, user_input_char);
                    strcpy(loco_2, node_element->name);
                    int result;
                    result = strcmp(loco_1, loco_2);
                    if (result == 0)
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

        void pick_show(){
            Publishers *node_element = Head;
            while (node_element != nullptr)
            {
                std::cout << std::endl;
                std::cout << '|'  <<  std::setfill(' ') << std::setw(10) << "index - " <<  std::setfill(' ') << std::setw(10) << node_element->index
                          << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name << std::endl;
                std::cout << std::endl;
                node_element = node_element->next;
            }

        }

        void journals_of_publisher(){
            pick_show();
            std::cout << "input name of publisher - " << std::endl;
            std::cin >> user_input_char;

            Publishers *node_element = Head;
            while (node_element != nullptr){
                int result = strcmp(user_input_char, node_element->name);
                if (result == 0){
                    std::cout << std::endl;
                    std::cout << '|'  <<  std::setfill(' ') << std::setw(10) << "index - " <<  std::setfill(' ') << std::setw(10) << node_element->index
                              << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                              << "|" <<  std::setfill(' ') << std::setw(10) << "address - " <<  std::setfill(' ') << std::setw(20) << node_element->address << "|" << std::endl;
                    std::cout << std::endl;

                }

                node_element = node_element->next;
            }
        }

        char publisher_choice_id[N]; // сюда записываем айди издателя для для действий с ним
        int choice_publisher_remove_or_edit; // choose remove or edit
        int magazine_choice_field;

        void publisher_action(){
            pick_show();
            std::cout << "choose publisher that you want edit or remove with id" << std::endl;
            std::cout << "input id of publisher" << std::endl;
            std::cin >> publisher_choice_id;
            Publishers *node_element = Head;
            while (node_element != nullptr){
                if (publisher_choice_id == node_element->index){
                    std::cout << "if you want remove this notation - 1" << std::endl;
                    std::cout << "if you want edit this notation - 2" << std::endl;
                    std::cin >> choice_publisher_remove_or_edit;
                    switch (choice_publisher_remove_or_edit) {
                        case 1:{
                            publisher_remove();
                            break;
                        }
                        case 2:{
                            publisher_edit();
                            break;
                        }
                    }
                    break;
                }
                node_element = node_element->next;
            }
        }

        void publisher_remove(){
            Publishers *node_element = Head;
            while (node_element->index != publisher_choice_id){
                if (node_element->index == publisher_choice_id){
                    node_element->prev->next = node_element->next;
                    node_element->next->prev = node_element->prev;
                    break;
                }
                node_element = node_element->next;
            }
            std::cout << "remove is succesfully finished" << std::endl;
            InformationSystem().menu();
        }

        void publisher_edit(){
            Publishers *node_element = Head;
            while (node_element->index != publisher_choice_id){
                if (node_element->index == publisher_choice_id) {
                    std::cout << "pick the field for edit" << std::endl;
                    std::cout << std::endl;
                    std::cout << '|' << std::setfill(' ') << std::setw(10) << "index - " << std::setfill(' ')
                              << std::setw(10) << node_element->index << '|' << std::setfill(' ') << std::setw(10) << "1"
                              << '|' << std::endl;
                    std::cout << "|" << std::setfill(' ') << std::setw(10) << "name - " << std::setfill(' ')
                              << std::setw(10) << node_element->name << '|' << std::setfill(' ') << std::setw(10) << "2"
                              << '|' << std::endl;
                    std::cout << "|" << std::setfill(' ') << std::setw(10) << "price - " << std::setfill(' ')
                              << std::setw(10) << node_element->address << '|' << std::setfill(' ') << std::setw(10) << "3"
                              << '|' << std::endl;
                    std::cout << std::endl;

                    std::cout << "pick the field for edit" << std::endl;
                    std::cin >> magazine_choice_field;
                    switch (magazine_choice_field) {
                        case 1:{
                            std::cout << "input new value for filed id (int)" << std::endl;
                            std::cin >> node_element->index;
                            break;
                        }
                        case 2:{
                            std::cout << "input new value for filed name (char)" << std::endl;
                            std::cin >> node_element->name;
                            break;
                        }
                        case 3:{
                            std::cout << "input new value for filed price (int)" << std::endl;
                            std::cin >> node_element->address;
                            break;
                        }
                    }
                    break;
                }
                node_element = node_element->next;
            }
            std::cout << "edit is successfully finished" << std::endl;
            InformationSystem().menu();
        }
    };


    Publishers_list just;

    void add_pub_menu(){
        std::cout << "choose the option" << std::endl;
        std::cout << "1 - Add new publisher with keyboard " << std::endl;
        std::cout << "0 - Get it from list" << std::endl;
        std::cin >> user_input_int;
        switch (user_input_int) {
            case 1:
                just.add_new();
                break;
            case 0:
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
        std::cin >> user_input_int;
        switch (user_input_int){
            case 1:
                add();
                break;
            case 0:
                menu();
                break;
        }
    }


    int magazine_choice;
    int magazine_remove_or_edit; // сюда записываем айди журнала для для действий с ним
    int magazine_choice_field;

    void magazine_action(){
        pick_show();
        std::cout << "choose journal that you want edit or remove" << std::endl;
        std::cout << "input id of journal" << std::endl;
        std::cin >> magazine_choice;
        Magazine *node_element = Head;
        while (node_element != nullptr){
            if (magazine_choice == node_element->id){
                std::cout << "if you want remove this notation - 1" << std::endl;
                std::cout << "if you want edit this notation - 2" << std::endl;
                std::cin >> magazine_remove_or_edit;
                switch (magazine_remove_or_edit) {
                    case 1:{
                        magazine_remove();
                        break;
                    }
                    case 2:{
                        magazine_edit();
                        break;
                    }
                }
            }
            node_element = node_element->next;
        }
    }

    void magazine_remove(){
        Magazine *node_element = Head;
        while (node_element->id != magazine_choice){
            if (node_element->id == magazine_choice){
                node_element->prev->next = node_element->next;
                node_element->next->prev = node_element->prev;
                break;
            }
            node_element = node_element->next;
        }
        std::cout << "remove is succesfully finished" << std::endl;
        menu();
    }

    void magazine_edit(){
        Magazine *node_element = Head;
        while (node_element->id != magazine_choice){
            if (node_element->id == magazine_choice) {
                std::cout << "pick the field for edit" << std::endl;
                std::cout << std::endl;
                std::cout << '|' << std::setfill(' ') << std::setw(10) << "index - " << std::setfill(' ')
                          << std::setw(10) << node_element->id << '|' << std::setfill(' ') << std::setw(10) << "1"
                          << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "name - " << std::setfill(' ')
                          << std::setw(10) << node_element->name << '|' << std::setfill(' ') << std::setw(10) << "2"
                          << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "price - " << std::setfill(' ')
                          << std::setw(10) << node_element->price << '|' << std::setfill(' ') << std::setw(10) << "3"
                          << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "release frequency - " << std::setfill(' ')
                          << std::setw(10) << node_element->release_frequency << '|' << std::setfill(' ')
                          << std::setw(10) << "4" << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "release number- " << std::setfill(' ')
                          << std::setw(10) << node_element->release_number << '|' << std::setfill(' ') << std::setw(10)
                          << "5" << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "discounts - " << std::setfill(' ')
                          << std::setw(10) << node_element->discounts << '|' << std::setfill(' ') << std::setw(10)
                          << "6" << '|' << std::endl;
                std::cout << "|" << std::setfill(' ') << std::setw(10) << "publisher - " << std::setfill(' ')
                          << std::setw(10) << node_element->publisher << '|' << std::setfill(' ') << std::setw(10)
                          << "7" << '|' << std::endl;
                std::cout << std::endl;

                std::cout << "pick the field for edit" << std::endl;
                std::cin >> magazine_choice_field;
                switch (magazine_choice_field) {
                    case 1:{
                        std::cout << "input new value for filed id (int)" << std::endl;
                        std::cin >> node_element->id;
                        break;
                    }
                    case 2:{
                        std::cout << "input new value for filed name (char)" << std::endl;
                        std::cin >> node_element->name;
                        break;
                    }
                    case 3:{
                        std::cout << "input new value for filed price (int)" << std::endl;
                        std::cin >> node_element->price;
                        break;
                    }
                    case 4:{
                        std::cout << "input new value for filed release frequency (int)" << std::endl;
                        std::cin >> node_element->release_frequency;
                        break;
                    }
                    case 5:{
                        std::cout << "input new value for filed release number (int)" << std::endl;
                        std::cin >> node_element->release_number;
                        break;
                    }
                    case 6:{
                        std::cout << "input new value for filed discounts (int)" << std::endl;
                        std::cin >> node_element->discounts;
                        break;
                    }
                    case 7:{
                        std::cout << "input new value for filed publisher (char)" << std::endl;
                        std::cin >> node_element->publisher;
                        break;
                    }
                }
                break;
            }
            node_element = node_element->next;
        }
        std::cout << "edit is successfully finished" << std::endl;
        menu();
    }

    void delete_or_edit_menu(){
        std::cout << "choose what you want edit or remove" << std::endl;
        std::cout << "magazine - 1" << std::endl;
        std::cout << "publisher - 2" << std::endl;
        std::cin >> user_input_int;
        switch (user_input_int) {
            case 1:{
                magazine_action();
                break;
            }
            case 2:{
                just.publisher_action();
                break;
            }
        }
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
            out.open("X:\\database.txt", std::ofstream::out | std::ofstream::app);
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
        std::ifstream file("X:\\database.txt");
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
        std::cin >> user_input_int;
        switch (user_input_int) {
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
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Delete or edit - 3" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        //std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Edit information - 4" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Save information to file - 5" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Load information from file - 6" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Search information - 7" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Exit - 0" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill('_') << std::setw(50) << '|' << std::endl;
        std::cout << "Your choice: ";
        std::cin >> user_input_int;
        std::cout << std::endl;
        switch (user_input_int) {
            case 1:{
                show_main();
                just.show();

                std::cout << "Type 0 for back to main menu " << std::endl;
                std::cin >> user_input_int;
                switch (user_input_int)
                {
                    case 0:
                        menu();
                        break;
                }
                break;
            }
            case 2:{
                add();
                break;
            }
            case 3:{
                delete_or_edit_menu();
                break;
            }
            case 4:{
                //edit();
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
            case 7:{
                search_menu();
                break;
            }
            case 0: {
                exit();
                break;
            }
        }
    }


    void search_menu(){
        /*
        - упорядоченных по цене, тиражу, названию газет и/или журналов,
        - о газетах и журналах, выпускаемых определенным издательством,
        - об определенной газете или журнале,
        - на какие газеты и/или журналы предоставляется льготная подписка.
        */
        std::cout << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " streamline journals by data - 1" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Show journals of publisher - 2" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Show journal - 3" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Show discounts - 4" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Exit to main menu - 0" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << std::endl;
        std::cout << "Your choice: ";
        std::cin >> user_input_int;
        std::cout << std::endl;
        switch (user_input_int) {
            case 1: {
                streamline_journals_menu();
                break;
            }
            case 2: {
                just.journals_of_publisher();
                break;
            }
            case 3: {
                show_journal();
                break;
            }
            case 4: {
                show_discounts();
                break;
            }
            case 0: {
                menu();
                break;
            }
        }
    }

    void streamline_journals_menu(){
        std::cout << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " sort by price - 1" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " sort by release number - 2" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " sort by name - 3" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << " Exit to search menu - 0" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << std::endl;
        std::cout << "Your choice: ";
        std::cin >> user_input_int;
        std::cout << std::endl;
        switch (user_input_int) {
            case 1: {
                streamline_price();
                break;
            }
            case 2: {
                streamline_release();
                break;
            }
            case 3: {
                streamline_name();
                break;
            }
            case 0:{
                search_menu();
                break;
            }
        }
    }

    void pick_show(){
        Magazine *node_element = Head;
        while (node_element != nullptr)
        {
            std::cout << std::endl;
            std::cout << '|'  <<  std::setfill(' ') << std::setw(10) << "index - " <<  std::setfill(' ') << std::setw(10) << node_element->id
                      << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                      << std::endl;
            std::cout << std::endl;
            node_element = node_element->next;
        }
    }

    void sort_show(){
        Magazine * temp = Head;                     //Направляем указатель на начало списка
        while (temp) {                           //Обходим список, то же что и while (temp != NULL)

            std::cout << std::endl;
            std::cout << '|' << std::setfill(' ') << std::setw(5) << "id - " << std::setfill(' ') << std::setw(5)
                      << temp->id
                      << "|" << std::setfill(' ') << std::setw(7) << "name - " << std::setfill(' ') << std::setw(10)
                      << temp->name
                      << "|" << std::setfill(' ') << std::setw(15) << "release num - " << std::setfill(' ')
                      << std::setw(15) << temp->release_number << "|" << std::endl
                      << "|" << std::setfill(' ') << std::setw(20) << "release frequency - " << std::setfill(' ')
                      << std::setw(15) << temp->release_frequency << "|" << std::endl
                      << "|" << std::setfill(' ') << std::setw(20) << "price - " << std::setfill(' ') << std::setw(15)
                      << temp->price << "|" << std::endl
                      << "|" << std::setfill(' ') << std::setw(20) << "discounts - " << std::setfill(' ')
                      << std::setw(15) << temp->discounts << "|" << std::endl
                      << "|" << std::setfill(' ') << std::setw(20) << "publisher - " << std::setfill(' ')
                      << std::setw(15) << temp->publisher << "|" << std::endl;
            std::cout << std::endl;

            temp = temp->next;                  //Направляем указатель на следующий элемент списка
        }
    }

    void streamline_price() {
        Magazine *left = Head;                 //Первый элемент — это пусть будет голова
        Magazine *right = Head->next;          //Второй элемент — это пусть будет следующий за головой элемент

        Magazine *temp = new Magazine;              //Временное звено для хранения переставляемого всех значений переставляемого звена

        while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
                if ((left->price) < (right->price)) {        //Проверяем необходимость перестановки
                    temp->price = left->price;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
                    temp->id = left->id;
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    temp->discounts = left->discounts;
                    temp->release_number = left->release_number;
                    temp->release_frequency = left->release_frequency;

                    left->price = right->price;             //Сейчас у нас имеется только x, поэтому только его
                    left->id = right->id;
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    left->discounts = right->discounts;
                    left->release_number = right->release_number;
                    left->release_frequency = right->release_frequency;

                    right->price = temp->price;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
                    right->id = temp->id;
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    right->discounts = temp->discounts;
                    right->release_number = temp->release_number;
                    right->release_frequency = temp->release_frequency;
                }
                right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            }
            left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
        }

        sort_show();
        streamline_journals_menu();
    }

    void streamline_release(){
        Magazine *left = Head;                 //Первый элемент — это пусть будет голова
        Magazine *right = Head->next;          //Второй элемент — это пусть будет следующий за головой элемент

        Magazine *temp = new Magazine;              //Временное звено для хранения переставляемого всех значений переставляемого звена

        while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
                if ((left->release_number) < (right->release_number)) {        //Проверяем необходимость перестановки
                    temp->price = left->price;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
                    temp->id = left->id;
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    temp->discounts = left->discounts;
                    temp->release_number = left->release_number;
                    temp->release_frequency = left->release_frequency;

                    left->price = right->price;             //Сейчас у нас имеется только x, поэтому только его
                    left->id = right->id;
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    left->discounts = right->discounts;
                    left->release_number = right->release_number;
                    left->release_frequency = right->release_frequency;

                    right->price = temp->price;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
                    right->id = temp->id;
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    right->discounts = temp->discounts;
                    right->release_number = temp->release_number;
                    right->release_frequency = temp->release_frequency;
                }
                right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            }
            left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
        }

        sort_show();
        streamline_journals_menu();
    }

    void streamline_name(){
        Magazine *left = Head;                 //Первый элемент — это пусть будет голова
        Magazine *right = Head->next;          //Второй элемент — это пусть будет следующий за головой элемент

        Magazine *temp = new Magazine;              //Временное звено для хранения переставляемого всех значений переставляемого звена
        char loco_1[N];
        char loco_2[N];
        int result;

        strcpy(loco_1, left->name);
        strcpy(loco_1, right->name);
        result = strcmp(loco_1, loco_2);

        while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
                if (result>0) {        //Проверяем необходимость перестановки
                    temp->price = left->price;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
                    temp->id = left->id;
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    temp->discounts = left->discounts;
                    temp->release_number = left->release_number;
                    temp->release_frequency = left->release_frequency;

                    left->price = right->price;             //Сейчас у нас имеется только x, поэтому только его
                    left->id = right->id;
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    left->discounts = right->discounts;
                    left->release_number = right->release_number;
                    left->release_frequency = right->release_frequency;

                    right->price = temp->price;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
                    right->id = temp->id;
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    right->discounts = temp->discounts;
                    right->release_number = temp->release_number;
                    right->release_frequency = temp->release_frequency;
                }
                right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            }
            left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
        }
        sort_show();
        streamline_journals_menu();
    }


    void show_journal(){
        pick_show();
        std::cout << "input name of publisher - " << std::endl;
        std::cin >> user_input_char;

        Magazine *node_element = Head;
        while (node_element != nullptr){
            int result = strcmp(user_input_char, node_element->name);
            if (result == 0){
                std::cout << std::endl;
                std::cout << '|'  <<  std::setfill(' ') << std::setw(5) << "id - " <<  std::setfill(' ') << std::setw(5) << node_element->id
                          << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                          << "|" <<  std::setfill(' ') << std::setw(15) << "release num - " <<  std::setfill(' ') << std::setw(15) << node_element->release_number << "|" << std::endl
                          << "|" <<  std::setfill(' ') << std::setw(20) << "release frequency - " <<  std::setfill(' ') << std::setw(15) << node_element->release_frequency << "|" << std::endl
                          << "|" <<  std::setfill(' ') << std::setw(20) << "price - " <<  std::setfill(' ') << std::setw(15) << node_element->price << "|" << std::endl
                          << "|" <<  std::setfill(' ') << std::setw(20) << "discounts - " <<  std::setfill(' ') << std::setw(15) << node_element->discounts << "|" << std::endl
                          << "|" <<  std::setfill(' ') << std::setw(20) << "publisher - " <<  std::setfill(' ') << std::setw(15) << node_element->publisher << "|" << std::endl;
                std::cout << std::endl;

            }
            else{
                std::cout << std::endl;
                std::cout << "Try again. I'm not understand you!" << std::endl;
                std::cout << std::endl;
                show_journal();
            }

            node_element = node_element->next;
        }
        search_menu();
    }


    void show_discounts(){
        Magazine *node_element = Head;
        while (node_element != nullptr){
            if (node_element->discounts != 0){
                std::cout << std::endl;
                std::cout << '|'  <<  std::setfill(' ') << std::setw(10) << "index - " <<  std::setfill(' ') << std::setw(10) << node_element->id
                          << "|" <<  std::setfill(' ') << std::setw(7) << "name - " <<  std::setfill(' ') << std::setw(10) << node_element->name
                          << "|" <<  std::setfill(' ') << std::setw(7) << "accessible discount - " <<  std::setfill(' ') << std::setw(10) << node_element->discounts
                          << std::endl;
                std::cout << std::endl;

            }
            node_element = node_element->next;
        }
        search_menu();
    }


};

int main() {
    InformationSystem test;
    test.menu();
    return 0;
}