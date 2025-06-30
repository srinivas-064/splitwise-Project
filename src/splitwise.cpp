#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

double round2(double value, int places) {
    double scale = pow(10.0, places);
    return round(value * scale) / scale;
}

string getKeyFromValue(const map<string, double>& details, double value) {
    for (map<string, double>::const_iterator it = details.begin(); it != details.end(); ++it) {
        if (fabs(it->second - value) < 1e-6) {
            return it->first;
        }
    }
    return "";
}

void findPath(map<string, double>& details) {
    if (details.empty()) return;

    map<string, double>::iterator maxIt = details.begin();
    map<string, double>::iterator minIt = details.begin();

    for (map<string, double>::iterator it = details.begin(); it != details.end(); ++it) {
        if (it->second > maxIt->second) maxIt = it;
        if (it->second < minIt->second) minIt = it;
    }

    double maxValue = maxIt->second;
    double minValue = minIt->second;

    if (fabs(maxValue - minValue) < 1e-6) return; // All settled

    string maxKey = maxIt->first;
    string minKey = minIt->first;

    double result = round2(maxValue + minValue, 1);

    if (result >= 0.0) {
        cout << minKey << " needs to pay " << maxKey << ": " << fixed << setprecision(2) << fabs(minValue) << endl;
        details.erase(maxKey);
        details.erase(minKey);
        details[maxKey] = result;
        details[minKey] = 0.0;
    } else {
        cout << minKey << " needs to pay " << maxKey << ": " << fixed << setprecision(2) << fabs(maxValue) << endl;
        details.erase(maxKey);
        details.erase(minKey);
        details[maxKey] = 0.0;
        details[minKey] = result;
    }
    findPath(details);
}

int main() {
    map<string, double> parm;
    int n;
    cout << "Enter number of persons: ";
    cin >> n;

    cout << "Enter name and balance for each person (negative for owes, positive for to receive):" << endl;
    for (int i = 0; i < n; ++i) {
        string name;
        double balance;
        cout << "Person " << (i + 1) << " name: ";
        cin >> name;
        cout << "Person " << (i + 1) << " balance: ";
        cin >> balance;
        parm[name] = balance;
    }

    cout << "\nSettlement steps:\n";
    findPath(parm);

    return 0;
}
