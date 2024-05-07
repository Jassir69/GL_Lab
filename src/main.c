using namespace std;
#include <iostream>

struct Attribute {
    string unit;
    string description;
};

int main() {
    ifstream file("attributes.csv");
    map<string, AttributeInfo> attributeMap;

    if (file.is_open()) {
        string line;
        // Ignorer la première ligne (en-têtes)
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
        return 1;
    }

    // Affichage des données chargées
    for (const auto& pair : attributeMap) {
        cout << "AttributeID: " << pair.first << ", Unit: " << pair.second.unit << ", Description: " << pair.second.description << endl;
    }

    return 0;
}