#include "Analysis_3.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "WeatherData.h"

TFile output_file{output_tempdatafile.c_str(), "UPDATE"};
if (output_file.IsZombie()) {
    std::cerr << "Error: Could not open data file." << std::endl;
    return;
}

    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData")); // replace with the actual tree name!!!!
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }
// Define the custom Gaussian function
double Gaussian(double* x, double* par) {
  return par[0] * exp(-0.5 * (x[0] * x[0] - 2 * x[0] * par[1] + par[1] * par[1]) / (par[2] * par[2]));
}

std::vector<Measurement> load_measurements(const std::string& data_file) {
  std::vector<Measurement> measurements;
  std::ifstream data_file_stream(data_file);

  if (data_file_stream.is_open()) {
    std::string line;
    while (std::getline(data_file_stream, line)) {
      Measurement measurement;
      if (sscanf(line.c_str(), "%d,%lf", &measurement.year, &measurement.temperature) == 2) {
        measurements.push_back(measurement);
      }
    }
    data_file_stream.close();
  } else {
    std::cerr << "Failed to open data file." << std::endl;
  }

  return measurements;
}

void analyze_warmest_and_coldest_days(const std::vector<Measurement>& measurements, const std::string& output_filename) {
  TFile output_file{output_filename.c_str(), "UPDATE"};
  
  // Define histogram properties for warmest and coldest days (modify as needed)
  TH1D* warmest_days_histogram{new TH1D{"warmest_days_histogram", "Warmest Days", 100, 0, 40}};
  TH1D* coldest_days_histogram{new TH1D{"coldest_days_histogram", "Coldest Days", 100, -20, 10}};
  
  for (const auto measurement : measurements) {
    // Calculate the warmest and coldest days and fill the histograms
    // Consider using temperature data for the calculations
  }
  
  auto func {new TF1{"Gaussian", Gaussian, 1, 366, 3}};
  func->SetParameters(5, 200, 50); // Starting values for fitting
  warmest_days_histogram->Fit(func, "Q0R");
  
  std::cout << "Mean for Warmest Days: " << func->GetParameter(1) << std::endl;
  std::cout << "Uncertainty for Mean: " << func->GetParError(1) << std::endl;
  
  TLegend *legend {new TLegend{0.65, 0.75, 0.92, 0.92, "", "NDC"}};
  legend->SetFillStyle(0); // Hollow fill (transparent)
  legend->SetBorderSize(0); // Get rid of the border
  legend->AddEntry(warmest_days_histogram, "Warmest Days", "F"); // Use custom title
  legend->AddEntry(coldest_days_histogram, "Coldest Days", "F"); // Use custom title
  
  TCanvas *canvas {new TCanvas{"canvas", "Analysis", 800, 600}};
  
  warmest_days_histogram->Draw();
  coldest_days_histogram->Draw("SAME"); // Draw on top of the existing plot
  legend->Draw(); // Legends are automatically drawn with "SAME"
  
  canvas->SaveAs("analysis_plot.png");
  canvas->Write();