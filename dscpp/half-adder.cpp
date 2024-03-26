#include <iostream>
#include <string>
#include <vector>
using namespace std;

// creates a class with a logic gate that returns the label, and boolean value
class LogicGate {
 public:
  explicit LogicGate(string n) { label = n; }
  string getLabel() { return label; }
  bool getOutput() {
    output = performGateLogic();
    return output;
  }
  virtual bool performGateLogic() {
    cout << "ERROR! performGateLogic BASE" << endl;
    return false;
  }

  virtual void setNextPin(bool source) {
    cout << "ERROR! setNextPin BASE" << endl;
  }

 protected:  // Changed literally just because of gates that are combination of
           // two gates
  string label;
  bool output;
};

// class that allows for the gates to have two inputs

class BinaryGate : public LogicGate {
 public:
  explicit BinaryGate(string n) : LogicGate(n) {
    pinATaken = false;
    pinBTaken = false;
  }
  bool getPinA() {
    if (pinATaken == false) {
      cout << "Enter Pin A input for gate " << getLabel() << ": ";
      cin >> pinA;
      pinATaken = true;
    }
    return pinA;
  }
  bool getPinB() {
    if (pinBTaken == false) {
      cout << "Enter Pin B input for gate " << getLabel() << ": ";
      cin >> pinB;
      pinBTaken = true;
    }
    return pinB;
  }
  virtual void setNextPin(bool source) {
    if (pinATaken == false) {
      pinA = source;
      this->pinATaken = true;
    } else if (pinBTaken == false) {
      pinB = source;
      this->pinBTaken = true;
    }
  }

 protected:
  bool pinA, pinATaken, pinB, pinBTaken;
};

// allows for the creation of a logic gate with  one input
class UnaryGate : public LogicGate {
 public:
  explicit UnaryGate(string n) : LogicGate(n) { pinTaken = false; }
  bool getPin() {
    if (pinTaken == false) {
      cout << "Enter Pin input for gate " << getLabel() << ": ";
      cin >> pin;
      pinTaken = true;
    }
    return pin;
  }
  virtual void setNextPin(bool source) {
    if (pinTaken == false) {
      pin = source;
      pinTaken = true;
    } else {
      return;
    }
  }

 private:
  bool pin, pinTaken;
};

// Class that sets up the logic for an "and" gate
class AndGate : public BinaryGate {
 public:
  explicit AndGate(string n) : BinaryGate(n) {}

  virtual bool performGateLogic() {
    bool a = getPinA();
    bool b = getPinB();
    if (a == 1 && b == 1) {
      return true;
    } else {
      return false;
    }
  }
};

// class that sets up the logic for an "or" gate
class OrGate : public BinaryGate {
 public:
  explicit OrGate(string n) : BinaryGate(n) {}

  virtual bool performGateLogic() {
    bool a = getPinA();
    bool b = getPinB();
    if (a == 1 || b == 1) {
      return true;
    } else {
      return false;
    }
  }
};

// class that sets up the logic for a "not" gate
class NotGate : public UnaryGate {
 public:
  explicit NotGate(string n) : UnaryGate(n) {}

  virtual bool performGateLogic() {
    if (getPin()) {
      return false;
    } else {
      return true;
    }
  }
};

// class that sets up logic for the connection of one gate to another
class Connector {
 public:
  Connector(LogicGate *fgate, LogicGate *tgate) {
    fromgate = fgate;
    togate = tgate;
    tgate->setNextPin(fromgate->getOutput());
  }
  LogicGate *getFrom() { return fromgate; }
  LogicGate *getTo() { return togate; }

 private:
  LogicGate *fromgate, *togate;
};

class NandGate : public BinaryGate {
 public:
  explicit NandGate(string n) : BinaryGate(n) {
    // Need to create new objects in the heap, otherwise objects are destructed
    // when initialisation goes out of scope.
    gand = new AndGate("gand_inside_gnand");
    gnot = new NotGate("gnot_indide_gnand");
  }

  ~NandGate() {
    delete gand;
    delete gnot;
  }

  virtual bool performGateLogic() {
    gand->setNextPin(getPinA());
    gand->setNextPin(getPinB());
    Connector _c(gand, gnot);
    // Connector gets destroyed once out of scope
    // but command to set pin of gate has already run
    return gnot->getOutput();
  }

 private:
  AndGate *gand;
  NotGate *gnot;
};

class XorGate : public BinaryGate {
 public:
  explicit XorGate(string n) : BinaryGate(n) {
    gnand0 = new NandGate("0");
    gnand1 = new NandGate("1");
    gnand2 = new NandGate("2");
    gnand3 = new NandGate("3");
  }
  ~XorGate() {
    delete gnand0;
    delete gnand1;
    delete gnand2;
    delete gnand3;
  }

 private:
  NandGate *gnand0;
  NandGate *gnand1;
  NandGate *gnand2;
  NandGate *gnand3;

  virtual bool performGateLogic() {
    // Check wikipedia page for the design
    gnand0->setNextPin(getPinA());
    gnand0->setNextPin(getPinB());
    gnand1->setNextPin(getPinA());
    Connector c1(gnand0, gnand1);
    Connector c2(gnand0, gnand2);
    gnand2->setNextPin(getPinB());
    Connector c3(gnand1, gnand3);
    Connector c4(gnand2, gnand3);
    return gnand3->getOutput();
  }
};

class FullOneBitAdder : public BinaryGate {
 private:
  bool Cin;
  bool CinTaken;
  bool Cout;
  bool CoutCalculated;

  XorGate *gxor1;
  XorGate *gxor2;
  AndGate *gand1;
  AndGate *gand2;
  OrGate *gor1;

