# AirWatcher - Software Engineering & UML Lab
### Département Informatique, 3IF, INSA Lyon

## Overview
**AirWatcher** is a software application developed as part of the Software Engineering labs at INSA Lyon. The main objective of this project is to apply software engineering principles to create a high-quality software tool that assists a government environmental protection agency in monitoring and analyzing air quality over a large territory.

## Description
AirWatcher analyzes data from various sensors spread across a region to check sensor functionality and aggregate air quality data. This helps in maintaining the sensor infrastructure and supports decision-making processes

### Key Features
- **Sensor Data Analysis:** Ensures each sensor is functioning correctly by analyzing data discrepancies and patterns.
- **Statistical Reporting:** Generates statistical insights about air quality, aiding in environmental assessment and decision-making.
- **Sensor Similarity Scoring:** Identifies and ranks sensors based on the similarity of the data they generate over a specified period, aiding in recognizing areas with similar air quality issues.
- **Air Quality Measurement:** Computes the air quality at a given geographical point and moment, regardless of sensor presence, using interpolated data from nearby sensors.

### Technologies
- **CSV Data Management:** Uses CSV files (`sensors.csv`, `measurements.csv`, and `attributes.csv`) for storing sensor data and attributes.
- **Python/Java/C++:** Depending on the chosen implementation language, the application handles file management, data processing, and user interactions.
- **Console-Based Interface:** Provides a simple, command-line interface for interacting with the application directly on the server.

