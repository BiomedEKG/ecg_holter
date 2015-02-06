#include <cstdio>
#include "EctopicBeatTest.h"

void testEctopicBeat::wyswietlWynik () {
    double czasyR [] = {78, 371, 664, 948, 1233, 1516, 1811, 2046, 2404, 2707, 2999, 3284, 3561, 3864, 4171, 4467, 4766, 5062, 5348, 5635, 5920, 6216, 6528, 6825, 7107, 7392, 7671, 7954, 8247, 8540, 8839, 9143, 9433, 9712};
    int N = 34;

    for (int i = 0; i < (N-1); i++) {
        Rtime.push_back(czasyR[i]);
    }

    map<int, vector<double> > klasy;

    for (int i = 0; i < (N-1); i++) {
        if (i%2 == 0) {
            klasy [1].push_back(czasyR[i]);
        }
        else {
            klasy [2].push_back(czasyR[i]);
        }
    }

    vector<double> ectopowe = searchEctopic (Rtime);

    if (ectopowe [0] == 2046) {
        cout << "test1 wypadl pomyslnie." << endl;
        cout << "Wykryto uderzenie ektopowe w " << ectopowe [0] << " ms" << endl;
    }
    else {
        cout << "test1 wypadl niepomyslnie - nie wykryto uderzenia ektopowego w oczekiwanym miejscu." << endl;
    }

    map<string, vector<double> > sklasyfikowane = classificationOfBeats (klasy, ectopowe);

    for (vector<double>::size_type i = 0; i < sklasyfikowane["S"].size(); i++ ) {
        cout << "test2 wypadl pomyslnie: Wykryte uderzenie ektopowe jest nadkomorowe." << endl;
    }

}
