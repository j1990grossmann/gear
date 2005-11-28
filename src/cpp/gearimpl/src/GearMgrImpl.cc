
#include "gearimpl/GearMgrImpl.h"

namespace gear{


  GearMgrImpl::GearMgrImpl() :
    _tpcParameters(0) ,
    _ecalBarrelParameters(0) ,
    _ecalEndcapParameters(0) ,
    _hcalBarrelParameters(0) ,
    _hcalEndcapParameters(0) ,
    _pointProperties(0) ,
    _distanceProperties(0) {
  }
  
  const GearParameters & GearMgrImpl::getGearParameters(const std::string & key) const 
    
    throw (UnknownParameterException, std::exception ) {
    
    ParameterMap::const_iterator it = _map.find( key ) ;
    if( it == _map.end() || it->second == 0 )
      throw UnknownParameterException( "No parameters set for : " + key ) ;
    return * it->second ;
    
  }   
  
  const TPCParameters & GearMgrImpl::getTPCParameters() const
    throw (UnknownParameterException, std::exception ) {
    
    if( _tpcParameters == 0 )
      throw UnknownParameterException( "No TPCParameters set ") ;

    return  *_tpcParameters ;

  }

  const CalorimeterParameters & GearMgrImpl::getEcalBarrelParameters() const
    throw (UnknownParameterException, std::exception ) {
    
    if( _ecalBarrelParameters == 0 )
      throw UnknownParameterException( "No EcalBarrelParameters set ") ;

    return  *_ecalBarrelParameters ;

  }
  const CalorimeterParameters & GearMgrImpl::getEcalEndcapParameters() const
    throw (UnknownParameterException, std::exception ) {
    
    if( _ecalEndcapParameters == 0 )
      throw UnknownParameterException( "No EcalEndcapParameters set ") ;

    return  *_ecalEndcapParameters ;

  }
  
  const CalorimeterParameters & GearMgrImpl::getHcalBarrelParameters() const
    throw (UnknownParameterException, std::exception ) {
    
    if( _hcalBarrelParameters == 0 )
      throw UnknownParameterException( "No HcalBarrelParameters set ") ;

    return  *_hcalBarrelParameters ;

  }
  const CalorimeterParameters & GearMgrImpl::getHcalEndcapParameters() const
    throw (UnknownParameterException, std::exception ) {
    
    if( _hcalEndcapParameters == 0 )
      throw UnknownParameterException( "No HcalEndcapParameters set ") ;

    return  *_hcalEndcapParameters ;

  }
  
  const GearPointProperties & GearMgrImpl::getPointProperties() const 
    throw (NotImplementedException, std::exception ) {

    if( _pointProperties == 0 )
      throw UnknownParameterException( "No PointProperties set or implemented ") ;
    
    return  *_pointProperties ;
  }
  
  
  
  const GearDistanceProperties & GearMgrImpl::getDistanceProperties() const 
    throw (NotImplementedException, std::exception ) {

    if( _distanceProperties == 0 )
      throw UnknownParameterException( "No DistanceProperties set or implemented ") ;
    
    return  *_distanceProperties ;

  }

  void GearMgrImpl::setGearParameters( const std::string & key, GearParameters* parameters ) {

    _map[ key ] = parameters ; 
  }
  
  void GearMgrImpl::setTPCParameters( TPCParameters* tpcParameters ) {
    
    _tpcParameters = tpcParameters ;
  }

  void GearMgrImpl::setEcalBarrelParameters( CalorimeterParameters* ecalBarrelParameters ) {
    
    _ecalBarrelParameters = ecalBarrelParameters ;
  }
  void GearMgrImpl::setEcalEndcapParameters( CalorimeterParameters* ecalEndcapParameters ) {
    
    _ecalEndcapParameters = ecalEndcapParameters ;
  }

  void GearMgrImpl::setHcalBarrelParameters( CalorimeterParameters* hcalBarrelParameters ) {
    
    _hcalBarrelParameters = hcalBarrelParameters ;
  }

  void GearMgrImpl::setHcalEndcapParameters( CalorimeterParameters* hcalEndcapParameters ) {

    _hcalEndcapParameters = hcalEndcapParameters ;
  }


  void GearMgrImpl::setPointProperties( GearPointProperties* pointProperties) {
    
    _pointProperties = pointProperties ;
  }

  void GearMgrImpl::setDistanceProperties( GearDistanceProperties* distanceProperties) {
 
   _distanceProperties = distanceProperties ;
  }
  
  const std::vector<std::string>& GearMgrImpl::getGearParameterKeys() const {

    _keys.clear() ;
    _keys.reserve( _map.size() ) ;

    for( ParameterMap::const_iterator it = _map.begin() ; it != _map.end() ; ++it ){
      _keys.push_back( it->first ) ;
    }
    return _keys ;
  }

}