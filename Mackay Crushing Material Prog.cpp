#include <iostream>
#include <vector>
#include <random>
#include <numeric>

struct Particle {
    double size; // Particle size in mm
    double massPercentage; // Mass percentage of the particle size fraction
};

// Function to simulate the crushing process and update PSD
void simulateCrushing(std::vector<Particle>& feedPSD, double minSize, double maxSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(minSize, maxSize);

    for (auto& particle : feedPSD) {
        particle.size = distribution(gen);
    }
}

// Function to display the final PSD
void displayPSD(const std::vector<Particle>& PSD) {
    std::cout << "Final Particle Size Distribution (PSD):\n";
    for (const auto& particle : PSD) {
        std::cout << "Size: " << particle.size << " mm, Mass Percentage: " << particle.massPercentage << "%\n";
    }
}

// Function to calculate and display the overall reduction ratio
void displayReductionRatio(const std::vector<Particle>& feedPSD, const std::vector<Particle>& crushedPSD) {
    double feedAverageSize = 0.0;
    double feedTotalPercentage = 0.0;
    double crushedAverageSize = 0.0;
    double crushedTotalPercentage = 0.0;

    for (const auto& particle : feedPSD) {
        feedAverageSize += particle.size * (particle.massPercentage / 100);
        feedTotalPercentage += particle.massPercentage;
    }
    for (const auto& particle : crushedPSD) {
        crushedAverageSize += particle.size * (particle.massPercentage / 100);
        crushedTotalPercentage += particle.massPercentage;
    }

    double reductionRatio = feedAverageSize / crushedAverageSize;
    std::cout << "Overall Reduction Ratio: " << reductionRatio << "\n";
}

int main() {
    // Input parameters
    double feedRate = 1000; // Example: 1000/hour
    std::vector<Particle> feedPSD = { {10.0, 20.0}, {2.0, 30.0}, {3.0, 25.0}, {4.0, 15.0}, {5.0, 10.0} }; // Example initial PSD
    double minCrusherSize = 2.0; // Example: 2.0 mm
    double maxCrusherSize = 5.0; // Example: 5.0 mm

    // Simulate crushing process
    simulateCrushing(feedPSD, minCrusherSize, maxCrusherSize);

    // Display the final PSD of the crushed material
    displayPSD(feedPSD);

    // Calculate and display the overall reduction ratio
    displayReductionRatio(feedPSD, feedPSD); // Assuming the same PSD for demonstration
    
    return 0;
} 