 public:
  explicit FullOneBitAdder(string n) : BinaryGate(n) {
    gxor1 = new XorGate("xor1");
    gxor2 = new XorGate("xor2");
    gand1 = new AndGate("and1");
    gand2 = new AndGate("and2");
    gor1 = new OrGate("or1");

    CinTaken = false;
    CoutCalculated = false;
  }

  ~FullOneBitAdder() {
    delete gxor1;
    delete gxor2;
    delete gand1;
    delete gand2;
    delete gor1;
  }

  void setInputs(const bool& pinA, const bool& pinB, const bool& Cin) {
    setNextPin(pinA);
    setNextPin(pinB);
    setCin(Cin);
    cout << "pinA: " << getPinA() << endl;
    cout << "pinB: " << getPinB() << endl;
    cout << "Cin: " << getCin() << endl;
  }

  void setCin(bool source) {
    if (CinTaken == false) {
      Cin = source;
      CinTaken = true;
    }
  }

  bool getCin() {
    if (CinTaken == false) {
      cout << "Enter Cin input for gate " << getLabel() << ": ";
      cin >> Cin;
      CinTaken = true;
    }
    return Cin;
  }

  bool getCout() {
    if (CoutCalculated == false) {
      performGateLogic();  // Need this for now, take out later
      Cout = calculateCout();
      CoutCalculated = true;
    }
    return Cout;
  }

  virtual bool performGateLogic() {
    gxor1->setNextPin(getPinA());
    gxor1->setNextPin(getPinB());

    Connector c1(gxor1, gxor2);
    gxor2->setNextPin(getCin());

    return gxor2->getOutput();
  }

  bool calculateCout() {
    gand2->setNextPin(getPinA());
    gand2->setNextPin(getPinB());

    Connector c2(gxor1, gand1);
    gand1->setNextPin(getCin());

    Connector c3(gand1, gor1);
    Connector c4(gand2, gor1);
    return gor1->getOutput();
  }
};

// class that sets up logic for the connection of one gate to another
class AdderConnector {
 public:
  AdderConnector(FullOneBitAdder* fadder, FullOneBitAdder* tadder) {
    fromadder = fadder;
    toadder = tadder;
    tadder->setCin(fromadder->getCout());
  }
  FullOneBitAdder *getFrom() { return fromadder; }
  FullOneBitAdder *getTo() { return toadder; }

 private:
  FullOneBitAdder *fromadder, *toadder;
};

class FullBitAdder
{
  private:
    int nbits;
    FullOneBitAdder** adderArray;
    AdderConnector** connectorsArray;
    bool* inputsA;
    bool* inputsB;
    bool* result;

    void setAdderChain () {

      // Initialise adders
      adderArray = new FullOneBitAdder* [nbits];
      for (int i=0; i<nbits; i++) {
        adderArray[i] = new FullOneBitAdder(std::to_string(i));
      }
    }

    void setChainInputs () {
      for (int i=0; i<nbits; i++) {
        adderArray[i]->setNextPin(inputsA[nbits-1-i]);
        adderArray[i]->setNextPin(inputsB[nbits-1-i]);
      }
      // Set the first carry to zero
      adderArray[0]->setCin(0);
    }

    void setConnections () {

      // Make connections
      connectorsArray = new AdderConnector* [nbits-1];
      for (int i=1; i<nbits; i++) {
        connectorsArray[i] = new AdderConnector(adderArray[i-1], adderArray[i]);
      } 
    }

    void printData () {
      for (int i=0; i<nbits; i++) {
        FullOneBitAdder* adder = adderArray[i];
        cout << "\nLabel: " << adder->getLabel() 
          << "\nPinA: " << adder->getPinA()
          << "\nPinB: " << adder->getPinB()
          << "\nS: " << adder->getOutput()
          << "\nCin: " << adder->getCin()
          << "\nCout: " << adder->getCout();
      }
    }

  public:
   FullBitAdder(int n, bool* inA, bool* inB) : nbits {n}, inputsA {inA}, inputsB {inB} {
     setAdderChain();
     setChainInputs();
     setConnections();
     printData();
   }

   ~FullBitAdder() {
     delete[] adderArray;
     delete[] connectorsArray;
     delete[] result;
   }

   bool* getBitOutput() {
     // Need to print in reverse
     result = new bool [nbits];
     for (int i=0; i<nbits; i++) {
       result[nbits-1-i] = (adderArray[i]->getOutput());
     }
     return result;
   }
};

void printBits (const bool* result_ptr, int nbits) { 
  for (int i=0; i<nbits; i++) {cout << result_ptr[i] << " ";}
}

int main() {
  // Okay but the fact that I was able to figure out that I needed
  // to put that gates in the heap was so slayful of me
  //
  // FUCK ME I SPENT SO MUCH TIME ON A STUPID ERROR DUE TO BAD INITIALISAITON

  std::vector<std::vector<bool>> input_combinations ({{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, 
      {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}});

  for (auto in : input_combinations) {
    FullOneBitAdder adder(" ADDER ");           // Initialiser because clearing the innitial inputs does not clear the whole circuit
    adder.setInputs(in[0], in[1], in[2]);
    cout << " S: " << adder.getOutput() << "Cout: " << adder.getCout() << endl;
  }

  bool inputA[] {0, 0, 1, 0};    // Use of cpp arrays SLAYYYY
  bool inputB[] {0, 0, 1, 0};

  FullBitAdder four_bit_adder (4, inputA, inputB);
  bool* result = four_bit_adder.getBitOutput();

  cout<< "4 bit output: "; 
  printBits(result, 4);

  // Results seem correct to be honest 
  return 0;
}
