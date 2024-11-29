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


#pragma region CombSort

template<typename ValueType, typename SizeType>
long long CombSort(ValueType*& _array, const SizeType& _arraySize)
{
    long long _operationCount = 0; // Compter le Nombre d'Opération

    SizeType _gap = _arraySize;
    bool _changed = true;
    while (_gap > 1 || _changed == true)
    {
        _gap = u_int(_gap / 1.3);
        _operationCount++; // Compter le Nombre d'Opération

        if (_gap < 1)
        {
            _gap = 1;
            _operationCount++; // Compter le Nombre d'Opération
        }

        SizeType _index = 0;
        _changed = false;
        _operationCount += 2; // Compter le Nombre d'Opération

        while (_index < _arraySize - _gap)
        {
            // < ordre décroissant
            // > ordre croissant
            if (_array[_index] > _array[_index + _gap])
            {
                Swap<ValueType>(_array, _index, _index + _gap);
                _changed = true;
                _operationCount += 4; // Compter le Nombre d'Opération
            }
            _index++;
            _operationCount++; // Compter le Nombre d'Opération
        }
    }
    return _operationCount; // Compter le Nombre d'Opération
}

template <typename ValueType, typename SizeType = u_int>
void CombSortDemo(const bool _wantToDisplayArray)
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

    if (_wantToDisplayArray) DisplayArray(_array, _arraySize, BLUE, "TABLEAU ORIGINAL");

    cout << RED << endl;
    cout << "Tri Pair-Impair en cours..." << endl;

    using Time = steady_clock::time_point;
    const Time& _start = high_resolution_clock::now();

    long long _operationCount = CombSort<ValueType, SizeType>(_array, _arraySize);

    const Time& _end = high_resolution_clock::now();
    const microseconds& _duration = duration_cast<microseconds>(_end - _start);

    cout << "Terminé !" << endl;

    if (_wantToDisplayArray) DisplayArray(_array, _arraySize, ORANGE, "TABLEAU MODIFIER");

    cout << CalculateAndGetTime(_duration) << endl;
    cout << "Nombre d'opération total :\t" + to_string(_operationCount) << endl;
    cout << RESET;

    delete[] _array;
    system("pause");
    system("cls");
    CombSortDemo<ValueType, SizeType>(_wantToDisplayArray);
}

#pragma endregion