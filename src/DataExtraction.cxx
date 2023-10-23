// piece of code to extract the csv data into a nice list using the library command



//piece of code to get that list into an output file, ex a TFile so we can use it wihROOT
void persist_measurements(const std::vector<Measurement>& measurements,
                          const std::string& output_filename) {
  // Note: We need .c_str() because TFile expects a C-string (char*) but
  // input_filename is a std::string.

  TFile output_file{output_filename.c_str(), "RECREATE"};
  TTree tree{"MNXB11", "MNXB11"};
  Double_t background;
  Double_t signal;
  Int_t id;
  tree.Branch("background", &background);
  tree.Branch("signal", &signal);
  tree.Branch("id", &id);

  for (const auto measurement : measurements) {
    id = measurement.get_id();
    background = measurement.get_background();
    signal = measurement.get_signal();
    tree.Fill();
  }
  tree.Write();
}