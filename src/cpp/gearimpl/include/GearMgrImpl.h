#ifndef GEAR_GearMgrImpl_H
#define GEAR_GearMgrImpl_H 1

#include <string>

#include "gear/GearMgr.h"
#include "gear/GearParameters.h"
#include "gear/TPCParameters.h"


namespace gear {
    
    
  /** Manager class that returns the Gear classes for the  relevant subdetectors.
   * 
   *  Based on ideas discussed at the 2004 Argonne Simulation Workshop as summarized by T.Behnke.
   *
   * @author F. Gaede, DESY
   * @version $Id: GearMgrImpl.h,v 1.1.1.1 2005-09-13 14:41:03 gaede Exp $
   */
  class GearMgrImpl : public GearMgr {
	
    typedef std::map< std::string ,  GearParameters* > ParameterMap ;

  public: 

    // C'tor 
    GearMgrImpl() ;
    
    /// Destructor.
    virtual ~GearMgrImpl() { /* nop */; }
	
    /** Get named parameters for key. This can be used to describe a subdetector that is not 
     *  yet forseen in the Gear API.
     * 
     *  @throws UnknownParameterException
     */
    virtual const GearParameters & getGearParameters(const std::string & key) const 
      throw (UnknownParameterException, std::exception )  ;

    /** Get the TPCParameters.
     */
    virtual const TPCParameters & getTPCParameters() const
      throw (UnknownParameterException, std::exception ) ;
    
     /** Get the Ecal barrel parameters.
     *
     *  @throws UnknownParameterException
     */
    virtual const CalorimeterParameters & getEcalBarrelParameters() const 
	throw (UnknownParameterException, std::exception ) ;

    /** Get the Ecal endcap parameters.
     *
     *  @throws UnknownParameterException
     */
    virtual const CalorimeterParameters & getEcalEndcapParameters() const 
	throw (UnknownParameterException, std::exception )  ;

    /** Get the Hcal barrel parameters.
     *
     *  @throws UnknownParameterException
     */
    virtual const CalorimeterParameters & getHcalBarrelParameters() const 
	throw (UnknownParameterException, std::exception )  ;

    /** Get the Hcal endcap parameters.
     *
     *  @throws UnknownParameterException
     */
    virtual const CalorimeterParameters & getHcalEndcapParameters() const 
	throw (UnknownParameterException, std::exception )  ;

   /** Get the point properties object.
     * 
     *  @throws NotImplementedException
     */
    virtual const GearPointProperties & getPointProperties() const 
      throw (NotImplementedException, std::exception ) ;
    
    
    /** Get the distance properties object.
     * 
     *  @throws NotImplementedException
     */
    virtual const GearDistanceProperties & getDistanceProperties() const 
      throw (NotImplementedException, std::exception ) ;


    /** Keys of all GearParameters. 
     */ 
    virtual const std::vector<std::string>  & getGearParameterKeys() const ;


    /** Set the GearParameters for the given key - overwrites any 
     *  existing entries.
     */
    virtual void setGearParameters( const std::string & key, GearParameters* parameters ) ;
    
    /** Set the TPCParameters.
     */
    virtual void setTPCParameters( TPCParameters* tpcParameters ) ;


    /** Set the EcalBarrelParameters.
     */
    virtual void setEcalBarrelParameters( CalorimeterParameters* ecalBarrelParameters ) ;

    /** Set the EcalEndcapParameters.
     */
    virtual void setEcalEndcapParameters( CalorimeterParameters* ecalEndcapParameters ) ;
    
    /** Set the HcalBarrelParameters.
     */
    virtual void setHcalBarrelParameters( CalorimeterParameters* hcalBarrelParameters ) ;

    /** Set the HcalEndcapParameters.
     */
    virtual void setHcalEndcapParameters( CalorimeterParameters* hcalEndcapParameters ) ;
    

    /** Set the point properties object 
     */
    virtual void  setPointProperties( GearPointProperties* pointProperties) ; 

    /** Set the distance properties object 
     */
    virtual void  setDistanceProperties( GearDistanceProperties* distanceProperties) ; 
    
    
    
    
  protected:
    
    ParameterMap _map ;
    TPCParameters* _tpcParameters ;
    CalorimeterParameters* _ecalBarrelParameters ;
    CalorimeterParameters* _ecalEndcapParameters ;
    CalorimeterParameters* _hcalBarrelParameters ;
    CalorimeterParameters* _hcalEndcapParameters ;
    GearPointProperties*  _pointProperties ;
    GearDistanceProperties*  _distanceProperties ;

    mutable StringVec _keys ;

  }; // class
} // namespace gear
#endif /* ifndef GEAR_GEARMGR_H */