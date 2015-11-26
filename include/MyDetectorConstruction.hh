#ifndef MyDetectorConstruction_H
#define MyDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"

class G4VPhysicalVolume;
class G4FieldManager;
class G4UniformMagField;
class MyDetectorMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction {

public:

  MyDetectorConstruction();
  ~MyDetectorConstruction();

  G4VPhysicalVolume* Construct();

  void ConstructSDandField();

  void SetMagField( const G4double fieldValue );
  
private:
  
  G4VPhysicalVolume* fWorld;

  G4GDMLParser* parser;

  //01.25.2009 Xin Dong: Threads do not share this member data.
  static G4ThreadLocal G4FieldManager* fieldMgr;
  // Pointer to the field manager.

  //01.25.2009 Xin Dong: Threads do not share this member data.
  static G4ThreadLocal G4UniformMagField* uniformMagField; 
  // Pointer to the uniform magnetic field.
  
  //01.25.2009 Xin Dong: Threads do not share this member data.
  //static G4ThreadLocal MyDetectorMessenger* detectorMessenger;
  MyDetectorMessenger* detectorMessenger;
  // Pointer to the Messenger.

};

#endif

