#include <iostream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;

 struct User{
    string loggin;
    int pin;
    string root;
};

struct Menu{
    string name;
    string type;
    int prize;
};



struct Chek{
    string log;
    int prize;
    vector<int> ports;
    vector<string> meal;
};


void menuUser();
void sectionsOfMenu(int num);
void  registration();

int nearlyMD5(string str){
    int cipher=0;
    for(int i=0;i<str.length();i++){
        cipher=cipher+(int)str[i];
    }
    return cipher;
}

string roots(){
    int choice;
    string root;
    string pinForAdmin;
    cout<<"Если вы админ нажмите 1"<<endl<<"если пользователь нажмите 0 : ";
    cin>>choice;
    if(choice==1){
        cout<<"Введите пароль для подтверждения своих прав : ";
        cin>>pinForAdmin;
        if(pinForAdmin == "realAdmin") root="admin";
    }
    else root = "user";
    return root;
}


string avtorization(){
    User user;
    string root;
    string pin;
    bool flag = true;
    while(flag){
    cout<<"----Авторизация----"<<endl;
    cout<<"Введите ваш логин : ";
    cin>>user.loggin;
    cout<<"Введите ваш пароль : ";
    cin>>pin;
   user.pin=nearlyMD5(pin);
    int num=0;
    string path="myFile.txt";
    
    ifstream fin;
    fin.open(path);
    if(!fin.is_open()){
        cout<<"Ошибка открытия файла "<<endl;
    }
    else{
        User user2;
        while(fin.read((char*)&user2, sizeof(User))){
            if(user.loggin==user2.loggin && user.pin == user2.pin){
                cout<<"Здраствйте "<<user2.root<<endl;
                num++;
                root=user2.root;
            }
            }
        }
    fin.close();
        if(num != 0) flag=false;
        else{
            cout<<"Ошибка, чтоб попробывать еще раз нажмите 1"<<endl;
            cout<<"Для перехода на регистрация нажмите 0 : ";
            int choice;
            cin>>choice;
            if(choice==0) registration();
            else continue;
            num=0;
        }
    }
    return root;
}



string chekLoggin(){
    string name;
    bool flag = true;
    int num =0;
    while(flag){
        cout<<"Введите логин : ";
    cin>>name;
   
    string path="myFile.txt";
    
    ifstream fin;
    fin.open(path);
    if(!fin.is_open()){
        cout<<"Ошибка открытия файла "<<endl;
    }
    else{
        User user2;
        while(fin.read((char*)&user2, sizeof(User))){
            if(name==user2.loggin){
                num++;
            }
        }
    }
    fin.close();
        if(num == 0) flag=false;
        else{
            cout<<"Извините,это имя уже занято, попробуйте другое"<<endl;
            num=0;
        }
    }
    return name;
}




void  registration(){
    User user,R;
    string pin;
    string pinForAdmin;
    cout<<"----Регистрация----"<<endl;
    user.loggin=chekLoggin();
    cout<<"Введите ваш пароль : ";
    cin>>pin;
    user.pin=nearlyMD5(pin);
    user.root=roots();
    
    string path="myFile.txt";
    
    ofstream fout;
    fout.open(path,ofstream::app);
    if(!fout.is_open()){
        cout<<"Oшибка открытия файла"<<endl;
    }
    else{
        fout.write((char*)&user, sizeof(User));
    }

    fout.close();
}


