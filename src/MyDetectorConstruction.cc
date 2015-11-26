#include "globals.hh"
#include "G4VisAttributes.hh"
#include "MyDetectorConstruction.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "MyDetectorMessenger.hh"
#include "G4SystemOfUnits.hh"

//01.25.2009 Xin Dong: Threads do not share this member data.
G4ThreadLocal G4FieldManager* MyDetectorConstruction::fieldMgr = 0;

//01.25.2009 Xin Dong: Threads do not share this member data.
G4ThreadLocal G4UniformMagField* MyDetectorConstruction::uniformMagField = 0;

MyDetectorConstruction::MyDetectorConstruction() {

  parser = new G4GDMLParser;
  detectorMessenger = new MyDetectorMessenger( this );
}

MyDetectorConstruction::~MyDetectorConstruction() {
  delete detectorMessenger;
  delete parser;
}

void MyDetectorConstruction::ConstructSDandField() {
  if (! fieldMgr ) {
    fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  }
}

G4VPhysicalVolume* MyDetectorConstruction::Construct() { 

  parser->Read( "cms.gdml" );  

  fWorld = (G4VPhysicalVolume *) parser->GetWorldVolume();

  fWorld->GetLogicalVolume()->SetVisAttributes (G4VisAttributes::Invisible);
  return fWorld;
}


void MyDetectorConstruction::SetMagField( const G4double fieldValue ) {
  if ( uniformMagField ) {
    delete uniformMagField;
  }
  if ( std::abs( fieldValue ) > 0.0 ) {
    // Apply a global uniform magnetic field along the Z axis.
    // Notice that only if the magnetic field is not zero, the Geant4
    // transportion in field gets activated.
    if (! fieldMgr ) {
      fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    }
    uniformMagField = new G4UniformMagField( G4ThreeVector( 0.0, 0.0, fieldValue ) );

    fieldMgr->SetDetectorField( uniformMagField );
    fieldMgr->CreateChordFinder( uniformMagField );

    G4cout << G4endl
           << " *** SETTING MAGNETIC FIELD : fieldValue = " << fieldValue / tesla
           << " Tesla *** " << G4endl 
	   << G4endl;

  } 
}
