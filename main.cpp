#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string.h>

const int N = 20;
int user_input_int;
char user_input_char[N];

struct Magazine{
public:
    char id[N]; //индекс
    char name[N]; //название
    char release_number[N]; //тираж
    char release_frequency[N]; // частота выхода (коллличество номеров за квартал)
    char price[N]; // цена
    char discounts[N]; // скидки
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


class InformationSystem{
public:
    Magazine *Head, *Tail;

    InformationSystem(): Head(nullptr), Tail(nullptr){};

    ~InformationSystem(){
        while (Head) {
            Tail = Head->next;
            delete Head;
            Head = Tail;
        }
    }


    class PublishersList{
    public:
        Publishers *Head, *Tail;
        // конструктор
        PublishersList(): Head(nullptr), Tail(nullptr){};

        // деструктор
        ~PublishersList(){
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
                        int change_index = -1;
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
                        strcpy(third_pub, data_from_file.c_str());
                        adder();
                        local_index = 1;
                        break;
                    }
                }
            }
            file.close();
            std::cout  << '.'  <<  std::setfill('_') << std::setw(50) << '.' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(30) << "load is done!" <<  std::setfill(' ') << std::setw(20) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill('_') << std::setw(50) << '|' << std::endl;
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

            std::cout  << '.'  <<  std::setfill('_') << std::setw(60) << '.' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(60) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(34) << "List of publishers" <<  std::setfill(' ') << std::setw(25) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill(' ') << std::setw(60) << '|' << std::endl;
            std::cout  << '|'  <<  std::setfill('_') << std::setw(60) << '|' << std::endl;