void saveNewMeal(string name, int prize,string type){
    const char* PATH = "C:\\EDAbaza\\5.txt";
    
    fstream file(PATH);
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    Menu R[size];
    ifstream fr(PATH, ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    
    Menu newR[size+1];
    
    for(int i =0;i<size;i++){
        newR[i].name=R[i].name;
        newR[i].prize=R[i].prize;
        newR[i].type=R[i].type;
    }
        newR[size].name=name;
        newR[size].prize=prize;
        newR[size].type=type;

    ofstream fout;
    fout.open(PATH);
    if(!fout.is_open()){
        cout<<"Oшибка открытия файла"<<endl;
    }
    else{
        fout.write((char*)&newR, sizeof(newR));
    }

    fout.close();
    
}


void createNewMeal(int num){
    string name;
    int prize;
    string type;
    
    switch (num) {
        case 1:
            sectionsOfMenu(1);
            cout<<"Введите название блюда : ";
            cin>>name;
            type="dessert";
            cout<<"Введите цену  блюда : ";
            cin>>prize;
            saveNewMeal(name, prize,type);
            break;
        case 2:
            sectionsOfMenu(2);
            cout<<"Введите название блюда : ";
            cin>>name;
            type="ice";
            cout<<"Введите цену  блюда : ";
            cin>>prize;
            saveNewMeal(name, prize,type);
            break;
        case 3:
            sectionsOfMenu(3);
            cout<<"Введите название блюда : ";
            cin>>name;
            type="hot";
            cout<<"Введите цену  блюда : ";
            cin>>prize;
            saveNewMeal(name, prize,type);
            break;
            
        default:
            break;
    }
}



void seeMenu(){
    int num=1;
    while(num!=0){
        menuUser();
        cin>>num;
        if(num==0) break;
        else{
        sectionsOfMenu(num);
        cout<<"Чтобы вернутся назад нажмите 1 : ";
        cin>>num;
        }
    }
    
}


void saveCorrectMeal(int numOfMeal,string name,int prize, string type){
    const char* PATH = "C:\\EDAbaza\\5.txt";
    
    fstream file(PATH);
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    Menu R[size];
    ifstream fr(PATH, ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    
    Menu newR[size];
    
    for(int i=0;i<size;i++){
        if(i!=numOfMeal){
        newR[i].name=R[i].name;
        newR[i].prize=R[i].prize;
        newR[i].type=R[i].type;
        }
        else{
            newR[i].name=name;
            newR[i].prize=prize;
            newR[i].type=type;
        }
    }
    ofstream fout;
    fout.open(PATH);
    if(!fout.is_open()){
        cout<<"Oшибка открытия файла"<<endl;
    }
    else{
        fout.write((char*)&newR, sizeof(newR));
    }

    fout.close();
    
    
}


void correctMeal(int num){
    int numOfMeal;
    string name;
    int prize;
    
    switch (num) {
        case 1:
            sectionsOfMenu(1);
            cout<<"Введите номер блюда которое нужно заменить : ";
            cin>>numOfMeal;
            cout<<"Введите новое название : ";
            cin>>name;
            cout<<"Введите цену : ";
            cin>>prize;
            saveCorrectMeal(numOfMeal-1, name, prize,"dessert");
            
            break;
        case 2:
            sectionsOfMenu(2);
            cout<<"Введите номер блюда которое нужно заменить : ";
            cin>>numOfMeal;
            cout<<"Введите новое название : ";
            cin>>name;
            cout<<"Введите цену : ";
            cin>>prize;
            saveCorrectMeal(numOfMeal-1, name, prize,"ice");
            break;
        case 3:
            sectionsOfMenu(3);
            cout<<"Введите номер блюда которое нужно заменить : ";
            cin>>numOfMeal;
            cout<<"Введите новое название : ";
            cin>>name;
            cout<<"Введите цену : ";
            cin>>prize;
            saveCorrectMeal(numOfMeal-1, name, prize,"hot");
            break;
            
        default:
            break;
    }
}


void saveWithoutMeal(int numOfMeal){
    const char* PATH = "C:\\EDAbaza\\5.txt";
    
    fstream file(PATH);
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    Menu R[size];
    ifstream fr(PATH, ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    
    Menu newR[size-1];
    
    for(int i=0;i<size;i++){
        if(i!=numOfMeal){
        newR[i].name=R[i].name;
        newR[i].prize=R[i].prize;
        newR[i].type=R[i].type;
        }
        else{
            newR[i].name=R[i+1].name;
            newR[i].prize=R[i+1].prize;
            newR[i].type=R[i+1].type;
            i++;
        }
    }
    ofstream fout;
    fout.open(PATH);
    if(!fout.is_open()){
        cout<<"Oшибка открытия файла"<<endl;
    }
    else{
        fout.write((char*)&newR, sizeof(newR));
    }

    fout.close();

}

void deleteMeal( int num){
    int numOfMeal;
    switch (num) {
        case 1:
            sectionsOfMenu(1);
            cout<<"Введите номер блюда которое нужно удалить : ";
            cin>>numOfMeal;
            saveWithoutMeal(numOfMeal-1);
            
            break;
        case 2:
            sectionsOfMenu(2);
            cout<<"Введите номер блюда которое нужно удалить : ";
            cin>>numOfMeal;
            saveWithoutMeal(numOfMeal-1);
            break;
        case 3:
            sectionsOfMenu(3);
            cout<<"Введите номер блюда которое нужно удалить : ";
            cin>>numOfMeal;
            saveWithoutMeal(numOfMeal-1);
            break;
            
        default:
            break;
    }
}




void outputSelect(int sign, int num){
    fstream file("C:\\EDAbaza\\5.txt");
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    Menu R[size];
    ifstream fr("C:\\EDAbaza\\5.txt", ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    if(sign==1){
        for(int i =0;i<size;i++){
            if(R[i].prize>num){
                cout<<i+1<<")"<<R[i].name<<" "<<R[i].prize<<" "<<R[i].type<<endl;
            }
        }
    }
    else{
        for(int i =0;i<size;i++){
            if(R[i].prize<num){
                cout<<i+1<<")"<<R[i].name<<" "<<R[i].prize<<" "<<R[i].type<<endl;
            }
        }
    }
    
}


void treatment(char str[]){
    
    
    char  **words = NULL, *p = NULL;
       int i, cnt = 0;

       for ( p = strtok(str, " "); p != NULL; p = strtok(NULL, " ") ){
           if ( ( words = (char**)realloc(words, sizeof(char*) * (cnt + 1)) ) == NULL ){
               printf("No memory to new word!\n");
               exit(1);
           }
           if ( ( words[cnt] = strdup(p) ) == NULL ){
               printf("Can't duplicate word!\n");
               exit(1);
           }
           ++cnt;
       }
    
    
    int sign;
    
    if(strcmp(words[0],"SELECT")==0 && strcmp(words[1],"from")==0 ){
        if(strcmp(words[cnt-3],"prize")==0){
            if(strcmp(words[cnt-2],">")==0){
                 sign=1;
                int num = stoi(words[cnt-1]);
                outputSelect(sign, num);
                
            }
            else{
                sign =0;
                int num = stoi(words[cnt-1]);
                outputSelect(sign, num);
            }
        }
    }
    else if(strcmp(words[0],"DELETE")==0 && strcmp(words[1],"from")==0 ){
        if(strcmp(words[cnt-2],"meal")==0){
            int num = stoi(words[cnt-1]);
            saveWithoutMeal(num-1);
        }
    }
        
        
       for ( i = 0; i < cnt; ++i ){
           if ( words[i] != NULL ){
               free(words[i]);
               words[i] = NULL;
           }
       }
       free(words);
       words = NULL;
    
    
}

void menuForAdmin(){
    int choice=1;
    while(choice!=0){
        char str[256]="";
        int section;
        cout<<"Admin, чем займемся ?"<<endl;
        cout<<"1. Создать новое блюдо "<<endl;
        cout<<"2. Посмтореть меню "<<endl;
        cout<<"3. Изменить название блюда "<<endl;
        cout<<"4. Удалить блюдо "<<endl;
        cout<<"5. SQL запросы "<<endl;
        cout<<"(0 - для завершения работы): ";
        cin>>choice;
        switch (choice) {
            case 1:
                cout<<"1. Dessert"<<endl;
                cout<<"2. Ice"<<endl;
                cout<<"3. Hot"<<endl;
                cout<<"Выбирите раздел : ";
                cin>>section;
                createNewMeal(section);
                break;
            case 2:
                seeMenu();
                break;
            case 3:
                cout<<"1. Dessert"<<endl;
                cout<<"2. Ice"<<endl;
                cout<<"3. Hot"<<endl;
                cout<<"Выбирите раздел : ";
                cin>>section;
                correctMeal(section);
                break;
            case 4:
                cout<<"1. Dessert"<<endl;
                cout<<"2. Ice"<<endl;
                cout<<"3. Hot"<<endl;
                cout<<"Выбирите раздел : ";
                cin>>section;
                deleteMeal(section);
                break;
            case 5:
                cout<<"Введите запрос : ";
                while(strlen(str)==0){
                cin.getline(str,256);
                }
                treatment(str);
                break;
            default:
                break;
        }
    }
}











void showClients(){
    fstream file("D:\\hello.txt");
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Chek);
    
    ifstream fr;
    fr.open("D:\\hello.txt");
    if(!fr.is_open()){
        cout<<"Ошибка открытия файла "<<endl;
    }
    else{
        Chek chek1;
        while(fr.read((char*)&chek1, sizeof(chek1))){
            cout<<chek1.log<<endl;
            cout<<chek1.prize<<endl;
        }
    }
    fr.close();
}







int saveUser(int chek,vector<int> nums_ans,vector<int> nums_ports, Menu R[]){
    
    cout<<"_____________________________________"<<endl;
    cout<<"Ваш чек : "<<chek<<endl;
    cout<<"Вы заказали : "<<endl;
    for(int i =0; i< nums_ans.size();i++){
        cout<<i+1<<") "<<nums_ports[i]<<" порций "<<R[(nums_ans[i])-1].name<<endl;
    }
    
    int answer = 0;
    string name="Vlad";
    while(answer!=1){
    cout<<"Заказ верен ?"<<endl;
    cout<<"1. Да"<<endl;
    cout<<"2. удалить какое-то блюдо"<<endl;
    
    
    cin>>answer;
        if(answer==1) break;
        cout<<"Вы заказали : "<<endl;
        for(int i =0; i<nums_ans.size();i++){
            cout<<i+1<<") "<<nums_ports[i]<<" порций "<<R[(nums_ans[i])-1].name<<endl;
        }
        cout<<"Введите номер блюда которое нужно удалить или нажмите 0 для завершения : ";
        int nomer=0;
        cin>>nomer;
        cout<<"Введите кол-во порций которые нужно удалить : ";
        int ports=0;
        cin>>ports;
        
        nums_ports[nomer-1]=nums_ports[nomer-1]-ports;
        chek = chek - (nums_ports[nomer-1]*R[nomer-1].prize);
        chek = chek +R[nomer-1].prize *nums_ports[nomer-1];
        
                if(nums_ports[nomer-1]==0){
                    cout<<"Вы заказали : "<<endl;
                    cout<<"Ваш чек : "<<chek<<endl;
                      for(int i =0; i<nums_ans.size();i++){
                        if((nomer-1)!=i){
                           cout<<i+1<<") "<<nums_ports[i]<<" порций "<<R[(nums_ans[i])-1].name<<endl;
                        }
                    }
                }
                else{
                    cout<<"Ваш чек : "<<chek<<endl;
                    cout<<"Вы заказали : "<<endl;
                    for(int i =0; i<nums_ans.size();i++){
                        cout<<i+1<<") "<<nums_ports[i]<<" порций "<<R[(nums_ans[i])-1].name<<endl;
                    }
                }
    }
    if(answer==1){
        Chek chhek;
        chhek.log=name;
        chhek.prize=chek;
        for(int i =0; i<nums_ans.size();i++){
            chhek.ports.push_back (nums_ports[i]);
            chhek.meal.push_back(R[(nums_ans[i])-1].name);
        }
        
        string path="D:\\hello.txt";

        ofstream fout;
        fout.open(path,ofstream::app);
        if(!fout.is_open()){
            cout<<"Oшибка открытия файла"<<endl;
        }
        else{
            fout.write((char*)&chhek, sizeof(Chek));
        }
        fout.close();
    }
  
    cout<<"Спасибо за заказ, ожидаем вас еще!"<<endl;
    return 0;
}







void menuUser(){
    cout<<"Here is our menu : "<<endl;
    cout<<"1. Dessert"<<endl;
    cout<<"2. Ice"<<endl;
    cout<<"3. Hot"<<endl;
    cout<<"Выбирите раздел для заказа ";
    cout<<"(если вы завершили заказ нажмите 0) : ";
}






void sectionsOfMenu(int num){
    const char* PATH = "C:\\EDAbaza\\5.txt";
    
    fstream file(PATH);
    
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    
    
    Menu R[size];
    ifstream fr(PATH, ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    if(num==1){
        for(int i =0;i<size;i++){
            if(R[i].type=="dessert"){
                cout<<i+1<<") "<< R[i].name <<" "<< R[i].prize <<" "<<R[i].type <<'\n';
            }
        }
    }
    else if(num==2){
        for(int i =0; i<size;i++){
            if(R[i].type=="ice"){
                cout<<i+1<<") "<< R[i].name <<" "<< R[i].prize <<" "<<R[i].type <<'\n';
            }
        }
    }
    else if(num==3){
        for(int i =0;i<size;i++){
            if(R[i].type=="hot"){
                cout<<i+1<<") "<< R[i].name <<" "<< R[i].prize <<" "<<R[i].type <<'\n';
            }
        }
    }
    
}

void User(){
    const char* PATH = "C:\\EDAbaza\\5.txt";
    
    fstream file(PATH);
    long long  size = 0;
        file.seekg (0, std::ios::end);
        size = file.tellg();
        file.close();

    size = size/sizeof(Menu);
    
    Menu R[size];
    ifstream fr(PATH, ios::binary);
            fr.read((char*)R, sizeof(R));
          fr.close();
    
    
    string finish ="";
    int answer;
    int portions;
    int chek = 0;
    vector<int> nums_ans;
    vector<int> nums_ports;
    int section=1;
    while(section!=0){
        menuUser();
        cin>>section;
        switch (section) {
            case 1:
                sectionsOfMenu(1);
                cout<<"Хотите что-то взять если да напишите номер :"
                <<"(для выхода на главное меню напишите 0)";
                cin>>answer;
                nums_ans.push_back(answer);
                if(answer==0) continue;
                else {
                    cout<<"Cколько порций блюда вы хотите ?";
                    cin>>portions;
                    nums_ports.push_back(portions);
                    if(portions==1) chek=chek+R[answer-1].prize;
                    else chek =chek+(R[answer-1].prize*portions);
                    answer=0;
                    break;
                }
                break;
            case 2:
                sectionsOfMenu(2);
                cout<<"Хотите что-то взять если да напишите номер :"
                <<"(для выхода на главное меню напишите 0)";
                cin>>answer;
                nums_ans.push_back(answer);
                if(answer==0) continue;
                else {
                    cout<<"Cколько порций блюда вы хотите ?";
                    cin>>portions;
                    nums_ports.push_back(portions);
                    if(portions==1) chek=chek+R[answer-1].prize;
                    else chek =chek+(R[answer-1].prize*portions);
                    answer=0;
                    break;
                }
                break;
            case 3:
                sectionsOfMenu(3);
                cout<<"Хотите что-то взять если да напишите номер :"
                <<"(для выхода на главное меню напишите 0)";
                cin>>answer;
                nums_ans.push_back(answer);
                if(answer==0) continue;
                else {
                    cout<<"Cколько порций блюда вы хотите ?";
                    cin>>portions;
                    nums_ports.push_back(portions);
                    if(portions==1) chek=chek+R[answer-1].prize;
                    else chek =chek+(R[answer-1].prize*portions);
                    answer=0;
                    break;
                }
                break;
            case 0:
                break;

            default:
                break;
        }
    }
    if(chek>0) saveUser(chek, nums_ans, nums_ports, R);
    else cout<<"До скорой встречи !"<<endl;
}




int main() {


    string name;
    cout<<"Вас приветствует веб-приложение ресторан! "<<endl<<endl;;
    int choise=0;
    cout<<"Если вы уже зарегистрированы нажмите 1  для входа,"<<endl;
    cout<<"если же вы желаете зарегистрироваться нажмите 0 : ";
    cin>>choise;
    if(choise==1){
        if(avtorization()=="admin"){
            menuForAdmin();
        }
        else User();

    }
    else if(choise==0){
        registration();
        if (avtorization()=="admin"){
            menuForAdmin();
        }
        else User();
    }
    

    return 0;
}
