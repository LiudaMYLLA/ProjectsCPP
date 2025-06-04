#include "wrapper.h"
#include <QVariant>
#include <QDebug>
Wrapper::Wrapper() {}

QVariantList Wrapper::getAll() const{
    QVariantList result;
    for(auto it = list1.begin(); it != list1.end(); ++it ){
        result.append(*it);
    }
    return result;
}

void Wrapper::addAtTheBeginning(const QVariant& value){

    // C++17: keyword constexpr. I am already know static_assert (uses in compilation stage)
    // main difference that constexpr performs different processing depending on the type and
    // static_assert disallows other types
    //std::is_same<T,int>::value is the same to std::is_same_v<T,int> - C++17
    //constexpr говорит компилятору:
    //“Если это условие можно вычислить на этапе компиляции — оставь этот кусок кода, а остальные выкинь

    int num = value.toInt();
    list1.addAtTheBeginning(num);

}

void Wrapper::addAtTheEnd(const QVariant& value){
    int num = value.toInt();
    list1.addAtTheEnd(num);
}

void Wrapper::deleteAll(){
    list1.deleteAll();
}

void Wrapper::printAllInBackOrder()const{
    list1.printAllInBackOrder();
}

void Wrapper::addAtThePosition(QVariant data, QVariant pos){
    int num = data.toInt();
    int posN = pos.toInt();
    list1.addAtThePosition(num, posN);
}

void Wrapper::deleteFromPosition(QVariant pos){
    int posN = pos.toInt();
    list1.deleteFromPosition(posN);
}
