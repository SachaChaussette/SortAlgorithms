#pragma once

#include <iostream>
#include <string>
#include <random>
#include <thread>

using namespace std;
using namespace std::chrono_literals;
using namespace chrono;
using namespace this_thread;

typedef unsigned int u_int;

#define BLUE "\x1B[38;5;63m"
#define RED "\x1B[38;5;196m"
#define ORANGE "\x1B[38;5;208m"
#define RESET "\033[0m"

template<typename ValueType>
ValueType GetRandomNumberInRange(const ValueType& _min, const ValueType& _max)
{
    random_device _rSeed; // Obtient un graine aléatoire
    mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
    uniform_int_distribution<> _distr(_min, _max); // Définit la distribution (les limites)

    return _distr(_gen); // Génération du nombre
}

template<typename ReturnType>
ReturnType Retrieve(const string& _question)
{
    cout << _question << endl;
    ReturnType _result;
    cin >> _result;
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    return _result;
}


string CalculateAndGetTime(const microseconds& _duration)
{
    const seconds& _secondDuration = duration_cast<seconds>(_duration);
    double _hours = double(_secondDuration.count() / 3600);
    double _minutes = double((_secondDuration.count() % 3600) / 60);
    double _seconds = double(_secondDuration.count() % 60);
    double _millis = double((_duration.count() / 1000) % 1000);
    double _micros = double(_duration.count());

    return ORANGE + to_string(_hours) + " heures, " + to_string(_minutes) + " minutes, " + to_string(_seconds)
        + " secondes, " + to_string(_millis) + " millisecondes, " + to_string(_micros) + " microsecondes";
}

template<typename ValueType, typename SizeType>
void DisplayArray(ValueType*& _array, const SizeType& _arraySize, const string& _color, const string& _title)
{
    cout << _color;
    cout << _title << endl;
    for (u_int _index = 0; _index < _arraySize; _index++)
    {
        cout << to_string(_index) + " -\t" + to_string(_array[_index]) << endl;
    }
}

template<typename ValueType>
void Swap(ValueType*& _array, ValueType _firstIndex, ValueType _secondIndex)
{
    ValueType _tempElement = _array[_firstIndex];
    _array[_firstIndex] = _array[_secondIndex];
    _array[_secondIndex] = _tempElement;
}


#pragma region QuickSort

template<typename ValueType>
ValueType Partition(ValueType*& _array, ValueType _firstIndex, ValueType _lastIndex)
{
    //static int _arraySize = _lastIndex / 2;
    ValueType _pivot = _array[_firstIndex];

    ValueType i = _firstIndex - 1;
    ValueType j = _lastIndex + 1;

    while (true)
    {
        do
        {
            i++;                        // > : ordre décroissant
        } while (_array[i] < _pivot);   // < : ordre croissant

        do
        {
            j--;                        // < : ordre décroissant 
        } while (_array[j] > _pivot);   // > : ordre croissant

        if (i >= j) return j;
        Swap(_array, i, j);
    }
}

template<typename ValueType>
void QuickSort(ValueType*& _array, const ValueType& _firstIndex, const ValueType& _lastIndex)
{
    if (_firstIndex >= 0 && _lastIndex >= 0 && _firstIndex < _lastIndex)
    {
        ValueType pivot = Partition(_array, _firstIndex, _lastIndex);
        QuickSort(_array, _firstIndex, pivot);

        QuickSort(_array, pivot + 1, _lastIndex);
    }
}

template <typename ValueType, typename SizeType = u_int>
void QuickSortDemo(const bool _wantToDisplayArray)
{
    SizeType _arraySize = Retrieve<SizeType>("Donne le taille du tableau");
    ValueType* _array = new ValueType[_arraySize];

    for (SizeType _index = 0, _revertIndex = _arraySize - 1; _index < _arraySize; _index++, _revertIndex--)
    {
        // CAS MOYEN :      GetRandomNumberInRange(0, _arraySize)
        // CAS OPTIMAL :    _index 
        // PIRE DES CAS :   _revertIndex 
        _array[_index] = GetRandomNumberInRange<ValueType>(0, _arraySize);
    }

    if(_wantToDisplayArray) DisplayArray(_array, _arraySize, BLUE, "TABLEAU ORIGINAL");
    
    cout << RED << endl;
    cout << "Tri Rapide en cours..." << endl;

    using Time = steady_clock::time_point;
    const Time& _start = high_resolution_clock::now();

    QuickSort<ValueType>(_array, 0, _arraySize - 1);

    const Time& _end = high_resolution_clock::now();
    const microseconds& _duration = duration_cast<microseconds>(_end - _start);

    cout << "Terminé !" << endl;

    if (_wantToDisplayArray) DisplayArray(_array, _arraySize, ORANGE, "TABLEAU MODIFIER");

    cout << CalculateAndGetTime(_duration) << endl;

    cout << RESET;

    delete[] _array;
    system("pause");
    system("cls");
    QuickSortDemo<ValueType, SizeType>(_wantToDisplayArray);
}

#pragma endregion