#include <iostream>
#include <iostream>
#include <vector>
#define N 5

using namespace std;

class Drugs_Box
{
private:
    string name;
    double length, width, hight;

public:
    Drugs_Box() { length = 1; width = 1; hight = 1; name = "Drug"; }
    Drugs_Box(string name) { length = 1; width = 1; hight = 1; this->name = name; }

    double Get_Volume() { return length * width * hight; }
    virtual double Get_Weight() { return 0; }


    virtual void Input()
    {
        cout << "\t" << this->name << endl;
        cout << "Length: ";
        cin >> this->length;

        cout << "Width: ";
        cin >> this->width;

        cout << "Hight: ";
        cin >> this->hight;
    }

};

class Box_for_Drugs_in_Bottles : public Drugs_Box
{
private:
    double weigth_bottle;
    double weigth_liquid;

public:

    Box_for_Drugs_in_Bottles() : Drugs_Box()
    {
        weigth_bottle = 1;
        weigth_liquid = 1;
    }

    Box_for_Drugs_in_Bottles(string name) : Drugs_Box(name)
    {
        weigth_bottle = 1;
        weigth_liquid = 1;
    }


    double Get_Weight() override
    {
        return weigth_bottle + weigth_liquid;
    }

    void Input() override
    {
        Drugs_Box::Input();
        cout << "Weight of Bottle: ";
        cin >> this->weigth_bottle;

        cout << "Weight of Substance: ";
        cin >> this->weigth_liquid;
    }
};

class Box_for_Drugs_in_Powders : public Drugs_Box
{
private:
    double weigth_powder;
public:
    Box_for_Drugs_in_Powders() : Drugs_Box()
    {
        weigth_powder = 1;
    }

    Box_for_Drugs_in_Powders(string name) : Drugs_Box(name)
    {
        weigth_powder = 1;
    }

    double Get_Weight() override
    {
        return weigth_powder;
    }

    void Input() override
    {
        Drugs_Box::Input();
        cout << "Weight of Powder: ";
        cin >> this->weigth_powder;
    }
};


class Place
{
private:
    vector<Drugs_Box*> Vector_Drug;

    double all_Weight = 0;
    double all_Wolume = 0;
    double max_Weight;
    double max_Volume;

    void Count_All_Weight(vector<Drugs_Box*> boxes)
    {
        int i;
        for (i = 0; i < boxes.size(); i++)
        {
            all_Weight += boxes[i]->Get_Weight();
        }
    }
    void Count_All_Volume(vector<Drugs_Box*> boxes)
    {
        int i;
        for (i = 0; i < boxes.size(); i++)
        {
            all_Wolume += boxes[i]->Get_Volume();
        }
    }

public:

    Place(Drugs_Box** parr, int size_of_parr)
    {
        int i;
        for (i = 0; i < size_of_parr; i++, parr)
        {
            Vector_Drug.push_back(parr[i]);
        }
    }
    void Set_Max_Weight(double weight)
    {
        max_Weight = weight;
    }

    void Set_Max_Volume(double volume)
    {
        max_Volume = volume;
    }

    void Locate(int num_of_elem, Drugs_Box obj, ...)
    {
        Drugs_Box* p = &obj;
        for (int i = 0; i < num_of_elem; i++)
        {
            Vector_Drug.push_back(p);
        }
    }

    double Get_Max_Weight() { return max_Weight; }
    double Get_Max_Volume() { return max_Volume; }
    double Get_All_Weight() { return all_Weight; }
    double Get_All_Volume() { return all_Wolume; }

    bool Can_Be_Placed()
    {
        Count_All_Volume(Vector_Drug);
        Count_All_Weight(Vector_Drug);
        if ((all_Wolume <= max_Volume) && (all_Weight <= max_Weight))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};


void Input_All_Obj(Drugs_Box** parr)
{

    for (int i = 0; i < N; i++, parr++)
    {
        (*parr)->Input();
    }
}

int main()
{
    Box_for_Drugs_in_Bottles   drug_1("Solpadein");
    Drugs_Box              drug_2("Astra");
    Box_for_Drugs_in_Bottles   drug_3("Nurofen");
    Drugs_Box              drug_4("Antimigren");
    Box_for_Drugs_in_Powders   drug_5("Dodecacelatein");

    Drugs_Box* parr[N]
    {
        &drug_1,
        &drug_2,
        &drug_3,
        &drug_4,
        &drug_5,
    };

    Input_All_Obj(parr);
    Place place(parr, N);
    place.Set_Max_Volume(100);
    place.Set_Max_Weight(35);

    if (place.Can_Be_Placed())
    {
        cout << endl;
        cout << "drugs CAN be placed here" << endl;
    }
    else
    {
        cout << endl;
        cout << "drugs CAN NOT be placed here" << endl;
    }

    cout << "\nMax Weight: " << place.Get_Max_Weight() << endl;
    cout << "Overall Weight: " << place.Get_All_Weight() << endl << endl;
    cout << "Max Volume: " << place.Get_Max_Volume() << endl;
    cout << "Overall Volume: " << place.Get_All_Volume() << endl;
}

//Створити базовий клас УПАКУВАННЯ ДЛЯ ЛІКІВ (задаються назва, розмір упакування (ширина, довжина, висота). 
//Створити похідні класи УПАКУВАННЯ ДЛЯ ЛІКІВ У ФЛАКОНАХ (задаються вага речовини, вага флакону) та УПАКУВАННЯ ДЛЯ ЛІКІВ У ПОРОШКАХ (задається вага порошку). 
//Для введених даних про різні ліки, наявні в аптеці, обчислити їх сумарну вагу та сумарний об’єм і визначити чи можна розмістити ці ліки у певній тарі із заданими максимально можливим об’ємом і максимально можливою вагою. 
//Для перевірки використати масив вказівників на об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів. 