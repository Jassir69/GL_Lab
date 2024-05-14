#include "SensorManagementServices.h"

// Fonction pour vérifier le fonctionnement d'un capteur en comparant ses mesures avec celles des capteurs proches
double SensorManagementServices::checkSensorOperation(const Sensor &sensorSelected, const std::unordered_map<std::string, Sensor> &allSensors, int period) {
    auto means = calculateMeans(sensorSelected, period);  // Calculer les valeurs moyennes pour le capteur sélectionné
    std::vector<Sensor> nearbySensors;                    // Créer un vecteur pour stocker les capteurs proches

    // Trouver les quatre capteurs les plus proches
    while (nearbySensors.size() < 4) {
        Sensor closest = closestSensor(sensorSelected, nearbySensors, allSensors);  // Trouver le capteur le plus proche qui n'est pas déjà dans le vecteur
        if (!closest.getSensorID().empty()) {                                       // Si un capteur valide a été trouvé
            nearbySensors.push_back(closest);                                       // Ajouter le capteur au vecteur
        } else {
            break;  // Si aucun capteur valide n'a été trouvé, sortir de la boucle
        }
    }

    auto weightedMeans = calculateWeightedMeans(sensorSelected, nearbySensors, period);  // Calculer les valeurs moyennes pondérées pour le capteur sélectionné et les capteurs proches
    std::vector<double> marginErrors;                                                    // Créer un vecteur pour stocker la marge d'erreur pour chaque polluant

    // Boucle sur les valeurs moyennes
    for (size_t i = 0; i < means.size(); i++) {
        marginErrors.push_back(calculateMarginError(means[i], weightedMeans[i]));  // Calculer la marge d'erreur et l'ajouter au vecteur
    }

    // Calculer la moyenne générale des marges d'erreur
    double sum = 0.0;
    for (const auto &error : marginErrors) {
        sum += error;
    }
    double overallMean = sum / marginErrors.size();

    return overallMean;  // Retourner la moyenne générale des marges d'erreur
}

// Fonction pour calculer les valeurs moyennes des polluants pour un capteur donné sur une période
std::vector<double> SensorManagementServices::calculateMeans(const Sensor &sensor, int period) {
    auto measurements = sensor.getMeasurementsForPeriod(period);        // Obtenir les mesures pour le capteur sur la période
    std::unordered_map<std::string, std::pair<double, int>> sumCounts;  // Créer une map pour stocker la somme et le compte de chaque polluant

    // Boucle sur les mesures
    for (const auto &measurement : measurements) {
        const auto &id = measurement.getAttributeID();  // Obtenir l'ID de l'attribut (type de polluant)
        sumCounts[id].first += measurement.getValue();  // Ajouter la valeur à la somme pour ce polluant
        sumCounts[id].second++;                         // Incrémenter le compte pour ce polluant
    }

    std::vector<double> means;                                                 // Créer un vecteur pour stocker les valeurs moyennes
    means.reserve(4);                                                          // Réserver de l'espace pour 4 polluants : O3, SO2, NO2, PM10
    const std::vector<std::string> pollutants = {"O3", "SO2", "NO2", "PM10"};  // Définir l'ordre des polluants

    // Boucle sur les polluants
    for (const auto &pollutant : pollutants) {
        if (sumCounts[pollutant].second > 0) {                                          // S'il y a des mesures pour ce polluant
            means.push_back(sumCounts[pollutant].first / sumCounts[pollutant].second);  // Calculer la moyenne et l'ajouter au vecteur
        } else {
            means.push_back(0);  // S'il n'y a pas de mesures pour ce polluant, ajouter 0 au vecteur
        }
    }

    return means;  // Retourner le vecteur des valeurs moyennes
}

// Fonction pour calculer les valeurs moyennes pondérées des polluants pour un capteur donné et ses capteurs proches sur une période
std::vector<double> SensorManagementServices::calculateWeightedMeans(const Sensor &selectedSensor, const std::vector<Sensor> &nearbySensors, int period) {
    double weightTotal = 0;                    // Initialiser le poids total
    std::vector<double> means = {0, 0, 0, 0};  // Initialiser le vecteur des valeurs moyennes

    // Boucle sur les capteurs proches
    for (const auto &sensor : nearbySensors) {
        double weight = 1 / distance(selectedSensor, sensor);  // Calculer le poids pour ce capteur (inverse de la distance)
        weightTotal += weight;                                 // Ajouter le poids au poids total
        auto tempMeans = calculateMeans(sensor, period);       // Calculer les valeurs moyennes pour ce capteur

        // Boucle sur les valeurs moyennes
        for (size_t i = 0; i < means.size(); i++) {
            means[i] += tempMeans[i] * weight;  // Ajouter la moyenne pondérée à la valeur correspondante dans le vecteur
        }
    }

    if (weightTotal > 0) {  // Si le poids total n'est pas 0
        for (double &mean : means) {
            mean /= weightTotal;  // Diviser chaque valeur moyenne par le poids total pour obtenir la moyenne pondérée
        }
    }
    return means;  // Retourner le vecteur des valeurs moyennes pondérées
}

// Fonction pour calculer la distance euclidienne entre deux capteurs
double SensorManagementServices::distance(const Sensor &sensor1, const Sensor &sensor2) {
    return sqrt(pow(sensor1.getLatitude() - sensor2.getLatitude(), 2) + pow(sensor1.getLongitude() - sensor2.getLongitude(), 2));
}

// Fonction pour calculer la marge d'erreur entre la concentration et la concentration pondérée
double SensorManagementServices::calculateMarginError(double concentration, double weightedConcentration) {
    return fabs(concentration - weightedConcentration) / weightedConcentration;
}

// Fonction pour trouver le capteur le plus proche d'un capteur donné qui n'est pas déjà dans une liste de capteurs exclus
Sensor SensorManagementServices::closestSensor(const Sensor &sensorSelected, const std::vector<Sensor> &excludedSensors, const std::unordered_map<std::string, Sensor> &allSensors) {
    double dist = std::numeric_limits<double>::max();  // Initialiser la distance minimale à la valeur maximale possible
    Sensor closest;                                    // Initialiser le capteur le plus proche

    // Boucle sur tous les capteurs
    for (const auto &pair : allSensors) {
        const auto &sensor = pair.second;  // Obtenir le capteur

        // Si le capteur n'est pas le capteur sélectionné et n'est pas dans la liste des capteurs exclus
        if (sensor.getSensorID() != sensorSelected.getSensorID() &&
            std::find_if(excludedSensors.begin(), excludedSensors.end(), [&sensor](const Sensor &s) { return s.getSensorID() == sensor.getSensorID(); }) == excludedSensors.end()) {
            double currentDist = distance(sensorSelected, sensor);  // Calculer la distance au capteur sélectionné
            if (currentDist < dist) {                               // Si la distance est inférieure à la distance minimale actuelle
                dist = currentDist;                                 // Mettre à jour la distance minimale
                closest = sensor;                                   // Mettre à jour le capteur le plus proche
            }
        }
    }
    return closest;  // Retourner le capteur le plus proche
}
