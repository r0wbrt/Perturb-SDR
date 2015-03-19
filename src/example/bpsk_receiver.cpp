#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <locale>
#include <fstream>

#include "perturb.h"
#include "streamTransforms/bpskDecoder.h"

void badInput(std::string message)
{
   std::cerr << message << std::endl;
   std::exit(EXIT_FAILURE);
}



int getInput(std::string paramN, std::string paramValue)
{
        int ret;
        try {
          ret = std::stoi(paramValue);
          if(ret <= 0)
          {
            badInput("Expected integer greater then 0 for -"+paramN);
          }
        } catch(const std::invalid_argument &a) {
          badInput("Expected integer for "+paramN+".");
        } catch(const std::out_of_range& oor) {
          badInput("Integer given to -"+paramN+" is out of range.");
        }

      return ret;
}



double getInputDouble(std::string paramN, std::string paramValue)
{
        double ret;
        try {
          ret = std::stof(paramValue);
        } catch(const std::invalid_argument &a) {
          badInput("Expected number for "+paramN+".");
        } catch(const std::out_of_range& oor) {
          badInput("Number given to -"+paramN+" is out of range.");
        }

   return ret;
}


void message(std::string name)
{
  std::cout << "usage: " << name << " input_file output_file [OPTIONS]..." << std::endl;
  std::cout << "\t-sr <Sample Rate>: Sample rate of the stream. Default is 44000 Samples/s" <<std::endl;
  std::cout << "\t-f <Frequency>: The frequency of the bpsk waveform in rads/s. Default is 0 rads/s." << std::endl;
  std::cout << "\t-sl <Symbol Length>: The length of an symbol in samples. Default is 20 samples." << std::endl;
  std::cout << "\t-c <TRUE|FALSE>: Whether results are real or complex. Default is real." << std::endl;
  std::cout << "\tNote: Real signals will be sent through an Hilbert Transform." << std::endl;
  std::cout << "\t-g <Amp Gain> Sets the gain of the signal." << std::endl;
}


char getData(std::vector<bool> dat)
{
  unsigned char ret = 0x00;
  std::vector<bool> data = dat;
  for(int i = 0; i < 8 && data.empty()!=true; i++)
  {
    bool d = data.back();
    data.pop_back();
    if(d == true)
      ret = (ret << 1 ) | 0x01;
    else
      ret = (ret << 1 ) | 0x00;
  }
  
  return (char) ret;
}


int main(int argc, char **args) {
  int sampleRate = 44000;
  int symbolLength = 20;
  double frequency = 0;
  double gain = 1;
  bool doComplex = false;
  perturb::bpskDecoder<double> radio;
  int statsSamples = 0;
  int symbols = 0;
  
  if(argc < 3)
  {
    message(args[0]);
    std::exit(EXIT_FAILURE);
  }
  
  if(argc > 3)
  {
    int i = 3;
    std::string param;
    std::string value;
    while(i<argc)
    {
      param = args[i++];
      if(i>=argc) 
      {
        message(args[0]);
        std::exit(EXIT_FAILURE);      
      }
      value = args[i++];
      if(param == "-sr")
      {
        sampleRate = getInput("sr", value);
      } else if(param == "-f") {
        frequency = getInputDouble("f", value);
      } else if(param == "-sl") {
        symbolLength = getInput("sl", value);
      } else if(param == "-g") {
        gain = getInputDouble("f", value);
      } else if(param == "-c") {
        std::locale loc;
        if(value == "true")
        {
          doComplex = true;
        } else if(value == "false") {
          doComplex = false;
        } else {
          badInput("-c expectes true or false");
        }
      } else {
          badInput("Unknown Param");
      }
    }
  }

  std::ifstream inputF;
  std::ofstream outputF;
  inputF.open(args[1], std::ifstream::in |  std::ifstream::binary);
  if(inputF.is_open() != true)
  {
    std::string file = args[1];
    badInput("Input File \""+file+"\" not found.");
  }

  outputF.open(args[2], std::ofstream::out | std::ofstream::binary | std::ofstream::ate);
  
  if(outputF.is_open() != true)
  {
    std::string file = args[2];
    badInput("Output File \""+file+"\" not found.");
  }


  frequency = -1.0*(frequency / sampleRate);
  std::complex<double> input;

  /*This loop is bad practice! Leads to reading over the end of the file.*/
  /*Also, this loop should be replaced with an buffering solution that takes 
    into account the delay an hilbert filter will introduce when it comes to 
    regenerating the complex baseband. */
  while(inputF.eof()!=true)
  {
    for(int j = 0; (j < 8) && (inputF.eof()!=true); j++)
    {
      for(int i = 0; (i < symbolLength) && (inputF.eof()!=true); i++)
      { 
        double real, imag;
        inputF.read((char *)&real, sizeof(double));
        statsSamples++;
        if(doComplex == true)
        {
          inputF.read((char *)&imag, sizeof(double));
          statsSamples++;
        } else {
          std::cerr << "Not build with Hilbert Filter, decoding can not proceed." << std::endl;
          std::exit(EXIT_FAILURE);
        }        
        int number = j*symbolLength + i;
        std::complex<double> lo(cos(frequency * (double)number ),sin(frequency * (double)number));
        input = std::complex<double>(real, imag);
        radio.inputSample(input*lo*gain);
        
      }
      radio.doDecode();
      radio.resetDecoder();    
      symbols++;
    }
    char byte = getData(radio.outputData());
    radio.clearData();
    outputF.write(&byte, sizeof(char));
  }

  outputF.close();
  inputF.close();
  std::cout << "Read " << statsSamples << " samples from " << symbols << " symbols" << std::endl;
  std::exit(EXIT_SUCCESS);

}