            while (node_element != nullptr)
            {
                std::cout << '|'  <<  std::setfill(' ') << std::setw(20) << "index - " <<  std::setfill(' ') << std::setw(39) << node_element->index << "|" << std::endl;
                std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "name - " <<  std::setfill(' ') << std::setw(39) << node_element->name << "|" << std::endl;
                std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "address - " <<  std::setfill(' ') << std::setw(39) << node_element->address << "|" << std::endl;
                std::cout  << '|'  <<  std::setfill('_') << std::setw(60) << '|' << std::endl;
                node_element = node_element->next;
            }
            std::cout << std::endl;
            std::cout << std::endl;
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
                std::cout << "pick the publisher - input the id of a publisher" << std::endl;
                std::cin >> user_input_char;
                std::cout << "you entered - " << user_input_char << std::endl;
                while (node_element != nullptr)
                {
                    int result;
                    result = strcmp(user_input_char, node_element->name);
                    std::cout << result << "its result" << std::endl;

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
            std::cout << "remove is successfully finished" << std::endl;
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


    PublishersList just;


    void show_main(){
        Magazine *node_element = Head;

        std::cout << std::endl;
        std::cout << std::endl;



        std::cout  << '.'  <<  std::setfill('_') << std::setw(60) << '.' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(60) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(35) << "list of magazines" <<  std::setfill(' ') << std::setw(25) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(60) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill('_') << std::setw(60) << '|' << std::endl;



        while (node_element != nullptr)
        {
            std::cout << '|'  <<  std::setfill(' ') << std::setw(20) << "id - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->id << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "name - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->name << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "release num - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->release_number << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "release frequency - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->release_frequency << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "price - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->price << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "discounts - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->discounts << "|" << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(20) << "publisher - " << '|'  <<  std::setfill(' ') << std::setw(39) << node_element->publisher << "|" << std::endl;
            std::cout  << '|'  <<  std::setfill('_') << std::setw(60) << '|' << std::endl;
            node_element = node_element->next;


        }
        std::cout  << std::endl;
        std::cout  << std::endl;
    }

    void add_pub_menu(){
        std::cout << "choose the option" << std::endl;
        std::cout << "1 - Add new publisher with keyboard " << std::endl;
        std::cout << "2 - Get it from list" << std::endl;
        std::cin >> user_input_int;
        switch (user_input_int) {
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
            std::cin >>node->id;

            std::cout << "enter name of magazine" << std::endl;
            std::cin >> node->name;//Записываем значение в структуру

            std::cout << "input release number" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            std::cout << "input release frequency, parts in year (example: 12)" << std::endl;
            std::cin >> node->release_frequency;//Записываем значение в структуру

            std::cout << "How much does it cost?" << std::endl;
            std::cin >> node->price;//Записываем значение в структуру

            std::cout << "input information about discounts in % (example: 30)" << std::endl;
            std::cin >> node->discounts;//Записываем значение в структуру

            add_pub_menu();
            strcpy(node->publisher, just.pub_list_name_pub);

        }
        else //Если список пустой
        {
            node->prev = nullptr; //Предыдущий элемент указывает в пустоту
            Head = Tail = node; //Голова=Хвост=тот элемент, что сейчас добавили

            std::cout << "add index" << std::endl;
            std::cin >>node->id;

            std::cout << "enter name of magazine" << std::endl;
            std::cin >> node->name;//Записываем значение в структуру

            std::cout << "input release number" << std::endl;
            std::cin >> node->release_number;//Записываем значение в структуру

            std::cout << "input release frequency, parts in year (example: 12)" << std::endl;
            std::cin >> node->release_frequency;//Записываем значение в структуру

            std::cout << "How much does it cost?" << std::endl;
            std::cin >> node->price;//Записываем значение в структуру

            std::cout << "input information about discounts in % (example: 30)" << std::endl;
            std::cin >> node->discounts;//Записываем значение в структуру

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


    char magazine_choice[N];
    int magazine_remove_or_edit; // сюда записываем айди журнала для для действий с ним
    int magazine_choice_field;

    void magazine_action(){
        pick_show();
        std::cout << "choose journal that you want edit or remove" << std::endl;
        std::cout << "input id of journal" << std::endl;
        std::cin >> magazine_choice;
        Magazine *node_element = Head;
        while (node_element != nullptr){
            int result = strcmp(magazine_choice, node_element->id);
            if (result == 0){
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
        while (node_element != nullptr){
            int result = strcmp(magazine_choice, node_element->id);
            if (result == 0){
                node_element->prev->next = node_element->next;
                node_element->next->prev = node_element->prev;
                break;
            }
            node_element = node_element->next;
        }
        std::cout << "remove is successfully finished" << std::endl;
        menu();
    }

    void magazine_edit(){
        Magazine *node_element = Head;
        while (node_element != nullptr){
            int result = strcmp(magazine_choice, node_element->id);
            if (result == 0) {
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
            std::string loco;
            loco = node_element->id;
            loco += " ";
            loco += node_element->name;
            loco += " ";
            loco += node_element->release_number;
            loco += " ";
            loco += node_element->release_frequency;
            loco += " ";
            loco += node_element->price;
            loco += " ";
            loco += node_element->discounts;
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
    char first[N];
    char second[N];
    char third[N];
    char fourth[N];
    char fifth[N];
    char sixth[N];
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
                    loco = data_from_file;
                    change_index = loco.find('\n');
                    if (change_index != -1){
                        loco = loco.erase(change_index, 1);
                    }
                    strcpy(first, loco.c_str());
                    local_index += 1;
                    break;
                }
                case 2: //name
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
                case 3: // release num
                {
                    strcpy(third, data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 4: // release_frequency
                {
                    strcpy(fourth, data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 5: // price
                {
                    strcpy(fifth, data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 6: //discounts
                {
                    strcpy(sixth, data_from_file.c_str());
                    local_index += 1;
                    break;
                }
                case 7: // publisher
                {
                    strcpy(seventh, data_from_file.c_str());
                    adder();
                    local_index = 1;
                    break;
                }
            }
        }
        file.close();

        std::cout  << '.'  <<  std::setfill('_') << std::setw(50) << '.' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(30) << "load is done!" <<  std::setfill(' ') << std::setw(20) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill(' ') << std::setw(50) << '|' << std::endl;
        std::cout  << '|'  <<  std::setfill('_') << std::setw(50) << '|' << std::endl;

        just.load();
        menu();
    }

    void adder(){
        Magazine *node_element = new Magazine;
        node_element->next = nullptr;

        strcpy(node_element->id, first);
        strcpy(node_element->name, second);
        strcpy(node_element->release_number, third);
        strcpy(node_element->release_frequency, fourth);
        strcpy(node_element->price, fifth);
        strcpy(node_element->discounts, sixth);
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
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Delete or edit information - 3" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Save information to file - 4" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Load information from file - 5" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
        std::cout << '|'  <<  std::setfill(' ') << std::setw(35) << "Search information - 6" <<  std::setfill(' ') << std::setw(15) << '|' << std::endl;
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
                save();
                break;
            }
            case 5:{
                load();
                break;
            }
            case 6:{
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
        std::cout << std::endl;
        std::cout << std::endl;
        while (node_element != nullptr)
        {

            std::cout  << '.'  <<  std::setfill('_') << std::setw(50) << '.' << std::endl;
            std::cout << '|'  <<  std::setfill(' ') << std::setw(25) << "index - " <<  std::setfill(' ') << std::setw(25) << node_element->id << std::endl;
            std::cout << "|" <<  std::setfill(' ') << std::setw(25) << "name - " <<  std::setfill(' ') << std::setw(25) << node_element->name << std::endl;
            std::cout  << '|'  <<  std::setfill('_') << std::setw(50) << '|' << std::endl;
            node_element = node_element->next;
        }
        std::cout << std::endl;
        std::cout << std::endl;
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

        char loco_1[N];
        char loco_2[N];
        int result;
        strcpy(loco_1, left->name);
        strcpy(loco_1, right->name);
        result = strcmp(loco_1, loco_2);

        while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
                if (result>0) {        //Проверяем необходимость перестановки

                    //И переставляем все внутренние элементы, за исключением указателей связи, местами

                    strcpy(temp->price, left->price);
                    strcpy(temp->id, left->id);
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    strcpy(temp->discounts, left->discounts);
                    strcpy(temp->release_number, left->release_number);
                    strcpy(temp->release_frequency, left->release_frequency);

                    strcpy(left->price, right->price);
                    strcpy(left->id, right->id);
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    strcpy(left->discounts, right->discounts);
                    strcpy(left->release_number, right->release_number);
                    strcpy(left->release_frequency, right->release_frequency);

                    strcpy(right->price, temp->price);
                    strcpy(right->id, temp->id);
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    strcpy(right->discounts, temp->discounts);
                    strcpy(right->release_number, temp->release_number);
                    strcpy(right->release_frequency, temp->release_frequency);
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

        char loco_1[N];
        char loco_2[N];
        int result;
        strcpy(loco_1, left->name);
        strcpy(loco_1, right->name);
        result = strcmp(loco_1, loco_2);

        while (left->next) {                 //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
                if (result>0) {        //Проверяем необходимость перестановки

                    //И переставляем все внутренние элементы, за исключением указателей связи, местами

                    strcpy(temp->price, left->price);
                    strcpy(temp->id, left->id);
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    strcpy(temp->discounts, left->discounts);
                    strcpy(temp->release_number, left->release_number);
                    strcpy(temp->release_frequency, left->release_frequency);

                    strcpy(left->price, right->price);
                    strcpy(left->id, right->id);
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    strcpy(left->discounts, right->discounts);
                    strcpy(left->release_number, right->release_number);
                    strcpy(left->release_frequency, right->release_frequency);

                    strcpy(right->price, temp->price);
                    strcpy(right->id, temp->id);
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    strcpy(right->discounts, temp->discounts);
                    strcpy(right->release_number, temp->release_number);
                    strcpy(right->release_frequency, temp->release_frequency);
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

                    //И переставляем все внутренние элементы, за исключением указателей связи, местами

                    strcpy(temp->price, left->price);
                    strcpy(temp->id, left->id);
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    strcpy(temp->discounts, left->discounts);
                    strcpy(temp->release_number, left->release_number);
                    strcpy(temp->release_frequency, left->release_frequency);

                    strcpy(left->price, right->price);
                    strcpy(left->id, right->id);
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    strcpy(left->discounts, right->discounts);
                    strcpy(left->release_number, right->release_number);
                    strcpy(left->release_frequency, right->release_frequency);

                    strcpy(right->price, temp->price);
                    strcpy(right->id, temp->id);
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    strcpy(right->discounts, temp->discounts);
                    strcpy(right->release_number, temp->release_number);
                    strcpy(right->release_frequency, temp->release_frequency);
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

                    //И переставляем все внутренние элементы, за исключением указателей связи, местами

                    strcpy(temp->price, left->price);
                    strcpy(temp->id, left->id);
                    strcpy(temp->publisher, left->publisher);
                    strcpy(temp->name, left->name);
                    strcpy(temp->discounts, left->discounts);
                    strcpy(temp->release_number, left->release_number);
                    strcpy(temp->release_frequency, left->release_frequency);

                    strcpy(left->price, right->price);
                    strcpy(left->id, right->id);
                    strcpy(left->publisher, right->publisher);
                    strcpy(left->name, right->name);
                    strcpy(left->discounts, right->discounts);
                    strcpy(left->release_number, right->release_number);
                    strcpy(left->release_frequency, right->release_frequency);

                    strcpy(right->price, temp->price);
                    strcpy(right->id, temp->id);
                    strcpy(right->publisher, temp->publisher);
                    strcpy(right->name, temp->name);
                    strcpy(right->discounts, temp->discounts);
                    strcpy(right->release_number, temp->release_number);
                    strcpy(right->release_frequency, temp->release_frequency);
                }
                right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            }
            left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
            right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
        }
        sort_show();
        streamline_journals_menu();
    }

};

int main() {
    InformationSystem test;
    test.menu();
    return 0;
}