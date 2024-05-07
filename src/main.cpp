using namespace std;
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

struct AttributeInfo {
    string unit;
    string description;
};

map<string, AttributeInfo> loadAttributesFromFile(const string& filename) {
    map<string, AttributeInfo> attributeMap;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string attributeID, unit, description;

            getline(ss, attributeID, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');

            // Ajouter à la map
            attributeMap[attributeID] = {unit, description};
        }

        file.close();
    } else {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
    }

    return attributeMap;
}

int main() {
    map<string, AttributeInfo> attributeMap = loadAttributesFromFile("dataset/attributes.csv");

    // Affichage des données chargées
    for (const auto& pair : attributeMap) {
        cout << "AttributeID: " << pair.first << ", Unit: " << pair.second.unit << ", Description: " << pair.second.description << endl;
    }

    return 0;
}
