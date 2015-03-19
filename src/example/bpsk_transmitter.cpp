#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <locale>
#include <fstream>

#include "perturb.h"
#include "streamTransforms/bpskEncoder.h"



void message(std::string name)
{
  std::cout << "usage: " << name << " input_file output_file [OPTIONS]..." << std::endl;
  std::cout << "\t-sr <Sample Rate>: Sample rate of the stream. Default is 44000 Samples/s" <<std::endl;
  std::cout << "\t-f <Frequency>: The frequency of the bpsk waveform in rads/s. Default is 0rads/s." << std::endl;
  std::cout << "\t-sl <Symbol Length>: The length of an symbol in samples. Default is 20 samples." << std::endl;
  std::cout << "\t-c <TRUE|FALSE>: Whether results should be real or complex output. Default is real" <<std::endl;
  std::cout << "\t-g <Amp Gain> Sets the gain of the signal. 1.0 is default." << std::endl;
}

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

int main(int argc, char ** args)
{

  int sampleRate = 44000;
  int symbolLength = 20;
  double frequency = 0;
  bool doComplex = false;
  perturb::bpskEncoder<double> radio;
  radio.setAmplitude(.8);
  int statsSamples = 0;
  int symbols = 0;
  double gain = 1.0;

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


  frequency = frequency / (double) sampleRate;
  char byte;
  while(inputF.get(byte))
  {
    for(int i = 0; i < 8; i++)
    {
      radio.inputByte((byte >> i), false);
      symbols++;
      for(int j = 0; j < symbolLength; j++)
      {
        double w; 
        std::complex<double> out = radio.doEncode();
        int number = i*symbolLength + j;
        std::complex<double> lo(cos(frequency * (double)number ),sin(frequency * (double)number));
        out = gain*out*lo;
         w = out.real();
        outputF.write((char *)&w, sizeof(double));
        statsSamples++;
        if(doComplex == true)
        {
          w = out.imag();
          outputF.write((char *)&w, sizeof(double));
          statsSamples++;
        }
      }
    }
  }

  outputF.close();
  inputF.close();
  std::cout << "Wrote " << statsSamples << " samples from " << symbols << " symbols" << std::endl;
  std::exit(EXIT_SUCCESS);

}
